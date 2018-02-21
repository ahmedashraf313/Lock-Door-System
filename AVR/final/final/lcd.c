#include "lcd.h"

/******************************************************************************/
#ifdef USE_TM4C123GH6PM
  static void vLcdTM4C123GPinsInit(void);
#endif

/******************************************************************************/
static void vLCDWrite(char Byte);
static void vLCDWriteInstruction(char command);

//*****************************************************************************
//
//! vLcdTM4C123GPinsInit.
//!
//! \param None.
//!
//! This function intialize the LCD control and DATA Pins for 4 bit mode.  this function
//! starts with clock gating for every pin port, then disable its lock , then disable its 
//! alternative function and finally enable the Digital function. 	
//! this function is compiled only if USE_TM4C123GH6PM is defined.
//!
//! \return None.
//
//*****************************************************************************
#ifdef USE_TM4C123GH6PM
  static void
  vLcdTM4C123GPinsInit(void)
  {
  // configure the TM4C123G pins for the data lines
  SYSCTL->RCGCGPIO      |= (1U<<LCD_PORT_D7_GATE);
  LCD_D7_PORT_BASE->LOCK = 0x4C4F434B;
  LCD_D7_PORT_BASE->CR  |= (1U<<D7_BIT);
  LCD_D7_PORT_BASE->AFSEL &=~ (1U<<D7_BIT);
  LCD_D7_PORT_BASE->DEN |= (1U<<D7_BIT);
  
  SYSCTL->RCGCGPIO      |= (1U<<LCD_PORT_D6_GATE);
  LCD_D6_PORT_BASE->LOCK = 0x4C4F434B;
  LCD_D6_PORT_BASE->CR  |= (1U<<D6_BIT);
  LCD_D6_PORT_BASE->AFSEL &=~ (1U<<D6_BIT);
  LCD_D6_PORT_BASE->DEN |= (1U<<D6_BIT);
  
  SYSCTL->RCGCGPIO      |= (1U<<LCD_PORT_D5_GATE);
  LCD_D5_PORT_BASE->LOCK = 0x4C4F434B;
  LCD_D5_PORT_BASE->CR  |= (1U<<D5_BIT);
  LCD_D5_PORT_BASE->AFSEL &=~ (1U<<D5_BIT);
  LCD_D5_PORT_BASE->DEN |= (1U<<D5_BIT);
  
  SYSCTL->RCGCGPIO      |= (1U<<LCD_PORT_D4_GATE);
  LCD_D4_PORT_BASE->LOCK = 0x4C4F434B;
  LCD_D4_PORT_BASE->CR  |= (1U<<D4_BIT);
  LCD_D4_PORT_BASE->AFSEL &=~ (1U<<D4_BIT);
  LCD_D4_PORT_BASE->DEN |= (1U<<D4_BIT);
  // configure the TM4C123G pins for the control lines
  SYSCTL->RCGCGPIO      |= (1U<<RS_PORT_GATE);
  RS_PORT_BASE->LOCK     = 0x4C4F434B;
  RS_PORT_BASE->CR      |= (1U<<RS_BIT);
  RS_PORT_BASE->AFSEL   &=~(1U<<RS_BIT);
  RS_PORT_BASE->DEN     |= (1U<<RS_BIT);
  
  SYSCTL->RCGCGPIO      |= (1U<<RW_PORT_GATE);
  RW_PORT_BASE->LOCK     = 0x4C4F434B;
  RW_PORT_BASE->CR      |= (1U<<RW_BIT);
  RW_PORT_BASE->AFSEL   &=~(1U<<RW_BIT);
  RW_PORT_BASE->DEN     |= (1U<<RW_BIT);
  
  SYSCTL->RCGCGPIO     |= (1U<<E_PORT_GATE);
  E_PORT_BASE->LOCK     = 0x4C4F434B;
  E_PORT_BASE->CR      |= (1U<<E_BIT);
  E_PORT_BASE->AFSEL   &=~(1U<<E_BIT);
  E_PORT_BASE->DEN     |= (1U<<E_BIT);
  }
#endif
  
