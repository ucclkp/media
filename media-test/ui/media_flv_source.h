// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_TEST_UI_MEDIA_FLV_SOURCE_H_
#define MEDIA_TEST_UI_MEDIA_FLV_SOURCE_H_

#include <vector>

#include "ukive/views/list/list_item.h"
#include "ukive/views/list/list_source.h"
#include "ukive/graphics/colors/color.h"


namespace ukive {
    class TextView;
    class ImageView;
}

namespace media {

    static const int ID_TITLE = 1;
    static const int ID_SUMMARY = 2;
    static const int ID_AVATAR = 3;

    class FLVListItem : public ukive::ListItem
    {
    public:
        explicit FLVListItem(ukive::View* v);

        ukive::TextView* title_label;
        ukive::TextView* summary_label;
        ukive::ImageView* avatar_image;
    };

    class MediaFLVSource : public ukive::ListSource
    {
    public:
        struct BindData {
            ukive::Color color;
            std::u16string title;
            std::u16string summary;
        };

        ukive::ListItem* onCreateListItem(
            ukive::LayoutView* parent, ukive::ListItemEventRouter* router,
            size_t position) override;
        void onSetListItemData(
            ukive::LayoutView* parent, ukive::ListItemEventRouter* router,
            ukive::ListItem* item) override;
        size_t onGetListDataCount(ukive::LayoutView* parent) const override;

        void addItem(
            const ukive::Color& c,
            const std::u16string_view& title,
            const std::u16string_view& summary);
        void addItem(
            size_t pos,
            const ukive::Color& c,
            const std::u16string_view& title,
            const std::u16string_view& summary);
        void modifyItem(
            const ukive::Color& c,
            const std::u16string_view& title,
            const std::u16string_view& summary);
        void removeItem(const std::u16string_view& title);
        void removeItem(size_t pos);
        void clear();

    private:
        std::vector<BindData> data_list_;
    };

}

#endif  // MEDIA_TEST_UI_MEDIA_FLV_SOURCE_H_