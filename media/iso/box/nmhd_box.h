// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_NMHD_BOX_H_
#define MEDIA_ISO_BOX_NMHD_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'nmhd'
     * Container: 'minf'
     * Mandatory: Yes
     * Exactly one specific media header shall be present
     */
    class NullMediaHeaderBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;
    };

}
}

#endif  // MEDIA_ISO_BOX_NMHD_BOX_H_