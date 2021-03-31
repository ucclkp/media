// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "hdlr_box.h"

#include "utils/stream_utils.h"


namespace media {
namespace iso {

    bool HandlerRefBox::parse(std::istream& s) {
        if (!FullBox::parse(s)) {
            return false;
        }

        READ_STREAM_BE(pre_defined, 4);
        READ_STREAM_BE(handler_type, 4);

        // reserved
        SKIP_BYTES(12);

        for (;;) {
            char buf;
            READ_STREAM(buf, 1);
            if (buf == 0) break;
            name.push_back(buf);
        }
        return true;
    }

}
}
