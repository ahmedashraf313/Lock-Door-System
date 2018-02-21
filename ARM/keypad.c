#include "keypad.h"

void  vKeypadInit(){
  //define the pin of the ports in the clock gating
#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3
#define PORTE    4
#define PORTF    5

 //enable the clock ggating for the gipo of the kaypad pins 
 SYSCTL->RCGCGPIO |= (1U<<R1_port) | (1U<<R2_port) | (1U<<R3_port) |(1U<<R4_port) | (1U<<C1_port) | (1U<<C2_port) | (1U<<C3_port) | (1U<<C4_port) ;
 
 //enable the digital function for the pins 
 R1_PORT ->DEN |= (1U<<R1);
 R2_PORT ->DEN |= (1U<<R2);
 R3_PORT ->DEN |= (1U<<R3);
 R4_PORT ->DEN |= (1U<<R4);
 C1_PORT ->DEN |= (1U<<C1);
 C2_PORT ->DEN |= (1U<<C2);
 C3_PORT ->DEN |= (1U<<C3);
 C4_PORT ->DEN |= (1U<<C4);

// make the rows   as outputs 
 R1_PORT->DIR  |= (1U<<R1);
 R2_PORT->DIR  |= (1U<<R2);
 R3_PORT->DIR  |= (1U<<R3);
 R4_PORT->DIR  |= (1U<<R4);
 
 //define the colums as inputs
 C1_PORT->DIR  &= ~(1U<<C1);
 C2_PORT->DIR  &= ~(1U<<C2);
 C3_PORT->DIR  &= ~(1U<<C3);
 C4_PORT->DIR  &= ~(1U<<C4);
 
 //raise the pullup for the colums
 C1_PORT->PUR |= (1U<<C1);
 C2_PORT->PUR |= (1U<<C2);
 C3_PORT->PUR |= (1U<<C3);
 C4_PORT->PUR |= (1U<<C4);
 
 

}


uint8_t u8KeypadRead( ){
 
  
   
     uint8_t i =0 ,key;
     for(i=0;i<4;i++){
       key=0;
       //make all the rows high
   R1_PORT->DATA |= (1U<<R1);
   R2_PORT->DATA |= (1U<<R2);
   R3_PORT->DATA |= (1U<<R3);
   R4_PORT->DATA |= (1U<<R4);
  
       if(i==0)       R1_PORT->DATA &= ~(1U<<R1); 
       else if(i==1)  R2_PORT->DATA &= ~(1U<<R2);
       else if(i==2)  R3_PORT->DATA &= ~(1U<<R3);
       else           R4_PORT->DATA &= ~(1U<<R4);
       
//put the pins of the lines in the variable (key)	
key =(((C1_PORT->DATA&(1U<<C1))>>C1)<<0);
key |=(((C2_PORT->DATA&(1U<<C2))>>C2)<<1);
key |=(((C3_PORT->DATA&(1U<<C3))>>C3)<<2);
key |=(((C4_PORT->DATA&(1U<<C4))>>C4)<<3);


if(((ALL_LINES)!=1))
{//while(((ALL_LINES)!=1));
	break;}


}
if(i==4) return 0;
       
       switch(i){
       case 0: 
              if     (key==0x07) return    'F'   ;
              else if(key==0x0b) return    '3'   ;
              else if(key==0x0d) return    '2'   ;
              else if(key==0x0e) return    '1'   ;
               break;
      
       case 1: 
             if     (key==0x07) return     'f'   ;
              else if(key==0x0b) return    '6'   ;
              else if(key==0x0d) return    '5'   ;
              else if(key==0x0e) return    '4'   ;
               break;
         
       case 2:
             if     (key==0x07) return     'S'   ;
              else if(key==0x0b) return    '9'   ;
              else if(key==0x0d) return    '8'   ;
              else if(key==0x0e) return    '7'   ;
               break;
               
       case 3:
            if     (key==0x07)  return     'e'   ;
              else if(key==0x0b) return    'c'  ;
              else if(key==0x0d) return    '0' ;
              else if(key==0x0e) return    'm' ;
              break;}
    
       return 0;
} 
