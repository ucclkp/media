// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "ctts_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool ComposTimeToSampleBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(entry_count, 4);
        if (version == 0) {
            sample_info0.reset(new SampleInfo0[entry_count], std::default_delete<SampleInfo0[]>());
            for (uint32_t i = 0; i < entry_count; ++i) {
                READ_STREAM_BE(sample_info0.get()[i].sample_count, 4);
                READ_STREAM_BE(sample_info0.get()[i].sample_offset, 4);
            }
        } else if (version == 1) {
            sample_info1.reset(new SampleInfo1[entry_count], std::default_delete<SampleInfo1[]>());
            for (uint32_t i = 0; i < entry_count; ++i) {
                READ_STREAM_BE(sample_info1.get()[i].sample_count, 4);
                READ_STREAM_BE(sample_info1.get()[i].sample_offset, 4);
            }
        }

        return true;
    }

}
}
