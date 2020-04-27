#include "longan_nano.h"

/* private variables */
static uint32_t GPIO_PORT[LEDn] = 
{
  LEDR_GPIO_PORT,
  LEDG_GPIO_PORT,
  LEDB_GPIO_PORT,
};

static uint32_t GPIO_PIN[LEDn] = 
{
  LEDR_PIN,
  LEDG_PIN,
  LEDB_PIN
};

static rcu_periph_enum GPIO_CLK[LEDn] = 
{
  LEDR_GPIO_CLK,
  LEDG_GPIO_CLK,
  LEDB_GPIO_CLK
};

void
longan_nano_led_init(led_typedef_enum lednum)
{
  /* enable the led clock */
  rcu_periph_clock_enable(GPIO_CLK[lednum]);

  /* configure led GPIO port */ 
  gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

  GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void
longan_nano_led_on(led_typedef_enum lednum)
{
  GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void
longan_nano_led_off(led_typedef_enum lednum)
{
  GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void
longan_nano_led_toggle(led_typedef_enum lednum)
{
  gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum],
      (bit_status)(1-gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));
}
