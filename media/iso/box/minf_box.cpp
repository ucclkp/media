// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "minf_box.h"

#include "utils/stream_utils.h"

#include "../iso_constants.h"

#include "nmhd_box.h"
#include "stbl_box.h"
#include "dinf_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool MediaInfoBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool {
            switch (box.type) {
            case kBoxType_nmhd:
            {
                auto header_box = std::make_shared<NullMediaHeaderBox>(box);
                if (!header_box->parse(s)) return false;
                children_.push_back(std::move(header_box));
                break;
            }

            case kBoxType_stbl:
            {
                auto table_box = std::make_shared<SampleTableBox>(box);
                if (!table_box->parse(s)) return false;
                children_.push_back(std::move(table_box));
                break;
            }

            case kBoxType_dinf:
            {
                auto info_box = std::make_shared<DataInfoBox>(box);
                if (!info_box->parse(s)) return false;
                children_.push_back(std::move(info_box));
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
