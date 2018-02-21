#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdint.h>

//define the prototypes of the functions 
uint8_t EEWriteByte(uint16_t , uint8_t );
uint8_t EEReadByte(uint16_t , uint8_t *);
void     TWIInit       (void);  
void     TWIStart      (void);
void     TWIStop       (void);
void     TWIWrite      (uint8_t );
uint8_t  TWIGetStatus  (void);
uint8_t  TWIReadACK    (void);
uint8_t  TWIReadNACK   (void);


