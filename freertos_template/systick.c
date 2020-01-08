#include "gd32vf103.h"
#include "FreeRTOS.h"

void vPortSetupTimerInterrupt(void)
{
  // eclic_global_interrupt_enable();

  // 1ms tick
  *(uint64_t*)(TIMER_CTRL_ADDR + TIMER_MTIMECMP) = TIMER_FREQ / 1000;

  eclic_set_nlbits(ECLIC_GROUP_LEVEL2_PRIO2);
  eclic_irq_enable(CLIC_INT_TMR, 3, 3);

  *(uint64_t*)(TIMER_CTRL_ADDR + TIMER_MTIME) = 0;
}

void eclic_mtip_handler(void)
{
  BaseType_t xTaskIncrementTick( void );
  void vTaskSwitchContext( void );

  *(uint64_t*)(TIMER_CTRL_ADDR + TIMER_MTIME) = 0;

  /* vPortSetupTimerInterrupt() uses LPIT0 to generate the tick interrupt. */
  if( xTaskIncrementTick() != 0 )
  {
    vTaskSwitchContext();
  }
}

void eclic_msip_handler(void)
{
}
