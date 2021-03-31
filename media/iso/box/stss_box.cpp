// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stss_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool SyncSampleBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(entry_count, 4);

        sample_numbers.reset(new uint32_t[entry_count], std::default_delete<uint32_t[]>());
        for (uint32_t i = 0; i < entry_count; ++i) {
            READ_STREAM_BE(sample_numbers.get()[i], 4);
        }
        return true;
    }

}
}
