// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STSD_BOX_H_
#define MEDIA_ISO_BOX_STSD_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    class SampleEntry : public Box {
    public:
        explicit SampleEntry(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;

        uint16_t data_ref_index;
    };


    /**
     * 'btrt'
     */
    class BitRateBox : public Box {
    public:
        explicit BitRateBox(const Box& b)
            : Box(b) {}

        bool parse(std::istream& s) override;

        uint32_t buffer_size_DB;
        uint32_t max_bitrate;
        uint32_t avg_bitrate;
    };


    /**
     * 'stsd'
     * Container: 'stbl'
     * Mandatory: Yes
     * Exactly one
     */
    class SampleDescBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
    };

}
}

#endif  // MEDIA_ISO_BOX_STSD_BOX_H_