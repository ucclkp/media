// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_TEST_UI_MEDIA_FLV_PAGE_H_
#define MEDIA_TEST_UI_MEDIA_FLV_PAGE_H_

#include "ukive/page/page.h"
#include "ukive/views/click_listener.h"


namespace ukive {
    class Button;
    class CheckBox;
    class ListView;
    class TextView;
}

namespace media {

    class MediaFLVSource;

    class MediaFLVPage :
        public ukive::Page, public ukive::OnClickListener
    {
    public:
        explicit MediaFLVPage(ukive::Window* w);

        // ukive::Page
        ukive::View* onCreate(ukive::LayoutView* parent) override;

        // ukive::OnClickListener
        void onClick(ukive::View* v) override;

    private:
        void parseSelectedFile();
        void generateH264File();

        ukive::Button* browser_button_ = nullptr;
        ukive::Button* parse_button_ = nullptr;
        ukive::TextView* path_tv_ = nullptr;

        std::u16string flv_file_path_;
        ukive::ListView* list_view_ = nullptr;
        MediaFLVSource* source_ = nullptr;
    };

}

#endif  // MEDIA_TEST_UI_MEDIA_FLV_PAGE_H_