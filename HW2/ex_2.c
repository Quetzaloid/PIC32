#include <p32xxxx.h>

void genSec( int n)
   {
     int i = 0;
     while (i <= 5333333*n)
        {
          i++;
        }
   }

int main()
   {
     asm("nop");
     genSec(1);
     asm("nop");

	 return 0;
   }