//*****************************************************************************
//
//! vLCDInit.
//!
//! \param None.
//! this fuction intialize the LCD module for ,5*7 font 
//! ,2 Lines ,4 bit mode and disable showing the curser position.
//! LCD pins have to be defined as connected to the hardware in the lcdconfig.h
//!
//! \return None.
//
//*****************************************************************************
void 
vLCDInit(void)
{
  #ifdef USE_TM4C123GH6PM
	vLcdTM4C123GPinsInit();
  #endif
  
    // configure the microprocessor pins for the data lines
    LCD_DDR_D7 |= (1U<<D7_BIT);           // 4 data lines - output
    LCD_DDR_D6 |= (1U<<D6_BIT);
    LCD_DDR_D5 |= (1U<<D5_BIT);
    LCD_DDR_D4 |= (1U<<D4_BIT);
    // configure the microprocessor pins for the control lines
    E_DDR	   |= (1U<<E_BIT);            // E line - output
    RS_DDR	   |= (1U<<RS_BIT);           // RS line - output
    RW_DDR	   |= (1U<<RW_BIT);		      // RW line - output
    // Power-up delay
    #ifdef USE_ATMEGA32
        _delay_ms(100);	        	  // initial 40 mSec delay
    #endif
    #ifdef USE_TM4C123GH6PM
        delay(MS(100));			      // initial 40 mSec delay
    #endif
    
    /* At this point the LCD module is in the 8-bit mode and it is expecting to receive  
    8 bits of data, one bit on each of its 8 data lines, each time the 'E' line is pulsed.
    
    Since the LCD module is wired for the 4-bit mode, only the upper four data lines are connected to 
    the microprocessor and the lower four data lines are typically left open.  Therefore, when 
    the 'E' line is pulsed, the LCD controller will read whatever data has been set up on the upper 
    four data lines and the lower four data lines will be high (due to internal pull-up circuitry).
    
    Fortunately the 'FunctionReset' instruction does not care about what is on the lower four bits so  
    this instruction can be sent on just the four available data lines and it will be interpreted 
    properly by the LCD controller.  The 'lcd_write' subroutine will accomplish this if the 
    control lines have previously been configured properly.*/
	
    // Set up the RS and E lines for the 'lcd_write' subroutine.
    RS_PORT &= ~(1U<<RS_BIT);			// select the Instruction Register (RS low)
    E_PORT  &= ~(1U<<E_BIT);			// make sure E is initially low
    RW_PORT &= ~(1U<<RW_BIT);
    // Reset the LCD controller
    vLCDWrite(LCD_FUNCTION_RESET);		// first part of reset sequence
    #ifdef USE_ATMEGA32
        _delay_ms(10);			       	// 4.1 mS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
         delay(MS(10));					// 4.1 mS delay (min)
    #endif
                                
    vLCDWrite(LCD_FUNCTION_RESET);		// second part of reset sequence
    #ifdef USE_ATMEGA32
		_delay_us(200);						// 100uS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
        delay(US(200));				// 100uS delay (min)
    #endif

    vLCDWrite(LCD_FUNCTION_RESET);		// third part of reset sequence
    #ifdef USE_ATMEGA32
		_delay_us(200);						// this delay is omitted in the data sheet
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(US(200));						// this delay is omitted in the data sheet
    #endif                          
    /* Preliminary Function Set instruction - used only to set the 4-bit mode.
    The number of lines or the font cannot be set at this time since the controller is still in the
    8-bit mode, but the data transfer mode can be changed since this parameter is determined by one 
    of the upper four bits of the instruction.*/
	
    vLCDWrite(LCD_FUNCTION_SET_4BIT);   // set 4-bit mode
    #ifdef USE_ATMEGA32
		_delay_us(80);						// 40uS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(US(80));						// 40uS delay (min)
    #endif
    // Function Set instruction
    vLCDWriteInstruction(LCD_FUNCTION_SET_4BIT);	        // set mode, lines, and font
    #ifdef USE_ATMEGA32
         _delay_us(80);						// 40uS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(US(80));						// 40uS delay (min)
    #endif
    /* The next three instructions are specified in the data sheet as part of the initialization routine, 
    so it is a good idea (but probably not necessary) to do them just as specified and then redo them 
    later if the application requires a different configuration.*/
	
    // Display On/Off Control instruction
    vLCDWriteInstruction(LCD_DISPLAYOFF);			// turn display OFF
    #ifdef USE_ATMEGA32
		_delay_us(80);									// 40uS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(US(80));									// 40uS delay (min)
    #endif
    // Clear Display instruction
    vLCDWriteInstruction(LCD_CLEAR_DISPLAY);        // clear display RAM
    #ifdef USE_ATMEGA32
		_delay_ms(4);									// 1.64 mS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(MS(4));									// 1.64 mS delay (min)
    #endif
    //  Entry Mode Set instruction
    vLCDWriteInstruction(LCD_ENTRYMODE);			// set desired shift characteristics
    #ifdef USE_ATMEGA32
		_delay_us(80);									// 40uS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(US(80));									// 40uS delay (min)
    #endif    
    /* This is the end of the LCD controller initialization as specified in the data sheet, but the display
    has been left in the OFF condition.  This is a good time to turn the display back ON.*/
	
    // Display On/Off Control instruction
    vLCDWriteInstruction(LCD_DISPLAYON);			// turn the display ON
    #ifdef USE_ATMEGA32
		_delay_us(80);									// 40uS delay (min)
    #endif
    #ifdef USE_TM4C123GH6PM
		delay(US(80));									// 40uS delay (min)
    #endif
}
//*****************************************************************************
//
//! vLCDWriteString.
//!
//! \param char *string.
//!
//! This function sends a string to be printed on the LCD
//!
//! \return None.
//
//*****************************************************************************
void 
vLCDWriteString(char *string)
{
    while (*string != '\0')
    {
        vLCDWriteCharacter(*string++);
        #ifdef USE_ATMEGA32
		_delay_us(80);                                // 40uS delay (min)
        #endif
        #ifdef USE_TM4C123GH6PM
		delay(US(80));                                // 40uS delay (min)
        #endif
    }
}
//*****************************************************************************
//
//
//! vLCDWriteCharacter.
//!
//! \param char Data.
//!
//! This function sends a character to be printed on the LCD
//!
//! \return None.
//
//
//*****************************************************************************

