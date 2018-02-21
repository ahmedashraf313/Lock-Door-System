#include "TM4C123GH6PM.h"
#include <stdint.h>

//define the ports of the row and colums
#define R1_PORT   GPIOE
#define R2_PORT   GPIOE
#define R3_PORT   GPIOE
#define R4_PORT   GPIOF
#define C1_PORT   GPIOD
#define C2_PORT   GPIOD
#define C3_PORT   GPIOD
#define C4_PORT   GPIOD

//define the pins of the rows and colums
#define R1     1
#define R2     2
#define R3     3
#define R4     1
#define C1     0
#define C2     1
#define C3     2
#define C4     3

//define the ports of the pins for the clock gating only
#define R1_port    PORTE
#define R2_port    PORTE
#define R3_port    PORTE
#define R4_port    PORTF
#define C1_port    PORTD
#define C2_port    PORTD
#define C3_port    PORTD
#define C4_port    PORTD