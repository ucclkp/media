// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_CTTS_BOX_H_
#define MEDIA_ISO_BOX_CTTS_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'ctts'
     * Container: 'stbl'
     * Mandatory: N
     * Zero or one
     */
    class ComposTimeToSampleBox : public FullBox {
    public:
        struct SampleInfo0 {
            uint32_t sample_count;
            uint32_t sample_offset;
        };

        struct SampleInfo1 {
            uint32_t sample_count;
            int32_t sample_offset;
        };

        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::shared_ptr<SampleInfo0> sample_info0;
        std::shared_ptr<SampleInfo1> sample_info1;
    };

}
}

#endif  // MEDIA_ISO_BOX_CTTS_BOX_H_