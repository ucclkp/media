// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "iso_media_parser.h"

#include <assert.h>

#include "iso_constants.h"

#include "box/iso_box.h"
#include "box/ftyp_box.h"
#include "box/mdat_box.h"
#include "box/skip_box.h"
#include "box/pdin_box.h"
#include "box/moov_box.h"
#include "box/unknown_box.h"


namespace media {
namespace iso {

    ISOMediaParser::ISOMediaParser(std::istream& s)
        : iso_file_(s) {}

    bool ISOMediaParser::parse() {
        for (;;) {
            // 到文件尾了，结束
            auto peek_ch = iso_file_.peek();
            if (!iso_file_) {
                return false;
            }
            if (peek_ch == EOF) {
                break;
            }

            auto prev_pos = iso_file_.tellg();

            Box box;
            if (!box.parse(iso_file_)) {
                return false;
            }

            switch (box.type) {
            case kBoxType_ftyp:
            {
                auto ftyp_box = std::make_shared<FileTypeBox>(box);
                if (!ftyp_box->parse(iso_file_)) return false;
                boxes_.push_back(std::move(ftyp_box));
                break;
            }

            case kBoxType_mdat:
            {
                auto mdat_box = std::make_shared<MediaDataBox>(box);
                if (!mdat_box->parse(iso_file_)) return false;
                boxes_.push_back(std::move(mdat_box));
                break;
            }

            case kBoxType_free:
            case kBoxType_skip:
            {
                auto skip_box = std::make_shared<SkipBox>(box);
                if (!skip_box->parse(iso_file_)) return false;
                boxes_.push_back(std::move(skip_box));
                break;
            }

            case kBoxType_pdin:
            {
                auto pdin_box = std::make_shared<ProgDLInfoBox>(box);
                if (!pdin_box->parse(iso_file_)) return false;
                boxes_.push_back(std::move(pdin_box));
                break;
            }

            case kBoxType_moov:
            {
                auto moov_box = std::make_shared<MovieBox>(box);
                if (!moov_box->parse(iso_file_)) return false;
                boxes_.push_back(std::move(moov_box));
                break;
            }

            default:
                // 无法识别的类型
                auto unkn_box = std::make_shared<UnknownBox>(box);
                if (!unkn_box->parse(iso_file_)) return false;
                boxes_.push_back(std::move(unkn_box));
                break;
            }

            // 确保尾部一致
            if (iso_file_.tellg() - prev_pos != box.size) {
                assert(false);
                return false;
            }
        }

        return true;
    }

    const std::vector<std::shared_ptr<Box>>& ISOMediaParser::getBoxes() const {
        return boxes_;
    }

}
}
