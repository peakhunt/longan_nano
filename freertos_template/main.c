#include "gd32vf103.h"
#include "longan_nano.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#define INTERVAL    150

extern uint32_t disable_mcycle_minstret();

static StackType_t    _led_task_stack[configMINIMAL_STACK_SIZE];
static StaticTask_t   _led_task;

void
vAssertCalled(void)
{
  while(1)
    ;
}

void
vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
    StackType_t **ppxIdleTaskStackBuffer,
    uint32_t *pulIdleTaskStackSize )
{
  static StaticTask_t       idleTCBBuffer;
  static StackType_t        idleStack[configMINIMAL_STACK_SIZE];

  *ppxIdleTaskTCBBuffer   = &idleTCBBuffer;
  *ppxIdleTaskStackBuffer = idleStack;
  *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}

static void
led_task(void* priv)
{
  while(1)
  {
    longan_nano_led_on(LEDR);
    longan_nano_led_off(LEDB);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    longan_nano_led_on(LEDG);
    longan_nano_led_off(LEDR);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    longan_nano_led_on(LEDB);
    longan_nano_led_off(LEDG);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);
  }
}

int
main(void)
{
  // vStartStaticallyAllocatedTasks();

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

  xTaskCreateStatic(led_task,
    "LEDTask",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 1,
    _led_task_stack,
    &_led_task
  );

  vTaskStartScheduler();

  // should never reach here
  return 0;
}
