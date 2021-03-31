// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "flv_to_string.h"


namespace media {
namespace flv {

    std::u16string tagTypeToString(uint8_t type) {
        std::u16string result;
        switch (type) {
        case TAG_VIDEO:  result.append(u"Video Tag"); break;
        case TAG_AUDIO:  result.append(u"Audio Tag"); break;
        case TAG_SCRIPT: result.append(u"Script Tag"); break;
        default:         result.append(u"Unknown Tag"); break;
        }
        return result;
    }

    std::u16string soundFormatToString(uint8_t format) {
        std::u16string result;
        switch (format) {
        case SF_LINEAR_PCM_PE:       result.append(u"Linear_PCM_PE"); break;
        case SF_ADPCM:               result.append(u"ADPCM"); break;
        case SF_MP3:                 result.append(u"MP3"); break;
        case SF_LINEAR_PCM_LE:       result.append(u"Linear_PCM_LE"); break;
        case SF_NELLYMOSER_16K_MONO: result.append(u"Nellymoser_16k_Mono"); break;
        case SF_NELLYMOSER_8K_MONO:  result.append(u"Nellymoser_8k_Mono"); break;
        case SF_NELLYMOSER:          result.append(u"Nellymoser"); break;
        case SF_G711_A_LAW_PCM:      result.append(u"G.711_A-law_log_PCM"); break;
        case SF_G711_MU_LAW_PCM:     result.append(u"G.711_mu-law_log_PCM"); break;
        case SF_RESERVED:            result.append(u"Reserved"); break;
        case SF_AAC:                 result.append(u"AAC"); break;
        case SF_SPEEX:               result.append(u"Speex"); break;
        case SF_MP3_8K:              result.append(u"MP3_8kHz"); break;
        case SF_DEVICE_SPECIFIC:     result.append(u"Device-specific_sound"); break;
        default:                     result.append(u"Unknown"); break;
        }
        return result;
    }

    std::u16string soundRateToString(uint8_t rate) {
        std::u16string result;
        switch (rate) {
        case 0:  result.append(u"5.5kHz"); break;
        case 1:  result.append(u"11kHz"); break;
        case 2:  result.append(u"22kHz"); break;
        case 3:  result.append(u"44kHz"); break;
        default: result.append(u"Unknown"); break;
        }
        return result;
    }

    std::u16string soundSizeToString(uint8_t size) {
        std::u16string result;
        switch (size) {
        case 0:  result.append(u"8bit"); break;
        case 1:  result.append(u"16bit"); break;
        default: result.append(u"Unknown"); break;
        }
        return result;
    }

    std::u16string soundTypeToString(uint8_t type) {
        std::u16string result;
        switch (type) {
        case 0:  result.append(u"Mono"); break;
        case 1:  result.append(u"Stereo"); break;
        default: result.append(u"Unknown"); break;
        }
        return result;
    }

    std::u16string videoCodecIDToString(uint8_t id) {
        std::u16string result;
        switch (id) {
        case VCID_SORENSON_H_263:  result.append(u"Sorenson_H.263"); break;
        case VCID_SCREEN_VIDEO:    result.append(u"Screen_video"); break;
        case VCID_ON2_VP6:         result.append(u"On2_VP6"); break;
        case VCID_ON2_VP6_WITH_A:  result.append(u"On2_VP6_with_a"); break;
        case VCID_SCREEN_VIDEO_V2: result.append(u"Screen_video_v2"); break;
        case VCID_AVC:             result.append(u"AVC"); break;
        default:                   result.append(u"Unknown"); break;
        }
        return result;
    }

    std::u16string videoFrameTypeToString(uint8_t type) {
        std::u16string result;
        switch (type) {
        case VFT_KEY_FRAME:              result.append(u"key_frame"); break;
        case VFT_INTER_FRAME:            result.append(u"inter_frame"); break;
        case VFT_DISPOSABLE_INTER_FRAME: result.append(u"disp_inter_frame"); break;
        case VFT_GENERATED_KEY_FRAME:    result.append(u"gene_key_frame"); break;
        case VFT_INFO_CMD_FRAME:         result.append(u"video_info_cmd_frame"); break;
        default:                         result.append(u"Unknown"); break;
        }
        return result;
    }

    std::u16string videoAVCPacketTypeToString(uint8_t type) {
        std::u16string result;
        switch (type) {
        case AVCPT_SEQ_HEADER: result.append(u"AVC_seq_header"); break;
        case AVCPT_NALUs:      result.append(u"AVC_NALUs"); break;
        case AVCPT_END_SEQ:    result.append(u"AVC_end_seq"); break;
        default:               result.append(u"Unknown"); break;
        }
        return result;
    }

}
}
