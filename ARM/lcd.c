#include "lcd.h"

void lcdInit(){
    
      CLK_GATING
        
      ENABLE_DIGITAL
        
      PINS_OUTPUT
       
      _delay_ms(100);
      
      
      
      
      RS_PORT->DATA &=~(1U<<RS);
      
      E_PORT->DATA &=~(1U<<E);
      
      lcdWrite(lcd_FunctionReset); 
      _delay_ms(10);
      
      lcdWrite(lcd_FunctionReset); 
      _delay_us(200);
      
      lcdWrite(lcd_FunctionReset); 
      _delay_us(200);
      
      
      lcdSendCommand(FUN_SET);
      _delay_us(80);
      
      lcdSendCommand(FUN_SET);         //set the 4 bit mode 
      _delay_us(80);
      
      lcdSendCommand(DISPLAY_OFF);
      _delay_us(80);
      
      lcdSendCommand(DISPLAY_CLEAR);
      _delay_ms(4);
      
      lcdSendCommand(ENTRY_MODE);
      _delay_us(80);
      
      lcdSendCommand(DISPLAY_ON);
      
      _delay_us(80);
      
      
      
    
}

 void lcdSendCommand(uint8_t command){
   
  RS_PORT->DATA &=~(1U<<RS);
  RW_PORT->DATA &=~(1U<<RW);
  E_PORT->DATA  &= ~(1U<<E);
  lcdWrite(command);
  lcdWrite(command << 4);
  }

void lcdSendChar(uint8_t data){
  RS_PORT->DATA |=(1U<<RS);
  RW_PORT->DATA &=~(1U<<RW);
  E_PORT->DATA  &= ~(1U<<E);
  lcdWrite(data);
  lcdWrite(data << 4);
}
    

void lcdWrite(uint8_t Byte){
  
  
        D7_PORT->DATA &= ~(1U<<D7);                        // assume that data is '0'
	if (Byte & (1U<<D7))
	D7_PORT->DATA |= (1U<<D7);			 // make data = '1' if necessary
	
	D6_PORT->DATA &= ~(1U<<D6);                       // repeat for each data bit
	if (Byte & (1U<<D6))
	D6_PORT->DATA |= (1U<<D6);

	D5_PORT->DATA &= ~(1U<<D5);
	if (Byte & (1U<<D5))
	D5_PORT->DATA |= (1U<<D5);

	D4_PORT->DATA &= ~(1U<<D4);
	if (Byte & (1U<<D4))
	D4_PORT->DATA |= (1U<<D4);
        
          E_PORT->DATA |=(1U<<E);
          _delay_us(5);
          E_PORT->DATA &=~(1U<<E);
          _delay_us(5);

  /*
  D4_PORT->DATA |=(((byte&(1U<<4))<<4)>>D4);
  D5_PORT->DATA |=(((byte&(1U<<5))<<5)>>D5);
  D6_PORT->DATA |=(((byte&(1U<<6))<<6)>>D6);
  D7_PORT->DATA |=(((byte&(1U<<7))<<7)>>D7);
  
  E_PORT->DATA |=(1U<<E);
  delay(3);
  E_PORT->DATA &=~(1U<<E);
  delay(3);
  
  byte = byte << 4;
  
  D4_PORT->DATA |=(((byte&(1U<<4))<<4)>>D4);
  D5_PORT->DATA |=(((byte&(1U<<5))<<5)>>D5);
  D6_PORT->DATA |=(((byte&(1U<<6))<<6)>>D6);
  D7_PORT->DATA |=(((byte&(1U<<7))<<7)>>D7);*/
}

  void  _delay_ms(uint8_t x){
    uint32_t i=0;
    while(i<(x*16000))
      i++;
      
  }

void _delay_us(uint8_t x)
{uint32_t i=0;
 while(i<(x*16))
   i++;
}

void lcdSendString (uint8_t* x){
  uint8_t i=0;
  while (x[i] !=0)
  {lcdSendChar(x[i]);
  i++;}
}  

void lcdCoordination(uint8_t y,uint8_t x)
{
	//first location on first row and first on second row
		uint8_t firstlocation[]={0x80,0xC0};
		lcdSendCommand((firstlocation[y-1])+(x-1)); 	
		_delay_us(100);
}