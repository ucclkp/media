// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "flv_parser.h"

#include <cassert>
#include <filesystem>

#include "utils/stream_utils.h"


namespace media {
namespace flv {

    FLVParser::FLVParser() {}

    bool FLVParser::parse(std::istream& s, FLVHeader* header, std::vector<FLVTag>* tags) {
        FLVHeader _header;
        if (!parseHeader(s, &_header)) {
            return false;
        }

        uint32_t count = 0;
        for (;;) {
            uint32_t prev_tag_size;
            READ_STREAM_BE(prev_tag_size, 4);

            auto peek_ch = s.peek();
            if (!s) { return false; }
            if (peek_ch == EOF) { break; }

            FLVTag tag;
            if (!parseTag(s, &tag)) {
                return false;
            }
            ++count;
            tags->push_back(std::move(tag));
        }

        *header = std::move(_header);
        return true;
    }

    bool FLVParser::parseHeader(std::istream& s, FLVHeader* header) {
        // Signature
        uint8_t sig[3];
        READ_STREAM(sig[0], 3);
        if (sig[0] != 0x46 || sig[1] != 0x4C || sig[2] != 0x56) {
            return false;
        }

        // Version
        READ_STREAM(header->version, 1);

        uint8_t flags;
        READ_STREAM(flags, 1);

        // TypeFlagsAudio
        header->audio_tag_present = ((flags >> 2) & 1) == 1;

        // TypeFlagsVideo
        header->video_tag_present = (flags & 1) == 1;

        uint32_t length;
        READ_STREAM_BE(length, 4);

        return true;
    }

    bool FLVParser::parseTag(std::istream& s, FLVTag* tag) {
        uint8_t flags;
        READ_STREAM(flags, 1);

        tag->filter = (flags >> 5) & 1;
        tag->tag_type = flags & 0x1F;
        tag->data_size = 0;
        READ_STREAM_MLBE(tag->data_size, 3);

        uint8_t timestamp_high;
        uint32_t timestamp_low = 0;
        READ_STREAM_MLBE(timestamp_low, 3);
        READ_STREAM(timestamp_high, 1);
        tag->timestamp = (uint32_t(timestamp_high) << 24) | timestamp_low;

        tag->stream_id = 0;
        READ_STREAM_MLBE(tag->stream_id, 3);

        int64_t cur = s.tellg();
        int64_t end = cur + tag->data_size;

        if (tag->tag_type == TAG_AUDIO) {
            AudioTagHeader header;
            if (!parseAudioTagHeader(s, &header)) {
                return false;
            }
            tag->audio_tag_header = header;
        } else if (tag->tag_type == TAG_VIDEO) {
            VideoTagHeader header;
            if (!parseVideoTagHeader(s, &header)) {
                return false;
            }
            tag->video_tag_header = header;
        }

        if (tag->filter == 1) {
            EncryptionTagHeader header;
            FilterParams params;
            if (!parseEncryptionTagHeader(s, &header, &params)) {
                return false;
            }
            tag->encrypt_tag_header = header;
            tag->filter_params = params;
        }

        if (tag->tag_type == TAG_AUDIO) {
            AUDIODATA data;
            if (!parseAudioData(s, *tag, end, &data)) {
                return false;
            }
            tag->audio_data = data;
        } else if (tag->tag_type == TAG_VIDEO) {
            VIDEODATA data;
            if (!parseVideoData(s, *tag, end, &data)) {
                return false;
            }
            tag->video_data = data;
        } else if (tag->tag_type == TAG_SCRIPT) {
            SCRIPTDATA data;
            if (!parseScriptData(s, *tag, end, &data)) {
                return false;
            }
            tag->script_data = data;
        }

        return true;
    }

    bool FLVParser::parseAudioTagHeader(std::istream& s, AudioTagHeader* header) {
        uint8_t flags;
        READ_STREAM(flags, 1);

        header->sound_format = flags >> 4;
        header->sound_rate = (flags >> 2) & 0x3;
        header->sound_size = (flags >> 1) & 0x1;
        header->sound_type = flags & 0x1;

        if (header->sound_format == SF_AAC) {
            READ_STREAM(header->aac_packet_type, 1);
        }
        return true;
    }

