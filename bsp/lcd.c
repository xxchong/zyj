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
//     ��        INT     PB5  �����ж�
//     ��        SCL     PB6  ����IIC ʱ����
//     ��        SDA     PB7  ����IIC ������
//     ��        RST     PB8  ������λ��
// ----------------------------------------------------------------
//******************************************************************************/
#include "lcd.h"
#include "lcdfont.h"
#include <string.h>
#include "stm32f4xx.h"                  // Device header
#include "spi.h"


uint16                   lcd_width_max    = 280;
uint16                   lcd_height_max   = 240;

#define SPI_MODE 1

#define LCD_DEFAULT_DISPLAY_DIR      (LCD_PORTAIT)                        // Ĭ�ϵ���ʾ����
#define LCD_DEFAULT_PENCOLOR         (RGB565_RED    )                        // Ĭ�ϵĻ�����ɫ
#define LCD_DEFAULT_BGCOLOR          (RGB565_WHITE  )                        // Ĭ�ϵı�����ɫ
#define LCD_DEFAULT_DISPLAY_FONT     (LCD_8X16_FONT)                      // Ĭ�ϵ�����ģʽ

static uint16                   lcd_pencolor     = LCD_DEFAULT_PENCOLOR;          // ������ɫ(����ɫ)
static uint16                   lcd_bgcolor      = LCD_DEFAULT_BGCOLOR;           // ������ɫ
static lcd_dir_enum          		lcd_display_dir  = LCD_DEFAULT_DISPLAY_DIR;       // ��ʾ����
static lcd_font_size_enum    		lcd_display_font = LCD_DEFAULT_DISPLAY_FONT;      // ��ʾ��������

/******************************************************************************
	  ����˵����LCD���SPI����д�뺯��
	  ������ݣ�dat  Ҫд��Ĵ�������
	  ����ֵ��  ��
******************************************************************************/
void lcd_soft_spi_write_data(uint8_t dat)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		LCD_SCLK(0);
		if (dat & 0x80)
			LCD_MOSI(1);
		else
			LCD_MOSI(0);
		LCD_SCLK(1);
		dat <<= 1;
	}
}
/******************************************************************************
      ����˵����LCDӲ��SPI����д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void lcd_hardware_spi_write_data(uint8_t data) 
{	
	 HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
	
}

/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void lcd_write_command(uint8_t dat)
{
	LCD_CS(0);
	LCD_DC(0);//д����
#if SPI_MODE
		lcd_hardware_spi_write_data(dat);
#else 
		lcd_soft_spi_write_data(dat);
#endif
	
	LCD_CS(1);
}

/******************************************************************************
      ����˵����LCDд��һ���ֽ�����
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void lcd_write_8bit_data(uint8_t dat)
{
	LCD_CS(0);
	LCD_DC(1);//д����
#if SPI_MODE
		lcd_hardware_spi_write_data(dat);
#else 
		lcd_soft_spi_write_data(dat);
#endif
	
	LCD_CS(1);
}


/******************************************************************************
      ����˵����LCDд2���ֽ�д������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void lcd_write_16bit_data(uint16_t dat)
{
	LCD_CS(0);
	LCD_DC(1);//д����
	
#if SPI_MODE
		lcd_hardware_spi_write_data(dat>>8);
		lcd_hardware_spi_write_data(dat);
#else 
		lcd_soft_spi_write_data(dat>>8);
		lcd_soft_spi_write_data(dat);
#endif

	LCD_CS(1);
}

/******************************************************************************
      ����˵����LCDд2���ֽ�����д������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void lcd_write_16bit_data_array(const uint16_t *dat, uint32_t len)
{
	int i;
	LCD_CS(0);
	LCD_DC(1);//д����
	for(i = 0; i < len;i++)
	{
#if SPI_MODE
		lcd_hardware_spi_write_data(dat[i]>>8);
		lcd_hardware_spi_write_data(dat[i]);
#else 
		lcd_soft_spi_write_data(dat[i]>>8);
		lcd_soft_spi_write_data(dat[i]);
#endif
	}
	LCD_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_lcd.h �� lcd_dir_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     lcd_set_dir(LCD_PORTAIT);
// ��ע��Ϣ     �������ֻ���ڳ�ʼ����Ļ֮ǰ���ò���Ч
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_dir (lcd_dir_enum dir)
{
    lcd_display_dir = dir;
    switch(lcd_display_dir)
    {
        case LCD_PORTAIT:
        case LCD_PORTAIT_180:
        {
            lcd_width_max = 240;
            lcd_height_max = 280;
        }break;
        case LCD_CROSSWISE:
        case LCD_CROSSWISE_180:
        {
            lcd_width_max = 280;
            lcd_height_max = 240;
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ��ɫ
// ����˵��     pen             ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ����˵��     bgcolor         ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     lcd_set_color(RGB565_RED, RGB565_GRAY);
// ��ע��Ϣ     ������ɫ�ͱ�����ɫҲ������ʱ�������� ���ú���Ч
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_color (const uint16 pen, const uint16 bgcolor)
{
    lcd_pencolor = pen;
    lcd_bgcolor = bgcolor;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_lcd.h �� lcd_font_size_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     lcd_set_font(LCD_8x16_FONT);
// ��ע��Ϣ     ���������ʱ�������� ���ú���Ч ������ʾ�����µ������С
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_font (lcd_font_size_enum font)
{
    lcd_display_font = font;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     x1              ��ʼx������
// ����˵��     y1              ��ʼy������
// ����˵��     x2              ����x������
// ����˵��     y2              ����y������
// ���ز���     void
// ʹ��ʾ��     lcd_set_region(0, 0, lcd_width_max - 1, lcd_height_max - 1);
// ��ע��Ϣ     �ڲ����� �û��������
//-------------------------------------------------------------------------------------------------------------------


// DMA ���亯��
void lcd_write_data_dma(const uint8_t* data, uint32_t size)
{
    HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)data, size);
    // �ȴ��������
    while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
}

// �޸�Ϊ��static���������ú���
void lcd_set_region(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
    lcd_write_command(0x2a);
    lcd_write_16bit_data(x1);
    lcd_write_16bit_data(x2);
    
    lcd_write_command(0x2b);
    lcd_write_16bit_data(y1);
    lcd_write_16bit_data(y2);
    
    lcd_write_command(0x2c);
}



/******************************************************************************
	  ����˵����LCD��ʼ������
	  ������ݣ���
	  ����ֵ��  ��
******************************************************************************/

