void genSec( ) 
   {
	DDPCONbits.JTAGEN = 0
	
	T2CON = 0x0020;
	TMR2 = 0x0;
	PR2 = 0xFFFF;
	T2CONSET = 0x8000;

	if (IFS0==0x00001000) {
	PORTD=1;
	IFS0=0x00000000;
	}
   }

int main() 
{ 
	asm("nop"); 
	genSec( ); 
	asm("nop"); 
	      
	return 0; 
}


