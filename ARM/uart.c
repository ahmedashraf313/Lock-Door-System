#include "uart.h"

void vUartInit(){
//enable the clock gating of the UART
   SYSCTL->RCGCUART |=(1U<<UART_module);

//enable the clock gating for the gpio connected to UART module
    //SYSCTL->RCGC2    |=(1U<<0); 
    SYSCTL->RCGCGPIO |=(1U<<UART_port); 
    
   
//set the pins of the UART as alternate function select
   UART_PORT->AFSEL |=(1U<<TX_PIN); 
   UART_PORT->AFSEL |=(1U<<RX_PIN);
   
//Configure the GPIO current level  (we select the -ma drive)  
      UART_PORT->DR2R |=(1U<<TX_PIN);
      UART_PORT->DR2R |=(1U<<RX_PIN);
      
//Configure the GPIO slew rate only for 8-mA drive   

   
//Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate pin  
      UART_PORT->PCTL =0x11;
      UART_PORT->DEN |=(1U<<0) |(1U<<1);


 //disable the UART
 UART_MODULE->CTL &=~(1U<<0);
 
 //write the integer part of the baud rate 
 UART_MODULE->IBRD =INTEGER_PART;
 
 //write the fraction part of the baud rate
 if(FRACTION_PART <64)  
 UART_MODULE->FBRD =FRACTION_PART;
 
 //select the type of parity odd(o) or even(e)
 if(PARITY_TYPE==0)
  UART_MODULE->LCRH &= ~(1U<<7); 
 else {
 UART_MODULE->LCRH |= (1U<<7) | (1U<<1);
 
 if (PARITY_TYPE==1)
   UART_MODULE->LCRH &=~(1U<<2);
 if(PARITY_TYPE==2)
   UART_MODULE->LCRH |=(1U<<2);
 }
 
 //select the number of the data bits 5,6,7 or 8
 if (DATA_BITS==5)
   UART_MODULE->LCRH &=~(1U<<5);
   UART_MODULE->LCRH &=~(1U<<6);
if(DATA_BITS==6)
   UART_MODULE->LCRH |=(1U<<5);
   UART_MODULE->LCRH &=~(1U<<6);
if(DATA_BITS==7)
   UART_MODULE->LCRH &=~(1U<<5);
   UART_MODULE->LCRH |=(1U<<6);
if(DATA_BITS==8)
   UART_MODULE->LCRH |=(1U<<5);
   UART_MODULE->LCRH |=(1U<<6);
   
//enable or disable the FIFO when disabled it becomes one byte deep holding register(i disabled it)
   UART_MODULE->LCRH &=~(1U<<4);
   
//control the number of the stop bits 0 for one bit and 1 for two bits
  UART_MODULE->LCRH &=~(1U<<3);
  
//control the send break 
 UART_MODULE->LCRH &=~(1U<<0);
 
//control the clock of the UART 
UART_MODULE->CC =0;     //selet the clock of the system 

//Optionally, configure the µDMA channel (see “Micro Direct Memory Access (µDMA)” on page 585)
//and enable the DMA option(s) in the UARTDMACTL register


//enable the UART
 UART_MODULE->CTL |=(1U<<0);
 
//enable the transmission and receiving pins
UART_MODULE->CTL  |=(1U<<8) | (1U<<9); 
 
}


uint8_t u8UartRecive(){
   
  while((UART_MODULE->FR & (1U<<4)) !=0);
  uint8_t x=UART_MODULE->DR;
  vUartTrans(x);
  return x;
}


void vUartTrans(uint8_t x){
   while((UART_MODULE->FR & (1U<<5)) !=0 ); 
 UART_MODULE->DR =x;
}

void vTransString(uint8_t* x){
  uint8_t i=0;
  while(x[i] !=0){
    vUartTrans(x[i]);
    i++;}
  vUartTrans(31);
}

uint8_t* u8ReciveString(){
  uint8_t* x;
  uint8_t  i=0;
  while(u8UartRecive()!=13){
    x[i]= u8UartRecive();
    i++;}
    
  return x;
}

void vUartDelete(){
  uint8_t i=0;
  while(i<100){
    vUartTrans(127);
    i++;}
}