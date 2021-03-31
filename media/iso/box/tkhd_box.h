// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_TKHD_BOX_H_
#define MEDIA_ISO_BOX_TKHD_BOX_H_

#include "iso_box.h"


namespace media {
    namespace iso {

        /**
         * 'tkhd'
         * Container: 'trak'
         * Mandatory: Yes
         * Exactly one
         */
        class TrackHeaderBox : public FullBox {
        public:
            using FullBox::FullBox;

            bool parse(std::istream& s) override;

            uint64_t creation_time;
            uint64_t modification_time;
            uint32_t track_ID;
            uint64_t duration;

            int16_t layer;
            int16_t alternate_group;
            int16_t volume;
            int32_t matrix[9];
            uint32_t width;
            uint32_t height;
        };

    }
}

#endif  // MEDIA_ISO_BOX_TKHD_BOX_H_