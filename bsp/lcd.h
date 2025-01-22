//******************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////
//  ���������ֿ��Ƽ����޹�˾  WWW.WLKLCD.COM  0755-32882855   רҵҺ����ʾ��Ӧ��   //
//  LCD��ʾͷ�ļ� �������û����ò�����                                           //
//  https://wlklcd.1688.com/     https://shop341012592.taobao.com/             //
//  ���̽���ѧϰ�ο�����������ʹ�ã�����������ҵ��;                              //
//*********************************************************************************/
// --------------�ӿ�����-----------------------------------
//     --        GND     ��Դ��
//     ��        VCC     3.3v��Դ
//               SCK     PA5  SPIʱ���ź�
//     ʾ        SDA     PA7  SPI�����ź�
//               RES     PA0  ��λ��
//     ��        DC      PA1
//     ��        CS      PA2
//		 --			   BLC     PA3  ���Ʊ���
//     ------------------------------------------------------
//     ��        INT     PA5  �����ж�
//     ��        SCL     PA6  ����IIC ʱ����
//     ��        SDA     PA7  ����IIC ������
//     ��        RST     PA8  ������λ��
// ----------------------------------------------------------------
//******************************************************************************/


#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"
#include "commont.h"
#include "stm32f4xx.h"                  // Device header

typedef enum
{
    LCD_PORTAIT                      = 0,                                    // ����ģʽ
    LCD_PORTAIT_180                  = 1,                                    // ����ģʽ  ��ת180
    LCD_CROSSWISE                    = 2,                                    // ����ģʽ
    LCD_CROSSWISE_180                = 3,                                    // ����ģʽ  ��ת180
}lcd_dir_enum;

typedef enum
{
    LCD_6X8_FONT                     = 0,                                    // 6x8      ����
    LCD_8X16_FONT                    = 1,                                    // 8x16     ����
    LCD_16X16_FONT                   = 2,                                    // 16x16    ���� Ŀǰ��֧��
}lcd_font_size_enum;

//-------������ɫ----------
typedef enum
{
    RGB565_WHITE    = (0xFFFF),                                                     // ��ɫ
    RGB565_BLACK    = (0x0000),                                                     // ��ɫ
    RGB565_BLUE     = (0x001F),                                                     // ��ɫ
    RGB565_PURPLE   = (0xF81F),                                                     // ��ɫ
    RGB565_PINK     = (0xFE19),                                                     // ��ɫ
    RGB565_RED      = (0xF800),                                                     // ��ɫ
    RGB565_MAGENTA  = (0xF81F),                                                     // Ʒ��
    RGB565_GREEN    = (0x07E0),                                                     // ��ɫ
    RGB565_CYAN     = (0x07FF),                                                     // ��ɫ
    RGB565_YELLOW   = (0xFFE0),                                                     // ��ɫ
    RGB565_BROWN    = (0xBC40),                                                     // ��ɫ
    RGB565_GRAY     = (0x8430),                                                     // ��ɫ

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
void    lcd_clear                    (void);                                                                                // LCD ��������
void    lcd_full                     (const uint16 color);                                                                  // LCD ��Ļ��亯��
void    lcd_set_dir                  (lcd_dir_enum dir);                                                                 // LCD ������ʾ����
void    lcd_set_font                 (lcd_font_size_enum font);                                                          // LCD ������ʾ����
void    lcd_set_color                (const uint16 pen, const uint16 bgcolor);                                              // LCD ������ʾ��ɫ
void    lcd_draw_point               (uint16 x, uint16 y, const uint16 color);                                              // LCD ���㺯��
void    lcd_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);      // LCD ���ߺ���

void    lcd_show_char                (uint16 x, uint16 y, const char dat);
void    lcd_show_string              (uint16 x, uint16 y, const char dat[]);
void    lcd_show_int                 (uint16 x, uint16 y, const int32 dat, uint8 num);
void    lcd_show_uint                (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    lcd_show_float               (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    lcd_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);                      // LCD ��ʾ��ֵͼ�� ����ÿ�˸������һ���ֽ�����
void    lcd_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);     // LCD ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ
void    lcd_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);   // LCD ��ʾ RGB565 ��ɫͼ��

void    lcd_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);                // LCD ��ʾ����
void    lcd_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);                                 // LCD ������ʾ

void lcd_set_region(uint16 x1, uint16 y1, uint16 x2, uint16 y2);




void lcd_write_data_dma(const uint8_t* data, uint32_t size);


extern  uint16  lcd_width_max;
extern  uint16  lcd_height_max;
#endif
