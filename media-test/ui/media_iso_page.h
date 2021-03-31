// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_TEST_UI_MEDIA_ISO_PAGE_H_
#define MEDIA_TEST_UI_MEDIA_ISO_PAGE_H_

#include "ukive/page/page.h"
#include "ukive/views/click_listener.h"
#include "ukive/views/list/list_view.h"


namespace ukive {
    class Button;
    class CheckBox;
    class ListView;
    class TextView;
    class TreeSource;
    class LinearListLayouter;
}

namespace media {
namespace iso {
    class Box;
}

    class MediaFLVSource;

    class MediaISOPage :
        public ukive::Page,
        public ukive::OnClickListener,
        public ukive::ListItemSelectedListener
    {
    public:
        explicit MediaISOPage(ukive::Window* w);

        // ukive::Page
        ukive::View* onCreate(ukive::LayoutView* parent) override;

        // ukive::OnClickListener
        void onClick(ukive::View* v) override;

        // ukive::ListItemSelectedListener
        void onItemClicked(ukive::ListView* lv, ukive::ListItem* item) override;

    private:
        void parseSelectedFile();
        void traverseTree(int parent_rpos, const std::shared_ptr<media::iso::Box>& parent);

        ukive::Button* browser_button_ = nullptr;
        ukive::Button* parse_button_ = nullptr;
        ukive::TextView* path_tv_ = nullptr;

        std::u16string iso_file_path_;
        ukive::ListView* list_view_ = nullptr;
        ukive::TreeSource* tree_source_ = nullptr;
        ukive::LinearListLayouter* layouter_ = nullptr;
    };

}

#endif  // MEDIA_TEST_UI_MEDIA_ISO_PAGE_H_