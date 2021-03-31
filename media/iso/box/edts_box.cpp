// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "edts_box.h"

#include "utils/stream_utils.h"
#include "../iso_constants.h"

#include "elst_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool EditBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool {
            switch (box.type) {
            case kBoxType_elst:
            {
                auto list_box = std::make_shared<EditListBox>(box);
                if (!list_box->parse(s)) return false;
                children_.push_back(std::move(list_box));
                break;
            }

            default:
                // 无法识别的类型，直接跳过
                auto unkn_box = std::make_shared<UnknownBox>(box);
                if (!unkn_box->parse(s)) return false;
                children_.push_back(std::move(unkn_box));
                break;
            }
            return true;
        });
    }

}
}
