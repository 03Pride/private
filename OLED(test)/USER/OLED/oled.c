#define  OLED_GLOBALS
#include "OLED.h" 
#include "asc.h"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include "i2c.h"
extern I2C_HandleTypeDef hi2c2;

static uint8_t OLED_GRAM[128][8];

void oled_write_byte(uint8_t dat, uint8_t cmd)
{
    static uint8_t cmd_data[2];
    if(cmd == OLED_CMD)
    {
        cmd_data[0] = 0x00;
    }
    else
    {
        cmd_data[0] = 0x40;
    }
    cmd_data[1] = dat;
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDRESS, cmd_data, 2, 10);
}
//初始化OLED模块，
 void OLED_init(void)
{
    oled_write_byte(0xAE, OLED_CMD);    //display off
    oled_write_byte(0x20, OLED_CMD);    //Set Memory Addressing Mode	
    oled_write_byte(0x10, OLED_CMD);    //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    oled_write_byte(0xb0, OLED_CMD);    //Set Page Start Address for Page Addressing Mode,0-7
    oled_write_byte(0xc8, OLED_CMD);    //Set COM Output Scan Direction
    oled_write_byte(0x00, OLED_CMD);    //---set low column address
    oled_write_byte(0x10, OLED_CMD);    //---set high column address
    oled_write_byte(0x40, OLED_CMD);    //--set start line address
    oled_write_byte(0x81, OLED_CMD);    //--set contrast control register
    oled_write_byte(0xff, OLED_CMD);    //brightness 0x00~0xff
    oled_write_byte(0xa1, OLED_CMD);    //--set segment re-map 0 to 127
    oled_write_byte(0xa6, OLED_CMD);    //--set normal display
    oled_write_byte(0xa8, OLED_CMD);    //--set multiplex ratio(1 to 64)
    oled_write_byte(0x3F, OLED_CMD);    //
    oled_write_byte(0xa4, OLED_CMD);    //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    oled_write_byte(0xd3, OLED_CMD);    //-set display offset
    oled_write_byte(0x00, OLED_CMD);    //-not offset
    oled_write_byte(0xd5, OLED_CMD);    //--set display clock divide ratio/oscillator frequency
    oled_write_byte(0xf0, OLED_CMD);    //--set divide ratio
    oled_write_byte(0xd9, OLED_CMD);    //--set pre-charge period
    oled_write_byte(0x22, OLED_CMD);    //
    oled_write_byte(0xda, OLED_CMD);    //--set com pins hardware configuration
    oled_write_byte(0x12, OLED_CMD);
    oled_write_byte(0xdb, OLED_CMD);    //--set vcomh
    oled_write_byte(0x20, OLED_CMD);    //0x20,0.77xVcc
    oled_write_byte(0x8d, OLED_CMD);    //--set DC-DC enable
    oled_write_byte(0x14, OLED_CMD);    //
    oled_write_byte(0xaf, OLED_CMD);    //--turn on oled panel
}
void OLED_display_on(void)
{
    oled_write_byte(0x8d, OLED_CMD);
    oled_write_byte(0x14, OLED_CMD);
    oled_write_byte(0xaf, OLED_CMD);
}
void OLED_display_off(void)
{
    oled_write_byte(0x8d, OLED_CMD);
    oled_write_byte(0x10, OLED_CMD);
    oled_write_byte(0xae, OLED_CMD);
}
//操作GRAM内存(128*8char数组)
 void OLED_operate_gram(pen_typedef pen)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        for (n = 0; n < 128; n++)
        {
            if (pen == PEN_WRITE)
            {
                OLED_GRAM[n][i] = 0xff;
            }
            else if (pen == PEN_CLEAR)
            {
                OLED_GRAM[n][i] = 0x00;
            }
            else
            {
                OLED_GRAM[n][i] = 0xff - OLED_GRAM[n][i];
            }
        }
    }
}
void OLED_set_pos(uint8_t x, uint8_t y)
{
    oled_write_byte((0xb0 + y), OLED_CMD);              //set page address y
    oled_write_byte(((x&0xf0)>>4)|0x10, OLED_CMD);      //set column high address
    oled_write_byte((x&0x0f), OLED_CMD);                //set column low address
}
void OLED_draw_point(int8_t x, int8_t y, pen_typedef pen)
{
    uint8_t page = 0, row = 0;

    /* check the corrdinate */
    if ((x < 0) || (x > (X_WIDTH - 1)) || (y < 0) || (y > (Y_WIDTH - 1)))
    {
        return;
    }
    page = y / 8;
    row = y % 8;

    if (pen == PEN_WRITE)
    {
        OLED_GRAM[x][page] |= 1 << row;
    }
    else if (pen == PEN_INVERSION)
    {
        OLED_GRAM[x][page] ^= 1 << row;
    }
    else
    {
        OLED_GRAM[x][page] &= ~(1 << row);
    }
}
void OLED_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, pen_typedef pen)
{
    uint8_t col = 0, row = 0;
    uint8_t x_st = 0, x_ed = 0, y_st = 0, y_ed = 0;
    float k = 0.0f, b = 0.0f;

    if (y1 == y2)
    {
        (x1 <= x2) ? (x_st = x1):(x_st = x2);
        (x1 <= x2) ? (x_ed = x2):(x_ed = x1);

        for (col = x_st; col <= x_ed; col++)
        {
            OLED_draw_point(col, y1, pen);
        }
    }
    else if (x1 == x2)
    {
        (y1 <= y2) ? (y_st = y1):(y_st = y2);
        (y1 <= y2) ? (y_ed = y2):(y_ed = y1);

        for (row = y_st; row <= y_ed; row++)
        {
            OLED_draw_point(x1, row, pen);
        }
    }
    else
    {
        k = ((float)(y2 - y1)) / (x2 - x1);
        b = (float)y1 - k * x1;

        (x1 <= x2) ? (x_st = x1):(x_st = x2);
        (x1 <= x2) ? (x_ed = x2):(x_ed = x2);

        for (col = x_st; col <= x_ed; col++)
        {
            OLED_draw_point(col, (uint8_t)(col * k + b), pen);
        }
    }
}
void OLED_show_char(uint8_t x,uint8_t y,uint8_t chr,uint8_t size)
{

    uint8_t temp,t,t1;
    uint8_t x0=x,y0=y;
    uint8_t csize=(size/8+((size%8)?1:0))*(size/2);      //得到字体一个字符对应点阵集所占的字节数
    chr=chr-' ';                                    //得到偏移后的值              
    for(t=0;t<csize;t++)
    {   
		if(size==8)temp=asc2_0806[chr][t]; //调用0806字体
        else if(size==12)temp=asc2_1206[chr][t];         //调用1206字体
        else if(size==16)temp=asc2_1608[chr][t];    //调用1608字体
        else if(size==24)temp=asc2_2412[chr][t];    //调用2412字体
        else return;                                //没有的字库
        for(t1=0;t1<8;t1++)
        {
            if(temp&0x01)OLED_draw_point(x,y,PEN_WRITE);
            else OLED_draw_point(x,y,!PEN_WRITE);
            temp>>=1;
            y++;
        }
		x++;
		if((size != 8)&&((x-x0) == size/2))
		{	
			x=x0;
			y0 = y0+8;
		}
		y=y0;
    }   
}

