// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "avc_decoder_conf_record.h"

#include <fstream>

#include "utils/stream_utils.h"


namespace media {
namespace avc {

    AVCDCRParser::AVCDCRParser() {}

    bool AVCDCRParser::parse(std::istream& s, AVCDecoderConfRecord* record) {
        READ_STREAM(record->conf_ver, 1);
        READ_STREAM(record->avc_profile_ind, 1);
        READ_STREAM(record->profile_compat, 1);
        READ_STREAM(record->avc_level_ind, 1);

        READ_STREAM(record->length_size_m1, 1);
        // bit(6) reserved
        record->length_size_m1 &= 0x3;

        READ_STREAM(record->sps_num, 1);
        // bit(3) reserved
        record->sps_num &= 0x1F;

        for (uint8_t i = 0; i < record->sps_num; ++i) {
            NALUInfo info;
            READ_STREAM_BE(info.length, 2);
            info.nalu.reset(new uint8_t[info.length], std::default_delete<uint8_t[]>());
            READ_STREAM(info.nalu.get()[0], info.length);
            record->sps_nalus.push_back(std::move(info));
        }

        READ_STREAM(record->pps_num, 1);

        for (uint8_t i = 0; i < record->pps_num; ++i) {
            NALUInfo info;
            READ_STREAM_BE(info.length, 2);
            info.nalu.reset(new uint8_t[info.length], std::default_delete<uint8_t[]>());
            READ_STREAM(info.nalu.get()[0], info.length);
            record->pps_nalus.push_back(std::move(info));
        }

        {
            // TODO:
        }
        return true;
    }

}
}
