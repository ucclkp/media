// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "sdtp_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool IndepDispSampleBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        sample_info.reset(new SampleInfo[sample_count_], std::default_delete<SampleInfo[]>());
        for (uint32_t i = 0; i < sample_count_; ++i) {
            uint8_t buf;
            READ_STREAM(buf, 1);
            sample_info.get()[i].is_leading = buf >> 6;
            sample_info.get()[i].sample_depends_on = (buf >> 4) & 0x3;
            sample_info.get()[i].sample_is_depended_on = (buf >> 2) & 0x3;
            sample_info.get()[i].sample_has_redundancy = buf & 0x3;
        }
        return true;
    }

}
}
