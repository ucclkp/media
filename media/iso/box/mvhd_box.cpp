// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "mvhd_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool MovieHeaderBox::parse(std::istream& s) {
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

        READ_STREAM_BE(rate, 4);
        READ_STREAM_BE(volume, 2);

        // reserved
        SKIP_BYTES(2 + 4 * 2);

        for (uint8_t i = 0; i < 9; ++i) {
            READ_STREAM_BE(matrix[i], 4);
        }

        READ_STREAM(pre_defined[0], 24);
        READ_STREAM_BE(next_track_ID, 4);
        return true;
    }

}
}