#include <p32xxxx.h>

int main()
   {
     TRISA = 0xff00;
     while(1)
        {
          int i=0, j=0;
          while (i <= 1400)
             {
               PORTA = 1;
               i++; 
             }
          while (j <= 700)
             {
               PORTA = 0;
               j++; 
             }
        }
     return 0;
   }