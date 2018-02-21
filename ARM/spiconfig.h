#include "TM4C123GH6PM.h"
#include <stdint.h>

//define the module of the spi  to enable the clk gating
#define SPI_module   MODULE2

//define the module of the SPI
#define SPI_MODULE    SSI2

//define the port of the SPI for the clock gating 
#define SPI_port     PORTB

//define the port of the SPI to control the pins 
#define SPI_PORT     GPIOB

//define the pins of the SPI 
#define Tx_PIN         7 
#define Rx_PIN         6
#define FSS_PIN        5
#define CLK_PIN        4

//define the SPI is MASTER or SLAVE
#define SPI_TYPE       0  //0.master mode  1.slave mode

//define the SPI SLave mode 
#define SLAVE_MODE    0    //0.output disabled  1.output enabled

//define the clock source for the SPI
#define CLK_SOURCE     0   //0.for system clock source   1.for PIOSc (60mhz)

//define the prescalar value which is a even value from 2 to 254 
#define PRESCALE       2 

//define the baud rate
#define BAUD_RATE      1   //in MegaHertz

//define the frame format of the SPI
#define FRAME_FORMAT   0    //0.free scale  1. texas  2. micowire

//define the data size 
#define DATA_SIZE      8    //in bits (at least 4 bits)

//define the clock phase captured on the first or second edge 
#define CLK_PHASE      0   //0. on the first edge  ** 1. on the second edge

//define the clock polarity steady state low or high
#define CLK_POLARITY   0  //0.steady state low **  1.steady state high

