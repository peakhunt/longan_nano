#ifndef LONGAN_NANO_DEF_H
#define LONGAN_NANO_DEF_H

#ifdef cplusplus
 extern "C" {
#endif

#include "gd32vf103.h"
     
/* exported types */
typedef enum 
{
  LEDR = 0,
  LEDG = 1,
  LEDB = 2,
} led_typedef_enum;

#define LEDn                             3U

#define LEDR_PIN                         GPIO_PIN_13
#define LEDR_GPIO_PORT                   GPIOC
#define LEDR_GPIO_CLK                    RCU_GPIOC

#define LEDG_PIN                         GPIO_PIN_1
#define LEDG_GPIO_PORT                   GPIOA
#define LEDG_GPIO_CLK                    RCU_GPIOA
  
#define LEDB_PIN                         GPIO_PIN_2
#define LEDB_GPIO_PORT                   GPIOA
#define LEDB_GPIO_CLK                    RCU_GPIOA
  
void longan_nano_led_init(led_typedef_enum lednum);
void longan_nano_led_on(led_typedef_enum lednum);
void longan_nano_led_off(led_typedef_enum lednum);
void longan_nano_led_toggle(led_typedef_enum lednum);

#ifdef cplusplus
}
#endif

#endif //!LONGAN_NANO_DEF_H
