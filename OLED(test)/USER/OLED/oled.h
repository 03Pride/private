#ifdef  OLED_GLOBALS
#define OLED_EXT
#else
#define OLED_EXT	extern
#endif

#ifndef OLED_H
#define OLED_H

#include <stdint.h>


// the I2C address of oled
#define OLED_I2C_ADDRESS    0x78

//the resolution of oled   128*64
#define MAX_COLUMN      128
#define MAX_ROW         64

#define X_WIDTH         MAX_COLUMN
#define Y_WIDTH         MAX_ROW

#define OLED_CMD        0x00
#define OLED_DATA       0x01

typedef enum
{
    PEN_CLEAR = 0x00,
    PEN_WRITE = 0x01,
    PEN_INVERSION= 0x02,
}pen_typedef;

OLED_EXT void OLED_init(void);
OLED_EXT void OLED_display_on(void);
OLED_EXT void OLED_display_off(void);
OLED_EXT void OLED_operate_gram(pen_typedef pen);
OLED_EXT void OLED_set_pos(uint8_t x, uint8_t y);
OLED_EXT void OLED_draw_point(int8_t x, int8_t y, pen_typedef pen);
OLED_EXT void OLED_show_string(uint8_t row, uint8_t col, uint8_t *chr, uint8_t size);
OLED_EXT void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);
OLED_EXT void OLED_printf(uint8_t row, uint8_t col, const char *fmt,...);
OLED_EXT void OLED_show_char(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
OLED_EXT uint32_t OLED_Pow(uint8_t m,uint8_t n);
OLED_EXT void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1,pen_typedef mode);
OLED_EXT void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,uint8_t BMP[],pen_typedef mode);
OLED_EXT void OLED_refresh_gram(void);
OLED_EXT void OLED_LOGO(void);
#endif







