#include <avr/io.h>
#define  F_CPU        8000000UL
#include <util/delay.h>
#include <stdint.h>

//set the pins of the master 
#define MASTER_MOSI_PORT        PORTA
#define MASTER_CLK_PORT         PORTA
#define MASTER_MISO_PORT        PORTA


//set the pins of the master 
#define SLAVE_MOSI_PORT         PORTB
#define SLAVE_CLK_PORT          PORTB 
#define SLAVE_MISO_PORT         PORTB



//set the pins of the master and slave 
#define  MASTER_MOSI              5
#define  MASTER_CLK               7
#define  MASTER_MISO              6


//set the pins of the master and slave 
#define  SLAVE_MOSI               5
#define  SLAVE_CLK                7
#define  SLAVE_MISO               6


//define the directions registers  of the master 
#define  MASTER_MOSI_DIR                  DDRB
#define  MASTER_CLK_DIR                   DDRB
#define  MASTER_MISO_DIR                  DDRB

//define the directions registers  of the master
#define  SLAVE_MOSI_DIR                   DDRB
#define  SLAVE_CLK_DIR                    DDRB
#define  SLAVE_MISO_DIR                   DDRB
