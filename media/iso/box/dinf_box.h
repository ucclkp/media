// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_DINF_BOX_H_
#define MEDIA_ISO_BOX_DINF_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'dinf'
     * Container: 'minf' or 'meta'
     * Mandatory: Y in 'minf'. N in 'meta'
     * Exactly one
     */
    class DataInfoBox : public Box {
    public:
        explicit DataInfoBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;
        bool isContainer() const override { return true; }
    };

}
}

#endif  // MEDIA_ISO_BOX_DINF_BOX_H_