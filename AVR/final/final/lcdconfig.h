#ifndef	LCDCONFIG_H_
#define LCDCONFIG_H_

//uncomment your Target
#define USE_ATMEGA32
//#define USE_TM4C123GH6PM


#ifndef USE_ATMEGA32
#ifndef USE_TM4C123GH6PM
	#error "your target is not defined. available targets are: USE_ATMEGA32 or USE_TM4C123GH6PM"
#endif
#endif


#ifdef USE_ATMEGA32
#ifdef USE_TM4C123GH6PM
	#error "USE_ATMEGA32 and USE_TM4C123GH6PM are both defined"
#endif
#endif


#ifdef USE_ATMEGA32
	#define F_CPU	8000000UL
	#include <avr/io.h>
	#include <util/delay.h>
#endif

#ifdef USE_TM4C123GH6PM
	#define F_CPU	16000000UL
	#include "TM4C123GH6PM.h"
	#include "delay.h"
#endif

#include <stdint.h>

/***************************************************************************
The four data lines as well as the two control lines may be
implemented on any available I/O pin of any port.  These are
the connections used for this program:

-----------                   ----------
|TM4C123GH6PM|                |   LCD    |
|           |                 |          |
|        PC7|---------------->|D7        |
|        PC6|---------------->|D6        |
|        PC5|---------------->|D5        |
|        PC4|---------------->|D4        |
|           |                 |D3        |
|           |                 |D2        |
|           |                 |D1        |
|           |                 |D0        |
|           |                 |          |
|        PA4|---------------->|E         |
|        PA3|---------------->|RW        |
|        PA2|---------------->|RS        |
-----------                   ----------

**************************************************************************/

#ifdef USE_TM4C123GH6PM
        #define  PORTA_GATE_PIN          0
        #define  PORTB_GATE_PIN          1
        #define  PORTC_GATE_PIN          2
        #define  PORTD_GATE_PIN          3
        #define  PORTE_GATE_PIN          4
        #define  PORTF_GATE_PIN          5
		//lcd D7 pin
        #define LCD_PORT_D7_GATE        PORTC_GATE_PIN
        #define LCD_D7_PORT_BASE        GPIOC
        //lcd D7 pin
        #define LCD_PORT_D6_GATE        PORTC_GATE_PIN
        #define LCD_D6_PORT_BASE        GPIOC
        //lcd D7 pin
        #define LCD_PORT_D5_GATE        PORTC_GATE_PIN
        #define LCD_D5_PORT_BASE        GPIOC
        //lcd D7 pin
        #define LCD_PORT_D4_GATE        PORTC_GATE_PIN
        #define LCD_D4_PORT_BASE        GPIOC
        //lcd Register Select pin
        #define RS_PORT_GATE            PORTA_GATE_PIN
        #define RS_PORT_BASE            GPIOA
        //lcd Read/write pin
        #define RW_PORT_GATE            PORTA_GATE_PIN
        #define RW_PORT_BASE            GPIOA
        //lcd Enable pin
        #define E_PORT_GATE             PORTA_GATE_PIN
        #define E_PORT_BASE             GPIOA
#endif
//lcd D7 pin
#define LCD_PORT_D7     	PORTA
#define LCD_DDR_D7      	DDRA
#define D7_BIT		        7
//lcd D6 pin
#define LCD_PORT_D6     	PORTA
#define LCD_DDR_D6      	DDRA
#define D6_BIT				6
//lcd D5 pin
#define LCD_PORT_D5     	PORTA
#define LCD_DDR_D5      	DDRA
#define D5_BIT				5
//lcd D4 pin
#define LCD_PORT_D4     	PORTA
#define LCD_DDR_D4      	DDRA
#define D4_BIT				4
//lcd Register Select pin
#define RS_PORT				PORTB
#define RS_BIT				1
#define RS_DDR				DDRB
//lcd Read/write pin	
#define RW_PORT				PORTB
#define RW_BIT				2
#define RW_DDR				DDRB
//lcd Enable pin	
#define E_PORT				PORTB
#define E_BIT				3
#define E_DDR				DDRB
 
#endif // LCDCONFIG_H_