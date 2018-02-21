#include "RTC.h"



void I2C_Init(){
	TWSR=0x00;  // set prescaler bits  to zero
	TWBR=32;    // SCL freq. is 100k for XTAL=8M
TWCR=0x04;} // enable TWI module


void I2C_Start(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
while (!(TWCR & (1<<TWINT))); }


void I2C_Stop(){
TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);}


void I2C_Write(uint8_t data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN) ;
while (!(TWCR & (1<<TWINT) ) ) ;}


uint8_t I2C_Read(uint8_t ack){
	TWCR = (1<<TWINT) | (1<<TWEN)|(ack<<TWEA) ;
while (!(TWCR & (1<<TWINT) ) ) ; 
return TWDR; }


void RTC_Set_Time()        {
	I2C_Start(); 		// transmit START condition
	I2C_Write(0xD0); 	// address DS1307 for write
	I2C_Write(0); 		// set register pointer to 0
	I2C_Write(second);  	// set seconds
	I2C_Write(mint); 	// set minuts
	I2C_Write(hour);  	// set Hours
I2C_Stop();            }

void RTC_Set_Date()     
   {
	I2C_Start(); 		// transmit START condition
	I2C_Write(0xD0);       // address DS1307 for write
	I2C_Write(0x04); 	// set register pointer to 4
	I2C_Write(day);  	// set day
	I2C_Write(month); 	// set month
	I2C_Write(year);  	// set year
I2C_Stop(); 
           }


void  RTC_Get_Time()
{
	I2C_Start () ;         //transmit START condition
	I2C_Write(0xD0);       //address DS1307 for write
	I2C_Write(0);          //set register pointer to 0
	I2C_Start () ; 		//transmit START condition
	I2C_Write(0xD1); 	//address DS1307 for read
	second = I2C_Read(1);	//read second, return ACK
	mint = I2C_Read(1);	//read minute, return ACK
	hour = I2C_Read(0);	//read hour, return NACK
I2C_Stop(); 
     }	//transmit STOP condition


void  RTC_Get_Date() {
	I2C_Start () ;         //transmit START condition
	I2C_Write(0xD0);       //address DS1307 for write
	I2C_Write(4);          //set register pointer to 4
	I2C_Start () ; 		//transmit START condition
	I2C_Write(0xD1); 	//address DS1307 for read
	day = I2C_Read(1);	//read second, return ACK
	month = I2C_Read(1);	//read minute, return ACK
	year = I2C_Read(0);	//read hour, return NACK
    I2C_Stop();       	//transmit STOP condition
	}