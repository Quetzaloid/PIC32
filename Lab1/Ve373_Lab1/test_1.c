#include <p32xxxx.h>
//#define DELAY_2 625000// 2s
//#define DELAY_1 312500// 1s
main(){
DDPCONbits.JTAGEN = 0; // disable JTAGport, free up PORTA
TRISD = 0xff00; //pin 4 as output
//T1CON = 0x8030; // TMR1 on, prescale 1:256 PB=80MHz
PR1 = 0xFFFF; // set period register to max
// 1. main loop
while(1) {
int i=0;
int j=0;
for (i=0;i<=80000;i++){}
PORTD = 1;
for (j=0;j<=80000;j++){}
PORTD = 0;
} // main loop
} // main