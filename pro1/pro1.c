#include <p32xxxx.h>

void delay()
  {
    int k;
    for(k=0; k<200; k++)
       {  }
  }

void main(){
  TRISD = 0x0000; 
  while(1) 
    {
      PORTD = 0xfff7;
      delay();
      PORTD = 0xfffb;
      delay();
      PORTD = 0xfffd;
      delay();
      PORTD = 0xfffe;
      delay();      
    } 
} 