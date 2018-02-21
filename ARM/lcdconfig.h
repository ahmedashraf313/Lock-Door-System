#include <stdint.h>
#include "TM4C123GH6PM.h"


//define the ports of the pins
#define RS_PORT    GPIOA
#define RW_PORT    GPIOA
#define E_PORT     GPIOA
#define D0_PORT    GPIOC
#define D1_PORT    GPIOC
#define D2_PORT    GPIOC
#define D3_PORT    GPIOC 
#define D4_PORT    GPIOC
#define D5_PORT    GPIOC
#define D6_PORT    GPIOC
#define D7_PORT    GPIOC

//define the ports only for the clock gating 

#define RS_port  PORTA
#define RW_port  PORTA
#define E_port   PORTA
#define D0_port  PORTC
#define D1_port  PORTC
#define D2_port  PORTC
#define D3_port  PORTC
#define D4_port  PORTC
#define D5_port  PORTC
#define D6_port  PORTC
#define D7_port  PORTC



//define the pins of the lcd pins
#define RS     2
#define RW     3
#define E      4
#define D0     0 
#define D1     1
#define D2     2 
#define D3     3
#define D4     4
#define D5     5
#define D6     6
#define D7     7

