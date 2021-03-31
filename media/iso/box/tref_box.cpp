// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "tref_box.h"

#include <assert.h>
#include <vector>

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    // TrackRefTypeBox
    bool TrackRefTypeBox::parse(std::istream& s) {
        auto box_size = getBoxFieldSize();
        assert(size != 0);
        assert(box_size < size);

        uint64_t remainder = size - box_size;
        assert(remainder % 4 == 0);
        size_t count = size_t(remainder / 4);

        track_IDs.reset(new uint32_t[count], std::default_delete<uint32_t[]>());
        for (uint64_t i = 0; i < count; ++i) {
            READ_STREAM_BE(track_IDs.get()[i], 4);
        }
        track_ID_count = count;
        return true;
    }


    // TrackRefBox
    bool TrackRefBox::parse(std::istream& s) {
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

            auto tref_box = std::make_shared<TrackRefTypeBox>(box);
            if (!tref_box->parse(s)) {
                return false;
            }

            // 确保尾部一致
            if (s.tellg() - pos != box.size) {
                assert(false);
                return false;
            }
            trefs.push_back(std::move(tref_box));
        }
        return true;
    }

}
}
