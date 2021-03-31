// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stdp_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    DegradPriorityBox::DegradPriorityBox(const Box& b, uint32_t sample_count)
        : FullBox(b),
          sample_count_(sample_count) {}

    bool DegradPriorityBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        priority.reset(new uint16_t[sample_count_], std::default_delete<uint16_t[]>());
        for (uint32_t i = 0; i < sample_count_; ++i) {
            READ_STREAM_BE(priority.get()[i], 2);
        }
        return true;
    }

}
}
