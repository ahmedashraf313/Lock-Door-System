#include "EEPROM.h"

uint8_t EEWriteByte(uint16_t u16addr, uint8_t u8data)
{
	TWIStart();
	if (TWIGetStatus() != 0x08)
	return 0; //error
	//select devise and send A2 A1 A0 address bits
	TWIWrite((0xA0));//|(uint8_t)((u16addr & 0x0700)>>7));
	if (TWIGetStatus() != 0x18)
	return 0;  //error
	//send the rest of address
	TWIWrite((uint8_t)(u16addr));
	if (TWIGetStatus() != 0x28)
	return 0;   //error
	//write byte to eeprom
	TWIWrite(u8data);
	if (TWIGetStatus() != 0x28)
	return 0;  //error
	TWIStop();
	return 1;  //success
}

void TWIInit()
{
	//set SCL to 400kHz
	TWSR = 0x00;
	TWBR = 0x0C;
	//enable TWI
	TWCR = (1<<TWEN);
}

void TWIStart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

//send stop signal
void TWIStop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWIWrite(uint8_t u8data)
{
	TWDR = u8data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t TWIGetStatus()
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}

uint8_t TWIReadACK()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

//read byte with NACK
uint8_t TWIReadNACK()
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t EEReadByte(uint16_t u16addr, uint8_t *u8data)
{
	//uint8_t databyte;
	TWIStart();
	if (TWIGetStatus() != 0x08)
	return 0; //error
	//select devise and send A2 A1 A0 address bits
	TWIWrite(0xA0);//|((uint8_t)((u16addr & 0x0700)>>7)));
	if (TWIGetStatus() != 0x18)
	return 0;   //error
	//send the rest of address
	TWIWrite((uint8_t)(u16addr));
	if (TWIGetStatus() != 0x28)
	return 0;
	//send start
	TWIStart();
	if (TWIGetStatus() != 0x10)
	return 0;  //error
	//select devise and send read bit
	TWIWrite(0xA1);//|((uint8_t)((u16addr & 0x0700)>>7))|1);
	if (TWIGetStatus() != 0x40)
	return 0;  //error
	*u8data = TWIReadNACK();
	if (TWIGetStatus() != 0x58)
	return 0;  //error
	TWIStop();
	return 1;  //success
}
