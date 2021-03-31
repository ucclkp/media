// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "mdat_box.h"

#include <cassert>

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool MediaDataBox::parse(std::istream& s) {
        auto prev_pos = s.tellg();

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

        size_t count = size_t(remainder);

        data.reset(new uint8_t[count]);
        READ_STREAM(data.get()[0], count);
        data_count = count;

        return true;
    }

}
}
