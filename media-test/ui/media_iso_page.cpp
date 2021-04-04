// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "media-test/ui/media_iso_page.h"

#include "utils/convert.h"

#include "ukive/views/button.h"
#include "ukive/views/text_view.h"
#include "ukive/views/image_view.h"
#include "ukive/elements/color_element.h"
#include "ukive/graphics/color.h"
#include "ukive/views/tree/tree_node.h"
#include "ukive/views/tree/tree_node_button.h"
#include "ukive/views/list/linear_list_layouter.h"
#include "ukive/views/combo_box.h"
#include "ukive/elements/texteditor_element.h"
#include "ukive/system/dialog/open_file_dialog.h"
#include "ukive/resources/layout_instantiator.h"
#include "ukive/views/layout/restraint_layout.h"
#include "ukive/views/layout_info/restraint_layout_info.h"

#include "media-test/resources/necro_resources_id.h"

#include "media/iso/iso_media_parser.h"
#include "media/iso/box/iso_box.h"


namespace media {

    // ExampleTreeItem
    ISOTreeItem::ISOTreeItem(ukive::View* v)
        : ListItem(v) {}

    MediaISOPage::MediaISOPage(ukive::Window* w)
        : Page(w) {}

    ukive::View* MediaISOPage::onCreate(ukive::LayoutView* parent) {
        auto v = ukive::LayoutInstantiator::from(
            parent->getContext(), parent, Res::Layout::media_iso_page_layout_xml);

        // Buttons
        browser_button_ = findViewById<ukive::Button>(v, Res::Id::bt_media_iso_browser_button);
        browser_button_->setOnClickListener(this);

        parse_button_ = findViewById<ukive::Button>(v, Res::Id::bt_media_iso_parse_button);
        parse_button_->setOnClickListener(this);

        path_tv_ = findViewById<ukive::TextView>(v, Res::Id::tv_media_iso_file_path);
        path_tv_->setBackground(new ukive::TextEditorElement(parent->getContext()));

        // ListView
        list_view_ = findViewById<ukive::ListView>(v, Res::Id::lv_media_iso_info_list);
        list_view_->setLayouter(new ukive::LinearListLayouter());
        list_view_->setSource(this);
        list_view_->setSecDimUnknown(true);
        list_view_->setItemEventRouter(new ukive::ListItemEventRouter(this));

        root_node_.setExpanded(true);
        return v;
    }

    ukive::ListItem* MediaISOPage::onCreateListItem(
        ukive::LayoutView* parent, ukive::ListItemEventRouter* router, size_t position)
    {
        auto c = parent->getContext();

        auto layout = new ukive::RestraintLayout(c);
        layout->setLayoutSize(ukive::View::LS_AUTO, ukive::View::LS_AUTO);

        using Rlp = ukive::RestraintLayoutInfo;

        auto expand_btn = new ukive::TreeNodeButton(c);
        expand_btn->setPadding(c.dp2pxi(2), c.dp2pxi(2), c.dp2pxi(2), c.dp2pxi(2));
        expand_btn->setLayoutSize(ukive::View::LS_AUTO, ukive::View::LS_AUTO);
        auto eb_lp = Rlp::Builder()
            .start(layout->getId())
            .top(layout->getId())
            .bottom(layout->getId())
            .build();
        expand_btn->setExtraLayoutInfo(eb_lp);
        layout->addView(expand_btn);

        auto avatar_view = new ukive::ImageView(c);
        avatar_view->setImage({});
        avatar_view->setLayoutSize(c.dp2pxi(12), c.dp2pxi(12));
        avatar_view->setLayoutMargin(c.dp2pxi(2), c.dp2pxi(2), 0, c.dp2pxi(2));
        Rlp* av_lp = new Rlp();
        av_lp->startHandle(expand_btn->getId(), Rlp::END);
        av_lp->topHandle(layout->getId(), Rlp::TOP);
        av_lp->bottomHandle(layout->getId(), Rlp::BOTTOM);
        avatar_view->setExtraLayoutInfo(av_lp);
        layout->addView(avatar_view);

        auto title_label = new ukive::TextView(c);
        title_label->setFontFamilyName(u"Consolas");
        title_label->setTextSize(c.dp2pxi(13));
        title_label->setClickable(true);
        title_label->setDoubleClickable(true);
        title_label->setPadding(c.dp2pxi(2), c.dp2pxi(2), c.dp2pxi(2), c.dp2pxi(2));
        title_label->setLayoutSize(ukive::View::LS_FILL, ukive::View::LS_AUTO);
        Rlp* tl_lp = new Rlp();
        tl_lp->startHandle(avatar_view->getId(), Rlp::END);
        tl_lp->endHandle(layout->getId(), Rlp::END);
        tl_lp->topHandle(layout->getId(), Rlp::TOP);
        tl_lp->bottomHandle(layout->getId(), Rlp::BOTTOM);
        title_label->setExtraLayoutInfo(tl_lp);
        layout->addView(title_label);

        auto root = new ISOTreeItem(layout);
        root->avatar_image = avatar_view;
        root->text_label = title_label;
        root->expand_button_ = expand_btn;

        return root;
    }

