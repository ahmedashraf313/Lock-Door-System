
#include "final.h"


int main()
{ //intialize the drivers 
  intial();
  
  //recive the passwords from the EEPROM  
  recive_pass();
  delay(MS(300));
  
  //recive the user names
 // recive_users();
 // delay(MS(300));
  
  //get the unwanted byte from the slave
  vSpiTransive(5);
  delay(MS(100));
  
  
while(1){

  //get the password by the user and view on the lcd  and on the UART 
  get_pass();
 
}
  
 /* 
  lcdInit();
  vKeypadInit();
  vUartInit();
  while(1){
    lcdSendCommand(DISPLAY_CLEAR);
     _delay_ms(20);
    lcdSendString("press enter");
    while(u8KeypadRead()!='e');
  lcdSendCommand(DISPLAY_CLEAR); 
   _delay_ms(20);
 lcdSendString("hello");
 _delay_ms(200);
 lcdSendCommand(DISPLAY_CLEAR);
 _delay_ms(20);
 lcdSendString("enter password");
 for(uint8_t i=0;i<4;i++){
   lcdCoordination(2,16-i);
   while(u8KeypadRead()==0);
   uint8_t x=u8KeypadRead();
   if(i==0)
   vUartDelete();
   lcdSendChar(x);
   vUartTrans(x);
   _delay_ms(50);
   lcdCoordination(2,16-i);
   lcdSendChar('*');}
  vTransString("   is entering the door at   ");
 lcdSendCommand(DISPLAY_CLEAR); 
 _delay_ms(20);
  lcdSendString("welcome");
   _delay_ms(200);
  }
  */
return 0;}
  
  
 
 
