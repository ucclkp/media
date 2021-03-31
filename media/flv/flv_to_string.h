// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_FLV_FLV_TO_STRING_H_
#define MEDIA_FLV_FLV_TO_STRING_H_

#include "flv.h"


namespace media {
namespace flv {

    std::u16string tagTypeToString(uint8_t type);

    std::u16string soundFormatToString(uint8_t format);
    std::u16string soundRateToString(uint8_t rate);
    std::u16string soundSizeToString(uint8_t size);
    std::u16string soundTypeToString(uint8_t type);

    std::u16string videoCodecIDToString(uint8_t id);
    std::u16string videoFrameTypeToString(uint8_t type);
    std::u16string videoAVCPacketTypeToString(uint8_t type);

}
}

#endif  // MEDIA_FLV_FLV_TO_STRING_H_