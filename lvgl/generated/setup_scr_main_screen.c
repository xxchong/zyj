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



void setup_scr_main_screen(lv_ui *ui)
{
    //Write codes main_screen
    ui->main_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->main_screen, 280, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_tabview_main
    ui->main_screen_tabview_main = lv_tabview_create(ui->main_screen, LV_DIR_TOP, 35);
    lv_obj_set_pos(ui->main_screen_tabview_main, 2, 0);
    lv_obj_set_size(ui->main_screen_tabview_main, 280, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen_tabview_main, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen_tabview_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_tabview_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_tabview_main, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_tabview_main, &lv_font_MiSansNormal_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_tabview_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_tabview_main, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_tabview_main, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_tabview_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_tabview_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_tabview_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_main_screen_tabview_main_extra_btnm_main_default
    static lv_style_t style_main_screen_tabview_main_extra_btnm_main_default;
    ui_init_style(&style_main_screen_tabview_main_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_main_screen_tabview_main_extra_btnm_main_default, 6);
    lv_style_set_bg_color(&style_main_screen_tabview_main_extra_btnm_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_main_screen_tabview_main_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_main_screen_tabview_main_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_main_screen_tabview_main_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->main_screen_tabview_main), &style_main_screen_tabview_main_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_main_screen_tabview_main_extra_btnm_items_default
    static lv_style_t style_main_screen_tabview_main_extra_btnm_items_default;
    ui_init_style(&style_main_screen_tabview_main_extra_btnm_items_default);

    lv_style_set_text_color(&style_main_screen_tabview_main_extra_btnm_items_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_main_screen_tabview_main_extra_btnm_items_default, &lv_font_MiSansNormal_15);
    lv_style_set_text_opa(&style_main_screen_tabview_main_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->main_screen_tabview_main), &style_main_screen_tabview_main_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_main_screen_tabview_main_extra_btnm_items_checked
    static lv_style_t style_main_screen_tabview_main_extra_btnm_items_checked;
    ui_init_style(&style_main_screen_tabview_main_extra_btnm_items_checked);

    lv_style_set_text_color(&style_main_screen_tabview_main_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_main_screen_tabview_main_extra_btnm_items_checked, &lv_font_MiSansNormal_15);
    lv_style_set_text_opa(&style_main_screen_tabview_main_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_main_screen_tabview_main_extra_btnm_items_checked, 2);
    lv_style_set_border_opa(&style_main_screen_tabview_main_extra_btnm_items_checked, 255);
    lv_style_set_border_color(&style_main_screen_tabview_main_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_border_side(&style_main_screen_tabview_main_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_main_screen_tabview_main_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_main_screen_tabview_main_extra_btnm_items_checked, 60);
    lv_style_set_bg_color(&style_main_screen_tabview_main_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_main_screen_tabview_main_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->main_screen_tabview_main), &style_main_screen_tabview_main_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes 首页
    ui->main_screen_tabview_main_tab_1 = lv_tabview_add_tab(ui->main_screen_tabview_main,"首页");
    lv_obj_t * main_screen_tabview_main_tab_1_label = lv_label_create(ui->main_screen_tabview_main_tab_1);
    lv_label_set_text(main_screen_tabview_main_tab_1_label, "");

    //Write codes main_screen_label_info
    ui->main_screen_label_info = lv_label_create(ui->main_screen_tabview_main_tab_1);
    lv_label_set_text(ui->main_screen_label_info, "基于STM32的博物馆监控系统");
    lv_label_set_long_mode(ui->main_screen_label_info, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_info, -16, -10);
    lv_obj_set_size(ui->main_screen_label_info, 269, 27);

    //Write style for main_screen_label_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_info, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_info, &lv_font_MiSansNormal_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_info, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_info, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_6
    ui->main_screen_label_6 = lv_label_create(ui->main_screen_tabview_main_tab_1);
    lv_label_set_text(ui->main_screen_label_6, "2025-02-24");
    lv_label_set_long_mode(ui->main_screen_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_6, 56, 78);
    lv_obj_set_size(ui->main_screen_label_6, 119, 23);

    //Write style for main_screen_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_5
    ui->main_screen_label_5 = lv_label_create(ui->main_screen_tabview_main_tab_1);
    lv_label_set_text(ui->main_screen_label_5, "17:02");
    lv_label_set_long_mode(ui->main_screen_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_5, 63, 46);
    lv_obj_set_size(ui->main_screen_label_5, 100, 32);

    //Write style for main_screen_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_5, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_7
    ui->main_screen_label_7 = lv_label_create(ui->main_screen_tabview_main_tab_1);
    lv_label_set_text(ui->main_screen_label_7, "张有金 202110264127");
    lv_label_set_long_mode(ui->main_screen_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_7, 29, 119);
    lv_obj_set_size(ui->main_screen_label_7, 188, 16);

    //Write style for main_screen_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_7, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes 数据
    ui->main_screen_tabview_main_tab_2 = lv_tabview_add_tab(ui->main_screen_tabview_main,"数据");
    lv_obj_t * main_screen_tabview_main_tab_2_label = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(main_screen_tabview_main_tab_2_label, "");

    //Write codes main_screen_label_humi_percentage
    ui->main_screen_label_humi_percentage = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_humi_percentage, "50%\n");
    lv_label_set_long_mode(ui->main_screen_label_humi_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_humi_percentage, 115, 125);
    lv_obj_set_size(ui->main_screen_label_humi_percentage, 35, 15);

    //Write style for main_screen_label_humi_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_humi_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_humi_percentage, &lv_font_MiSansNormal_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_humi_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_humi_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_humi_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_humi_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_bar_humi
    ui->main_screen_bar_humi = lv_bar_create(ui->main_screen_tabview_main_tab_2);
    lv_obj_set_style_anim_time(ui->main_screen_bar_humi, 1000, 0);
    lv_bar_set_mode(ui->main_screen_bar_humi, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->main_screen_bar_humi, 0, 100);
    lv_bar_set_value(ui->main_screen_bar_humi, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->main_screen_bar_humi, 15, 125);
    lv_obj_set_size(ui->main_screen_bar_humi, 100, 15);

    //Write style for main_screen_bar_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_bar_humi, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_bar_humi, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_bar_humi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_bar_humi, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_bar_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_bar_humi, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_bar_humi, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_bar_humi, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_bar_humi, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_bar_humi, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes main_screen_arc_fumes
    ui->main_screen_arc_fumes = lv_arc_create(ui->main_screen_tabview_main_tab_2);
    lv_arc_set_mode(ui->main_screen_arc_fumes, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->main_screen_arc_fumes, 0, 100);
    lv_arc_set_bg_angles(ui->main_screen_arc_fumes, 135, 45);
    lv_arc_set_value(ui->main_screen_arc_fumes, 70);
    lv_arc_set_rotation(ui->main_screen_arc_fumes, 0);
    lv_obj_set_pos(ui->main_screen_arc_fumes, 78, -6);
    lv_obj_set_size(ui->main_screen_arc_fumes, 80, 80);

    //Write style for main_screen_arc_fumes, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->main_screen_arc_fumes, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->main_screen_arc_fumes, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->main_screen_arc_fumes, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_arc_fumes, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_arc_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_arc_fumes, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->main_screen_arc_fumes, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->main_screen_arc_fumes, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->main_screen_arc_fumes, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for main_screen_arc_fumes, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_arc_fumes, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_arc_fumes, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_arc_fumes, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->main_screen_arc_fumes, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes main_screen_arc_light
    ui->main_screen_arc_light = lv_arc_create(ui->main_screen_tabview_main_tab_2);
    lv_arc_set_mode(ui->main_screen_arc_light, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->main_screen_arc_light, 0, 100);
    lv_arc_set_bg_angles(ui->main_screen_arc_light, 135, 45);
    lv_arc_set_value(ui->main_screen_arc_light, 50);
    lv_arc_set_rotation(ui->main_screen_arc_light, 0);
    lv_obj_set_pos(ui->main_screen_arc_light, -6, -5);
    lv_obj_set_size(ui->main_screen_arc_light, 80, 80);

    //Write style for main_screen_arc_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->main_screen_arc_light, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->main_screen_arc_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->main_screen_arc_light, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_arc_light, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_arc_light, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->main_screen_arc_light, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->main_screen_arc_light, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->main_screen_arc_light, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for main_screen_arc_light, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_arc_light, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_arc_light, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_arc_light, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->main_screen_arc_light, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes main_screen_label_light_percentage
    ui->main_screen_label_light_percentage = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_light_percentage, "100%\n");
    lv_label_set_long_mode(ui->main_screen_label_light_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_light_percentage, 10, 25);
    lv_obj_set_size(ui->main_screen_label_light_percentage, 48, 17);

    //Write style for main_screen_label_light_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_light_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_light_percentage, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_light_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_light_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_light_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_light_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_temp_percentage
    ui->main_screen_label_temp_percentage = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_temp_percentage, "50%");
    lv_label_set_long_mode(ui->main_screen_label_temp_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_temp_percentage, 114, 103);
    lv_obj_set_size(ui->main_screen_label_temp_percentage, 36, 12);

    //Write style for main_screen_label_temp_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_temp_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_temp_percentage, &lv_font_MiSansNormal_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_temp_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_temp_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_temp_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_temp_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_vibration_percentage
    ui->main_screen_label_vibration_percentage = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_vibration_percentage, "100%\n");
    lv_label_set_long_mode(ui->main_screen_label_vibration_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_vibration_percentage, 180, 22);
    lv_obj_set_size(ui->main_screen_label_vibration_percentage, 50, 17);

    //Write style for main_screen_label_vibration_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_vibration_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_vibration_percentage, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_vibration_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_vibration_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_vibration_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_vibration_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_bar_temp
    ui->main_screen_bar_temp = lv_bar_create(ui->main_screen_tabview_main_tab_2);
    lv_obj_set_style_anim_time(ui->main_screen_bar_temp, 1000, 0);
    lv_bar_set_mode(ui->main_screen_bar_temp, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->main_screen_bar_temp, 0, 100);
    lv_bar_set_value(ui->main_screen_bar_temp, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->main_screen_bar_temp, 16, 101);
    lv_obj_set_size(ui->main_screen_bar_temp, 100, 15);

    //Write style for main_screen_bar_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_bar_temp, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_bar_temp, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_bar_temp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_bar_temp, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_bar_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_bar_temp, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_bar_temp, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_bar_temp, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_bar_temp, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_bar_temp, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes main_screen_arc_vibration
    ui->main_screen_arc_vibration = lv_arc_create(ui->main_screen_tabview_main_tab_2);
    lv_arc_set_mode(ui->main_screen_arc_vibration, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->main_screen_arc_vibration, 0, 100);
    lv_arc_set_bg_angles(ui->main_screen_arc_vibration, 135, 45);
    lv_arc_set_value(ui->main_screen_arc_vibration, 100);
    lv_arc_set_rotation(ui->main_screen_arc_vibration, 0);
    lv_obj_set_pos(ui->main_screen_arc_vibration, 164, -9);
    lv_obj_set_size(ui->main_screen_arc_vibration, 80, 80);

    //Write style for main_screen_arc_vibration, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->main_screen_arc_vibration, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->main_screen_arc_vibration, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->main_screen_arc_vibration, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_arc_vibration, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_arc_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_arc_vibration, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->main_screen_arc_vibration, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->main_screen_arc_vibration, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->main_screen_arc_vibration, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for main_screen_arc_vibration, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_arc_vibration, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_arc_vibration, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_arc_vibration, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->main_screen_arc_vibration, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes main_screen_label_light
    ui->main_screen_label_light = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_light, "光敏强度");
    lv_label_set_long_mode(ui->main_screen_label_light, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_light, -2, 67);
    lv_obj_set_size(ui->main_screen_label_light, 73, 17);

    //Write style for main_screen_label_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_light, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_light, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_light, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_light, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_fumes_percentage
    ui->main_screen_label_fumes_percentage = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_fumes_percentage, "100%\n");
    lv_label_set_long_mode(ui->main_screen_label_fumes_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_fumes_percentage, 93, 23);
    lv_obj_set_size(ui->main_screen_label_fumes_percentage, 51, 17);

    //Write style for main_screen_label_fumes_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_fumes_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_fumes_percentage, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_fumes_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_fumes_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_fumes_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_fumes_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_fumes
    ui->main_screen_label_fumes = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_fumes, "烟雾浓度\n");
    lv_label_set_long_mode(ui->main_screen_label_fumes, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_fumes, 84, 68);
    lv_obj_set_size(ui->main_screen_label_fumes, 75, 17);

    //Write style for main_screen_label_fumes, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_fumes, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_fumes, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_fumes, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_fumes, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_fumes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_fumes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_vibration
    ui->main_screen_label_vibration = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_vibration, "振动强度");
    lv_label_set_long_mode(ui->main_screen_label_vibration, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_vibration, 171, 67);
    lv_obj_set_size(ui->main_screen_label_vibration, 73, 17);

    //Write style for main_screen_label_vibration, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_vibration, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_vibration, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_vibration, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_vibration, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_vibration, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_vibration, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_temp
    ui->main_screen_label_temp = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_temp, "温度");
    lv_label_set_long_mode(ui->main_screen_label_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_temp, -14, 102);
    lv_obj_set_size(ui->main_screen_label_temp, 32, 15);

    //Write style for main_screen_label_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_temp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_temp, &lv_font_MiSansNormal_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_temp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_humi
    ui->main_screen_label_humi = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_humi, "湿度");
    lv_label_set_long_mode(ui->main_screen_label_humi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_humi, -14, 126);
    lv_obj_set_size(ui->main_screen_label_humi, 31, 16);

    //Write style for main_screen_label_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_humi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_humi, &lv_font_MiSansNormal_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_humi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_humi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_sw_1
    ui->main_screen_sw_1 = lv_switch_create(ui->main_screen_tabview_main_tab_2);
    lv_obj_set_pos(ui->main_screen_sw_1, 206, 106);
    lv_obj_set_size(ui->main_screen_sw_1, 45, 25);

    //Write style for main_screen_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_sw_1, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->main_screen_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->main_screen_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->main_screen_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for main_screen_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes main_screen_label_2
    ui->main_screen_label_2 = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_2, "继电器\n");
    lv_label_set_long_mode(ui->main_screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_2, 153, 112);
    lv_obj_set_size(ui->main_screen_label_2, 52, 14);

    //Write style for main_screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_2, &lv_font_MiSansNormal_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_3
    ui->main_screen_label_3 = lv_label_create(ui->main_screen_tabview_main_tab_2);
    lv_label_set_text(ui->main_screen_label_3, "火焰状况\n");
    lv_label_set_long_mode(ui->main_screen_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_3, -14, 154);
    lv_obj_set_size(ui->main_screen_label_3, 60, 14);

    //Write style for main_screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_3, &lv_font_MiSansNormal_13, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_led_1
    ui->main_screen_led_1 = lv_led_create(ui->main_screen_tabview_main_tab_2);
    lv_led_set_brightness(ui->main_screen_led_1, 255);
    lv_led_set_color(ui->main_screen_led_1, lv_color_hex(0xFF3030));
    lv_obj_set_pos(ui->main_screen_led_1, 60, 156);
    lv_obj_set_size(ui->main_screen_led_1, 10, 10);

    //Write codes 设置
    ui->main_screen_tabview_main_tab_3 = lv_tabview_add_tab(ui->main_screen_tabview_main,"设置");
    lv_obj_t * main_screen_tabview_main_tab_3_label = lv_label_create(ui->main_screen_tabview_main_tab_3);
    lv_label_set_text(main_screen_tabview_main_tab_3_label, "");

    //Write codes main_screen_btn_main_brightness
    ui->main_screen_btn_main_brightness = lv_btn_create(ui->main_screen_tabview_main_tab_3);
    ui->main_screen_btn_main_brightness_label = lv_label_create(ui->main_screen_btn_main_brightness);
    lv_label_set_text(ui->main_screen_btn_main_brightness_label, "" LV_SYMBOL_SETTINGS "  亮度调节");
    lv_label_set_long_mode(ui->main_screen_btn_main_brightness_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_btn_main_brightness_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_btn_main_brightness, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->main_screen_btn_main_brightness_label, LV_PCT(100));
    lv_obj_set_pos(ui->main_screen_btn_main_brightness, -9, -6);
    lv_obj_set_size(ui->main_screen_btn_main_brightness, 260, 50);

    //Write style for main_screen_btn_main_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_btn_main_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_btn_main_brightness, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_btn_main_brightness, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_btn_main_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_btn_main_brightness, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_btn_main_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_btn_main_brightness, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_btn_main_brightness, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_btn_main_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_btn_main_brightness, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_btn_main_net
    ui->main_screen_btn_main_net = lv_btn_create(ui->main_screen_tabview_main_tab_3);
    ui->main_screen_btn_main_net_label = lv_label_create(ui->main_screen_btn_main_net);
    lv_label_set_text(ui->main_screen_btn_main_net_label, "" LV_SYMBOL_WIFI "  网络配置");
    lv_label_set_long_mode(ui->main_screen_btn_main_net_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_btn_main_net_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_btn_main_net, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->main_screen_btn_main_net_label, LV_PCT(100));
    lv_obj_set_pos(ui->main_screen_btn_main_net, -9, 117);
    lv_obj_set_size(ui->main_screen_btn_main_net, 260, 50);

    //Write style for main_screen_btn_main_net, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_btn_main_net, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_btn_main_net, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_btn_main_net, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_btn_main_net, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_btn_main_net, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_btn_main_net, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_btn_main_net, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_btn_main_net, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_btn_main_net, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_btn_main_net, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_btn_main_mqtt
    ui->main_screen_btn_main_mqtt = lv_btn_create(ui->main_screen_tabview_main_tab_3);
    ui->main_screen_btn_main_mqtt_label = lv_label_create(ui->main_screen_btn_main_mqtt);
    lv_label_set_text(ui->main_screen_btn_main_mqtt_label, "  " LV_SYMBOL_UPLOAD "  MQTT上报");
    lv_label_set_long_mode(ui->main_screen_btn_main_mqtt_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_btn_main_mqtt_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_btn_main_mqtt, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->main_screen_btn_main_mqtt_label, LV_PCT(100));
    lv_obj_set_pos(ui->main_screen_btn_main_mqtt, -9, 56);
    lv_obj_set_size(ui->main_screen_btn_main_mqtt, 260, 50);

    //Write style for main_screen_btn_main_mqtt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_btn_main_mqtt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_btn_main_mqtt, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_btn_main_mqtt, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_btn_main_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_btn_main_mqtt, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_btn_main_mqtt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_btn_main_mqtt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_btn_main_mqtt, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_btn_main_mqtt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_btn_main_mqtt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main_screen.

    //Update current screen layout.
    lv_obj_update_layout(ui->main_screen);

    //Init events for screen.
    events_init_main_screen(ui);
}