void lcd_init(void)
{
    lcd_set_dir(lcd_display_dir);
    lcd_set_color(lcd_pencolor, lcd_bgcolor);   

    LCD_BL(1);
    LCD_RST(0);  
    HAL_Delay(5);
    LCD_RST(1);      
    HAL_Delay(120);             
      
    lcd_write_command(0x11);    // Sleep Out
    HAL_Delay(120);

    lcd_write_command(0x36);
    switch(lcd_display_dir)
    {
        case LCD_PORTAIT:        lcd_write_8bit_data(0x00);   break;
        case LCD_PORTAIT_180:    lcd_write_8bit_data(0xC0);   break;
        case LCD_CROSSWISE:      lcd_write_8bit_data(0x70);   break;
        case LCD_CROSSWISE_180:  lcd_write_8bit_data(0xA0);   break;
    }
		
		lcd_write_command(0x3A);
    lcd_write_8bit_data(0x05);
    
    lcd_write_command(0xB2);
    lcd_write_8bit_data(0x0C);
    lcd_write_8bit_data(0x0C);
    lcd_write_8bit_data(0x00);
    lcd_write_8bit_data(0x33);
    lcd_write_8bit_data(0x33);

    lcd_write_command(0xB7);
    lcd_write_8bit_data(0x35);

    lcd_write_command(0xBB);
    lcd_write_8bit_data(0x29);                                               // 32 Vcom=1.35V

    lcd_write_command(0xC2);
    lcd_write_8bit_data(0x01);

    lcd_write_command(0xC3);
    lcd_write_8bit_data(0x19);                                               // GVDD=4.8V 

    lcd_write_command(0xC4);
    lcd_write_8bit_data(0x20);                                               // VDV, 0x20:0v

    lcd_write_command(0xC5);
    lcd_write_8bit_data(0x1A);                                               // VCOM Offset Set

    lcd_write_command(0xC6);
    lcd_write_8bit_data(0x01F);                                              // 0x0F:60Hz

    lcd_write_command(0xD0);
    lcd_write_8bit_data(0xA4);
    lcd_write_8bit_data(0xA1);
                
    lcd_write_command(0xE0);
    lcd_write_8bit_data(0xD0);
    lcd_write_8bit_data(0x08);
    lcd_write_8bit_data(0x0E);
    lcd_write_8bit_data(0x09);
    lcd_write_8bit_data(0x09);
    lcd_write_8bit_data(0x05);
    lcd_write_8bit_data(0x31);
    lcd_write_8bit_data(0x33);
    lcd_write_8bit_data(0x48);
    lcd_write_8bit_data(0x17);
    lcd_write_8bit_data(0x14);
    lcd_write_8bit_data(0x15);
    lcd_write_8bit_data(0x31);
    lcd_write_8bit_data(0x34);

    lcd_write_command(0xE1);  
    lcd_write_8bit_data(0xD0);
    lcd_write_8bit_data(0x08);
    lcd_write_8bit_data(0x0E);
    lcd_write_8bit_data(0x09);
    lcd_write_8bit_data(0x09);
    lcd_write_8bit_data(0x15);
    lcd_write_8bit_data(0x31);
    lcd_write_8bit_data(0x33);
    lcd_write_8bit_data(0x48);
    lcd_write_8bit_data(0x17);
    lcd_write_8bit_data(0x14);
    lcd_write_8bit_data(0x15);
    lcd_write_8bit_data(0x31);
    lcd_write_8bit_data(0x34);

    lcd_write_command(0x21);
    
    lcd_write_command(0x29);
		
    lcd_clear();                                                             // ��ʼ��Ϊ����
}


