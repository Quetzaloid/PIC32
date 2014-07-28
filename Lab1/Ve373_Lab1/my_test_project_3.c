#include <p32xxxx.h>
main(){
TRISD = 0xff00; 
while(1) {
int i=0;
int j=0;
for (i=0;i<727;i++){asm("nop");}
PORTD = 1;
for (j=0;j<1454;j++){asm("nop");}
PORTD = 0;
} 
} 