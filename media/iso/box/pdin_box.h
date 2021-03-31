// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_PDIN_BOX_H_
#define MEDIA_ISO_BOX_PDIN_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'pdin'
     * Container: File
     * Mandatory: No
     * Zero or one
     */
    class ProgDLInfoBox : public FullBox {
    public:
        using FullBox::FullBox;

        struct Info {
            uint32_t rate;
            uint32_t initial_delay;
        };

        bool parse(std::istream& s) override;

        std::shared_ptr<Info> data;
        size_t data_count;
    };

}
}

#endif // MEDIA_ISO_BOX_PDIN_BOX_H_