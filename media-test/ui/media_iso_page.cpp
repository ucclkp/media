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
#include "ukive/views/tree/tree_source.h"
#include "ukive/views/tree/tree_node.h"
#include "ukive/views/list/linear_list_layouter.h"
#include "ukive/views/combo_box/combo_box.h"
#include "ukive/elements/texteditor_element.h"
#include "ukive/system/dialog/open_file_dialog.h"
#include "ukive/resources/layout_instantiator.h"

#include "media-test/resources/necro_resources_id.h"

#include "media/iso/iso_media_parser.h"
#include "media/iso/box/iso_box.h"


namespace media {

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
        layouter_ = new ukive::LinearListLayouter();
        tree_source_ = new ukive::TreeSource(layouter_);

        auto list_view = findViewById<ukive::ListView>(v, Res::Id::lv_media_iso_info_list);
        list_view->setLayouter(layouter_);
        list_view->setSource(tree_source_);
        list_view->setSecDimUnknown(true);

        return v;
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
            tree_source_->clearNodes();
            parseSelectedFile();
        }
    }

    void MediaISOPage::onItemClicked(ukive::ListView* lv, ukive::ListItem* item) {
        int pos = item->data_pos;
        auto node = tree_source_->getNode(pos);
        if (node->is_expand) {
            node->is_expand = false;
        } else {
            node->is_expand = true;
        }
        tree_source_->notifyDataChanged();
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

            int rpos = tree_source_->addNodeByVP(-1, utl::UTF8ToUTF16(name_u8));

            traverseTree(rpos, box_ptr);
        }
    }

    void MediaISOPage::traverseTree(int parent_rpos, const std::shared_ptr<media::iso::Box>& parent) {
        auto& boxes = parent->getChildren();
        for (const auto& box_ptr : boxes) {
            uint32_t type = box_ptr->type;
            std::string name_u8;
            name_u8.push_back((type >> 24) & 0xFF);
            name_u8.push_back((type >> 16) & 0xFF);
            name_u8.push_back((type >> 8) & 0xFF);
            name_u8.push_back((type >> 0) & 0xFF);

            int rpos = tree_source_->addNodeByRP(parent_rpos, utl::UTF8ToUTF16(name_u8));

            traverseTree(rpos, box_ptr);
        }
    }

}
