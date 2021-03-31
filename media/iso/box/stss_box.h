// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STSS_BOX_H_
#define MEDIA_ISO_BOX_STSS_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'stss'
     * Container: 'stbl'
     * Mandatory: N
     * Zero or one
     */
    class SyncSampleBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::shared_ptr<uint32_t> sample_numbers;
    };

}
}

#endif  // MEDIA_ISO_BOX_STSS_BOX_H_