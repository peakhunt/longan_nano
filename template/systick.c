#include "gd32vf103.h"
#include "systick.h"

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count)
{
  uint64_t start_mtime, delta_mtime;

  // Don't start measuruing until we see an mtime tick
  uint64_t tmp = get_timer_value();
  do {
    start_mtime = get_timer_value();
  } while (start_mtime == tmp);

  //
  // GD32VF103 user manual, section 5.2.1
  // CK_CST (CPU sys tick) is CK_AHB / 4
  // In my case, it should be 108Mhz / 4 if everything is setup ok
  // So 1ms mtime increment is 108Mhz / 4 / 1000
  //
  do {
    delta_mtime = get_timer_value() - start_mtime;
  }while(delta_mtime <(SystemCoreClock/4000.0 *count ));
}
