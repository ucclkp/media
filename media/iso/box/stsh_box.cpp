// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stsh_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool ShadowSyncSampleBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(entry_count, 4);

        sample_info.reset(new SampleInfo[entry_count], std::default_delete<SampleInfo[]>());
        for (uint32_t i = 0; i < entry_count; ++i) {
            READ_STREAM_BE(sample_info.get()[i].shadowed_sample_number, 4);
            READ_STREAM_BE(sample_info.get()[i].sync_sample_number, 4);
        }
        return true;
    }

}
}
