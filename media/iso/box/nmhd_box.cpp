// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "nmhd_box.h"


namespace media {
namespace iso {

    bool NullMediaHeaderBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }
        return true;
    }

}
}
