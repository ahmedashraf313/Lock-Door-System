#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>
#include "delayconfig.h"
#ifndef F_CPU
  #warning "F_CPU is not defined for delay.h"
  #define F_CPU 16000000UL 	// 16 Mhz 
#endif

#define LOOP_CYCLES 5 		//Number of cycles that the loop takes

#define US(NUM) (NUM/(LOOP_CYCLES*(1/(F_CPU/1000000.0))))
#define MS(NUM) (NUM/(LOOP_CYCLES*(1/(F_CPU/1000.0))))

void delay(uint32_t period);





#endif   //DELAY_H_