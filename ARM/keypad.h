#include "keypadconfig.h"

#define ALL_LINES   ((((C1_PORT->DATA&(1U<<C1))>>C1))&(((C2_PORT->DATA&(1U<<C2))>>C2))&(((C3_PORT->DATA &(1U<<C3))>>C3))&(((C4_PORT->DATA&(1U<<C4))>>C4)))

//define the prototypes of the functions 
uint8_t u8KeypadRead(void );
void    vKeypadInit(void  ); 



