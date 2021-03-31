// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_HDLR_BOX_H_
#define MEDIA_ISO_BOX_HDLR_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'hdlr'
     * Container: 'mdia' or 'meta'
     * Mandatory: Yes
     * Exactly one
     */
    class HandlerRefBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t pre_defined;
        uint32_t handler_type;
        std::string name;
    };

}
}

#endif  // MEDIA_ISO_BOX_HDLR_BOX_H_