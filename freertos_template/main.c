#include "gd32vf103.h"
#include "longan_nano.h"
#include "systick.h"
#include <stdio.h>

#define INTERVAL    150

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
