// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "media-test/ui/media_window.h"

#include "ukive/elements/color_element.h"
#include "ukive/views/tab/tab_view.h"
#include "ukive/views/tab/tab_strip_view.h"

#include "media-test/ui/media_flv_page.h"
#include "media-test/ui/media_iso_page.h"
#include "media-test/resources/necro_resources_id.h"


namespace media {

    MediaWindow::MediaWindow()
        : Window() {}

    MediaWindow::~MediaWindow() {
    }

    void MediaWindow::onCreated() {
        Window::onCreated();

        setBackgroundColor(ukive::Color::Transparent);
        setContentView(Res::Layout::media_window_layout_xml);
        getContentView()->setBackground(new ukive::ColorElement(ukive::Color::White));
        showTitleBar();

        auto strip_view = findView<ukive::TabStripView>(Res::Id::tsv_media_strip);
        strip_view->setBackground(new ukive::ColorElement(ukive::Color::White));
        strip_view->setShadowRadius(getContext().dp2pxi(2));

        auto tab_view = findView<ukive::TabView>(Res::Id::tv_media_table);
        tab_view->setStripView(strip_view);

        tab_view->addPage(new MediaFLVPage(this), u"FLV");
        tab_view->addPage(new MediaISOPage(this), u"ISO");

        tab_view->setSelectedPage(1);
    }

    bool MediaWindow::onGetWindowIconName(std::u16string* icon_name, std::u16string* small_icon_name) const {
        return false;
    }

}
