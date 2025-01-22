//******************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////
//  深圳市沃乐康科技有限公司  WWW.WLKLCD.COM  0755-32882855   专业液晶显示供应商   //
//  LCD显示头文件 （定义用户配置参数）                                           //
//  https://wlklcd.1688.com/     https://shop341012592.taobao.com/             //
//  例程仅供学习参考，不做量产使用，不得用于商业用途                              //
//*********************************************************************************/
// --------------接口连线-----------------------------------
//     --        GND     电源地
//     显        VCC     3.3v电源
//               SCK     PA5  SPI时钟信号
//     示        SDA     PA7  SPI数据信号
//               RES     PA0  复位脚
//     接        DC      PA1
//     口        CS      PA2
//		 --			   BLC     PA3  控制背光
//     ------------------------------------------------------
//     触        INT     PA5  触摸中断
//     摸        SCL     PA6  触摸IIC 时钟线
//     接        SDA     PA7  触摸IIC 数据线
//     口        RST     PA8  触摸复位脚
// ----------------------------------------------------------------
//******************************************************************************/


#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"
#include "commont.h"
#include "stm32f4xx.h"                  // Device header

typedef enum
{
    LCD_PORTAIT                      = 0,                                    // 竖屏模式
    LCD_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
    LCD_CROSSWISE                    = 2,                                    // 横屏模式
    LCD_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
}lcd_dir_enum;

typedef enum
{
    LCD_6X8_FONT                     = 0,                                    // 6x8      字体
    LCD_8X16_FONT                    = 1,                                    // 8x16     字体
    LCD_16X16_FONT                   = 2,                                    // 16x16    字体 目前不支持
}lcd_font_size_enum;

//-------常用颜色----------
typedef enum
{
    RGB565_WHITE    = (0xFFFF),                                                     // 白色
    RGB565_BLACK    = (0x0000),                                                     // 黑色
    RGB565_BLUE     = (0x001F),                                                     // 蓝色
    RGB565_PURPLE   = (0xF81F),                                                     // 紫色
    RGB565_PINK     = (0xFE19),                                                     // 粉色
    RGB565_RED      = (0xF800),                                                     // 红色
    RGB565_MAGENTA  = (0xF81F),                                                     // 品红
    RGB565_GREEN    = (0x07E0),                                                     // 绿色
    RGB565_CYAN     = (0x07FF),                                                     // 青色
    RGB565_YELLOW   = (0xFFE0),                                                     // 黄色
    RGB565_BROWN    = (0xBC40),                                                     // 棕色
    RGB565_GRAY     = (0x8430),                                                     // 灰色

    RGB565_39C5BB   = (0x3616),
    RGB565_66CCFF   = (0x665F),
}rgb565_color_enum;

#define LCD_RST_PORT       GPIOA
#define LCD_DC_PORT        GPIOA
#define LCD_CS_PORT        GPIOA
#define LCD_BL_PORT        GPIOA
#define LCD_SCLK_PORT      GPIOA
#define LCD_MOSI_PORT      GPIOA

#define LCD_RST_PIN       GPIO_PIN_0
#define LCD_DC_PIN        GPIO_PIN_1
#define LCD_CS_PIN        GPIO_PIN_2
#define LCD_BL_PIN        GPIO_PIN_3
#define LCD_SCLK_PIN      GPIO_PIN_5
#define LCD_MOSI_PIN      GPIO_PIN_7

#define LCD_SCLK(x)      ((x) ? (HAL_GPIO_WritePin(LCD_SCLK_PORT, LCD_SCLK_PIN,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(LCD_SCLK_PORT, LCD_SCLK_PIN,GPIO_PIN_RESET)))
#define LCD_MOSI(x)     ((x) ? (HAL_GPIO_WritePin(LCD_MOSI_PORT, LCD_MOSI_PIN,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(LCD_MOSI_PORT, LCD_MOSI_PIN,GPIO_PIN_RESET)))
#define LCD_CS(x)      ((x) ? (HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN,GPIO_PIN_RESET)))
#define LCD_RST(x)     ((x) ? (HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN,GPIO_PIN_RESET)))
#define LCD_DC(x)      ((x) ? (HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN,GPIO_PIN_RESET)))
#define LCD_BL(x)      ((x) ? (HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN,GPIO_PIN_SET)) : (HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN,GPIO_PIN_RESET)))

void lcd_soft_spi_write_data(uint8_t dat);
void lcd_hardware_spi_write_data(uint8_t data);
void lcd_write_command(uint8_t dat);
void lcd_write_8bit_data(uint8_t dat);
void lcd_write_16bit_data(uint16_t dat);


void Hardware_SPI_Init(void);
void STM_Port_Init(void);

void    lcd_init                  	(void);
void    lcd_clear                    (void);                                                                                // LCD 清屏函数
void    lcd_full                     (const uint16 color);                                                                  // LCD 屏幕填充函数
void    lcd_set_dir                  (lcd_dir_enum dir);                                                                 // LCD 设置显示方向
void    lcd_set_font                 (lcd_font_size_enum font);                                                          // LCD 设置显示字体
void    lcd_set_color                (const uint16 pen, const uint16 bgcolor);                                              // LCD 设置显示颜色
void    lcd_draw_point               (uint16 x, uint16 y, const uint16 color);                                              // LCD 画点函数
void    lcd_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);      // LCD 画线函数

void    lcd_show_char                (uint16 x, uint16 y, const char dat);
void    lcd_show_string              (uint16 x, uint16 y, const char dat[]);
void    lcd_show_int                 (uint16 x, uint16 y, const int32 dat, uint8 num);
void    lcd_show_uint                (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    lcd_show_float               (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    lcd_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);                      // LCD 显示二值图像 数据每八个点组成一个字节数据
void    lcd_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);     // LCD 显示 8bit 灰度图像 带二值化阈值
void    lcd_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);   // LCD 显示 RGB565 彩色图像

void    lcd_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);                // LCD 显示波形
void    lcd_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);                                 // LCD 汉字显示

void lcd_set_region(uint16 x1, uint16 y1, uint16 x2, uint16 y2);




void lcd_write_data_dma(const uint8_t* data, uint32_t size);


extern  uint16  lcd_width_max;
extern  uint16  lcd_height_max;
#endif
