// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "trak_box.h"

#include "../iso_constants.h"

#include "tkhd_box.h"
#include "tref_box.h"
#include "trgr_box.h"
#include "mdia_box.h"
#include "edts_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool TrackBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool {
            switch (box.type) {
            case kBoxType_tkhd:
            {
                auto header_box = std::make_shared<TrackHeaderBox>(box);
                if (!header_box->parse(s)) return false;
                children_.push_back(std::move(header_box));
                break;
            }

            case kBoxType_tref:
            {
                auto track_ref_box = std::make_shared<TrackRefBox>(box);
                if (!track_ref_box->parse(s)) return false;
                children_.push_back(std::move(track_ref_box));
                break;
            }

            case kBoxType_trgr:
            {
                auto group_box = std::make_shared<TrackGroupBox>(box);
                if (!group_box->parse(s)) return false;
                children_.push_back(std::move(group_box));
                break;
            }

            case kBoxType_mdia:
            {
                auto media_box = std::make_shared<MediaBox>(box);
                if (!media_box->parse(s)) return false;
                children_.push_back(std::move(media_box));
                break;
            }

            case kBoxType_edts:
            {
                auto edit_box = std::make_shared<EditBox>(box);
                if (!edit_box->parse(s)) return false;
                children_.push_back(std::move(edit_box));
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
