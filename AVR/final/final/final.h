#include "spi.h"
#include "RTC.h"
#include "EEPROM.h"
#include "lcd.h"

//the prototypes of the functions
void intial         (void);
void send_usernames (void);
void send_passwords (void);
void add_password   (void);