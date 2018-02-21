#include "final.h"

int main(void)
{
 /*
//write the intial value for passwords
_delay_ms(5);
EEWriteByte(0x0000,1);
_delay_ms(5);
EEWriteByte(0x0001,2);
_delay_ms(5);
EEWriteByte(0x0002,3);
_delay_ms(5);
EEWriteByte(0x0003,4);
_delay_ms(5);
EEWriteByte(0x0004,1);
_delay_ms(5);
EEWriteByte(0x0005,3);
_delay_ms(5);
EEWriteByte(0x0006,0);
_delay_ms(5);
EEWriteByte(0x0007,3);
_delay_ms(5);
EEWriteByte(0x0008,2);
_delay_ms(5);
EEWriteByte(0x0009,8);
_delay_ms(5);
EEWriteByte(0x000A,4);
_delay_ms(5);
EEWriteByte(0x000B,9);
_delay_ms(5);

//write the user names 
EEWriteByte(0x0100,'a');
_delay_ms(300);
EEWriteByte(0x0101,'h');
_delay_ms(300);
EEWriteByte(0x0102,'m');
_delay_ms(300);
EEWriteByte(0x0103,'e');
_delay_ms(300);
EEWriteByte(0x0104,'d');
_delay_ms(300);
EEWriteByte(0x0105,0);
_delay_ms(300);
EEWriteByte(0x0106,'k');
_delay_ms(300);
EEWriteByte(0x0107,'a');
_delay_ms(300);
EEWriteByte(0x0108,'r');
_delay_ms(300);
EEWriteByte(0x0109,'i');
_delay_ms(300);
EEWriteByte(0x010A,'m');
_delay_ms(300);
EEWriteByte(0x010B,0);
_delay_ms(300);
EEWriteByte(0x010C,'a');
_delay_ms(300);
EEWriteByte(0x010D,'l');
_delay_ms(300);
EEWriteByte(0x010E,'i');
_delay_ms(300);
EEWriteByte(0x010F,0);
_delay_ms(300);
EEWriteByte(0x0110,'m');
_delay_ms(300);
EEWriteByte(0x0111,'o');
_delay_ms(300);
EEWriteByte(0x0112,'h');
_delay_ms(30);
EEWriteByte(0x0113,'a');
_delay_ms(300);
EEWriteByte(0x0114,'m');
_delay_ms(300);
EEWriteByte(0x0115,'e');
_delay_ms(300);
EEWriteByte(0x0116,'d');
_delay_ms(300);
EEWriteByte(0x0117,0);
_delay_ms(300);
*/
//intial the drivers
intial();

//send the passwords and user names of the employees
 send_passwords();
 _delay_ms(100);
//sent the user names

//send_usernames();
 
 //set the time of the RTC
 hour=4;
 mint=30;
 second=0;
 RTC_Set_Time();
 

 uint8_t m;
while (1)
{   
	m = slaveTransive('8'); 
if(m==5){
	RTC_Get_Time();
	m = slaveTransive(hour);
	m = slaveTransive(mint);}

if(m==2){
         add_password();
 
 }
 
 }
 
 }