void 
vLCDWriteCharacter(char Data)
{
    RS_PORT |= (1U<<RS_BIT);                 // select the Data Register (RS high)
    E_PORT  &= ~(1U<<E_BIT);                 // make sure E is initially low
    RW_PORT &= ~(1U<<RW_BIT);
    vLCDWrite(Data);	    		    	 // write the upper 4-bits of the data
    vLCDWrite(Data << 4);		    		 // write the lower 4-bits of the data
}
//*****************************************************************************
//
//
//! vLCDWriteInstruction.
//!
//! \param char Command.
//!
//! This function sends a command to configure a certain function on the LCD
//! This function is intended to be used within the module only. 
//! 
//! \return None.
//
//*****************************************************************************
static void 
vLCDWriteInstruction(char command)
{
    RS_PORT &= ~(1U<<RS_BIT);                 // select the Instruction Register (RS low)
    E_PORT  &= ~(1U<<E_BIT);                  // make sure E is initially low
    RW_PORT &= ~(1U<<RW_BIT);
    vLCDWrite(command);		              	  // write the upper 4-bits of the data
    vLCDWrite(command << 4);                  // write the lower 4-bits of the data
}
//*****************************************************************************
//
//! vLCDWrite.
//!
//! \param char Byte.
//!
//! This function sends a 4 bits to the LCD pin D4-D7. 
//! This function is intended to be used within the module only. 
//! 
//! \return None.
//
//*****************************************************************************
static void 
vLCDWrite(char Byte)
{
    LCD_PORT_D7 &= ~(1<<D7_BIT);              // assume that data is '0'
    LCD_PORT_D6 &= ~(1<<D6_BIT);              // repeat for each data bit
    LCD_PORT_D5 &= ~(1U<<D5_BIT);
    LCD_PORT_D4 &= ~(1U<<D4_BIT);
	
    if ((Byte & (1U<<7))==(1U<<7))
    {
        LCD_PORT_D7 |= (1<<D7_BIT);	       	  // make data = '1' if necessary
    }
        
    if ((Byte & (1U<<6))== (1U<<6))
    {
        LCD_PORT_D6 |= (1U<<D6_BIT);
    }
    
    if ((Byte & (1U<<5))==(1U<<5))
    { 
        LCD_PORT_D5 |= (1U<<D5_BIT);
    }
    
    if ((Byte & (1U<<4))==(1U<<4))
    { 
        LCD_PORT_D4 |= (1U<<D4_BIT);
    }
    // write the data
    E_PORT |= (1U<<E_BIT);					// Enable pin high
    #ifdef USE_ATMEGA32
	_delay_us(10);                          // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
    #endif
    #ifdef USE_TM4C123GH6PM
	delay(US(10));                          // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
    #endif
        
    E_PORT &= ~(1U<<E_BIT);			        // Enable pin low
    #ifdef USE_ATMEGA32
	_delay_us(10);                          // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
    #endif
    #ifdef USE_TM4C123GH6PM
          delay(US(10));                    // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
    #endif
}

