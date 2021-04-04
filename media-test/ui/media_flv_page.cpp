// Copyright (c) 2020 ucclkp <ucclkp@gmail.com>.
// This file is part of media project.
//
// This program is licensed under GPLv3 license that can be
// found in the LICENSE file.

#include "media-test/ui/media_flv_page.h"

#include <fstream>

#include "utils/convert.h"
#include "utils/endian.hpp"

#include "ukive/views/button.h"
#include "ukive/views/text_view.h"
#include "ukive/views/image_view.h"
#include "ukive/graphics/color.h"
#include "ukive/views/list/list_view.h"
#include "ukive/elements/color_element.h"
#include "ukive/graphics/color.h"
#include "ukive/views/list/grid_list_layouter.h"
#include "ukive/views/list/flow_list_layouter.h"
#include "ukive/views/list/linear_list_layouter.h"
#include "ukive/views/combo_box.h"
#include "ukive/elements/texteditor_element.h"
#include "ukive/system/dialog/open_file_dialog.h"
#include "ukive/resources/layout_instantiator.h"

#include "media-test/ui/media_flv_source.h"
#include "media-test/resources/necro_resources_id.h"

#include "media/flv/flv_parser.h"
#include "media/flv/flv_to_string.h"


namespace media {

    MediaFLVPage::MediaFLVPage(ukive::Window* w)
        : Page(w) {}

    ukive::View* MediaFLVPage::onCreate(ukive::LayoutView* parent) {
        auto v = ukive::LayoutInstantiator::from(
            parent->getContext(), parent, Res::Layout::media_flv_page_layout_xml);

        // Buttons
        browser_button_ = findViewById<ukive::Button>(v, Res::Id::bt_media_flv_browser_button);
        browser_button_->setOnClickListener(this);

        parse_button_ = findViewById<ukive::Button>(v, Res::Id::bt_media_flv_parse_button);
        parse_button_->setOnClickListener(this);

        path_tv_ = findViewById<ukive::TextView>(v, Res::Id::tv_media_flv_path);
        path_tv_->setBackground(new ukive::TextEditorElement(parent->getContext()));

        // ListView
        source_ = new MediaFLVSource();

        auto list_view = findViewById<ukive::ListView>(v, Res::Id::lv_media_flv_info_list);
        list_view->setLayouter(new ukive::LinearListLayouter());
        list_view->setSource(source_);

        return v;
    }

    void MediaFLVPage::onClick(ukive::View* v) {
        if (v == browser_button_) {
            std::unique_ptr<ukive::OpenFileDialog> dialog(ukive::OpenFileDialog::create());
            dialog->addType(u"*.flv", u"FLV文件");
            dialog->addType(u"*.*", u"所有文件");
            if (dialog->show(getWindow(), 0) == 1) {
                auto& files = dialog->getSelectedFiles();
                if (!files.empty()) {
                    flv_file_path_ = files.front();
                    path_tv_->setText(flv_file_path_);
                }
            }
        } else if (parse_button_ == v) {
            source_->clear();
            parseSelectedFile();
            generateH264File();
        }
    }

