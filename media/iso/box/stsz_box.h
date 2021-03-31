// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STSZ_BOX_H_
#define MEDIA_ISO_BOX_STSZ_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'stsz'
     * Container: 'stbl'
     * Mandatory: Y
     * Exactly one variant must be present
     */
    class SampleSizeBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t sample_size;
        uint32_t sample_count;
        std::shared_ptr<uint32_t> entry_size;
    };


    /**
     * 'stz2'
     */
    class CompactSampleSizeBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint8_t field_size;
        uint32_t sample_count;
        std::shared_ptr<uint16_t> entry_size;
    };

}
}

#endif  // MEDIA_ISO_BOX_STSZ_BOX_H_