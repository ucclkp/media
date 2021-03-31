// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_FTYP_BOX_H_
#define MEDIA_ISO_BOX_FTYP_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'ftyp'
     * Container: File
     * Mandatory: Yes
     * Exactly one*
     */
    class FileTypeBox : public Box {
    public:
        explicit FileTypeBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;

        uint32_t major_brand;
        uint32_t minor_version;

        std::shared_ptr<uint32_t> compatible_brands;
        size_t compatible_brands_count = 0;
    };

}
}

#endif  // MEDIA_ISO_BOX_FTYP_BOX_H_