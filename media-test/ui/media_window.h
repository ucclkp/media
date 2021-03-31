// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#ifndef MEDIA_TEST_UI_MEDIA_WINDOW_H_
#define MEDIA_TEST_UI_MEDIA_WINDOW_H_

#include "ukive/window/window.h"


namespace ukive {
    class Button;
    class ImageView;
    class CheckBox;
    class ListView;
    class TextView;
    class SpinnerView;
}

namespace media {

    class MediaWindow : public ukive::Window {
    public:
        MediaWindow();
        ~MediaWindow();

        // ukive::Window
        void onCreated() override;
        bool onGetWindowIconName(std::u16string* icon_name, std::u16string* small_icon_name) const override;
    };

}

#endif  // MEDIA_TEST_UI_MEDIA_WINDOW_H_