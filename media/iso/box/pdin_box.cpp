// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "pdin_box.h"

#include <assert.h>

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool ProgDLInfoBox::parse(std::istream& s) {
        auto prev_pos = s.tellg();

        if (!FullBox::parse(s)) {
            return false;
        }

        uint64_t remainder;
        if (size > 0) {
            remainder = s.tellg() - prev_pos + getBoxFieldSize();
            assert(remainder < size);
            remainder = size - remainder;
        } else {
            // 直到文件末尾
            prev_pos = s.tellg();
            s.seekg(0, std::ios::end);
            remainder = s.tellg() - prev_pos;
            s.seekg(prev_pos, std::ios::beg);
        }

        assert(remainder % 8 == 0);
        size_t count = size_t(remainder / 8);

        data.reset(new Info[count], std::default_delete<Info[]>());
        for (uint64_t i = 0; i < count; ++i) {
            READ_STREAM_BE(data.get()[i].rate, 4);
            READ_STREAM_BE(data.get()[i].initial_delay, 4);
        }
        data_count = count;

        return true;
    }

}
}
