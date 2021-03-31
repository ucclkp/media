// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "utils/log.h"
#include "utils/platform_utils.h"

#include "ukive/app/application.h"

#include "media-test/ui/media_window.h"


GUI_MAIN()
{
    utl::Log::Params log_params;
    log_params.file_name = u"media-debug.log";
    log_params.short_file_name = false;
    log_params.target = utl::Log::OutputTarget::DEBUGGER | utl::Log::OutputTarget::FILE;
    utl::InitLogging(log_params);

    LOG(Log::INFO) << "media-test start.";

    ukive::Application::Options options;
    options.is_auto_dpi_scale = false;
    auto app = std::make_shared<ukive::Application>(options);

    auto media_window = std::make_shared<media::MediaWindow>();
    media_window->init(ukive::Window::InitParams());
    media_window->setTitle(u"Media");
    media_window->setWidth(ukive::Application::dp2pxi(600));
    media_window->setHeight(ukive::Application::dp2pxi(600));
    media_window->center();
    media_window->show();

    app->run();

    LOG(Log::INFO) << "media-test exit.\n";

    utl::UninitLogging();

    return 0;
}