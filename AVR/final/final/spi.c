#include "spi.h"

void masterInit(){
	//enable the SPI
	  SPCR |= (1U<<SPE);
	  
	//set the device as master
	 SPCR |= (1U<<MSTR);
	 
	//set the MOSI and CLk as output
	  MASTER_MOSI_DIR |= (1U<<MASTER_MOSI);
	  MASTER_CLK_DIR  |= (1U<<MASTER_CLK );
	
	//set the MISO as input
	  MASTER_MISO_DIR &=~(1U<<MASTER_MISO);
	  
	//set the clock polarity  Leading Edge(Rising) Trailing Edge  (Falling)
	  SPCR &=~(1U<<CPOL);
	  
	//set the clock phase
	 SPCR &=~(1U<<CPHA);  
	
   //set the clock rate (Fosc/16) 0 0 1
     SPCR |=(1U<<SPR0);
	 SPCR &=~(1U<<SPR1);
	 SPSR &=~(1U<<SPI2X); 	
	
}

void slaveInit (){
	//enable the SPI
	SPCR |= (1U<<SPE);
	
	//set the device as slave
	SPCR &= ~(1U<<MSTR);
	
	//set the MOSI and CLk as input
	MASTER_MOSI_DIR &= ~(1U<<MASTER_MOSI);
	MASTER_CLK_DIR  &= ~(1U<<MASTER_CLK );
	
	//set the MISO as output
	MASTER_MISO_DIR |=(1U<<MASTER_MISO);
	
	
	
}

uint8_t masterTransive(uint8_t data){
	SPDR =data;
	
	while(!(SPSR & (1<<SPIF)));
}

uint8_t slaveTransive(uint8_t data){
	SPDR=data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}