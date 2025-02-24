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



void setup_scr_mqtt_param_screen(lv_ui *ui)
{
    //Write codes mqtt_param_screen
    ui->mqtt_param_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->mqtt_param_screen, 280, 240);
    lv_obj_set_scrollbar_mode(ui->mqtt_param_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for mqtt_param_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mqtt_param_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mqtt_param_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mqtt_param_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mqtt_param_screen_label_mqtt
    ui->mqtt_param_screen_label_mqtt = lv_label_create(ui->mqtt_param_screen);
    lv_label_set_text(ui->mqtt_param_screen_label_mqtt, "上报间隔");
    lv_label_set_long_mode(ui->mqtt_param_screen_label_mqtt, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mqtt_param_screen_label_mqtt, 2, 87);
    lv_obj_set_size(ui->mqtt_param_screen_label_mqtt, 81, 16);

    //Write style for mqtt_param_screen_label_mqtt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mqtt_param_screen_label_mqtt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mqtt_param_screen_label_mqtt, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mqtt_param_screen_label_mqtt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mqtt_param_screen_label_mqtt, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mqtt_param_screen_label_mqtt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mqtt_param_screen_label_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mqtt_param_screen_ddlist_mqtt
    ui->mqtt_param_screen_ddlist_mqtt = lv_dropdown_create(ui->mqtt_param_screen);
    lv_dropdown_set_options(ui->mqtt_param_screen_ddlist_mqtt, "5S\n10S\n20S\n30S\n60S");
    lv_obj_set_pos(ui->mqtt_param_screen_ddlist_mqtt, 83, 80);
    lv_obj_set_size(ui->mqtt_param_screen_ddlist_mqtt, 170, 31);

    //Write style for mqtt_param_screen_ddlist_mqtt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mqtt_param_screen_ddlist_mqtt, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mqtt_param_screen_ddlist_mqtt, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mqtt_param_screen_ddlist_mqtt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mqtt_param_screen_ddlist_mqtt, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mqtt_param_screen_ddlist_mqtt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mqtt_param_screen_ddlist_mqtt, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mqtt_param_screen_ddlist_mqtt, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mqtt_param_screen_ddlist_mqtt, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mqtt_param_screen_ddlist_mqtt, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mqtt_param_screen_ddlist_mqtt, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mqtt_param_screen_ddlist_mqtt, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mqtt_param_screen_ddlist_mqtt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mqtt_param_screen_ddlist_mqtt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mqtt_param_screen_ddlist_mqtt, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mqtt_param_screen_ddlist_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked
    static lv_style_t style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked;
    ui_init_style(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked);

    lv_style_set_border_width(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, lv_color_hex(0xbbc8c9));
    lv_style_set_bg_grad_dir(&style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->mqtt_param_screen_ddlist_mqtt), &style_mqtt_param_screen_ddlist_mqtt_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default
    static lv_style_t style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default;
    ui_init_style(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default);

    lv_style_set_max_height(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, 90);
    lv_style_set_text_color(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, 255);
    lv_style_set_border_width(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, 255);
    lv_style_set_border_color(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->mqtt_param_screen_ddlist_mqtt), &style_mqtt_param_screen_ddlist_mqtt_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default
    static lv_style_t style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default;
    ui_init_style(&style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default);

    lv_style_set_radius(&style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default, 2);
    lv_style_set_bg_opa(&style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default, 145);
    lv_style_set_bg_color(&style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default, lv_color_hex(0xacacac));
    lv_style_set_bg_grad_dir(&style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->mqtt_param_screen_ddlist_mqtt), &style_mqtt_param_screen_ddlist_mqtt_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes mqtt_param_screen_btn_mqtt_return
    ui->mqtt_param_screen_btn_mqtt_return = lv_btn_create(ui->mqtt_param_screen);
    ui->mqtt_param_screen_btn_mqtt_return_label = lv_label_create(ui->mqtt_param_screen_btn_mqtt_return);
    lv_label_set_text(ui->mqtt_param_screen_btn_mqtt_return_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->mqtt_param_screen_btn_mqtt_return_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mqtt_param_screen_btn_mqtt_return_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mqtt_param_screen_btn_mqtt_return, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mqtt_param_screen_btn_mqtt_return_label, LV_PCT(100));
    lv_obj_set_pos(ui->mqtt_param_screen_btn_mqtt_return, 9, 8);
    lv_obj_set_size(ui->mqtt_param_screen_btn_mqtt_return, 50, 50);

    //Write style for mqtt_param_screen_btn_mqtt_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mqtt_param_screen_btn_mqtt_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mqtt_param_screen_btn_mqtt_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mqtt_param_screen_btn_mqtt_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mqtt_param_screen_btn_mqtt_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mqtt_param_screen_btn_mqtt_return, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mqtt_param_screen_btn_mqtt_return, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mqtt_param_screen_btn_mqtt_return, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mqtt_param_screen_btn_mqtt_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mqtt_param_screen_btn_mqtt_enter
    ui->mqtt_param_screen_btn_mqtt_enter = lv_btn_create(ui->mqtt_param_screen);
    ui->mqtt_param_screen_btn_mqtt_enter_label = lv_label_create(ui->mqtt_param_screen_btn_mqtt_enter);
    lv_label_set_text(ui->mqtt_param_screen_btn_mqtt_enter_label, "确定");
    lv_label_set_long_mode(ui->mqtt_param_screen_btn_mqtt_enter_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mqtt_param_screen_btn_mqtt_enter_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mqtt_param_screen_btn_mqtt_enter, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mqtt_param_screen_btn_mqtt_enter_label, LV_PCT(100));
    lv_obj_set_pos(ui->mqtt_param_screen_btn_mqtt_enter, 89, 160);
    lv_obj_set_size(ui->mqtt_param_screen_btn_mqtt_enter, 102, 45);

    //Write style for mqtt_param_screen_btn_mqtt_enter, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mqtt_param_screen_btn_mqtt_enter, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mqtt_param_screen_btn_mqtt_enter, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mqtt_param_screen_btn_mqtt_enter, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mqtt_param_screen_btn_mqtt_enter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mqtt_param_screen_btn_mqtt_enter, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mqtt_param_screen_btn_mqtt_enter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mqtt_param_screen_btn_mqtt_enter, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mqtt_param_screen_btn_mqtt_enter, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mqtt_param_screen_btn_mqtt_enter, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mqtt_param_screen_btn_mqtt_enter, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of mqtt_param_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->mqtt_param_screen);

    //Init events for screen.
    events_init_mqtt_param_screen(ui);
}
