// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STTS_BOX_H_
#define MEDIA_ISO_BOX_STTS_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'stts'
     * Container: 'stbl'
     * Mandatory: Y
     * Exactly one
     */
    class DecodingTimeToSampleBox : public FullBox {
    public:
        struct SampleInfo {
            uint32_t sample_count;
            uint32_t sample_delta;
        };

        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::shared_ptr<SampleInfo> sample_info;
    };

}
}

#endif  // MEDIA_ISO_BOX_STTS_BOX_H_