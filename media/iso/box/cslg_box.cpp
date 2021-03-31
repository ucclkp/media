// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "cslg_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool ComposToDecodeBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        if (version == 0) {
            int32_t c_to_dts_shift;
            int32_t ld_to_dd;
            int32_t gd_to_dd;
            int32_t cst, cet;

            READ_STREAM_BE(c_to_dts_shift, 4);
            READ_STREAM_BE(ld_to_dd, 4);
            READ_STREAM_BE(gd_to_dd, 4);
            READ_STREAM_BE(cst, 4);
            READ_STREAM_BE(cet, 4);

            compos_to_dts_shift = c_to_dts_shift;
            least_decode_to_display_delta = ld_to_dd;
            greatest_decode_to_display_delta = gd_to_dd;
            compos_start_time = cst;
            compos_end_time = cet;
        } else {
            READ_STREAM_BE(compos_to_dts_shift, 8);
            READ_STREAM_BE(least_decode_to_display_delta, 8);
            READ_STREAM_BE(greatest_decode_to_display_delta, 8);
            READ_STREAM_BE(compos_start_time, 8);
            READ_STREAM_BE(compos_end_time, 8);
        }

        return true;
    }

}
}
