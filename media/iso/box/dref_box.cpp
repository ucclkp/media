// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "dref_box.h"

#include <cassert>

#include "utils/stream_utils.h"
#include "../iso_constants.h"

#include "skip_box.h"


namespace media {
namespace iso {

    // DataEntryUrlBox
    bool DataEntryUrlBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        // 自包含标志设置，表示后面没有字符串
        if (flags & 0x1) {
            return true;
        }

        for (;;) {
            char buf;
            READ_STREAM(buf, 1);
            if (buf == 0) break;
            location.push_back(buf);
        }
        return true;
    }


    // DataEntryUrnBox
    bool DataEntryUrnBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        for (;;) {
            char buf;
            READ_STREAM(buf, 1);
            if (buf == 0) break;
            name.push_back(buf);
        }
        for (;;) {
            char buf;
            READ_STREAM(buf, 1);
            if (buf == 0) break;
            location.push_back(buf);
        }
        return true;
    }


    // DataRefBox
    bool DataRefBox::parse(std::istream& s) {
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

            switch (box.type) {
            case kBoxType_url_:
            {
                auto url_box = std::make_shared<DataEntryUrlBox>(box);
                if (!url_box->parse(s)) return false;
                data_entries.push_back(url_box);
                break;
            }

            case kBoxType_urn_:
            {
                auto urn_box = std::make_shared<DataEntryUrnBox>(box);
                if (!urn_box->parse(s)) return false;
                data_entries.push_back(urn_box);
                break;
            }

            case kBoxType_free:
            case kBoxType_skip:
            {
                SkipBox skip_box(box);
                if (!skip_box.parse(s)) return false;
                break;
            }

            default:
            {
                // 无法识别的类型，直接跳过。
                SKIP_BYTES(box.size - box.getBoxFieldSize());
                break;
            }
            }

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
