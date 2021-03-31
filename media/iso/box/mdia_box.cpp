// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "mdia_box.h"

#include "utils/stream_utils.h"

#include "../iso_constants.h"

#include "mdhd_box.h"
#include "hdlr_box.h"
#include "minf_box.h"
#include "elng_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool MediaBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool {
            switch (box.type) {
            case kBoxType_mdhd:
            {
                auto header_box = std::make_shared<MediaHeaderBox>(box);
                if (!header_box->parse(s)) return false;
                children_.push_back(std::move(header_box));
                break;
            }

            case kBoxType_hdlr:
            {
                auto ref_box = std::make_shared<HandlerRefBox>(box);
                if (!ref_box->parse(s)) return false;
                children_.push_back(std::move(ref_box));
                break;
            }

            case kBoxType_minf:
            {
                auto info_box = std::make_shared<MediaInfoBox>(box);
                if (!info_box->parse(s)) return false;
                children_.push_back(std::move(info_box));
                break;
            }

            case kBoxType_elng:
            {
                auto ext_language_tag = std::make_shared<ExtLanguageTag>(box);
                if (!ext_language_tag->parse(s)) return false;
                children_.push_back(std::move(ext_language_tag));
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
