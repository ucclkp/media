// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_AVC_AVC_DECODER_CONF_RECORD_H_
#define MEDIA_AVC_AVC_DECODER_CONF_RECORD_H_

#include <cstdint>
#include <memory>
#include <vector>


namespace media {
namespace avc {

    struct NALUInfo {
        uint16_t length;
        std::shared_ptr<uint8_t> nalu;
    };

    struct AVCDecoderConfRecord {
        uint8_t conf_ver;
        uint8_t avc_profile_ind;
        uint8_t profile_compat;
        uint8_t avc_level_ind;
        uint8_t length_size_m1;

        uint8_t sps_num;
        std::vector<NALUInfo> sps_nalus;

        uint8_t pps_num;
        std::vector<NALUInfo> pps_nalus;

        // if profile_idc == 100/110/122/144
        uint8_t chroma_format;
        uint8_t bit_depth_luma_minus8;
        uint8_t bit_depth_chroma_minus8;

        uint8_t sps_ext_num;
        std::vector<NALUInfo> sps_ext_nalus;
    };


    class AVCDCRParser {
    public:
        AVCDCRParser();

        bool parse(std::istream& s, AVCDecoderConfRecord* record);
    };

}
}

#endif  // MEDIA_AVC_AVC_DECODER_CONF_RECORD_H_