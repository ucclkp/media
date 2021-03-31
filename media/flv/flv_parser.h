// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_FLV_FLV_PARSER_H_
#define MEDIA_FLV_FLV_PARSER_H_

#include <vector>

#include "flv.h"


namespace media {
namespace flv {

    /**
     * Adobe Flash Video File Format Specification
     * Version 10.1
     */
    class FLVParser {
    public:
        FLVParser();

        bool parse(std::istream& s, FLVHeader* header, std::vector<FLVTag>* tags);

    private:
        bool parseHeader(std::istream& s, FLVHeader* header);
        bool parseTag(std::istream& s, FLVTag* tag);
        bool parseAudioTagHeader(std::istream& s, AudioTagHeader* header);
        bool parseVideoTagHeader(std::istream& s, VideoTagHeader* header);
        bool parseEncryptionTagHeader(std::istream& s, EncryptionTagHeader* header, FilterParams* params);

        bool parseAudioData(std::istream& s, const FLVTag& tag, int64_t end, AUDIODATA* data);
        bool parseVideoData(std::istream& s, const FLVTag& tag, int64_t end, VIDEODATA* data);
        bool parseScriptData(std::istream& s, const FLVTag& tag, int64_t end, SCRIPTDATA* data);
    };

}
}

#endif  // MEDIA_FLV_FLV_PARSER_H_