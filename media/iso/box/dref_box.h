// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_BOX_DREF_BOX_H_
#define MEDIA_ISO_BOX_DREF_BOX_H_

#include <vector>

#include "iso_box.h"


namespace media {
namespace iso {

    /**
     * 'url '
     * Container: 'dref'
     * Mandatory: Y (at least one of 'url ' or 'urn ')
     * One or more
     */
    class DataEntryUrlBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        std::string location;
    };


    /**
     * 'urn '
     * Container: 'dref'
     * Mandatory: Y (at least one of 'url ' or 'urn ')
     * One or more
     */
    class DataEntryUrnBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        std::string name;
        std::string location;
    };


    /**
     * 'dref'
     * Container: 'dinf'
     * Mandatory: Y
     * Exactly one
     */
    class DataRefBox : public FullBox {
    public:
        using FullBox::FullBox;

        bool parse(std::istream& s) override;

        uint32_t entry_count;
        std::vector<std::shared_ptr<FullBox>> data_entries;
    };

}
}

#endif  // MEDIA_ISO_BOX_DREF_BOX_H_