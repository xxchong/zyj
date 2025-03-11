/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "tim.h"  //亮度调节头文件
#include "main.h"
extern bool relay_status;
typedef struct
{
  
	lv_obj_t *main_screen;
	bool main_screen_del;
	lv_obj_t *main_screen_tabview_main;
	lv_obj_t *main_screen_tabview_main_tab_1;
	lv_obj_t *main_screen_tabview_main_tab_2;
	lv_obj_t *main_screen_tabview_main_tab_3;
	lv_obj_t *main_screen_label_info;
	lv_obj_t *main_screen_label_6;
	lv_obj_t *main_screen_label_5;
	lv_obj_t *main_screen_label_7;
	lv_obj_t *main_screen_label_humi_percentage;
	lv_obj_t *main_screen_bar_humi;
	lv_obj_t *main_screen_arc_fumes;
	lv_obj_t *main_screen_arc_light;
	lv_obj_t *main_screen_label_light_percentage;
	lv_obj_t *main_screen_label_temp_percentage;
	lv_obj_t *main_screen_bar_temp;
	lv_obj_t *main_screen_label_light;
	lv_obj_t *main_screen_label_fumes_percentage;
	lv_obj_t *main_screen_label_fumes;
	lv_obj_t *main_screen_label_temp;
	lv_obj_t *main_screen_label_humi;
	lv_obj_t *main_screen_sw_1;
	lv_obj_t *main_screen_label_2;
	lv_obj_t *main_screen_label_3;
	lv_obj_t *main_screen_led_1;
	lv_obj_t *main_screen_cont_1;
	lv_obj_t *main_screen_label_13;
	lv_obj_t *main_screen_label_14;
	lv_obj_t *main_screen_label_15;
	lv_obj_t *main_screen_label_12;
	lv_obj_t *main_screen_btn_main_brightness;
	lv_obj_t *main_screen_btn_main_brightness_label;
	lv_obj_t *main_screen_btn_main_net;
	lv_obj_t *main_screen_btn_main_net_label;
	lv_obj_t *main_screen_btn_main_mqtt;
	lv_obj_t *main_screen_btn_main_mqtt_label;
	lv_obj_t *brightness_screen;
	bool brightness_screen_del;
	lv_obj_t *brightness_screen_slider_brightness;
	lv_obj_t *brightness_screen_label_brightness;
	lv_obj_t *brightness_screen_btn_brightness_return;
	lv_obj_t *brightness_screen_btn_brightness_return_label;
	lv_obj_t *brightness_screen_label_percentage;
	lv_obj_t *mqtt_param_screen;
	bool mqtt_param_screen_del;
	lv_obj_t *mqtt_param_screen_label_mqtt;
	lv_obj_t *mqtt_param_screen_ddlist_mqtt;
	lv_obj_t *mqtt_param_screen_btn_mqtt_return;
	lv_obj_t *mqtt_param_screen_btn_mqtt_return_label;
	lv_obj_t *mqtt_param_screen_btn_mqtt_enter;
	lv_obj_t *mqtt_param_screen_btn_mqtt_enter_label;
	lv_obj_t *threshold_screen;
	bool threshold_screen_del;
	lv_obj_t *threshold_screen_slider_humi;
	lv_obj_t *threshold_screen_slider_temp;
	lv_obj_t *threshold_screen_slider_mq2;
	lv_obj_t *threshold_screen_slider_light;
	lv_obj_t *threshold_screen_btn_1;
	lv_obj_t *threshold_screen_btn_1_label;
	lv_obj_t *threshold_screen_label_1;
	lv_obj_t *threshold_screen_label_2;
	lv_obj_t *threshold_screen_label_3;
	lv_obj_t *threshold_screen_label_4;
	lv_obj_t *threshold_screen_label_5;
	lv_obj_t *threshold_screen_label_6;
	lv_obj_t *threshold_screen_label_7;
	lv_obj_t *threshold_screen_label_8;
	lv_obj_t *threshold_screen_label_9;
	
	
	lv_timer_t *sensor_timer;

}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;
void sensor_timer_callback(lv_timer_t *timer);


void setup_scr_main_screen(lv_ui *ui);
void setup_scr_brightness_screen(lv_ui *ui);
void setup_scr_mqtt_param_screen(lv_ui *ui);
void setup_scr_threshold_screen(lv_ui *ui);

LV_FONT_DECLARE(lv_font_MiSansNormal_15)
LV_FONT_DECLARE(lv_font_MiSansNormal_18)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_MiSansNormal_16)
LV_FONT_DECLARE(lv_font_MiSansNormal_13)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_14)


#ifdef __cplusplus
}
#endif
#endif
