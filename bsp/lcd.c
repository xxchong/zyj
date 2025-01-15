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
//     触        INT     PB5  触摸中断
//     摸        SCL     PB6  触摸IIC 时钟线
//     接        SDA     PB7  触摸IIC 数据线
//     口        RST     PB8  触摸复位脚
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

#define LCD_DEFAULT_DISPLAY_DIR      (LCD_PORTAIT)                        // 默认的显示方向
#define LCD_DEFAULT_PENCOLOR         (RGB565_RED    )                        // 默认的画笔颜色
#define LCD_DEFAULT_BGCOLOR          (RGB565_WHITE  )                        // 默认的背景颜色
#define LCD_DEFAULT_DISPLAY_FONT     (LCD_8X16_FONT)                      // 默认的字体模式

static uint16                   lcd_pencolor     = LCD_DEFAULT_PENCOLOR;          // 画笔颜色(字体色)
static uint16                   lcd_bgcolor      = LCD_DEFAULT_BGCOLOR;           // 背景颜色
static lcd_dir_enum          		lcd_display_dir  = LCD_DEFAULT_DISPLAY_DIR;       // 显示方向
static lcd_font_size_enum    		lcd_display_font = LCD_DEFAULT_DISPLAY_FONT;      // 显示字体类型

/******************************************************************************
	  函数说明：LCD软件SPI数据写入函数
	  入口数据：dat  要写入的串行数据
	  返回值：  无
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
      函数说明：LCD硬件SPI数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void lcd_hardware_spi_write_data(uint8_t data) 
{	
	 HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
	
}

/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void lcd_write_command(uint8_t dat)
{
	LCD_CS(0);
	LCD_DC(0);//写命令
#if SPI_MODE
		lcd_hardware_spi_write_data(dat);
#else 
		lcd_soft_spi_write_data(dat);
#endif
	
	LCD_CS(1);
}

/******************************************************************************
      函数说明：LCD写入一个字节数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void lcd_write_8bit_data(uint8_t dat)
{
	LCD_CS(0);
	LCD_DC(1);//写数据
#if SPI_MODE
		lcd_hardware_spi_write_data(dat);
#else 
		lcd_soft_spi_write_data(dat);
#endif
	
	LCD_CS(1);
}


/******************************************************************************
      函数说明：LCD写2个字节写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void lcd_write_16bit_data(uint16_t dat)
{
	LCD_CS(0);
	LCD_DC(1);//写数据
	
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
      函数说明：LCD写2个字节数组写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void lcd_write_16bit_data_array(const uint16_t *dat, uint32_t len)
{
	int i;
	LCD_CS(0);
	LCD_DC(1);//写数据
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
// 函数简介     设置显示方向
// 参数说明     dir             显示方向  参照 zf_device_lcd.h 内 lcd_dir_enum 枚举体定义
// 返回参数     void
// 使用示例     lcd_set_dir(LCD_PORTAIT);
// 备注信息     这个函数只有在初始化屏幕之前调用才生效
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
// 函数简介     设置显示颜色
// 参数说明     pen             颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 参数说明     bgcolor         颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     lcd_set_color(RGB565_RED, RGB565_GRAY);
// 备注信息     字体颜色和背景颜色也可以随时自由设置 设置后生效
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_color (const uint16 pen, const uint16 bgcolor)
{
    lcd_pencolor = pen;
    lcd_bgcolor = bgcolor;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示字体
// 参数说明     dir             显示方向  参照 zf_device_lcd.h 内 lcd_font_size_enum 枚举体定义
// 返回参数     void
// 使用示例     lcd_set_font(LCD_8x16_FONT);
// 备注信息     字体可以随时自由设置 设置后生效 后续显示就是新的字体大小
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_font (lcd_font_size_enum font)
{
    lcd_display_font = font;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示区域
// 参数说明     x1              起始x轴坐标
// 参数说明     y1              起始y轴坐标
// 参数说明     x2              结束x轴坐标
// 参数说明     y2              结束y轴坐标
// 返回参数     void
// 使用示例     lcd_set_region(0, 0, lcd_width_max - 1, lcd_height_max - 1);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------


// DMA 传输函数
void lcd_write_data_dma(const uint8_t* data, uint32_t size)
{
    HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)data, size);
    // 等待传输完成
    while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
}

// 修改为非static的区域设置函数
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
	  函数说明：LCD初始化函数
	  入口数据：无
	  返回值：  无
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
		
    lcd_clear();                                                             // 初始化为白屏
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     LCD 清屏函数
// 参数说明     void
// 返回参数     void
// 使用示例     lcd_clear();
// 备注信息     将屏幕清空成背景颜色
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
// 函数简介     LCD 屏幕填充函数
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     lcd_full(RGB565_BLACK);
// 备注信息     将屏幕填充成指定颜色
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
// 函数简介     LCD 显示字符
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd_height_max-1]
// 参数说明     dat             需要显示的字符
// 返回参数     void
// 使用示例     lcd_show_char(0, 0, 'x');                     // 坐标0,0写一个字符x
// 备注信息     
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
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
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
            // 暂不支持
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     LCD 显示字符串
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd_height_max-1]
// 参数说明     dat             需要显示的字符串
// 返回参数     void
// 使用示例     lcd_show_string(0, 0, "seekfree");
// 备注信息     
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
            case LCD_16X16_FONT: break;                                      // 暂不支持
        }
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     LCD 显示32位有符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd_height_max-1]
// 参数说明     dat             需要显示的变量 数据类型 int32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     lcd_show_int(0, 0, x, 3);                    // x 可以为 int32 int16 int8 类型
// 备注信息     负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num+1);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
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
// 函数简介     LCD 显示32位无符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd114_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 uint32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     lcd_show_uint(0, 0, x, 3);                   // x 可以为 uint32 uint16 uint8 类型
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
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
// 函数简介     LCD 显示浮点数(去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd_height_max-1]
// 参数说明     dat             需要显示的变量 数据类型 double
// 参数说明     num             整数位显示长度   最高8位  
// 参数说明     pointnum        小数位显示长度   最高6位
// 返回参数     void
// 使用示例     lcd_show_float(0, 0, x, 2, 3);               // 显示浮点数   整数显示2位   小数显示三位
// 备注信息     特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//              负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_float (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum)
{
    double dat_temp = dat;
    double offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num+pointnum+2);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    for(; 0 < num; num --)
    {
        offset *= 10;
    }
    dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    func_double_to_str(data_buffer, dat_temp, pointnum);
    lcd_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     汉字显示
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd_height_max-1]
// 参数说明     size            取模的时候设置的汉字字体大小 也就是一个汉字占用的点阵长宽为多少个点 取模的时候需要长宽是一样的
// 参数说明     *chinese_buffer 需要显示的汉字数组
// 参数说明     number          需要显示多少位
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     lcd_show_chinese(0, 0, 16, chinese_test[0], 4, RGB565_RED);//显示font文件里面的 示例
// 备注信息     使用PCtoLCD2002软件取模           阴码、逐行式、顺向   16*16
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
// 函数简介     LCD 画点
// 参数说明     x               坐标x方向的起点 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 [0, lcd_height_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     lcd_draw_point(0, 0, RGB565_RED);            //坐标0,0画一个红色的点
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void lcd_draw_point (uint16 x, uint16 y, const uint16 color)
{
    lcd_set_region(x, y, x, y);
    lcd_write_16bit_data(color);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     LCD 画线
// 参数说明     x_start         坐标x方向的起点 [0, lcd_width_max-1]
// 参数说明     y_start         坐标y方向的起点 [0, lcd_height_max-1]
// 参数说明     x_end           坐标x方向的终点 [0, lcd_width_max-1]
// 参数说明     y_end           坐标y方向的终点 [0, lcd_height_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     lcd_draw_line(0, 0, 10, 10, RGB565_RED);     // 坐标 0,0 到 10,10 画一条红色的线
// 备注信息     
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
// 函数简介     LCD 显示波形
// 参数说明     x               坐标x方向的起点 参数范围 [0, lcd_width_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, lcd_height_max-1]
// 参数说明     *wave           波形数组指针
// 参数说明     width           波形实际宽度
// 参数说明     value_max       波形实际最大值
// 参数说明     dis_width       波形显示宽度 参数范围 [0, lcd_width_max]
// 参数说明     dis_value_max   波形显示最大值 参数范围 [0, lcd_height_max]
// 返回参数     void
// 使用示例     lcd_show_wave(0, 0, data, 128, 64, 64, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;
    uint16 data_buffer[dis_width];

    lcd_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // 设置显示区域
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

