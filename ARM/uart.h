#include "uartconfig.h"

//define the moduels of the UART
#define MODULE0         0
#define MODULE1         1
#define MODULE2         2
#define MODULE3         3
#define MODULE4         4
#define MODULE5         5
#define MODULE6         6
#define MODULE7         7

//set the clock gating pin for each port in the GPIO
#define PORTA           0
#define PORTB           1
#define PORTC           2
#define PORTD           3
#define PORTE           4
#define PORTF           5



//define the prototypes of the UART functions
void        vUartInit      (void       );
void        vUartTrans     (uint8_t    );
uint8_t     u8UartRecive   (void       ); 
void        vTransString   (uint8_t *  );
uint8_t*    u8ReciveString (void       );
void        vUartDelete       (void       ); 
