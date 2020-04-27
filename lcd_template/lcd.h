#ifndef __LCD_H
#define __LCD_H		

#include <stdint.h>
#include "systick.h"
#include "stdlib.h"	
#include "gd32vf103_gpio.h"

#define USE_HORIZONTAL 2  //Set horizontal or vertical screen display 0 or 1 for vertical screen 2 or 3 for horizontal screen
#define HAS_BLK_CNTL    0

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 80
#define LCD_H 160
#else
#define LCD_W 160
#define LCD_H 80
#endif

// #define LED_ON gpio_bit_reset(GPIOC,GPIO_PIN_13)
// #define LED_OFF gpio_bit_set(GPIOC,GPIO_PIN_13)

#define LED_ON 
#define LED_OFF 

#define SPI0_CFG 1  //hardware spi
// #define SPI0_CFG 2  //hardware spi dma
// #define SPI0_CFG 3  //software spi

#define FRAME_SIZE  25600

//-----------------OLED端口定义---------------- 
#if SPI0_CFG == 1
#define OLED_SCLK_Clr() 
#define OLED_SCLK_Set() 

#define OLED_SDIN_Clr()
#define OLED_SDIN_Set()

#define OLED_CS_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_2)     //CS PB2
#define OLED_CS_Set() gpio_bit_set(GPIOB,GPIO_PIN_2)
#elif SPI0_CFG == 2
#define OLED_SCLK_Clr() 
#define OLED_SCLK_Set() 

#define OLED_SDIN_Clr()
#define OLED_SDIN_Set()

#define OLED_CS_Clr()
#define OLED_CS_Set()
#else /* SPI0_CFG */
#define OLED_SCLK_Clr() gpio_bit_reset(GPIOA,GPIO_PIN_5)    //CLK PA5
#define OLED_SCLK_Set() gpio_bit_set(GPIOA,GPIO_PIN_5)

#define OLED_SDIN_Clr() gpio_bit_reset(GPIOA,GPIO_PIN_7)    //DIN PA7
#define OLED_SDIN_Set() gpio_bit_set(GPIOA,GPIO_PIN_7)

#define OLED_CS_Clr()  gpio_bit_reset(GPIOB,GPIO_PIN_2)     //CS PB2
#define OLED_CS_Set()  gpio_bit_set(GPIOB,GPIO_PIN_2)
#endif /* SPI0_CFG */

#define OLED_RST_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_1)     //RES PB1
#define OLED_RST_Set() gpio_bit_set(GPIOB,GPIO_PIN_1)

#define OLED_DC_Clr() gpio_bit_reset(GPIOB,GPIO_PIN_0)      //DC PB0
#define OLED_DC_Set() gpio_bit_set(GPIOB,GPIO_PIN_0)


#if     HAS_BLK_CNTL
#define OLED_BLK_Clr()  gpio_bit_reset(GPIOA,GPIO_PIN_5)//BLK
#define OLED_BLK_Set()  gpio_bit_set(GPIOA,GPIO_PIN_5)
#else
#define OLED_BLK_Clr()
#define OLED_BLK_Set()
#endif

#define OLED_CMD  0	//Write command
#define OLED_DATA 1	//Write data

extern  uint16_t BACK_COLOR;   //Background color
extern unsigned char image[12800];

void LCD_Writ_Bus(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);
void LCD_WR_REG(uint8_t dat);
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Lcd_Init(void);
void LCD_Clear(uint16_t Color);
void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t index,uint8_t size,uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void LCD_DrawPoint_big(uint16_t x,uint16_t y,uint16_t color);
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode,uint16_t color);
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t color);
uint32_t mypow(uint8_t m,uint8_t n);
void LCD_ShowNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t color);
void LCD_ShowNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t color);
void LCD_ShowPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_ShowLogo(void);


//Brush color
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //brown
#define BRRED 			 0XFC07 //maroon
#define GRAY  			 0X8430 //gray
//GUI color

#define DARKBLUE      	 0X01CF	//navy blue
#define LIGHTBLUE      	 0X7D7C	//light blue 
#define GRAYBLUE       	 0X5458 //gray blue
//The above three colors are the colors of PANEL
 
#define LIGHTGREEN     	 0X841F //light green
#define LGRAY 			     0XC618 //Light gray (PANNEL), form background color

#define LGRAYBLUE        0XA651 //Light gray blue (middle layer color)
#define LBBLUE           0X2B12 //Light brown blue (inverted color of selected item)


					  		 
#endif  
