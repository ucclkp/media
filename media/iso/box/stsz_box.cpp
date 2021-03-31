// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stsz_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    // SampleSizeBox
    bool SampleSizeBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(sample_size, 4);
        READ_STREAM_BE(sample_count, 4);

        if (sample_size == 0) {
            entry_size.reset(new uint32_t[sample_count], std::default_delete<uint32_t[]>());
            for (uint32_t i = 0; i < sample_count; ++i) {
                READ_STREAM_BE(entry_size.get()[i], 4);
            }
        }
        return true;
    }


    // CompactSampleSizeBox
    bool CompactSampleSizeBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        // reserved
        SKIP_BYTES(3);

        READ_STREAM(field_size, 1);
        READ_STREAM_BE(sample_count, 4);

        entry_size.reset(new uint16_t[sample_count], std::default_delete<uint16_t[]>());
        for (uint32_t i = 0; i < sample_count; ++i) {
            if (field_size == 4) {
                uint8_t buf;
                READ_STREAM(buf, 1);
                entry_size.get()[i] = buf >> 4;
                ++i;
                if (i < sample_count) {
                    entry_size.get()[i] = buf & 0x0F;
                }
            } else if (field_size == 8) {
                uint8_t buf;
                READ_STREAM(buf, 1);
                entry_size.get()[i] = buf;
            } else if (field_size == 16) {
                READ_STREAM_BE(entry_size.get()[i], 2);
            } else {
                return false;
            }
        }

        return true;
    }

}
}
