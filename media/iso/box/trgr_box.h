// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_TRGR_BOX_H_
#define MEDIA_ISO_BOX_TRGR_BOX_H_

#include <vector>

#include "iso_box.h"


namespace media {
namespace iso {

    class TrackGroupTypeBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t track_group_id;

        std::shared_ptr<uint8_t> data;
        size_t data_count;
    };


    /**
     * 'trgr'
     * Container: 'trak'
     * Mandatory: No
     * Zero or one
     */
    class TrackGroupBox : public Box {
    public:
        explicit TrackGroupBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;

        std::vector<std::shared_ptr<TrackGroupTypeBox>> tgtbs;
    };

}
}

#endif  // MEDIA_ISO_BOX_TRGR_BOX_H_