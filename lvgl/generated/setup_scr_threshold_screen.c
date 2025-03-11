/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_threshold_screen(lv_ui *ui)
{
    //Write codes threshold_screen
    ui->threshold_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->threshold_screen, 280, 240);
    lv_obj_set_scrollbar_mode(ui->threshold_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for threshold_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_slider_humi
    ui->threshold_screen_slider_humi = lv_slider_create(ui->threshold_screen);
    lv_slider_set_range(ui->threshold_screen_slider_humi, 0, 100);
    lv_slider_set_mode(ui->threshold_screen_slider_humi, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->threshold_screen_slider_humi, threshold_data.humi, LV_ANIM_OFF);
    lv_obj_set_pos(ui->threshold_screen_slider_humi, 61, 64);
    lv_obj_set_size(ui->threshold_screen_slider_humi, 160, 8);

    //Write style for threshold_screen_slider_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_humi, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_humi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_humi, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->threshold_screen_slider_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_slider_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_humi, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_humi, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_humi, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_humi, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_humi, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_humi, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_humi, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_humi, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_humi, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_humi, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes threshold_screen_slider_temp
    ui->threshold_screen_slider_temp = lv_slider_create(ui->threshold_screen);
    lv_slider_set_range(ui->threshold_screen_slider_temp, 0, 100);
    lv_slider_set_mode(ui->threshold_screen_slider_temp, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->threshold_screen_slider_temp, threshold_data.temp, LV_ANIM_OFF);
    lv_obj_set_pos(ui->threshold_screen_slider_temp, 61, 109);
    lv_obj_set_size(ui->threshold_screen_slider_temp, 160, 8);

    //Write style for threshold_screen_slider_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_temp, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_temp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_temp, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->threshold_screen_slider_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_slider_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_temp, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_temp, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_temp, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_temp, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_temp, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_temp, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_temp, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_temp, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_temp, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_temp, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes threshold_screen_slider_mq2
    ui->threshold_screen_slider_mq2 = lv_slider_create(ui->threshold_screen);
    lv_slider_set_range(ui->threshold_screen_slider_mq2, 0, 100);
    lv_slider_set_mode(ui->threshold_screen_slider_mq2, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->threshold_screen_slider_mq2, threshold_data.mq2, LV_ANIM_OFF);
    lv_obj_set_pos(ui->threshold_screen_slider_mq2, 61, 154);
    lv_obj_set_size(ui->threshold_screen_slider_mq2, 160, 8);

    //Write style for threshold_screen_slider_mq2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_mq2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_mq2, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_mq2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_mq2, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->threshold_screen_slider_mq2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_slider_mq2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_mq2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_mq2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_mq2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_mq2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_mq2, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_mq2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_mq2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_mq2, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_mq2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_mq2, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes threshold_screen_slider_light
    ui->threshold_screen_slider_light = lv_slider_create(ui->threshold_screen);
    lv_slider_set_range(ui->threshold_screen_slider_light, 0, 100);
    lv_slider_set_mode(ui->threshold_screen_slider_light, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->threshold_screen_slider_light, threshold_data.light, LV_ANIM_OFF);
    lv_obj_set_pos(ui->threshold_screen_slider_light, 61, 199);
    lv_obj_set_size(ui->threshold_screen_slider_light, 160, 8);

    //Write style for threshold_screen_slider_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_light, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_light, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_light, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->threshold_screen_slider_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_slider_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_light, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_light, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_light, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_light, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_light, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for threshold_screen_slider_light, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_slider_light, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->threshold_screen_slider_light, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->threshold_screen_slider_light, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_slider_light, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes threshold_screen_btn_1
    ui->threshold_screen_btn_1 = lv_btn_create(ui->threshold_screen);
    ui->threshold_screen_btn_1_label = lv_label_create(ui->threshold_screen_btn_1);
    lv_label_set_text(ui->threshold_screen_btn_1_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->threshold_screen_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->threshold_screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->threshold_screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->threshold_screen_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->threshold_screen_btn_1, 9, 7);
    lv_obj_set_size(ui->threshold_screen_btn_1, 50, 50);

    //Write style for threshold_screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->threshold_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->threshold_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_btn_1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_1
    ui->threshold_screen_label_1 = lv_label_create(ui->threshold_screen);
    lv_label_set_text(ui->threshold_screen_label_1, "阈值设置\n");
    lv_label_set_long_mode(ui->threshold_screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_1, 92, 17);
    lv_obj_set_size(ui->threshold_screen_label_1, 95, 16);

    //Write style for threshold_screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_1, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_2
    ui->threshold_screen_label_2 = lv_label_create(ui->threshold_screen);
    lv_label_set_text(ui->threshold_screen_label_2, "温度");
    lv_label_set_long_mode(ui->threshold_screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_2, 9, 57);
    lv_obj_set_size(ui->threshold_screen_label_2, 46, 16);

    //Write style for threshold_screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_2, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_3
    ui->threshold_screen_label_3 = lv_label_create(ui->threshold_screen);
    lv_label_set_text(ui->threshold_screen_label_3, "烟雾");
    lv_label_set_long_mode(ui->threshold_screen_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_3, 9, 149);
    lv_obj_set_size(ui->threshold_screen_label_3, 46, 16);

    //Write style for threshold_screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_3, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_4
    ui->threshold_screen_label_4 = lv_label_create(ui->threshold_screen);
    lv_label_set_text(ui->threshold_screen_label_4, "湿度");
    lv_label_set_long_mode(ui->threshold_screen_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_4, 9, 104);
    lv_obj_set_size(ui->threshold_screen_label_4, 46, 16);

    //Write style for threshold_screen_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_4, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_5
    ui->threshold_screen_label_5 = lv_label_create(ui->threshold_screen);
    lv_label_set_text(ui->threshold_screen_label_5, "光照");
    lv_label_set_long_mode(ui->threshold_screen_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_5, 9, 194);
    lv_obj_set_size(ui->threshold_screen_label_5, 46, 16);

    //Write style for threshold_screen_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_5, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_6
    ui->threshold_screen_label_6 = lv_label_create(ui->threshold_screen);
    lv_label_set_text_fmt(ui->threshold_screen_label_6, "%d%%", threshold_data.humi);
    lv_label_set_long_mode(ui->threshold_screen_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_6, 229, 60);
    lv_obj_set_size(ui->threshold_screen_label_6, 46, 16);

    //Write style for threshold_screen_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_6, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_7
    ui->threshold_screen_label_7 = lv_label_create(ui->threshold_screen);
    lv_label_set_text_fmt(ui->threshold_screen_label_7, "%d%%", threshold_data.temp);
    lv_label_set_long_mode(ui->threshold_screen_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_7, 229, 104);
    lv_obj_set_size(ui->threshold_screen_label_7, 46, 16);

    //Write style for threshold_screen_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_7, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_8
    ui->threshold_screen_label_8 = lv_label_create(ui->threshold_screen);
    lv_label_set_text_fmt(ui->threshold_screen_label_8, "%d%%", threshold_data.mq2);
    lv_label_set_long_mode(ui->threshold_screen_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_8, 229, 149);
    lv_obj_set_size(ui->threshold_screen_label_8, 46, 16);

    //Write style for threshold_screen_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_8, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes threshold_screen_label_9
    ui->threshold_screen_label_9 = lv_label_create(ui->threshold_screen);
    lv_label_set_text_fmt(ui->threshold_screen_label_9, "%d%%", threshold_data.light);
    lv_label_set_long_mode(ui->threshold_screen_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->threshold_screen_label_9, 229, 194);
    lv_obj_set_size(ui->threshold_screen_label_9, 46, 16);

    //Write style for threshold_screen_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->threshold_screen_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->threshold_screen_label_9, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->threshold_screen_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->threshold_screen_label_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->threshold_screen_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->threshold_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of threshold_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->threshold_screen);

    //Init events for screen.
    events_init_threshold_screen(ui);
}
