#include <mega16.h>
#include <delay.h> 
 
// Declare your global variables here
flash char display [10] = {0x3f, 0x06,0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
long int n = 12345678;
char myNumber[8] = {1,2,3,4,5,6,7,8} ;
void fill_myNumber(void);
interrupt [EXT_INT2] void ext_int2_isr(void)
{
 n-- ; fill_myNumber();

}

void main(void)
{
// Declare your local variables here
    int counter =0  ;   
    char pd = 0x01 ;
//    char temp ;
// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (0<<PORTB1) | (1<<PORTB0); //Pull-Up

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=1 Bit6=1 Bit5=1 Bit4=1 Bit3=1 Bit2=1 Bit1=1 Bit0=0 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);
//PORTC = display[2] ;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
GICR|=(0<<INT1) | (0<<INT0) | (1<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (0<<INTF0) | (1<<INTF2)  ;

// Global enable interrupts
#asm("sei")


while (1)
      {
      // Place your code here
       pd= 0x01 ;
      for ( counter = 0 ; counter < 8 ; counter ++)
      {
      delay_ms(5);
      PORTD = ~pd ;
      PORTC  = display[ myNumber[counter]]; 
      pd = pd << 1 ;
      }
      if(PINB.0 == 0){ n++; fill_myNumber();
      while (PINB.0 ==0) {} ;}
//      if(PINB.2 == 0 ){ n-- ; fill_myNumber();
//      while (PINB.2 == 0 ) {};}
     }
}


void fill_myNumber()
{
    myNumber[7] = n%10 ;
    myNumber[6] = (n/10)%10 ;
    myNumber[5] = (n/100)%10 ;
    myNumber[4] = (n/1000)%10 ;
    myNumber[3] = (n/10000)%10 ;
    myNumber[2] = (n/100000)%10 ;
    myNumber[1] = (n/1000000)%10 ;
    myNumber[0] = (n/10000000)%10 ;

}