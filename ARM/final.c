#include "final.h"

uint32_t pass_bits  ;
uint32_t users_bytes  =17;

uint8_t* admin_pass = "1234";
uint8_t error_number=0;

uint8_t  pass[4];
uint8_t  passwords[200];
uint8_t  users    [200];
uint8_t  pass_index;
uint8_t  hour,mint;

void intial(){
  lcdInit();
  vKeypadInit();
  vUartInit();
  vSpiInit();
  
  //buzzer intialization 
   GPIOA->DEN |=(1U<<5);
   GPIOA->DIR |=(1U<<5);
}

void get_pass(){
  
//intialize the lcd to write the password on it  
  lcdSendCommand(DISPLAY_CLEAR);
     delay(MS(20));
    lcdSendString("press enter");
   
    while(u8KeypadRead()!='e'){
    if((UART_MODULE->FR & (1U<<4)) ==0)
        
      admin_control();
      

    }
    lcdSendCommand(DISPLAY_CLEAR); 
   delay(MS(20));
   lcdSendString("HELLO");
   delay(MS(1000));
   lcdSendCommand(DISPLAY_CLEAR);
   delay(MS(20));
  lcdSendString("enter password");
 
  //write the pasword on lcd and store it 
  write_pass();
  
  
 //check password
   if(check_pass(pass)==1)
      welcome_msg();
   else
      error_msg();
  }

void welcome_msg(){
  
  lcdSendCommand(DISPLAY_CLEAR);
   delay(MS(20));
   lcdCoordination(1,1);
  lcdSendString("WELCOME");
  lcd_user();
  delay(MS(2000));
  vUartTrans('\n');
  vUartTrans(13);
  vTransString("the user ");
  uart_user();
  vTransString(" who has password ");
  for(uint8_t i=0;i<4;i++)
    vUartTrans(pass[i]);
  vTransString(" is enterd the door at ");
    print_time();
  error_number=0;}

void recive_pass(){
  uint8_t x;
  //recive unwanted byte
  x=vSpiTransive(8);
   vUartTrans(x+48);
   delay(MS(100));
   //the bytes number of passwords
    x=vSpiTransive(8);
   pass_bits=(4*x);
    vUartTrans(x+48);
    delay(MS(100));
    
   //recive the passwords 
  for(uint8_t i=0;i<36;i++){
    x=vSpiTransive(8);
    passwords[i]=x+48;
      pass_bits=(x*4)+1;
    vUartTrans(x+48);
    delay(MS(100));
}
  
  
}
uint8_t UartRecive(){
   
  while((UART_MODULE->FR & (1U<<4)) !=0);
  uint8_t x=UART_MODULE->DR;
  return x;
}

void error_msg(){
  error_number ++;
  if(error_number==3)
  { 
    BUZZER_ON
     /*new line */ vUartTrans('\n');vUartTrans(13);
      vTransString("maybe there is a stranger on the door ") ;
     /*new line */ vUartTrans('\n');vUartTrans(13);
     vTransString("the system is not working unless you will order to work ");
     while(error_number==3)
     admin_control();
       
  }
lcdSendCommand(DISPLAY_CLEAR);
        delay(MS(20));
     lcdSendString("WRONG PASSWORD");
     delay(MS(1000));
      lcdCoordination(2,1);
      lcdSendString("please try again");
      delay(MS(2000));
     /*new line */ vUartTrans('\n');vUartTrans(13);
  vTransString("some one try to enter the door with fake password  ");
  for(uint8_t i=0;i<4;i++)
    vUartTrans(pass[i]);
  vTransString(" at ");
  print_time();
  
}
      
      


uint8_t check_pass(uint8_t* password ){
  uint8_t i=0;
  while(i<pass_bits){
    uint8_t flag=0;
    for(uint8_t j=0;j<4;j++){
      if(password[j]!=passwords[i])
         flag++;
      i++;}
    if(flag==0){
      pass_index=i-4;
      return 1;}}
  return 0;}

void write_pass(){
  //write the pasword on lcd and store it 
 for(uint8_t i=0;i<4;i++){
   lcdCoordination(2,16-i);
   while(u8KeypadRead()<48 | (u8KeypadRead()>57&& u8KeypadRead()!='c') | (u8KeypadRead()=='c' && i==0));
   if(u8KeypadRead()=='c'){
     i--;
     lcdCoordination(2,16-i);
     lcdSendChar(' ');
     i--;
     _delay_ms(50);
   }
   
   else{
   pass[i]=u8KeypadRead();
   lcdSendChar(pass[i]);
   _delay_ms(50);
   lcdCoordination(2,16-i);
   lcdSendChar('*');
   }
   }
}

void get_time(){
uint8_t x;
x=vSpiTransive(5);
delay(MS(100));

/*

 */
  
hour=vSpiTransive(5);
delay(MS(100));
mint=vSpiTransive(5);
delay(MS(100));
x=x;

}

