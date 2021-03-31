// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "stbl_box.h"

#include "utils/stream_utils.h"

#include "../iso_constants.h"

#include "stsd_box.h"
#include "stdp_box.h"
#include "cslg_box.h"
#include "stss_box.h"
#include "stsh_box.h"
#include "sdtp_box.h"
#include "stsz_box.h"
#include "stsc_box.h"
#include "unknown_box.h"


namespace media {
namespace iso {

    bool SampleTableBox::parse(std::istream& s) {
        return parseContainer(s, [&](const Box& box)->bool {
            switch (box.type) {
            case kBoxType_stsd:
            {
                auto desc_box = std::make_shared<SampleDescBox>(box);
                if (!desc_box->parse(s)) return false;
                children_.push_back(std::move(desc_box));
                break;
            }

            case kBoxType_stdp:
            {
                if (!stsz_ptr_) {
                    return false;
                }

                auto priority_box = std::make_shared<DegradPriorityBox>(box, stsz_ptr_->sample_count);
                if (!priority_box->parse(s)) return false;
                children_.push_back(std::move(priority_box));
                break;
            }

            case kBoxType_cslg:
            {
                auto decode_box = std::make_shared<ComposToDecodeBox>(box);
                if (!decode_box->parse(s)) return false;
                children_.push_back(std::move(decode_box));
                break;
            }

            case kBoxType_stss:
            {
                auto sample_box = std::make_shared<SyncSampleBox>(box);
                if (!sample_box->parse(s)) return false;
                children_.push_back(std::move(sample_box));
                break;
            }

            case kBoxType_stsh:
            {
                auto sample_box = std::make_shared<ShadowSyncSampleBox>(box);
                if (!sample_box->parse(s)) return false;
                children_.push_back(std::move(sample_box));
                break;
            }

            case kBoxType_sdtp:
            {
                uint32_t sample_count;
                if (stsz_ptr_) {
                    sample_count = stsz_ptr_->sample_count;
                } else if (stz2_ptr_) {
                    sample_count = stz2_ptr_->sample_count;
                } else {
                    return false;
                }

                auto sample_box = std::make_shared<IndepDispSampleBox>(box, sample_count);
                if (!sample_box->parse(s)) return false;
                children_.push_back(std::move(sample_box));
                break;
            }

            case kBoxType_stsz:
            {
                auto size_box = std::make_shared<SampleSizeBox>(box);
                if (!size_box->parse(s)) return false;

                stsz_ptr_ = size_box.get();
                children_.push_back(std::move(size_box));
                break;
            }

            case kBoxType_stz2:
            {
                auto size_box = std::make_shared<CompactSampleSizeBox>(box);
                if (!size_box->parse(s)) return false;

                stz2_ptr_ = size_box.get();
                children_.push_back(std::move(size_box));
                break;
            }

            case kBoxType_stsc:
            {
                auto chunk_box = std::make_shared<SampleToChunkBox>(box);
                if (!chunk_box->parse(s)) return false;
                children_.push_back(std::move(chunk_box));
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
