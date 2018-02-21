#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "delay.h"
#include "spi.h"




//define the prototype of the functions
void         intial               (void    ); //intial all the drivers we using in the system

/**/
void         recive_pass          (void    );//recive all the passwords from the EEPROM
void         recive_users         (void    );//recive the usernames from the EEPROM

/**/
void         get_pass             (void    ); // manage the password of the users    // the most important  function
void         write_pass           (void    );// manage writing  the password on the lcd
uint8_t      check_pass           (uint8_t*);//check if the password exist in the list of passwords reciving from EEPROM return 1 if the password exists
void         welcome_msg          (void    ); //if the user enter a valid password
void         error_msg            (void    ); //if the user enter a invalid password 
uint8_t      get_username         (void    );//get the user name which has the enterd password 
void         uart_user            (void    );//print the user name on the UART screen
void         lcd_user             (void    );//print the user name on the lcd
void         get_time             (void    );//get the current time from the RTC
void         print_time           (void    );//print the time reciving from the RTC in readable form on the UART

/**/
void         admin_control        (void    );//manage the admin control of the system
uint8_t      u8UartRecivepass     (void    );//recive a character from the UART and  show it as a star(*)
uint8_t*     u8Recivepassword     (void    );//recive the password from the admin and use the last function 
uint8_t      check_admin          (uint8_t*);//insure that the password which entered by the admin true or not
void         add_password         (void    );//add password by the admin 

// buzzer on and off 
#define BUZZER_ON      GPIOA->DATA |= (1U<<5);
#define BUZZER_OFF     GPIOA->DATA &=~(1U<<5);










