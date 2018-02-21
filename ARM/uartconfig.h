#include "TM4C123GH6PM.h"
#include <stdint.h>


//set the module of the UART
#define UART_module     0

//set the module of the UART to access registers of the UART
#define UART_MODULE      UART0

//set the GPIO pin connected to the UART module for clock gating only
#define UART_port     PORTA 

//set the port connected to the UART
#define UART_PORT     GPIOA

//define the transmit pin and recive pin 
#define TX_PIN   1
#define RX_PIN   0

//the configration of the UART
#define DATA_BITS       8
#define PARITY_TYPE     0    //0.disable  1. odd  2. even 
#define INTEGER_PART    104
#define FRACTION_PART   11
