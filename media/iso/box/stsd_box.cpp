// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stsd_box.h"

#include <cassert>

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    // SampleEntry
    bool SampleEntry::parse(std::istream& s) {
        SKIP_BYTES(6);
        READ_STREAM_BE(data_ref_index, 2);
        return true;
    }

    // BitRateBox
    bool BitRateBox::parse(std::istream& s) {
        READ_STREAM_BE(buffer_size_DB, 4);
        READ_STREAM_BE(max_bitrate, 4);
        READ_STREAM_BE(avg_bitrate, 4);
        return true;
    }

    // SampleDescBox
    bool SampleDescBox::parse(std::istream& s) {
        auto end_pos = s.tellg();
        end_pos += size - getBoxFieldSize();

        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(entry_count, 4);
        for (uint32_t i = 0; i < entry_count; ++i) {
            auto prev_pos = s.tellg();
            // 将超出表大小，解析失败
            if (prev_pos >= end_pos) {
                return false;
            }

            Box box;
            if (!box.parse(s)) {
                return false;
            }

            SampleEntry entry(box);
            if (!entry.parse(s)) {
                return false;
            }

            // TODO: 解析 SampleEntry 子类成员，这里先跳过
            SKIP_BYTES(box.size - (s.tellg() - prev_pos));

            // 确保尾部一致
            if (s.tellg() - prev_pos != box.size) {
                assert(false);
                return false;
            }
        }

        return true;
    }

}
}
