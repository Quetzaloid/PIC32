#include "test.h"
#include <plib.h> 

int main() {
char clkwise=1;
initPort();
while(1) {
int i=0,j=0;
if (clkwise) {
for (i=0;i<=7;i++)
{
for (j=0;j<5;j++)
{
PORTDCLR = 0x0002;
PORTDSET = 0x0010;
DelayMotor();
PORTDCLR = 0x0010;
PORTDSET = 0x0008;
DelayMotor();
PORTDCLR = 0x0008;
PORTDSET = 0x0004;
DelayMotor();
PORTDCLR = 0x0004;
PORTDSET = 0x0002;
DelayMotor(); 
}
DelayMsec(30);
} 
}
else {
DelayMsec(30);
for (i=0;i<=7;i++)
{
for (j=0;j<5;j++)
{
PORTDCLR = 0x0010;
PORTDSET = 0x0002;
DelayMotor();
PORTDCLR = 0x0002;
PORTDSET = 0x0004;
DelayMotor();
PORTDCLR = 0x0004;
PORTDSET = 0x0008;
DelayMotor();
PORTDCLR = 0x0008;
PORTDSET = 0x0010;
DelayMotor(); 
}   
DelayMsec(30);
} 
}
}
}

void initPort() {
TRISD = 0xffe0; 
TRISDCLR = 0x001e; 
}


