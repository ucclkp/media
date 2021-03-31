// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "ftyp_box.h"

#include <cassert>

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool FileTypeBox::parse(std::istream& s) {
        auto prev_pos = s.tellg();

        READ_STREAM_BE(major_brand, 4);
        READ_STREAM_BE(minor_version, 4);

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

        assert(remainder % 4 == 0);
        size_t count = size_t(remainder / 4);

        compatible_brands.reset(new uint32_t[count]);
        for (uint64_t i = 0; i < count; ++i) {
            READ_STREAM_BE(compatible_brands.get()[i], 4);
        }
        compatible_brands_count = count;

        return true;
    }

}
}