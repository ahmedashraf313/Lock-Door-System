#include "delay.h"

void delay(uint32_t period)
{
  while(period--)
  {
    asm volatile("nop");
  }
  
}
