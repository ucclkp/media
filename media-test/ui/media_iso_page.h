// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_TEST_UI_MEDIA_ISO_PAGE_H_
#define MEDIA_TEST_UI_MEDIA_ISO_PAGE_H_

#include "ukive/page/page.h"
#include "ukive/views/click_listener.h"
#include "ukive/views/list/list_item.h"
#include "ukive/views/list/list_item_event_router.h"
#include "ukive/views/list/list_view.h"
#include "ukive/views/tree/tree_node.h"


namespace ukive {
    class Button;
    class CheckBox;
    class ImageView;
    class ListView;
    class TextView;
    class TreeSource;
    class LinearListLayouter;
    class TreeNodeButton;
}

namespace media {
namespace iso {
    class Box;
}

    class ISOTreeItem : public ukive::ListItem {
    public:
        explicit ISOTreeItem(ukive::View* v);

        ukive::TextView* text_label = nullptr;
        ukive::ImageView* avatar_image = nullptr;
        ukive::TreeNodeButton* expand_button_ = nullptr;
    };

    class ISOTreeNode : public ukive::TreeNode {
    public:
        int image_rid = 0;
        std::u16string text;
        bool is_selected = false;
    };


    class MediaISOPage :
        public ukive::Page,
        public ukive::ListSource,
        public ukive::ListItemEventListener,
        public ukive::OnClickListener
    {
    public:
        explicit MediaISOPage(ukive::Window* w);

        // ukive::Page
        ukive::View* onCreate(ukive::LayoutView* parent) override;

        // ukive::ListSource
        ukive::ListItem* onCreateListItem(
            ukive::LayoutView* parent, ukive::ListItemEventRouter* router,
            size_t position) override;
        void onSetListItemData(
            ukive::LayoutView* parent, ukive::ListItemEventRouter* router,
            ukive::ListItem* item) override;
        size_t onGetListDataCount(ukive::LayoutView* parent) const override;

        // ukive::OnClickListener
        void onClick(ukive::View* v) override;
        void onDoubleClick(ukive::View* v) override;

        // ukive::ListItemEventListener
        void onItemClicked(
            ukive::ListView* list_view, ukive::ListItem* item, ukive::View* v) override;
        void onItemDoubleClicked(
            ukive::ListView* list_view, ukive::ListItem* item, ukive::View* v) override;

    private:
        void parseSelectedFile();
        void traverseTree(
            ukive::TreeNode* parent_node,
            const std::shared_ptr<media::iso::Box>& parent);

        ukive::Button* browser_button_ = nullptr;
        ukive::Button* parse_button_ = nullptr;
        ukive::TextView* path_tv_ = nullptr;

        std::u16string iso_file_path_;
        ukive::ListView* list_view_ = nullptr;

        ukive::TreeNode root_node_;
        ukive::TreeNode* selected_node_ = nullptr;
    };

}

#endif  // MEDIA_TEST_UI_MEDIA_ISO_PAGE_H_