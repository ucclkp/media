// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_STDP_BOX_H_
#define MEDIA_ISO_BOX_STDP_BOX_H_

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'stdp'
     * Container: 'stbl'
     * Mandatory: N
     * Zero or one
     */
    class DegradPriorityBox : public FullBox {
    public:
        DegradPriorityBox(const Box& b, uint32_t sample_count);

        bool parse(std::istream& s) override;

        std::shared_ptr<uint16_t> priority;

    private:
        uint32_t sample_count_;
    };

}
}

#endif  // MEDIA_ISO_BOX_STDP_BOX_H_