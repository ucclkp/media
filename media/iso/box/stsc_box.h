// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STSC_BOX_H_
#define MEDIA_ISO_BOX_STSC_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'stsc'
     * Container: 'stbl'
     * Mandatory: Y
     * Exactly one
     */
    class SampleToChunkBox : public FullBox {
    public:
        struct Info {
            uint32_t first_chunk;
            uint32_t samples_per_chunk;
            uint32_t sample_desc_index;
        };

        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::shared_ptr<Info> info;
    };

}
}

#endif  // MEDIA_ISO_BOX_STSC_BOX_H_