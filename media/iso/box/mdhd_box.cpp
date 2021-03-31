// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "mdhd_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool MediaHeaderBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        if (version == 1) {
            READ_STREAM_BE(creation_time, 8);
            READ_STREAM_BE(modification_time, 8);
            READ_STREAM_BE(timescale, 4);
            READ_STREAM_BE(duration, 8);
        } else {
            uint32_t ct32, mt32, dur32;
            READ_STREAM_BE(ct32, 4);
            READ_STREAM_BE(mt32, 4);
            READ_STREAM_BE(timescale, 4);
            READ_STREAM_BE(dur32, 4);

            creation_time = ct32;
            modification_time = mt32;
            duration = dur32;
        }

        uint8_t buf;
        READ_STREAM(buf, 1);
        language[0] = (buf >> 2) & 0x1F;

        language[1] = (buf & 0x3) << 3;

        READ_STREAM(buf, 1);
        language[1] |= (buf >> 5) & 0x7;

        language[2] = buf & 0x1F;

        READ_STREAM_BE(pre_defined, 2);
        return true;
    }

}
}
