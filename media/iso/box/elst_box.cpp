// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "elst_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool EditListBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(entry_count, 4);

        info.reset(new Info[entry_count], std::default_delete<Info[]>());
        for (uint32_t i = 0; i < entry_count; ++i) {
            if (version == 1) {
                READ_STREAM_BE(info.get()[i].segment_duration, 8);
                READ_STREAM_BE(info.get()[i].media_time, 8);
            } else {
                uint32_t sd;
                int32_t mt;
                READ_STREAM_BE(sd, 4);
                READ_STREAM_BE(mt, 4);

                info.get()[i].segment_duration = sd;
                info.get()[i].media_time = mt;
            }

            READ_STREAM_BE(info.get()[i].media_rate_int, 2);
            READ_STREAM_BE(info.get()[i].media_rate_fraction, 2);
        }

        return true;
    }

}
}
