// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "dinf_box.h"

#include "utils/stream_utils.h"
#include "../iso_constants.h"

#include "dref_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool DataInfoBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool {
            switch (box.type) {
            case kBoxType_dref:
            {
                auto ref_box = std::make_shared<DataRefBox>(box);
                if (!ref_box->parse(s)) return false;
                children_.push_back(std::move(ref_box));
                break;
            }

            default:
                // 无法识别的类型
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
