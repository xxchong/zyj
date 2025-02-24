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



void setup_scr_brightness_screen(lv_ui *ui)
{
    //Write codes brightness_screen
    ui->brightness_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->brightness_screen, 280, 240);
    lv_obj_set_scrollbar_mode(ui->brightness_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for brightness_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->brightness_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->brightness_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->brightness_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes brightness_screen_slider_brightness
    ui->brightness_screen_slider_brightness = lv_slider_create(ui->brightness_screen);
    lv_slider_set_range(ui->brightness_screen_slider_brightness, 0, 100);
    lv_slider_set_mode(ui->brightness_screen_slider_brightness, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->brightness_screen_slider_brightness, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->brightness_screen_slider_brightness, 28, 127);
    lv_obj_set_size(ui->brightness_screen_slider_brightness, 240, 50);

    //Write style for brightness_screen_slider_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->brightness_screen_slider_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->brightness_screen_slider_brightness, lv_color_hex(0xa3a3a3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->brightness_screen_slider_brightness, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->brightness_screen_slider_brightness, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->brightness_screen_slider_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->brightness_screen_slider_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for brightness_screen_slider_brightness, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->brightness_screen_slider_brightness, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->brightness_screen_slider_brightness, lv_color_hex(0xece9ed), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->brightness_screen_slider_brightness, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->brightness_screen_slider_brightness, 5, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for brightness_screen_slider_brightness, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->brightness_screen_slider_brightness, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->brightness_screen_slider_brightness, 20, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes brightness_screen_label_brightness
    ui->brightness_screen_label_brightness = lv_label_create(ui->brightness_screen);
    lv_label_set_text(ui->brightness_screen_label_brightness, "亮度\n");
    lv_label_set_long_mode(ui->brightness_screen_label_brightness, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->brightness_screen_label_brightness, 97, 90);
    lv_obj_set_size(ui->brightness_screen_label_brightness, 44, 16);

    //Write style for brightness_screen_label_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->brightness_screen_label_brightness, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->brightness_screen_label_brightness, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->brightness_screen_label_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->brightness_screen_label_brightness, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->brightness_screen_label_brightness, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->brightness_screen_label_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes brightness_screen_btn_brightness_return
    ui->brightness_screen_btn_brightness_return = lv_btn_create(ui->brightness_screen);
    ui->brightness_screen_btn_brightness_return_label = lv_label_create(ui->brightness_screen_btn_brightness_return);
    lv_label_set_text(ui->brightness_screen_btn_brightness_return_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->brightness_screen_btn_brightness_return_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->brightness_screen_btn_brightness_return_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->brightness_screen_btn_brightness_return, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->brightness_screen_btn_brightness_return_label, LV_PCT(100));
    lv_obj_set_pos(ui->brightness_screen_btn_brightness_return, 8, 8);
    lv_obj_set_size(ui->brightness_screen_btn_brightness_return, 50, 50);

    //Write style for brightness_screen_btn_brightness_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->brightness_screen_btn_brightness_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->brightness_screen_btn_brightness_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->brightness_screen_btn_brightness_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->brightness_screen_btn_brightness_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->brightness_screen_btn_brightness_return, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->brightness_screen_btn_brightness_return, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->brightness_screen_btn_brightness_return, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->brightness_screen_btn_brightness_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes brightness_screen_label_percentage
    ui->brightness_screen_label_percentage = lv_label_create(ui->brightness_screen);
    char percentage[10];
    sprintf(percentage, "%d%%", brightness_percentage);
    lv_label_set_text(ui->brightness_screen_label_percentage, percentage);
    lv_label_set_long_mode(ui->brightness_screen_label_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->brightness_screen_label_percentage, 138, 90);
    lv_obj_set_size(ui->brightness_screen_label_percentage, 50, 15);

    //Write style for brightness_screen_label_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->brightness_screen_label_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->brightness_screen_label_percentage, &lv_font_MiSansNormal_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->brightness_screen_label_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->brightness_screen_label_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->brightness_screen_label_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->brightness_screen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of brightness_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->brightness_screen);

    //Init events for screen.
    events_init_brightness_screen(ui);
}
