// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_ELNG_BOX_H_
#define MEDIA_ISO_BOX_ELNG_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'elng'
     * Container: 'mdia'
     * Mandatory: Yes
     * Zero or one
     */
    class ExtLanguageTag : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        std::string ext_language;
    };

}
}

#endif  // MEDIA_ISO_BOX_ELNG_BOX_H_