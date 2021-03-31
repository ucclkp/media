// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_TREF_BOX_H_
#define MEDIA_ISO_BOX_TREF_BOX_H_

#include <vector>

#include "iso_box.h"


namespace media {
namespace iso {

    class TrackRefTypeBox : public Box {
    public:
        explicit TrackRefTypeBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;

        std::shared_ptr<uint32_t> track_IDs;
        size_t track_ID_count = 0;
    };


    /**
     * Box Type: 'tref'
     * Container: 'trak'
     * Mandatory: No
     * Zero or one
     */
    class TrackRefBox : public Box {
    public:
        explicit TrackRefBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;

        std::vector<std::shared_ptr<TrackRefTypeBox>> trefs;
    };

}
}

#endif  // MEDIA_ISO_BOX_TREF_BOX_H_