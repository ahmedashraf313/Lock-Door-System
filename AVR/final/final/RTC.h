#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdint.h>

//set the global variables of the date and time 
uint8_t hour, mint, second, day, month, year;


//include the prototypes of the functions
void          I2C_Init     (void);
void          I2C_Start    (void);
void          I2C_Stop     (void);
void          I2C_Write    (uint8_t );
uint8_t       I2C_Read     (uint8_t );
void          RTC_Set_Time (void );
void          RTC_Set_Date (void );
void          RTC_Get_Time (void );
void          RTC_Get_Date (void )  ;
