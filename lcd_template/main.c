#include "gd32vf103.h"
#include "longan_nano.h"
#include "systick.h"
#include <stdio.h>

#include "lcd.h"
#include "fatfs/tf_card.h"

#define INTERVAL    100

unsigned char image[12800];
FATFS fs;

extern uint32_t disable_mcycle_minstret();

int
main(void)
{
  uint8_t mount_is_ok = 1; /* 0: mount successful ; 1: mount failed */
  int offset = 0;
  FIL fil;
  FRESULT fr;     /* FatFs return code */
  UINT br;

  // at this point
  // a) the chip is set to use external 8 MHz crystal to
  //    generate 108 MHz core clock
  //
  // b) ...
  //
  longan_nano_led_init(LEDR);
  longan_nano_led_init(LEDG);
  longan_nano_led_init(LEDB);

  longan_nano_led_off(LEDR);
  longan_nano_led_off(LEDG);
  longan_nano_led_off(LEDB);

  Lcd_Init();     // init OLED
  LCD_Clear(WHITE);
  BACK_COLOR = WHITE;

	fr = f_mount(&fs, "", 1);
	if (fr == 0)
		mount_is_ok = 1;
	else
		mount_is_ok = 0;

	if (!mount_is_ok)
  {
    LCD_ShowString(24,  0, (uint8_t *)("no card found!"), BLACK);
    LCD_ShowString(24, 16, (uint8_t *)("no card found!"), BLUE);
    LCD_ShowString(24, 32, (uint8_t *)("no card found!"), BRED);
    LCD_ShowString(24, 48, (uint8_t *)("no card found!"), GBLUE);
    LCD_ShowString(24, 64, (uint8_t *)("no card found!"), RED);
  }

  while(1){
    if (!mount_is_ok)
    {
      longan_nano_led_on(LEDR);
      longan_nano_led_off(LEDB);
      delay_1ms(INTERVAL);

      longan_nano_led_on(LEDG);
      longan_nano_led_off(LEDR);
      delay_1ms(INTERVAL);

      longan_nano_led_on(LEDB);
      longan_nano_led_off(LEDG);
      delay_1ms(INTERVAL);
    }
    else
    {
      offset = 0;
      fr = f_open(&fil, "logo.bin", FA_READ);
      if (fr) printf("open error: %d!\n\r", (int)fr);
      f_lseek(&fil, offset);
      fr = f_read(&fil, image, sizeof(image), &br);
      LCD_ShowPicture(0,0,159,39);

      offset += 12800;

      longan_nano_led_toggle(LEDG);
      
      f_lseek(&fil, offset);
      fr = f_read(&fil, image, sizeof(image), &br);
      LCD_ShowPicture(0,40,159,79);

      longan_nano_led_toggle(LEDG);

      delay_1ms(1500);
      f_close(&fil);

      fr = f_open(&fil, "bmp.bin", FA_READ);
      if (fr) printf("open error: %d!\n\r", (int)fr);
      offset = 0;

      for (int i=0; i<2189;i++)
      {
        fr = f_read(&fil, image, sizeof(image), &br);
        LCD_ShowPicture(0,0,159,39);
        offset += 12800;
        f_lseek(&fil, offset);
        
        longan_nano_led_toggle(LEDG);
        
        fr = f_read(&fil, image, sizeof(image), &br);
        LCD_ShowPicture(0,40,159,79);
        offset += 12800;
        f_lseek(&fil, offset);

        longan_nano_led_toggle(LEDG);
      }
      /* Close the file */
      f_close(&fil);
    }
  }
}
