#include <p32xxxx.h>  
#pragma interrupt INT3_ISR ipl7 vector 15  
double y=0;
  
main(){  
DDPCONbits.JTAGEN = 0; // disable JTAGport, free up PORTA  
 
T2CON = 0x8000; // TMR3 on, prescale 1:1 PB=8MHz  
PR2 = 0x0001; // set period register to 0x10  
  
INTCONbits.MVEC = 1;  

asm("ei");
  
IEC0CLR = 0x00008000; // disable INT3
INTCONCLR = 0x00000008; // clear the bit, falling edge trigger
IFS0CLR = 0x00008000; // clear the interrupt flag
IEC0SET = 0x00008000; // enable INT3  
  
TMR2=0;  
while(1) {}   
asm("di");  
} 
  
void INT3_ISR (void)  
{  
  y = TMR2-y;
  IFS0CLR = 0x00000100;// Clear timer 2 interrupt flag  
}
