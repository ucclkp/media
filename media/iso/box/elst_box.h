// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_ELST_BOX_H_
#define MEDIA_ISO_BOX_ELST_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    class EditListBox : public FullBox {
    public:
        struct Info {
            uint64_t segment_duration;
            int64_t media_time;
            int16_t media_rate_int;
            int16_t media_rate_fraction;
        };

        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::shared_ptr<Info> info;
    };

}
}

#endif  // MEDIA_ISO_BOX_ELST_BOX_H_