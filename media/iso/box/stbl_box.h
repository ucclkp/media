// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STBL_BOX_H_
#define MEDIA_ISO_BOX_STBL_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    class SampleSizeBox;
    class CompactSampleSizeBox;

    /**
     * 'stbl'
     * Container: 'minf'
     * Mandatory: Yes
     * Exactly one
     */
    class SampleTableBox : public Box {
    public:
        explicit SampleTableBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;
        bool isContainer() const override { return true; }

    private:
        SampleSizeBox* stsz_ptr_ = nullptr;
        CompactSampleSizeBox* stz2_ptr_ = nullptr;
    };

}
}

#endif  // MEDIA_ISO_BOX_STBL_BOX_H_