//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     lcd_clear();
// ��ע��Ϣ     ����Ļ��ճɱ�����ɫ
//-------------------------------------------------------------------------------------------------------------------
void lcd_clear (void)
{
    uint16 color_buffer[lcd_width_max];
    uint16 i = 0, j = 0;

    lcd_set_region(0, 0, lcd_width_max - 1, lcd_height_max - 1);
    for(i = 0; i < lcd_width_max; i ++)
    {
        color_buffer[i] = lcd_bgcolor;
    }
    for (j = 0; j < lcd_height_max; j ++)
    {
        lcd_write_16bit_data_array(color_buffer, lcd_width_max);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��Ļ��亯��
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     lcd_full(RGB565_BLACK);
// ��ע��Ϣ     ����Ļ����ָ����ɫ
//-------------------------------------------------------------------------------------------------------------------
void lcd_full (const uint16 color)
{
    uint16 color_buffer[lcd_width_max];
    uint16 i = 0, j = 0;

    lcd_set_region(0, 0, lcd_width_max - 1, lcd_height_max - 1);
    for(i = 0; i < lcd_width_max; i ++)
    {
        color_buffer[i] = color;
    }
    for (j = 0; j < lcd_height_max; j ++)
    {
        lcd_write_16bit_data_array(color_buffer, lcd_width_max);
    }
}
//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��ʾ�ַ�
// ����˵��     x               ����x�������� ������Χ [0, lcd_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ�
// ���ز���     void
// ʹ��ʾ��     lcd_show_char(0, 0, 'x');                     // ����0,0дһ���ַ�x
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_char (uint16 x, uint16 y, const char dat)
{
    uint8 i = 0, j = 0;

    switch(lcd_display_font)
    {
        case LCD_6X8_FONT:
        {
            uint16 display_buffer[6*8];
            lcd_set_region(x, y, x + 5, y + 7);
            for(i = 0; 6 > i; i ++)
            {
                // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        display_buffer[i + j * 6] = (lcd_pencolor);
                    }
                    else
                    {
                        display_buffer[i + j * 6] = (lcd_bgcolor);
                    }
                    temp_top >>= 1;
                }
            }
            lcd_write_16bit_data_array(display_buffer, 6*8);
        }break;
        case LCD_8X16_FONT:
        {
            uint16 display_buffer[8*16];
            lcd_set_region(x, y, x + 7, y + 15);
            for(i = 0; 8 > i; i ++)
            {
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        display_buffer[i + j * 8] = (lcd_pencolor);
                    }
                    else
                    {
                        display_buffer[i + j * 8] = (lcd_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        display_buffer[i + j * 8 + 4 * 16] = (lcd_pencolor);
                    }
                    else
                    {
                        display_buffer[i + j * 8 + 4 * 16] = (lcd_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
            lcd_write_16bit_data_array(display_buffer, 8 * 16);
        }break;
        case LCD_16X16_FONT:
        {
            // �ݲ�֧��
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��ʾ�ַ���
// ����˵��     x               ����x�������� ������Χ [0, lcd_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ���
// ���ز���     void
// ʹ��ʾ��     lcd_show_string(0, 0, "seekfree");
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_string (uint16 x, uint16 y, const char dat[])
{
    uint16 j = 0;
    while('\0' != dat[j])
    {
        switch(lcd_display_font)
        {
            case LCD_6X8_FONT:   lcd_show_char(x + 6 * j, y, dat[j]); break;
            case LCD_8X16_FONT:  lcd_show_char(x + 8 * j, y, dat[j]); break;
            case LCD_16X16_FONT: break;                                      // �ݲ�֧��
        }
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��ʾ32λ�з��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, lcd_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� int32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     lcd_show_int(0, 0, x, 3);                    // x ����Ϊ int32 int16 int8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num+1);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    lcd_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��ʾ32λ�޷��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, lcd114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� uint32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     lcd_show_uint(0, 0, x, 3);                   // x ����Ϊ uint32 uint16 uint8 ����
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    lcd_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��ʾ������(ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, lcd_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd_height_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� double
// ����˵��     num             ����λ��ʾ����   ���8λ  
// ����˵��     pointnum        С��λ��ʾ����   ���6λ
// ���ز���     void
// ʹ��ʾ��     lcd_show_float(0, 0, x, 2, 3);               // ��ʾ������   ������ʾ2λ   С����ʾ��λ
// ��ע��Ϣ     �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//              ��������ʾһ�� ��-����
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_float (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum)
{
    double dat_temp = dat;
    double offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num+pointnum+2);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    for(; 0 < num; num --)
    {
        offset *= 10;
    }
    dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    func_double_to_str(data_buffer, dat_temp, pointnum);
    lcd_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ
// ����˵��     x               ����x�������� ������Χ [0, lcd_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd_height_max-1]
// ����˵��     size            ȡģ��ʱ�����õĺ��������С Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��� ȡģ��ʱ����Ҫ������һ����
// ����˵��     *chinese_buffer ��Ҫ��ʾ�ĺ�������
// ����˵��     number          ��Ҫ��ʾ����λ
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     lcd_show_chinese(0, 0, 16, chinese_test[0], 4, RGB565_RED);//��ʾfont�ļ������ ʾ��
// ��ע��Ϣ     ʹ��PCtoLCD2002���ȡģ           ���롢����ʽ��˳��   16*16
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_chinese (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color)
{
    int i = 0, j = 0, k = 0; 
    uint8 temp = 0, temp1 = 0, temp2 = 0;
    const uint8 *p_data = chinese_buffer;
    
    temp2 = size / 8;
    
    lcd_set_region(x, y, number * size - 1 + x, y + size - 1);
    
    for(i = 0; i < size; i ++)
    {
        temp1 = number;
        p_data = chinese_buffer + i * temp2;
        while(temp1 --)
        {
            for(k = 0; k < temp2; k ++)
            {
                for(j = 8; 0 < j; j --)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if(temp)
                    {
                        lcd_write_16bit_data(color);
                    }
                    else
                    {
                        lcd_write_16bit_data(lcd_bgcolor);
                    }
                }
                p_data ++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }   
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ����
// ����˵��     x               ����x�������� [0, lcd_width_max-1]
// ����˵��     y               ����y�������� [0, lcd_height_max-1]
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     lcd_draw_point(0, 0, RGB565_RED);            //����0,0��һ����ɫ�ĵ�
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void lcd_draw_point (uint16 x, uint16 y, const uint16 color)
{
    lcd_set_region(x, y, x, y);
    lcd_write_16bit_data(color);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ����
// ����˵��     x_start         ����x�������� [0, lcd_width_max-1]
// ����˵��     y_start         ����y�������� [0, lcd_height_max-1]
// ����˵��     x_end           ����x������յ� [0, lcd_width_max-1]
// ����˵��     y_end           ����y������յ� [0, lcd_height_max-1]
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     lcd_draw_line(0, 0, 10, 10, RGB565_RED);     // ���� 0,0 �� 10,10 ��һ����ɫ����
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void lcd_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if(x_start != x_end)
        {
            temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
            temp_b = (float)y_start - (float)x_start * temp_rate;
        }
        else
        {
            while(y_start != y_end)
            {
                lcd_draw_point(x_start, y_start, color);
                y_start += y_dir;
            }
            lcd_draw_point(x_start, y_start, color);
            break;
        }
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                lcd_draw_point(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
            lcd_draw_point(x_start, y_start, color);
        }
        else
        {
            while(x_start != x_end)
            {
                lcd_draw_point(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
            lcd_draw_point(x_start, y_start, color);
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     LCD ��ʾ����
// ����˵��     x               ����x�������� ������Χ [0, lcd_width_max-1]
// ����˵��     y               ����y�������� ������Χ [0, lcd_height_max-1]
// ����˵��     *wave           ��������ָ��
// ����˵��     width           ����ʵ�ʿ��
// ����˵��     value_max       ����ʵ�����ֵ
// ����˵��     dis_width       ������ʾ��� ������Χ [0, lcd_width_max]
// ����˵��     dis_value_max   ������ʾ���ֵ ������Χ [0, lcd_height_max]
// ���ز���     void
// ʹ��ʾ��     lcd_show_wave(0, 0, data, 128, 64, 64, 32);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;
    uint16 data_buffer[dis_width];

    lcd_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // ������ʾ����
    for(j = 0; j < dis_value_max; j ++)
    {
        for(i = 0; i < dis_width; i ++)
        {
            data_buffer[i] = (lcd_bgcolor); 
        }
        lcd_write_16bit_data_array(data_buffer, dis_width);
    }

    for(i = 0; i < dis_width; i ++)
    {
        width_index = i * width / dis_width;
        value_max_index = *(wave + width_index) * (dis_value_max - 1) / value_max;
        lcd_draw_point((uint16)(i + x), (uint16)((dis_value_max - 1) - value_max_index + y), lcd_pencolor);
    }
}

