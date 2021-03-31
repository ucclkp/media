// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "media-test/ui/media_flv_source.h"

#include "utils/log.h"
#include "utils/convert.h"
#include "utils/number.hpp"

#include "ukive/views/layout/restraint_layout.h"
#include "ukive/views/layout_info/restraint_layout_info.h"
#include "ukive/views/image_view.h"
#include "ukive/views/text_view.h"
#include "ukive/elements/color_element.h"
#include "ukive/graphics/color.h"
#include "ukive/window/window.h"


namespace media {

    ukive::ListItem* MediaFLVSource::onListCreateItem(
        ukive::LayoutView* parent, int position)
    {
        auto c = parent->getContext();

        auto layout = new ukive::RestraintLayout(c);
        layout->setLayoutSize(ukive::View::LS_FILL, ukive::View::LS_AUTO);
        layout->setLayoutMargin(c.dp2pxi(2), c.dp2pxi(2), c.dp2pxi(2), c.dp2pxi(2));

        using Rlp = ukive::RestraintLayoutInfo;

        ukive::TextView* title_label = new ukive::TextView(c);
        title_label->setId(ID_TITLE);
        title_label->setFontFamilyName(u"Consolas");
        title_label->setLayoutSize(ukive::View::LS_FILL, ukive::View::LS_AUTO);
        title_label->setLayoutMargin(c.dp2pxi(16), c.dp2pxi(8), c.dp2pxi(8), 0);
        Rlp* tl_lp = new Rlp();
        tl_lp->startHandle(layout->getId(), Rlp::START);
        tl_lp->topHandle(layout->getId(), Rlp::TOP);
        tl_lp->endHandle(layout->getId(), Rlp::END);
        layout->addView(title_label, tl_lp);

        ukive::TextView* summary_label = new ukive::TextView(c);
        summary_label->setId(ID_SUMMARY);
        summary_label->setFontFamilyName(u"Consolas");
        summary_label->setLayoutSize(ukive::View::LS_FILL, ukive::View::LS_AUTO);
        summary_label->setLayoutMargin(c.dp2pxi(16), c.dp2pxi(4), c.dp2pxi(8), c.dp2pxi(8));
        Rlp* sl_lp = new Rlp();
        sl_lp->startHandle(layout->getId(), Rlp::START);
        sl_lp->topHandle(ID_TITLE, Rlp::BOTTOM);
        sl_lp->endHandle(layout->getId(), Rlp::END);
        sl_lp->bottomHandle(layout->getId(), Rlp::BOTTOM);
        layout->addView(summary_label, sl_lp);

        return new FLVListItem(layout);
    }

    void MediaFLVSource::onListSetItemData(ukive::ListItem* item, int position) {
        auto& data = data_list_.at(position);
        FLVListItem* flv_list_item = reinterpret_cast<FLVListItem*>(item);

        flv_list_item->title_label->setText(data.title);
        flv_list_item->summary_label->setText(data.summary);

        auto bg = flv_list_item->item_view->getBackground();
        if (bg) {
            static_cast<ukive::ColorElement*>(bg)->setColor(data.color);
            flv_list_item->item_view->requestDraw();
        } else {
            flv_list_item->item_view->setBackground(new ukive::ColorElement(data.color));
        }

        //LOG(INFO) << "ListSource::onListSetItemData():" << position << " data has been bound.";
    }

    int MediaFLVSource::onListGetDataCount() {
        return utl::num_cast<int>(data_list_.size());
    }

    void MediaFLVSource::addItem(
        const ukive::Color& c, const std::u16string& title, const std::u16string& summary)
    {
        BindData data ;
        data.color = c;
        data.title = title;
        data.summary = summary;

        data_list_.push_back(data);
    }

    void MediaFLVSource::addItem(
        int pos, const ukive::Color& c, const std::u16string& title, const std::u16string& summary)
    {
        BindData data;
        data.color = c;
        data.title = title;
        data.summary = summary;

        if (data_list_.size() == 0)
            data_list_.push_back(data);
        else {
            int index = 0;
            for (auto it = data_list_.begin();
                it != data_list_.end(); ++it, ++index) {
                if (pos == index) {
                    data_list_.insert(it, data);
                    break;
                }
            }
        }
    }

    void MediaFLVSource::modifyItem(
        const ukive::Color& c, const std::u16string& title, const std::u16string& summary)
    {
        for (auto it = data_list_.begin();
            it != data_list_.end(); ++it) {
            if ((*it).title == title) {
                (*it).color = c;
                (*it).summary = summary;
            }
        }
    }

    void MediaFLVSource::removeItem(const std::u16string& title) {
        for (auto it = data_list_.begin();
            it != data_list_.end();) {
            if ((*it).title == title) {
                it = data_list_.erase(it);
            } else {
                ++it;
            }
        }
    }

    void MediaFLVSource::removeItem(int pos) {
        int index = 0;
        for (auto it = data_list_.begin();
            it != data_list_.end(); ++index, ++it) {
            if (index == pos) {
                data_list_.erase(it);
                break;
            }
        }
    }

    void MediaFLVSource::clear() {
        data_list_.clear();
    }

}