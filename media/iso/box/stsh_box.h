// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STSH_BOX_H_
#define MEDIA_ISO_BOX_STSH_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'stsh'
     * Container: 'stbl'
     * Mandatory: N
     * Zero or one
     */
    class ShadowSyncSampleBox : public FullBox {
    public:
        struct SampleInfo {
            uint32_t shadowed_sample_number;
            uint32_t sync_sample_number;
        };

        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::shared_ptr<SampleInfo> sample_info;
    };

}
}

#endif  // MEDIA_ISO_BOX_STSH_BOX_H_