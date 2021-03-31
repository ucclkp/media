// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "tkhd_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool TrackHeaderBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        if (version == 1) {
            READ_STREAM_BE(creation_time, 8);
            READ_STREAM_BE(modification_time, 8);
            READ_STREAM_BE(track_ID, 4);
            // reserved
            SKIP_BYTES(4);
            READ_STREAM_BE(duration, 8);
        } else {
            uint32_t ct, mt, dr;
            READ_STREAM_BE(ct, 4);
            READ_STREAM_BE(mt, 4);
            READ_STREAM_BE(track_ID, 4);
            // reserved
            SKIP_BYTES(4);
            READ_STREAM_BE(dr, 4);

            creation_time = ct;
            modification_time = mt;
            duration = dr;
        }

        //reserved
        SKIP_BYTES(8);
        READ_STREAM_BE(layer, 2);
        READ_STREAM_BE(alternate_group, 2);
        READ_STREAM_BE(volume, 2);
        //reserved
        SKIP_BYTES(2);

        for (uint8_t i = 0; i < 9; ++i) {
            READ_STREAM_BE(matrix[i], 4);
        }
        READ_STREAM_BE(width, 4);
        READ_STREAM_BE(height, 4);

        return true;
    }

}
}
