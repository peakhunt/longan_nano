#include "gd32vf103.h"

void
external_interrupt_handler(uint32_t cause)
{
}

void
irq_entry(uint32_t mcause)
{
  uint32_t ulInterruptNumber;
  typedef void ( * irq_handler_t )( void );
  extern const irq_handler_t vector_base[];

  ulInterruptNumber = mcause & 0xFFF;

  if( vector_base[ ulInterruptNumber ])
  {
    vector_base[ ulInterruptNumber ]();
  }
}
