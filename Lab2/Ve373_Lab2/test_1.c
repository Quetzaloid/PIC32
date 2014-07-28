#include <p32xxxx.h>
#pragma interrupt T4_ISR ipl7 vector 16
int x = 0;
int y = 0;

int main( )
{
	DDPCONbits.JTAGEN = 0; 

	T4CON = 0x0;
    TMR4 = 0x0;
	PR4 = 0xffff; 
	T4CONSET = 0x8002;
	INTCONbits.MVEC = 1;
	asm("ei");
	IPC1SET = 0x0000001c;
	IFS0CLR = 0x00010000;//Clear Timer interrupts
	IEC0SET = 0x00010000;//Enable Timer interrupts
	
	while(1) 
    {
      if(TMR4 == PR4) x++; 
    } 
	asm("di");
} 
	
	void T4_ISR (void) 
    {
        y = TMR4+x*65535+y;
		IFS0CLR = 0x00001000;	    
	    return 0;
    }