    bool FLVParser::parseVideoTagHeader(std::istream& s, VideoTagHeader* header) {
        uint8_t flags;
        READ_STREAM(flags, 1);

        header->frame_type = flags >> 4;
        header->codec_id = flags & 0xF;

        if (header->codec_id == VCID_AVC) {
            READ_STREAM(header->avc_packet_type, 1);
            header->composition_time = 0;
            READ_STREAM_MLBE(header->composition_time, 3);
        }
        return true;
    }

    bool FLVParser::parseEncryptionTagHeader(std::istream& s, EncryptionTagHeader* header, FilterParams* params) {
        // header
        READ_STREAM(header->filter_num, 1);
        for (;;) {
            uint8_t buf;
            READ_STREAM(buf, 1);
            if (buf == 0) {
                break;
            }
            header->filter_name.push_back(buf);
        }
        READ_STREAM_MLBE(header->length, 3);

        // params
        if (header->filter_name == "Encryption") {
            READ_STREAM(params->IV[0], 16);
        } else if (header->filter_name == "SE") {
            uint8_t flags;
            READ_STREAM(flags, 1);
            params->sefp.encrypted_au = flags >> 7;
            if (params->sefp.encrypted_au == 1) {
                READ_STREAM(params->sefp.IV[0], 16);
            }
        }
        return true;
    }

    bool FLVParser::parseAudioData(std::istream& s, const FLVTag& tag, int64_t end, AUDIODATA* data) {
        if (tag.filter == 1) {
            s.seekg(end, std::ios::beg);
        } else {
            AudioTagBody body;
            if (tag.audio_tag_header.sound_format == SF_AAC) {
                if (tag.audio_tag_header.aac_packet_type == 0) {
                    // TODO: ISO 14496-3 AudioSpecificConfig
                    s.seekg(end, std::ios::beg);
                } else if (tag.audio_tag_header.aac_packet_type == 1) {
                    // raw AAC frame data
                    size_t length = size_t(end - s.tellg());
                    body.aac_data.opaque_data.reset(new uint8_t[length], std::default_delete<uint8_t[]>());
                    READ_STREAM(body.aac_data.opaque_data.get()[0], length);
                    body.aac_data.length = length;
                }
            } else {
                // varies by format
                size_t length = size_t(end - s.tellg());
                body.opaque_data.reset(new uint8_t[length], std::default_delete<uint8_t[]>());
                READ_STREAM(body.opaque_data.get()[0], length);
                body.length = length;
            }
        }

        return true;
    }

    bool FLVParser::parseVideoData(std::istream& s, const FLVTag& tag, int64_t end, VIDEODATA* data) {
        if (tag.filter == 1) {
            s.seekg(end, std::ios::beg);
        } else {
            VideoTagBody body;
            if (tag.video_tag_header.frame_type == VFT_INFO_CMD_FRAME) {
                READ_STREAM(body.data, 1);
            } else {
                switch (tag.video_tag_header.codec_id) {
                case VCID_SORENSON_H_263: break;
                case VCID_SCREEN_VIDEO: break;
                case VCID_ON2_VP6: break;
                case VCID_ON2_VP6_WITH_A: break;
                case VCID_SCREEN_VIDEO_V2: break;
                case VCID_AVC:
                {
                    if (tag.video_tag_header.avc_packet_type == AVCPT_SEQ_HEADER) {
                        avc::AVCDCRParser dcr_parser;
                        if (!dcr_parser.parse(s, &body.avcp.record)) {
                            return false;
                        }
                        auto adf = end - s.tellg();
                        assert(adf >= 0);
                    } else if (tag.video_tag_header.avc_packet_type == AVCPT_NALUs) {
                        size_t length = size_t(end - s.tellg());
                        body.avcp.nalus.reset(new uint8_t[length], std::default_delete<uint8_t[]>());
                        READ_STREAM(body.avcp.nalus.get()[0], length);
                        body.avcp.length = length;

                        assert(s.tellg() == end);
                    }
                    break;
                }
                default:break;
                }
                s.seekg(end, std::ios::beg);
            }

            data->v_body = std::move(body);
        }
        return true;
    }

    bool FLVParser::parseScriptData(std::istream& s, const FLVTag& tag, int64_t end, SCRIPTDATA* data) {
        if (tag.filter == 1) {

        } else {
        }

        s.seekg(end, std::ios::beg);
        return true;
    }

}
}