    void MediaFLVPage::parseSelectedFile() {
        std::ifstream file(std::filesystem::path(flv_file_path_), std::ios::binary);
        if (!file) {
            return;
        }

        media::flv::FLVParser parser;
        media::flv::FLVHeader header;
        std::vector<media::flv::FLVTag> tags;
        if (parser.parse(file, &header, &tags)) {
            uint32_t count = 0;
            for (const auto& tag : tags) {
                std::u16string title;
                title.append(utl::to_u16string(count)).append(u" ");
                title.append(media::flv::tagTypeToString(tag.tag_type));

                std::u16string summary;
                summary.append(tag.filter == 1 ? u"Encrypted " : u"");
                summary.append(u"ts:").append(utl::to_u16string(tag.timestamp)).append(u"ms");

                if (tag.tag_type == media::flv::TAG_VIDEO) {
                    summary.append(u" | ");
                    summary.append(media::flv::videoFrameTypeToString(tag.video_tag_header.frame_type)).append(u" ");
                    summary.append(media::flv::videoCodecIDToString(tag.video_tag_header.codec_id));
                    if (tag.video_tag_header.codec_id == media::flv::VCID_AVC) {
                        summary.append(u" | ");
                        summary.append(media::flv::videoAVCPacketTypeToString(tag.video_tag_header.avc_packet_type));
                        if (tag.video_tag_header.avc_packet_type == media::flv::AVCPT_NALUs) {
                            summary.append(u" | ");
                            summary.append(utl::to_u16string(tag.video_tag_header.composition_time)).append(u"ms");
                        }
                    }
                    source_->addItem(ukive::Color::Orange300, title, summary);
                } else if (tag.tag_type == media::flv::TAG_AUDIO) {
                    summary.append(u" | ");
                    summary.append(media::flv::soundFormatToString(tag.audio_tag_header.sound_format)).append(u" ");
                    summary.append(media::flv::soundRateToString(tag.audio_tag_header.sound_rate)).append(u" ");
                    summary.append(media::flv::soundSizeToString(tag.audio_tag_header.sound_size)).append(u" ");
                    summary.append(media::flv::soundTypeToString(tag.audio_tag_header.sound_type));
                    source_->addItem(ukive::Color::Blue300, title, summary);
                } else if (tag.tag_type == media::flv::TAG_SCRIPT) {
                    source_->addItem(ukive::Color::Yellow300, title, summary);
                } else {
                    // ???
                    source_->addItem(ukive::Color::Red100, title, summary);
                }

                ++count;
            }
        } else {
            source_->addItem(ukive::Color::Red300, u"ERROR", u"Cannot parse flv file.");
        }

        source_->notifyDataChanged();
    }

    void MediaFLVPage::generateH264File() {
        std::ifstream file(std::filesystem::path(flv_file_path_), std::ios::binary);
        if (!file) {
            return;
        }

        media::flv::FLVParser parser;
        media::flv::FLVHeader header;
        std::vector<media::flv::FLVTag> tags;
        if (parser.parse(file, &header, &tags)) {
            bool is_first = true;
            char buf[] = { 0x00,0x00,0x00,0x01 };
            std::ofstream h264_file(L"D:\\test.h264", std::ios::binary);

            for (const auto& tag : tags) {
                if (tag.filter == 1) {
                    return;
                }

                if (tag.tag_type == media::flv::TAG_VIDEO) {
                    if (tag.video_tag_header.codec_id == media::flv::VCID_AVC) {
                        if (tag.video_tag_header.avc_packet_type == media::flv::AVCPT_SEQ_HEADER)
                        {
                            auto& rec = tag.video_data.v_body.avcp.record;

                            // SPS
                            h264_file.write(buf, 4);
                            h264_file.write(
                                reinterpret_cast<char*>(rec.sps_nalus[0].nalu.get()),
                                rec.sps_nalus[0].length);

                            // PPS
                            h264_file.write(buf, 4);
                            h264_file.write(
                                reinterpret_cast<char*>(rec.pps_nalus[0].nalu.get()),
                                rec.pps_nalus[0].length);
                        } else if (tag.video_tag_header.avc_packet_type == media::flv::AVCPT_NALUs)
                        {
                            if (is_first) {
                                is_first = false;
                                auto& avcp = tag.video_data.v_body.avcp;

                                size_t cur = 0;
                                do {
                                    h264_file.write(buf, 4);
                                    uint32_t size = utl::fromToBE(
                                        *reinterpret_cast<uint32_t*>(avcp.nalus.get() + cur));
                                    cur += 4;
                                    h264_file.write(
                                        reinterpret_cast<char*>(avcp.nalus.get() + cur), size);
                                    cur += size;
                                } while (cur < avcp.length);
                            }
                        }
                    }
                } else if (tag.tag_type == media::flv::TAG_AUDIO) {

                }
            }
        }
    }
}
