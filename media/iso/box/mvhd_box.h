// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_MVHD_BOX_H_
#define MEDIA_ISO_BOX_MVHD_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'mvhd'
     * Container: 'moov'
     * Mandatory: Yes
     * Exactly one
     */
    class MovieHeaderBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint64_t creation_time;
        uint64_t modification_time;
        uint32_t timescale;
        uint64_t duration;

        int32_t rate;
        int16_t volume;
        int32_t matrix[9];
        // bit(32)[6]
        uint8_t pre_defined[24];
        uint32_t next_track_ID;
    };

}
}

#endif  // MEDIA_ISO_BOX_MVHD_BOX_H_