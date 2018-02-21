#include "lcdconfig.h"

// the prototypes of the function 
void  lcdInit           (void            );
void  lcdSendChar       (uint8_t         );
void  lcdSendCommand    (uint8_t         );
void  lcdWrite          (uint8_t         );
void  _delay_ms         (uint8_t         );
void  _delay_us         (uint8_t         );
void  lcdSendString     (uint8_t *       );
void  lcdCoordination   (uint8_t ,uint8_t);

//define the number of the ports only for clock gating
#define  PORTA  0
#define  PORTB  1
#define  PORTC  2
#define  PORTD  3
#define  PORTE  4
#define  PORTF  5

//the functions of the lcd micro
#define FUNCTION_SET       0x3c  //2lines , 5*10 font and 8bit mode
#define FUN_SET            0x28  //2lines , 5*8 font and 4bit mode 0b00101000
#define DISPLAY_OFF        0x08  //no display , no cursor and no blinking
#define DISPLAY_ON         0x0f  //display on , cursor on and no blinking 0b00001111
#define DISPLAY_CLEAR      0x01
#define ENTRY_MODE         0x06  //increment and no shift
#define lcd_FunctionReset  0x3c  

 //enable the clock gating for the ports of the pins
#define CLK_GATING      SYSCTL->RCGCGPIO |=(1U<<RS_port);\
                        SYSCTL->RCGCGPIO |=(1U<<RW_port);\
                        SYSCTL->RCGCGPIO |=(1U<<E_port);\
                        SYSCTL->RCGCGPIO |=(1U<<D4_port);\
                        SYSCTL->RCGCGPIO |=(1U<<D5_port);\
                        SYSCTL->RCGCGPIO |=(1U<<D6_port);\
                        SYSCTL->RCGCGPIO |=(1U<<D7_port);



//enable the digital function for all pins
#define  ENABLE_DIGITAL         RS_PORT->DEN |=(1U<<RS);\
                                RW_PORT->DEN |=(1U<<RW);\
                                E_PORT->DEN  |=(1U<<E);\
                                D4_PORT->DEN |=(1U<<D4);\
                                D5_PORT->DEN |=(1U<<D5);\
                                D6_PORT->DEN |=(1U<<D6);\
                                D7_PORT->DEN |=(1U<<D7);
                                

 //set the direction of the pins as output
#define PINS_OUTPUT         RS_PORT->DIR |=(1U<<RS);\
                            RW_PORT->DIR |=(1U<<RW);\
                            E_PORT->DIR  |=(1U<<E);\
                            D4_PORT->DIR |=(1U<<D4);\
                            D5_PORT->DIR |=(1U<<D5);\
                            D6_PORT->DIR |=(1U<<D6);\
                            D7_PORT->DIR |=(1U<<D7);                               