void OLED_show_string(uint8_t row, uint8_t col, uint8_t *chr, uint8_t size)
{
	while((*chr>=' ')&&(*chr<='~'))//判断是不是非法字符!
	{
		OLED_show_char(row, col, *chr, size);
		if(size==8)row+=6;
		else row+=size/2;
		chr++;
  }
}

/**
  *@brief			显示数字
  *@param			x,y :起点坐标
  *					num :要显示的数字
  *					len :数字的位数
  *					size1:字体大小
  *@author			HZH
  */
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1)
{
	uint8_t t,temp,m=0;
	if(size1==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				OLED_show_char(x+(size1/2+m)*t,y,'0',size1);
      }
			else 
			{
				OLED_show_char(x+(size1/2+m)*t,y,temp+'0',size1);
			}
  }
}

//格式输出
void OLED_printf(uint8_t row, uint8_t col, const char *fmt,...)
{
    static uint8_t LCD_BUF[128] = {0};
    static va_list ap;
    uint8_t remain_size = 0;

    if ((row > 4) || (col > 20) )
    {
        return;
    }
    va_start(ap, fmt);

    vsprintf((char *)LCD_BUF, fmt, ap);

    va_end(ap);

    remain_size = 21 - col;

    LCD_BUF[remain_size] = '\0';

    OLED_show_string(row, col, LCD_BUF,16);
}

//发送数据到OLED的GRAM
  
void OLED_refresh_gram(void)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        OLED_set_pos(0, i);
        for (n = 0; n < 128; n++)
        {
            oled_write_byte(OLED_GRAM[n][i], OLED_DATA);
        }
    }
}

//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}

//显示汉字
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1,pen_typedef mode)
{
	uint8_t m,temp;
	uint8_t x0=x,y0=y;
	uint16_t i,size3=(size1/8+((size1%8)?1:0))*size1;  //得到字体一个字符对应点阵集所占的字节数
	for(i=0;i<size3;i++)
	{
		if(size1==16)
				{temp=Hzk1[num][i];}//调用16*16字体
		else if(size1==24)
				{temp=Hzk2[num][i];}//调用24*24字体
		else if(size1==32)       
				{temp=Hzk3[num][i];}//调用32*32字体
		else if(size1==64)
				{temp=Hzk4[num][i];}//调用64*64字体
		else return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)OLED_draw_point(x,y,mode);
			else OLED_draw_point(x,y,!mode);
			temp>>=1;
			y++;
		}
		x++;
		if((x-x0)==size1)
		{x=x0;y0=y0+8;}
		y=y0;
	}
}
/**
  *@brief		显示图片
  *@param		x,y：起点坐标
				sizex,sizey,图片长宽
				BMP[]：要写入的图片数组
				mode:0,反色显示;1,正常显示
  *@author		HZH
  */
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,uint8_t BMP[],pen_typedef mode)
{
	uint16_t j=0;
	uint8_t i,n,temp,m;
	uint8_t x0=x,y0=y;
	sizey=sizey/8+((sizey%8)?1:0);
	for(n=0;n<sizey;n++)
	{
		 for(i=0;i<sizex;i++)
		 {
				temp=BMP[j];
				j++;
				for(m=0;m<8;m++)
				{
					if(temp&0x01)OLED_draw_point(x,y,mode);
					else OLED_draw_point(x,y,!mode);
					temp>>=1;
					y++;
				}
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y0=y0+8;
				}
				y=y0;
     }
	 }
}


















