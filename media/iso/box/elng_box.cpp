// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "elng_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool ExtLanguageTag::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        for (;;) {
            char buf;
            READ_STREAM(buf, 1);
            if (buf == 0) break;
            ext_language.push_back(buf);
        }
        return true;
    }

}
}