    void MediaISOPage::onSetListItemData(
        ukive::LayoutView* parent, ukive::ListItemEventRouter* router,
        ukive::ListItem* item)
    {
        auto node = static_cast<ISOTreeNode*>(
            root_node_.getExpandedDescendantAt(item->data_pos));
        auto tree_item = static_cast<ISOTreeItem*>(item);

        tree_item->expand_button_->setOnClickListener(router);
        tree_item->text_label->setOnClickListener(router);

        tree_item->ex_margins.start = node->getLevel() * 16;
        tree_item->text_label->setText(node->text);

        if (node->getChildCount() == 0) {
            tree_item->expand_button_->setStatus(ukive::TreeNodeButton::NONE);
        }
        else {
            tree_item->expand_button_->setStatus(
                node->isExpanded() ? ukive::TreeNodeButton::EXPANDED : ukive::TreeNodeButton::COLLAPSED);
        }

        if (node->is_selected) {
            auto b = tree_item->text_label->getBackground();
            if (b) {
                static_cast<ukive::ColorElement*>(b)->setColor(ukive::Color::Blue300);
            }
            else {
                tree_item->text_label->setBackground(new ukive::ColorElement(ukive::Color::Blue300));
            }
        }
        else {
            auto b = tree_item->text_label->getBackground();
            if (b) {
                static_cast<ukive::ColorElement*>(b)->setColor(ukive::Color::Transparent);
            }
        }

        //LOG(INFO) << "ListSource::onListSetItemData():" << position << " data has been bound.";
    }

    size_t MediaISOPage::onGetListDataCount(ukive::LayoutView* parent) const {
        return root_node_.getExpandedDescendantCount();
    }

    void MediaISOPage::onClick(ukive::View* v) {
        if (v == browser_button_) {
            std::unique_ptr<ukive::OpenFileDialog> dialog(ukive::OpenFileDialog::create());
            dialog->addType(u"*.mp4", u"ISO媒体文件");
            dialog->addType(u"*.*", u"所有文件");
            if (dialog->show(getWindow(), 0) == 1) {
                auto& files = dialog->getSelectedFiles();
                if (!files.empty()) {
                    iso_file_path_ = files.front();
                    path_tv_->setText(iso_file_path_);
                }
            }
        } else if (parse_button_ == v) {
            root_node_.removeAllNodes();
            notifyDataChanged();
            parseSelectedFile();
        }
    }

    void MediaISOPage::onDoubleClick(ukive::View* v) {
    }

    void MediaISOPage::onItemClicked(
        ukive::ListView* list_view, ukive::ListItem* item, ukive::View* v)
    {
        auto tree_item = static_cast<ISOTreeItem*>(item);
        if (v == tree_item->expand_button_) {
            auto node = root_node_.getExpandedDescendantAt(item->data_pos);
            node->setExpanded(!node->isExpanded());
            notifyDataChanged();
        }
        else if (v == tree_item->text_label) {
            auto node = static_cast<ISOTreeNode*>(
                root_node_.getExpandedDescendantAt(item->data_pos));
            node->is_selected = true;
            if (selected_node_ && selected_node_ != node) {
                static_cast<ISOTreeNode*>(selected_node_)->is_selected = false;
            }
            selected_node_ = node;
            notifyDataChanged();
        }
    }

    void MediaISOPage::onItemDoubleClicked(
        ukive::ListView* list_view, ukive::ListItem* item, ukive::View* v)
    {
        auto tree_item = static_cast<ISOTreeItem*>(item);
        if (v == tree_item->text_label) {
            auto node = root_node_.getExpandedDescendantAt(item->data_pos);
            node->setExpanded(!node->isExpanded());
            notifyDataChanged();
        }
    }

    void MediaISOPage::parseSelectedFile() {
        std::ifstream file(std::filesystem::path(iso_file_path_), std::ios::binary);
        if (!file) {
            return;
        }
        media::iso::ISOMediaParser iso_parser(file);
        if (!iso_parser.parse()) {
            return;
        }

        auto& boxes = iso_parser.getBoxes();
        for (const auto& box_ptr : boxes) {
            uint32_t type = box_ptr->type;
            std::string name_u8;
            name_u8.push_back((type >> 24) & 0xFF);
            name_u8.push_back((type >> 16) & 0xFF);
            name_u8.push_back((type >> 8) & 0xFF);
            name_u8.push_back((type >> 0) & 0xFF);

            ISOTreeNode* node = new ISOTreeNode();
            node->text = utl::UTF8ToUTF16(name_u8);
            root_node_.addNode(node);

            traverseTree(node, box_ptr);
        }

        notifyDataChanged();
    }

    void MediaISOPage::traverseTree(
        ukive::TreeNode* parent_node,
        const std::shared_ptr<media::iso::Box>& parent)
    {
        auto& boxes = parent->getChildren();
        for (const auto& box_ptr : boxes) {
            uint32_t type = box_ptr->type;
            std::string name_u8;
            name_u8.push_back((type >> 24) & 0xFF);
            name_u8.push_back((type >> 16) & 0xFF);
            name_u8.push_back((type >> 8) & 0xFF);
            name_u8.push_back((type >> 0) & 0xFF);

            ISOTreeNode* node = new ISOTreeNode();
            node->text = utl::UTF8ToUTF16(name_u8);
            parent_node->addNode(node);

            traverseTree(node, box_ptr);
        }
    }

}
