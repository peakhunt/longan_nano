#include "gd32vf103.h"
#include "longan_nano.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define INTERVAL    150

#define R   0
#define G   1
#define B   2

static void led_task_r(void* priv);
static void led_task_g(void* priv);
static void led_task_b(void* priv);

typedef struct
{
  StackType_t       stack[configMINIMAL_STACK_SIZE];
  StaticTask_t      task;
  StaticQueue_t     queue;
  uint8_t           queue_buf[4];
  QueueHandle_t     queue_handle;
  const char*       name;
  TaskFunction_t    func;
} led_task_t;

static led_task_t   _led_tasks[3] =
{
  {
    .name = "LEDTaskR",
    .func = led_task_r,
  },
  {
    .name = "LEDTaskG",
    .func = led_task_g,
  },
  {
    .name = "LEDTaskB",
    .func = led_task_b,
  },
};


const int  __attribute__((used)) uxTopUsedPriority = configMAX_PRIORITIES - 1;

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
led_task_r(void* priv)
{
  uint8_t   b = 0xff;

  while(1)
  {
    longan_nano_led_on(LEDR);
    longan_nano_led_off(LEDB);

    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    xQueueSend(_led_tasks[G].queue_handle, &b, portMAX_DELAY);

    xQueueReceive(_led_tasks[R].queue_handle, &b, portMAX_DELAY);
  }

}

static void
led_task_g(void* priv)
{
  uint8_t b;

  while(1)
  {
    xQueueReceive(_led_tasks[G].queue_handle, &b, portMAX_DELAY);

    longan_nano_led_on(LEDG);
    longan_nano_led_off(LEDR);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    xQueueSend(_led_tasks[B].queue_handle, &b, portMAX_DELAY);
  }
}

static void
led_task_b(void* priv)
{
  uint8_t b;

  while(1)
  {
    xQueueReceive(_led_tasks[B].queue_handle, &b, portMAX_DELAY);

    longan_nano_led_on(LEDB);
    longan_nano_led_off(LEDG);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    xQueueSend(_led_tasks[R].queue_handle, &b, portMAX_DELAY);
  }
}

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

  for(int i = 0; i < 3; i++)
  {
    xTaskCreateStatic(_led_tasks[i].func,
      _led_tasks[i].name,
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 1,
      _led_tasks[i].stack,
      &_led_tasks[i].task
    );
    _led_tasks[i].queue_handle = xQueueCreateStatic(sizeof(_led_tasks[i].queue_buf), 1, _led_tasks[i].queue_buf, &_led_tasks[i].queue);
  }

  vTaskStartScheduler();

  // should never reach here
  return 0;
}