//*****************************************************************************
//
//! cLCDGotoXY.
//!
//! \param char pos which defines the X position for the LCD 
//! \param char line which defines the Y position for the LCD
//!
//! This function sends instruction to access a certain position 
//! on the LCD. This function is configured to deal with LCD 2*16 
//! only , that's why LINE has to have value between LINE_1 and LINE_2 
//! and Pos has to have value between POS_1 and POS_16 which are configured in lcd.h 
//! 
//! \return  LOCATION_FOUND_AND_SET if the location successfully set.
//! \return  LOCATION_NOT_FOUND if the location sent was out of LCD boundries
//
//*****************************************************************************
char 
cLCDGotoXY (char pos, char line)					
{
	if((line == LINE_1 ||line == LINE_2) && ((pos >= POS_1) && (pos <= POS_16) ))
	{
		vLCDWriteInstruction((0x80|(line<<6))+pos);
		#ifdef USE_ATMEGA32
			_delay_us (50);
		#endif
		#ifdef USE_TM4C123GH6PM
			delay(MS(50));
		#endif

		return LOCATION_FOUND_AND_SET;
	}
	else 
	{
		return LOCATION_NOT_FOUND;
	}
	 
}
//*****************************************************************************
//
//! vLCDClearDisplay.
//!
//! \param None.
//!
//! This function sends clears the LCD and set the cursor at LINE_1 and POS_1. 
//! This function is intended to be used within the module only. 
//! 
//! \return None.
//
//*****************************************************************************
void 
vLCDClearDisplay(void)	 
{
	vLCDWriteInstruction(LCD_CLEAR_DISPLAY);
	#ifdef USE_ATMEGA32
		_delay_ms (2);
	#endif
	#ifdef USE_TM4C123GH6PM
		delay(MS(2));
	#endif

}
//*****************************************************************************
//
//! cLCDShowInt.
//!
//! \param char x which defines the starting x position for the number to be shown.
//! \param char Y which defines the Y position for the number to be shown.
//! \param uint32_t Num which is the integer number to be shown on lcd.
//! \param char Len the maximum number of digits for the number to be shown.
//!
//! This function Displays an int number on LCD at the given position.
//!
//!
//! \return NUMBER_OUT_LCD_BOUNDRIES if len + x are greater than POS_16.
//! \return SUCCESS if the number was successfully shown on LCD.
//
//*****************************************************************************

char 
cLCDShowInt(char x, char Y, uint32_t Num, char Len)
{
	unsigned char Digit;
	char loop, x_position,location;
	x_position = x + Len -1;					 
	    
	for(loop=0;loop<Len;loop++)
	{
		Digit = Num%10;
		Num /= 10;
		location = cLCDGotoXY((x_position-loop),Y);
		if (location == LOCATION_FOUND_AND_SET)
		{
			if((Digit!=0)||(Num!=0)||(loop==0))
			{
				vLCDWriteCharacter(Digit|0x30);
			}
			else
			{
				vLCDWriteCharacter(' ');
			}
		
		}
		else
		{
			return NUMBER_OUT_LCD_BOUNDRIES;
		}
		
	}
	return SUCCESS;
}
//*****************************************************************************
//
//! cLCDShowFloat.
//!
//! \param char x_position which defines the starting x position for the number to be shown.
//! \param char y_position which defines the Y position for the number to be shown.
//! \param float number which is the integer number to be shown on lcd.
//! \param char decimal_Len the maximum number of Decimal digits for the number to be shown.
//! \param char fraction_len the maximum number of Fraction digits for the number to be shown.
//!
//!  This function Displays a float number on LCD at the given position
//!
//!
//! \return NUMBER_OUT_LCD_BOUNDRIES if decimal_Len + fraction_len + x_position are greater than POS_16.
//! \return SUCCESS if the number was successfully shown on LCD.
//
//*****************************************************************************

char 
cLCDShowFloat(char x_position, char y_position, float number, char decimal_Len, char fraction_len)      
   {                                                                                                           
        uint8_t Digit,location;                                            
        uint32_t Num;                                               
        char loop, Len , X;                                               
                                                                        
        Len = decimal_Len + fraction_len;                                            
        X = x_position + Len;                                                 
                                                                        
        for(loop=0;loop<fraction_len;loop++)
		{
			number *= 10;
		}                                             
        Num = (uint32_t )number;                                        
                                                                       
        for(loop=0;loop<=Len;loop++)                                   
        {                                                      
            if(loop == fraction_len)                                       
            {
				location = cLCDGotoXY((X-loop),y_position);
				if (location == LOCATION_FOUND_AND_SET)
				{
					vLCDWriteCharacter('.');
					continue;
				}
				else
				{
					return NUMBER_OUT_LCD_BOUNDRIES;
				}                                            
            }                                             
            Digit = Num%10;                                          
            Num /= 10;                                               
            location = cLCDGotoXY((X-loop),y_position);                                
            if (location == LOCATION_FOUND_AND_SET)
            {
				if((Digit!=0)||(Num!=0)||(loop==0))
				{
					vLCDWriteCharacter(Digit|0x30);
				}                         
				else if(loop <= fraction_len+1)
				{
					vLCDWriteCharacter('0');
				}	                                  
				else 
				{
					vLCDWriteCharacter(' ');
				}
			}
			else
			{
				return NUMBER_OUT_LCD_BOUNDRIES;
			}                                                              
        }                                                          
     return SUCCESS;                              
}             