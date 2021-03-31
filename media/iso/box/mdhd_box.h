// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_MDHD_BOX_H_
#define MEDIA_ISO_BOX_MDHD_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'mdhd'
     * Container: 'mdia'
     * Mandatory: Yes
     * Exactly one
     */
    class MediaHeaderBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint64_t creation_time;
        uint64_t modification_time;
        uint32_t timescale;
        uint64_t duration;

        // bit(1) pad
        // uint(5)[3]
        uint8_t language[3];
        uint16_t pre_defined;
    };

}
}

#endif  // MEDIA_ISO_BOX_MDHD_BOX_H_