void  print_time(){
  get_time();
  uint8_t h=hour,m=mint;
  uint8_t x[2];
  x[0]=h%10;
  h=h/10;
  x[1]=h%10;
  vUartTrans(x[1]+48);
  vUartTrans(x[0]+48);
  vUartTrans(':');
  x[0]=m%10;
  m=m/10;
  x[1]=m%10;
  vUartTrans(x[1]+48);
  vUartTrans(x[0]+48);
}
uint8_t u8UartRecivepass(){
   
  while((UART_MODULE->FR & (1U<<4)) !=0);
  uint8_t x=UART_MODULE->DR;
  vUartTrans(x);
  delay(MS(500));
  vUartTrans(127);
  vUartTrans('*');
  return x;
}
uint8_t* u8Recivepassword(){
  uint8_t x[4];
  uint8_t  i=0;
  while(i<4){
    x[i]= u8UartRecivepass();
    i++;}
    
  return x;
}
  

void admin_control(){
  
  /*new line */ vUartTrans('\n');vUartTrans(13);
  
  vTransString("welcome admin");
  
  /*new line */ vUartTrans('\n');vUartTrans(13);
     
  u8UartRecive();
  
  vTransString("please enter your password:");
  
  uint8_t * x=u8Recivepassword();
  
  //if the password is correct
  if(check_admin(x)==1){
  
  /*new line */ vUartTrans('\n');vUartTrans(13);  
  vTransString("please enter your choice");  
  /*new line */ vUartTrans('\n');vUartTrans(13);

  vTransString("1.add password");
  /*new line */ vUartTrans('\n');vUartTrans(13);

  vTransString("2.edit password");
  /*new line */ vUartTrans('\n');vUartTrans(13);

  vTransString("3.delte password");
  /*new line */ vUartTrans('\n');vUartTrans(13);

  vTransString("4.open door manually ");
  /*new line */ vUartTrans('\n');vUartTrans(13);

  
  //get the choice
  uint8_t a =u8UartRecive();
  
  switch(a){
  case '1':
    
      add_password();
  //get the unwanted byte from the slave
  vSpiTransive(5);
  delay(MS(100));
  //get the unwanted byte from the slave
  vSpiTransive(5);
  delay(MS(100));
      break;
  case '2':
      //edit_password();
      break;
  case '3':
      //delete_password();
      break;
  case '4':
     BUZZER_OFF
     /*new line */ vUartTrans('\n');vUartTrans(13);
     vTransString("ok the system is working now ");
     error_number=0;
      break;
  default:
    /*new line */ vUartTrans('\n');vUartTrans(13);
    vTransString("please make sure that you select a choice from the avaliable choices"); 
  }
 
  }
  else {
    /*new line */ vUartTrans('\n');vUartTrans(13);
    vTransString("you enter a invalid password maybe you arenot the admin");
}
}
  
uint8_t check_admin(uint8_t* x){
  
  for(uint8_t i=0;i<4;i++){
    if(x[i]!= admin_pass[i])
      return 0;}
  
  return 1;}


void recive_users(){
  uint8_t x;
  for(uint8_t i=0;i<users_bytes;i++){
    x=vSpiTransive(8);
    if(i!=0)
    users[i-1]=x;
    vUartTrans(x);
    delay(MS(100));
  }
}

uint8_t get_username(){
  uint8_t user_index = pass_index /4;
  return user_index;}

void uart_user(){
  uint8_t x=get_username();
  uint32_t i=0,flag=0;
  while(i<users_bytes){
    if(users[i]==0)
      flag++;
      i++;
    if(flag==x){
      while(users[i]!=0){
      vUartTrans(users[i]);
      i++;}
     break;
    }
  }
}

void lcd_user(){
  uint8_t x=get_username();
  uint32_t i=0,flag=0;
  while(i<users_bytes){
    if(users[i]==0)
      flag++;
      i++;
    if(flag==x){
      while(users[i]!=0){
      lcdSendChar(users[i]);
      i++;}
     break;
    }
  }
}

void add_password(){
  vUartDelete();
  /*new line */ vUartTrans('\n');vUartTrans(13);
  vTransString("enter the password you want to add:");
  uint8_t* x= u8Recivepassword();
   
  //if the same password exists already
  if(check_pass(x)==1){
    /*new line */ vUartTrans('\n');vUartTrans(13);
    vTransString("the same password has  already taken by another user please try late to enter another password ");}
  
  else{
    /*new line */ vUartTrans('\n');vUartTrans(13);
    vTransString("ok the password is added successfully");
     uint8_t m=vSpiTransive(2);
     delay(MS(100));
     for(uint8_t i=0;i<4;i++){
       m=vSpiTransive(x[i]-48);
       vUartTrans(x[i]);
       passwords[pass_bits-1]=x[i];
        pass_bits++;           
       delay(MS(100));}
       
  }            
  
  
}