#include <mega16.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>

#define C0 PIND.4
#define C1 PIND.5
#define C2 PIND.6
#define C3 PIND.7


// Declare your global variables here

char keypad(void);
flash char shift[4] = {0xFE, 0xFD, 0xFB, 0xF7}  ; // Why char ?? Cuz it is 8 bits !!!
  //0b111 0111
flash char keypad_layout[4][4] = {'7','8','9','/','4','5','6','*','1','2','3','-','C','0','=','+'};

interrupt [EXT_INT2] void ext_int2_isr(void)
{         
 char charecter ; 
      charecter = keypad();
       PORTD  = 0xF0;
         if(charecter == 'C') lcd_clear();
         else
             lcd_putchar(charecter);

}

void main(void)
{
// Declare your local variables here 
   
    PORTD  = 0xF0;
    DDRD = 0x0F ;             
    lcd_init(16);
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
       
        
      }
}

char keypad(void)
{
int row = 0 , column = -1 , position = 0   ;
//while(1)
//{
 
 for ( row = 0 ; row < 4 ; row ++ )
 {
     PORTD = shift[row];
     if(C0 == 0) {column = 0 ;}
     if(C1 == 0) {column = 1 ;}
     if(C2 == 0) {column = 2 ;}
     if(C3 == 0) {column = 3 ;}
     if(column != -1)
         {
            position = row * 4 + column ;
            //lcd_putchar(keypad_layout[position]);  
            //lcd_putchar(keypad_layout[row][column]) ;
                
            while(C0 == 0 ){;}
            while(C1 == 0 ){;}
            while(C2 == 0 ){;}
            while(C3 == 0 ){;} 
            //return keypad_layout[position] ; // one dimensional array
            return keypad_layout[row][column];
            column = -1 ;
         }
     delay_ms(50);
 }
 //}
}
