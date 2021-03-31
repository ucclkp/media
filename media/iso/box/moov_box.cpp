// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "moov_box.h"

#include "utils/stream_utils.h"

#include "../iso_constants.h"

#include "mvhd_box.h"
#include "trak_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool MovieBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool{
            switch (box.type) {
            case kBoxType_mvhd:
            {
                auto header_box = std::make_shared<MovieHeaderBox>(box);
                if (!header_box->parse(s)) return false;
                children_.push_back(std::move(header_box));
                break;
            }

            case kBoxType_trak:
            {
                auto track_box = std::make_shared<TrackBox>(box);
                if (!track_box->parse(s)) return false;
                children_.push_back(std::move(track_box));
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