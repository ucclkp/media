// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "trgr_box.h"

#include <cassert>

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    // TrackGroupTypeBox
    bool TrackGroupTypeBox::parse(std::istream& s) {
        auto prev_pos = s.tellg();

        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(track_group_id, 4);

        assert(size != 0);
        uint64_t remainder = s.tellg() - prev_pos + getBoxFieldSize();
        assert(remainder < size);
        remainder = size - remainder;

        size_t count = size_t(remainder);

        data.reset(new uint8_t[count], std::default_delete<uint8_t[]>());
        READ_STREAM(data.get()[0], count);
        data_count = count;

        return true;
    }


    // TrackGroupBox
    bool TrackGroupBox::parse(std::istream& s) {
        auto end_pos = s.tellg();
        end_pos += size - getBoxFieldSize();

        for (;;) {
            auto pos = s.tellg();
            // 超出表大小，解析失败
            if (pos > end_pos) {
                return false;
            }
            // 到达表结尾，返回
            if (pos == end_pos) {
                break;
            }

            Box box;
            if (!box.parse(s)) {
                return false;
            }

            auto tgtb_box = std::make_shared<TrackGroupTypeBox>(box);
            if (!tgtb_box->parse(s)) {
                return false;
            }

            // 确保尾部一致
            if (s.tellg() - pos != box.size) {
                assert(false);
                return false;
            }
            tgtbs.push_back(std::move(tgtb_box));
        }
        return true;
    }

}
}
