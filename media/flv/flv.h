// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_FLV_FLV_H_
#define MEDIA_FLV_FLV_H_

#include <string>

#include "media/avc/avc_decoder_conf_record.h"


namespace media {
namespace flv {

    enum TagType {
        TAG_AUDIO = 8,
        TAG_VIDEO = 9,
        TAG_SCRIPT = 18
    };

    enum SoundFormat {
        SF_LINEAR_PCM_PE = 0,
        SF_ADPCM = 1,
        SF_MP3 = 2,
        SF_LINEAR_PCM_LE = 3,
        SF_NELLYMOSER_16K_MONO = 4,
        SF_NELLYMOSER_8K_MONO = 5,
        SF_NELLYMOSER = 6,
        SF_G711_A_LAW_PCM = 7,
        SF_G711_MU_LAW_PCM = 8,
        SF_RESERVED = 9,
        SF_AAC = 10,
        SF_SPEEX = 11,
        SF_MP3_8K = 14,
        SF_DEVICE_SPECIFIC = 15,
    };

    enum VideoCodecID {
        VCID_SORENSON_H_263 = 2,
        VCID_SCREEN_VIDEO = 3,
        VCID_ON2_VP6 = 4,
        VCID_ON2_VP6_WITH_A = 5,
        VCID_SCREEN_VIDEO_V2 = 6,
        VCID_AVC = 7,
    };

    enum VideoFrameType {
        VFT_KEY_FRAME = 1,
        VFT_INTER_FRAME = 2,
        VFT_DISPOSABLE_INTER_FRAME = 3,
        VFT_GENERATED_KEY_FRAME = 4,
        VFT_INFO_CMD_FRAME = 5,
    };

    enum AVCPacketType {
        AVCPT_SEQ_HEADER = 0,
        AVCPT_NALUs = 1,
        AVCPT_END_SEQ = 2,
    };


    struct FLVHeader {
        uint8_t version;
        bool audio_tag_present;
        bool video_tag_present;
    };

    struct AudioTagHeader {
        uint8_t sound_format;
        uint8_t sound_rate;
        uint8_t sound_size;
        uint8_t sound_type;
        // if sound_format == 10
        uint8_t aac_packet_type;
    };

    struct VideoTagHeader {
        uint8_t frame_type;
        uint8_t codec_id;
        // if codec_id == 7
        uint8_t avc_packet_type;
        // if codec_id == 7
        int32_t composition_time;
    };

    struct VideoTagBody {
        // if frame_type == 5
        uint8_t data;
        // else if codec_id == 2
        // TODO: H263VIDEOPACKET
        // else if codec_id == 3
        // TODO: SCREENVIDEOPACKET
        // else if codec_id == 4
        // TODO: VP6FLVVIDEOPACKET
        // else if codec_id == 5
        // TODO: VP6FLVALPHAVIDEOPACKET
        // else if codec_id == 6
        // TODO: SCREENV2VIDEOPACKET
        // else if codec_id == 7
        struct AVCVIDEOPACKET {
            // if avc_packet_type == 0
            avc::AVCDecoderConfRecord record;
            // if avc_packet_type == 1
            size_t length;
            std::shared_ptr<uint8_t> nalus;
        } avcp;
    };

    struct AudioTagBody {
        // if sound_format == 10
        struct AACAUDIODATA {
            // if aac_packet_type == 0
            // TODO: struct AudioSpecificConfig (ISO 14496-3)
            // else if aac_packet_type == 1
            size_t length;
            std::shared_ptr<uint8_t> opaque_data;
        }aac_data;
        // else
        size_t length;
        std::shared_ptr<uint8_t> opaque_data;
    };

    struct SCRIPTDATASTRING {
        uint16_t length;
        uint8_t* data;
    };

    struct SCRIPTDATAOBJECTPROPERTY;

    struct SCRIPTDATAVALUE {
        uint8_t type;
        union {
            // if type == 0
            double d_val;
            // if type == 1
            uint8_t u8_val;
            // if type == 2
            SCRIPTDATASTRING sds_val;
            // if type == 3
            struct SCRIPTDATAOBJECT {
                SCRIPTDATAOBJECTPROPERTY* variables;
                // terminator: OBJECTEND: 0, 0, 9
            }sdo_val;
            // if type == 7
            uint16_t u16_val;
            // if type == 8
            struct SCRIPTDATAECMAARRAY {
                uint32_t length;
                SCRIPTDATAOBJECTPROPERTY* variables;
                // terminator: OBJECTEND: 0, 0, 9
            }sdea_val;
            // if type == 10
            struct SCRIPTDATASTRICTARRAY {
                uint32_t length;
                SCRIPTDATAVALUE* value;
            }sdsa_val;
            // if type == 11
            struct SCRIPTDATADATE {
                double date_time;
                int16_t local_data_time_off;
            }sdd_val;
            // if type == 12
            struct SCRIPTDATALONGSTRING {
                uint32_t length;
                uint8_t* data;
            }sdls_val;
        }u;
    };

    struct SCRIPTDATAOBJECTPROPERTY {
        SCRIPTDATASTRING name;
        SCRIPTDATAVALUE data;
    };

    struct ScriptTagBody {
        SCRIPTDATAVALUE name;
        SCRIPTDATAVALUE value;
    };

    struct EncryptionTagHeader {
        uint8_t filter_num;
        std::string filter_name;
        uint32_t length;
    };

    struct FilterParams {
        // if filter_name == 'Encryption'
        uint8_t IV[16];
        // if filter_name == 'SE'
        struct SelectiveEncryptionFilterParams {
            uint8_t encrypted_au;
            // if encrypted_au == 1
            uint8_t IV[16];
        }sefp;
    };

    struct AUDIODATA {
        // if encrypted
        struct EncryptedBody {} e_body;
        // else
        AudioTagBody a_body;
    };

    struct VIDEODATA {
        // if encrypted
        struct EncryptedBody {} e_body;
        // else
        VideoTagBody v_body;
    };

    struct SCRIPTDATA {
        // if encrypted
        struct EncryptedBody {} e_body;
        // else
        ScriptTagBody s_body;
    };

    struct FLVTag {
        uint8_t filter;
        uint8_t tag_type;
        uint32_t data_size;
        uint32_t timestamp;
        uint32_t stream_id;
        // if tag_type == 8
        AudioTagHeader audio_tag_header;
        // if tag_type == 9
        VideoTagHeader video_tag_header;
        // if filter == 1
        EncryptionTagHeader encrypt_tag_header;
        // if filter == 1
        FilterParams filter_params;
        // if tag_type == 8
        AUDIODATA audio_data;
        // if tag_type == 9
        VIDEODATA video_data;
        // if tag_type == 18
        SCRIPTDATA script_data;
    };

}
}

#endif  // MEDIA_FLV_FLV_H_