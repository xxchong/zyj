/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "relay.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void main_screen_btn_main_brightness_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		lv_timer_pause(guider_ui.sensor_timer);
        lv_timer_del(guider_ui.sensor_timer);
        ui_load_scr_animation(&guider_ui, &guider_ui.brightness_screen, guider_ui.brightness_screen_del, &guider_ui.main_screen_del, setup_scr_brightness_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 20, true, true);
        break;
    }
    default:
        break;
    }
}

static void main_screen_btn_main_net_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
			
		lv_timer_pause(guider_ui.sensor_timer);
        lv_timer_del(guider_ui.sensor_timer);
        ui_load_scr_animation(&guider_ui, &guider_ui.threshold_screen, guider_ui.threshold_screen_del, &guider_ui.main_screen_del, setup_scr_threshold_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 20, true, true);
        break;
    }
    default:
        break;
    }
}

static void main_screen_btn_main_mqtt_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
			
		lv_timer_pause(guider_ui.sensor_timer);
        lv_timer_del(guider_ui.sensor_timer);
        ui_load_scr_animation(&guider_ui, &guider_ui.mqtt_param_screen, guider_ui.mqtt_param_screen_del, &guider_ui.main_screen_del, setup_scr_mqtt_param_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 20, true, true);
        break;
    }
    default:
        break;
    }
}
static void main_screen_sw_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        relay_status = !relay_status;
        if(relay_status)
        {
            lv_obj_add_state(ui->main_screen_sw_1, LV_STATE_CHECKED);
            RELAY_ON;
            
        }else{
            lv_obj_clear_state(ui->main_screen_sw_1, LV_STATE_CHECKED);
            RELAY_OFF;
        }

    }
    default:
        break;
    }
}
void events_init_main_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->main_screen_btn_main_brightness, main_screen_btn_main_brightness_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_btn_main_net, main_screen_btn_main_net_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_btn_main_mqtt, main_screen_btn_main_mqtt_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_sw_1, main_screen_sw_1_event_handler, LV_EVENT_VALUE_CHANGED, ui);

    ui->sensor_timer = lv_timer_create(sensor_timer_callback, 1500, NULL);
}

static void brightness_screen_slider_brightness_event_handler (lv_event_t *e)
{
		char percentage[10];
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);    
		switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int32_t brightness = lv_slider_get_value(ui->brightness_screen_slider_brightness);
        uint16_t percentage_val = (brightness * 999) / 100; 
        brightness_percentage = brightness;
        brightness_pwm = percentage_val;
        sprintf(percentage, "%d%%", brightness);
        lv_label_set_text(ui->brightness_screen_label_percentage, percentage);
        LCD_SetBrightness(percentage_val);  
        break;
    }
    default:
        break;
    }
}

static void brightness_screen_btn_brightness_return_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.brightness_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 50, 20, true, true);
        lv_tabview_set_act(guider_ui.main_screen_tabview_main, 2, LV_ANIM_OFF);
				break;
    }
    default:
        break;
    }
}

void events_init_brightness_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->brightness_screen_slider_brightness, brightness_screen_slider_brightness_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->brightness_screen_btn_brightness_return, brightness_screen_btn_brightness_return_event_handler, LV_EVENT_ALL, ui);
}

static void mqtt_param_screen_btn_mqtt_return_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.mqtt_param_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 50, 20, true, true);
        lv_tabview_set_act(guider_ui.main_screen_tabview_main, 2, LV_ANIM_OFF);
				break;
    }
    default:
        break;
    }
}


static void mqtt_param_screen_ddlist_mqtt_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int32_t value = lv_dropdown_get_selected(ui->mqtt_param_screen_ddlist_mqtt);

        uint16_t interval[5] = {5000, 10000, 20000, 30000, 60000};

        switch(value)
        {   
            case 0:
                mqtt_send_interval = interval[0];
                break;
            case 1:
                mqtt_send_interval = interval[1];
                break;
            case 2:
                mqtt_send_interval = interval[2];
                break;
            case 3:
                mqtt_send_interval = interval[3];
                break;
            case 4:
                mqtt_send_interval = interval[4];
                break;
        }
        break;
    }
    default:
        break;  
    }
}

void events_init_mqtt_param_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->mqtt_param_screen_btn_mqtt_return, mqtt_param_screen_btn_mqtt_return_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mqtt_param_screen_ddlist_mqtt, mqtt_param_screen_ddlist_mqtt_event_handler, LV_EVENT_ALL, ui);
}

static void threshold_screen_slider_humi_event_handler (lv_event_t *e)
{
    char buffer[10];
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_obj_t *target = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        if(target == ui->threshold_screen_slider_humi)
        {
            int32_t value = lv_slider_get_value(ui->threshold_screen_slider_humi);
            threshold_data.humi = value;
            sprintf(buffer, "%d%%", value);
            lv_label_set_text(ui->threshold_screen_label_6, buffer);
        }
        else if(target == ui->threshold_screen_slider_temp)
        {
            int32_t value = lv_slider_get_value(ui->threshold_screen_slider_temp);
            threshold_data.temp = value;
            sprintf(buffer, "%d%%", value);
            lv_label_set_text(ui->threshold_screen_label_7, buffer);
        }else if(target == ui->threshold_screen_slider_mq2)
        {
            int32_t value = lv_slider_get_value(ui->threshold_screen_slider_mq2);
            threshold_data.mq2 = value;
            sprintf(buffer, "%d%%", value);
            lv_label_set_text(ui->threshold_screen_label_8, buffer);
        }else if(target == ui->threshold_screen_slider_light)
        {   
            int32_t value = lv_slider_get_value(ui->threshold_screen_slider_light);
            threshold_data.light = value;
            sprintf(buffer, "%d%%", value);
            lv_label_set_text(ui->threshold_screen_label_9, buffer);
        }
        break;
    }
    default:
        break;
    }
}


static void threshold_screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.threshold_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 50, 20, true, true);
        lv_tabview_set_act(guider_ui.main_screen_tabview_main, 2, LV_ANIM_OFF);
				break;
    }
    default:
        break;
    }
}

void events_init_threshold_screen (lv_ui *ui)
{
    
	lv_obj_add_event_cb(ui->threshold_screen_btn_1, threshold_screen_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->threshold_screen_slider_humi, threshold_screen_slider_humi_event_handler, LV_EVENT_VALUE_CHANGED, ui);
    lv_obj_add_event_cb(ui->threshold_screen_slider_temp, threshold_screen_slider_humi_event_handler, LV_EVENT_VALUE_CHANGED, ui);
    lv_obj_add_event_cb(ui->threshold_screen_slider_mq2, threshold_screen_slider_humi_event_handler, LV_EVENT_VALUE_CHANGED, ui);
    lv_obj_add_event_cb(ui->threshold_screen_slider_light, threshold_screen_slider_humi_event_handler, LV_EVENT_VALUE_CHANGED, ui);

}


void events_init(lv_ui *ui)
{

}
