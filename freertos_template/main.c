#include "gd32vf103.h"
#include "longan_nano.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define INTERVAL    250

#define R   0
#define G   1
#define B   2

// static StackType_t    _led_task_stack[configMINIMAL_STACK_SIZE];
// static StaticTask_t   _led_task;

static StackType_t    _led_tasks_stack[3][configMINIMAL_STACK_SIZE];
static StaticTask_t   _led_tasks[3];

static StaticQueue_t  _led_queues[3];
static uint8_t        _led_queue_bufs[3][4];
static QueueHandle_t  _led_queue_handles[3];

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

    xQueueSend(_led_queue_handles[1], &b, portMAX_DELAY);

    xQueueReceive(_led_queue_handles[0], &b, portMAX_DELAY);
  }

}

static void
led_task_g(void* priv)
{
  uint8_t b;

  while(1)
  {
    xQueueReceive(_led_queue_handles[1], &b, portMAX_DELAY);

    longan_nano_led_on(LEDG);
    longan_nano_led_off(LEDR);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    xQueueSend(_led_queue_handles[2], &b, portMAX_DELAY);
  }
}

static void
led_task_b(void* priv)
{
  uint8_t b;

  while(1)
  {
    xQueueReceive(_led_queue_handles[2], &b, portMAX_DELAY);

    longan_nano_led_on(LEDB);
    longan_nano_led_off(LEDG);
    vTaskDelay(INTERVAL / portTICK_PERIOD_MS);

    xQueueSend(_led_queue_handles[0], &b, portMAX_DELAY);
  }
}

/*
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
*/

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

  /*
  xTaskCreateStatic(led_task,
    "LEDTask",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 1,
    _led_task_stack,
    &_led_task
  );
  */
  xTaskCreateStatic(led_task_r,
    "LEDTaskR",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 1,
    _led_tasks_stack[0],
    &_led_tasks[0]
  );
  _led_queue_handles[0] = xQueueCreateStatic(4, 1, _led_queue_bufs[0], &_led_queues[0]);

  xTaskCreateStatic(led_task_g,
    "LEDTaskG",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 1,
    _led_tasks_stack[1],
    &_led_tasks[1]
  );
  _led_queue_handles[1] = xQueueCreateStatic(4, 1, _led_queue_bufs[1], &_led_queues[1]);

  xTaskCreateStatic(led_task_b,
    "LEDTaskB",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 1,
    _led_tasks_stack[2],
    &_led_tasks[2]
  );
  _led_queue_handles[2] = xQueueCreateStatic(4, 1, _led_queue_bufs[2], &_led_queues[2]);

  vTaskStartScheduler();

  // should never reach here
  return 0;
}
