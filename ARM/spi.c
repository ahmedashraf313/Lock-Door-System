#include "spi.h"

void vSpiInit(){
  //enable the spi module 
   SYSCTL->RCGCSSI |=(1U<<SPI_module);
   
  //enable the clock gating for the gpio configured o the SPi module 
   SYSCTL->RCGCGPIO |= (1U<<SPI_port);
   
   //make the pins of the SPI module controlled by another hardware periphal not by GPIO
   SPI_PORT->AFSEL |=(1U<<Tx_PIN)  | (1U<<Rx_PIN) | (1U<<FSS_PIN) | (1U<<CLK_PIN);

   //write the pmc encoding in the oins of the SPI  (the pmc encoding for the SPI is 2)
   SPI_PORT->PCTL  |=(2U<<(4* Tx_PIN))  | (2U<<(4 * Rx_PIN)) | (2U<<(4 *FSS_PIN)) | (2U<<(4 * CLK_PIN));
   
   //enable the digital function for the corresponding pins
    SPI_PORT->DEN  |=(1U<<Tx_PIN)  | (1U<<Rx_PIN) | (1U<<FSS_PIN) | (1U<<CLK_PIN);
    
   //clear the SSE bit in the SSICR1 register to disable the SPI operations 
     SPI_MODULE->CR1 &= ~ (1U<<1);
    //slect the type of the SPI MASTER or SLAVE 
      //select  the SPI as a MASTER by setting the SSICR1 register by 0x00000000
        if(SPI_TYPE ==0) SPI_MODULE->CR1 = 0x00000000; 
       
     //select the SPI as a SLAVE 
        //1. to output enable slave mode put 0x00000004 in the SSICR1 register
            if (SPI_TYPE==1 & SLAVE_MODE == 1)  SPI_MODULE->CR1 = 0x00000004 ;
        //2. to output disabled slave mode put 0x0000000c in the  SSICR1 register       
          if (SPI_TYPE==1 & SLAVE_MODE == 0)  SPI_MODULE->CR1 = 0x0000000c ;  
      
       
  //set the clock source system clock or PIOSc
     SPI_MODULE->CC = CLK_SOURCE;
     
  //set the value of the prescale 
     SPI_MODULE->CPSR =PRESCALE;
  
  //set the serial clock rate   
     uint8_t x =(16/(BAUD_RATE * PRESCALE))-1;
     SPI_MODULE->CR0 |=(x <<8);   
     
  //set the size of the data 
     SPI_MODULE->CR0 |= (DATA_SIZE-1)  ;
       
  //set the frame format 
     SPI_MODULE ->CR0 |=(FRAME_FORMAT<<4) ;  
     
  //set the clock phase captured on the first or second edge
      SPI_MODULE->CR0 |=(CLK_POLARITY <<6);
   
     
  //set the clock phase captured on the first or second edge 
     SPI_MODULE->CR0 |=  (CLK_PHASE <<7);  
  
  
  //enable the SPI by setting the SEE bit in the SSICR1 register.
     SPI_MODULE->CR1 |=(1U<<1) ;

}  

uint8_t vSpiTransive(uint8_t x){
  
  
   //transmit 
   SPI_MODULE->DR =x;
    while(SPI_MODULE->SR & (1U<<0) ==0);
   
    //receive    
     //while(SPI_MODULE->SR & (1U<<2) ==0) ;
     return SPI_MODULE->DR;
}
