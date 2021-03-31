// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_ISO_ISO_CONSTANTS_H_
#define MEDIA_ISO_ISO_CONSTANTS_H_

#include <cstdint>


namespace media {
namespace iso {

    const uint32_t kBoxType_uuid = 0x75756964;

    const uint32_t kBoxType_ftyp = 0x66747970;
    const uint32_t kBoxType_mdat = 0x6D646174;
    const uint32_t kBoxType_free = 0x66726565;
    const uint32_t kBoxType_skip = 0x736B6970;
    const uint32_t kBoxType_pdin = 0x7064696E;
    const uint32_t kBoxType_moov = 0x6D6F6F76;
    const uint32_t kBoxType_mvhd = 0x6D766864;
    const uint32_t kBoxType_trak = 0x7472616B;
    const uint32_t kBoxType_tkhd = 0x746B6864;
    const uint32_t kBoxType_tref = 0x74726566;
    const uint32_t kBoxType_trgr = 0x74726772;
    const uint32_t kBoxType_mdia = 0x6D646961;
    const uint32_t kBoxType_mdhd = 0x6D646864;
    const uint32_t kBoxType_hdlr = 0x68646C72;
    const uint32_t kBoxType_minf = 0x6D696E66;
    const uint32_t kBoxType_nmhd = 0x6E6D6864;
    const uint32_t kBoxType_elng = 0x656C6E67;
    const uint32_t kBoxType_stbl = 0x7374626C;
    const uint32_t kBoxType_stsd = 0x73747364;
    const uint32_t kBoxType_stdp = 0x73746470;
    const uint32_t kBoxType_stts = 0x73747473;
    const uint32_t kBoxType_ctts = 0x63747473;
    const uint32_t kBoxType_cslg = 0x63736C67;
    const uint32_t kBoxType_stss = 0x73747373;
    const uint32_t kBoxType_stsh = 0x73747368;
    const uint32_t kBoxType_sdtp = 0x73647470;
    const uint32_t kBoxType_edts = 0x65647473;
    const uint32_t kBoxType_elst = 0x656C7374;
    const uint32_t kBoxType_dinf = 0x64696E66;
    const uint32_t kBoxType_dref = 0x64726566;
    const uint32_t kBoxType_url_ = 0x75726C20;
    const uint32_t kBoxType_urn_ = 0x75726E20;
    const uint32_t kBoxType_stsz = 0x7374737A;
    const uint32_t kBoxType_stz2 = 0x73747A32;
    const uint32_t kBoxType_stsc = 0x73747363;

}
}

#endif  // MEDIA_ISO_ISO_CONSTANTS_H_