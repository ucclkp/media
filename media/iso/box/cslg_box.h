// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_CSLG_BOX_H_
#define MEDIA_ISO_BOX_CSLG_BOX_H_


#include "iso_box.h"

namespace media {
namespace iso {

    /**
     * 'cslg'
     * Container: 'stbl' or 'trep'
     * Mandatory: N
     * Zero or one
     */
    class ComposToDecodeBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        int64_t compos_to_dts_shift;
        int64_t least_decode_to_display_delta;
        int64_t greatest_decode_to_display_delta;
        int64_t compos_start_time;
        int64_t compos_end_time;
    };

}
}

#endif  // MEDIA_ISO_BOX_CSLG_BOX_H_