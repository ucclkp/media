// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_SDTP_BOX_H_
#define MEDIA_ISO_BOX_SDTP_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'sdtp'
     * Container: 'stbl'
     * Mandatory: N
     * Zero or one
     */
    class IndepDispSampleBox : public FullBox {
    public:
        struct SampleInfo {
            uint8_t is_leading;
            uint8_t sample_depends_on;
            uint8_t sample_is_depended_on;
            uint8_t sample_has_redundancy;
        };

        IndepDispSampleBox(const Box& b, uint32_t sample_count)
            : FullBox(b), sample_count_(sample_count) {}

        bool parse(std::istream& s) override;

        std::shared_ptr<SampleInfo> sample_info;

    private:
        uint32_t sample_count_;
    };

}
}

#endif  // MEDIA_ISO_BOX_SDTP_BOX_H_