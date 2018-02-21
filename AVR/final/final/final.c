#include "final.h"

uint8_t pass_bytes;


void intial(){
I2C_Init();
EEReadByte(0x10f0,&pass_bytes);
slaveInit();
vLCDInit();

}


void send_passwords(){
uint16_t i=0;
uint8_t x=1,m;
//vLCDWriteString("aaa");
//read the passwords
m=slaveTransive(pass_bytes);
while(i<(4*pass_bytes)){
EEReadByte(0x0000+i,&x);
_delay_ms(50);
m=slaveTransive(x);
//vLCDWriteCharacter(m);
i++;
m=m;
_delay_ms(50);
}


}

void send_usernames(){
	uint16_t i=0;
	uint8_t x=1;
	//vLCDWriteString("aaa");
	//read the usernames
	while(i<12){
		EEReadByte(0x1100+i,&x);
		uint8_t m=slaveTransive(x);
		//vLCDWriteCharacter(m);
		i++;
		m=m;
		_delay_ms(100);
	}


}

void add_password(){
 uint16_t x=(pass_bytes * 4);
 for(uint8_t i=0;i<4;i++){
 uint8_t m=slaveTransive(1);
 EEWriteByte(0x0000+x+i,m);
 _delay_ms(5);
 }
 pass_bytes ++;
 EEWriteByte(0x10f0,pass_bytes);
 _delay_ms(5);
}