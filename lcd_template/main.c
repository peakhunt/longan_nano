#include "gd32vf103.h"
#include "longan_nano.h"
#include "systick.h"
#include <stdio.h>

#include "lcd.h"

#define INTERVAL    100

extern uint32_t disable_mcycle_minstret();

int
main(void)
{
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

   LCD_ShowString(24,  0, (uint8_t *)("no card found!"), BLACK);
   LCD_ShowString(24, 16, (uint8_t *)("no card found!"), BLUE);
   LCD_ShowString(24, 32, (uint8_t *)("no card found!"), BRED);
   LCD_ShowString(24, 48, (uint8_t *)("no card found!"), GBLUE);
   LCD_ShowString(24, 64, (uint8_t *)("no card found!"), RED);

  while(1){
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
}
