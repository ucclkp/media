// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stsc_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool SampleToChunkBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(entry_count, 4);

        info.reset(new Info[entry_count], std::default_delete<Info[]>());
        for (uint32_t i = 0; i < entry_count; ++i) {
            auto& dat = info.get()[i];
            READ_STREAM_BE(dat.first_chunk, 4);
            READ_STREAM_BE(dat.samples_per_chunk, 4);
            READ_STREAM_BE(dat.sample_desc_index, 4);
        }

        return true;
    }

}
}
