#include "test.h"
#include <plib.h> 

void initTimer2(void);
void initTimer4(void);
void initPort(void);
void DisplayTMR2(void);
void DisplayTMR4(void);
void initCN (void);
void initPWM(void);
void alarm(void);

long start; 
int a,b,c, a1,b1,c1;
int motor_position;
int alm;

int main() {
initPWM();
a=0;b=0;c=0;
a1=0;b1=0;c1=0;
first=1;
start=0;
alm=0;
motor_position=0;
int k=0;
for (k=0;k<=7;k++) {ref_distance1[k]=0;ref_distance2[k]=0;cur_distance1[k]=0;cur_distance2[k]=0;}
initIntGlobal();
initCN();
initTimer2();
initTimer4();
initPort();
LCD_init(); 

while(1)
{
while(start)
{
int i=0,j=0;
for (i=1;i<=8;i++)
{
motor_position=i;
for (j=0;j<32;j++)
{
}
///////////////////////////////////////////////////////////////////////////////////////////
TMR2=0; TMR4=0;
PORTDSET=0x0220;
DelayUsec(15);
PORTDCLR=0x0220;
DelayMsec(16);
a=TMR2; a1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0220;
DelayUsec(15);
PORTDCLR=0x0220;
DelayMsec(16);
b=TMR2; b1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0220;
DelayUsec(15);
PORTDCLR=0x0220;
DelayMsec(16);
c=TMR2; c1=TMR4;

DisplayTMR2();
DisplayTMR4();
if ( (a<80000 || a1<80000 || b<80000 || b1<80000 || c<80000 || c1<80000)&& (b-c>1000 
|| c-b>1000 || b1-c1>1000 || c1-b1>1000 || a-b>1000 || b-a>1000 ||
a1-b1>1000 || b1-a1>1000 || a-c>1000 || c-a>1000 || a1-c1>1000 || c1-a1>1000 ))
{PORTDbits.RD7=1;PORTDbits.RD8=1;}
DelayMsec(20);
PORTDbits.RD7=0;PORTDbits.RD8=0;
///////////////////////////////////////////////////////////////////////////////////////////
} 
first=0;

for (i=7;i>=0;i--)
{
motor_position=i;
for (j=0;j<32;j++)
{ 
}   
///////////////////////////////////////////////////////////////////////////////////////////
TMR2=0; TMR4=0;
PORTDSET=0x0220;
DelayUsec(15);
PORTDCLR=0x0220;
DelayMsec(16);
a=TMR2; a1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0220;
DelayUsec(15);
PORTDCLR=0x0220;
DelayMsec(16);
b=TMR2; b1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0220;
DelayUsec(15);
PORTDCLR=0x0220;
DelayMsec(16);
c=TMR2; c1=TMR4;

DisplayTMR2();
DisplayTMR4();
if ( (a<80000 || a1<80000 || b<80000 || b1<80000 || c<80000 || c1<80000)&& (b-c>1000 
|| c-b>1000 || b1-c1>1000 || c1-b1>1000 || a-b>1000 || b-a>1000 ||
a1-b1>1000 || b1-a1>1000 || a-c>1000 || c-a>1000 || a1-c1>1000 || c1-a1>1000 ))
{PORTDbits.RD7=1;PORTDbits.RD8=1;}
DelayMsec(20);
PORTDbits.RD7=0;PORTDbits.RD8=0;
///////////////////////////////////////////////////////////////////////////////////////////
}
}
}
}

void initPort() {
TRISD = 0xfc40; 
TRISG = 0xffff; 
TRISDCLR = 0x01bf; 
TRISC = 0xffeb;
TRISE = 0xff00;
PORTCCLR = 0x0001f;
}

void DisplayTMR2() {
echo_time=TMR2;
uchar str1[10];
int i=0;
int p=1;
for (i=0;i<9;i++) 
{
int temp=echo_time/10;
int digit=echo_time-temp*10;
str1[8-i]=digit+48;
echo_time-=digit;
echo_time/=10;
}
str1[9]=NULL;
LCD_goto(0x0);
LCD_puts(str1);
}

void DisplayTMR4() {
echo_time4=TMR4;
uchar str1[10];
int i=0;
int p=1;
for (i=0;i<9;i++) 
{
int temp=echo_time4/10;
int digit=echo_time4-temp*10;
str1[8-i]=digit+48;
echo_time4-=digit;
echo_time4/=10;
}
str1[9]=NULL;
LCD_goto(0x40);
LCD_puts(str1);
}

void initTimer2() {
T2CON = 0x0;
T3CON = 0x0; 
T2CONSET = 0x0088; 
TMR2 = 0x0;
PR2 = 0xFFFFFFFF; 
T2CONSET = 0x8000;
}

void initTimer4() {
T4CON = 0x0;
T5CON = 0x0; 
T4CONSET = 0x0088; 
TMR4 = 0x0;
PR4 = 0xFFFFFFFF; 
T4CONSET = 0x8000;
}

void initCN () {
asm("di");
CNCON = 0x8000;
CNEN = 0x00008400;
my_port_d6 = PORTDbits.RD6;
my_port_g8 = PORTGbits.RG8;

IPC6SET = 0x00140000;
IPC6SET = 0x00030000;
IFS1CLR = 0x0001;
IEC1SET = 0x0001;
asm("ei");
}

#pragma interrupt CN_ISR ipl5 vector 26
void CN_ISR (void) {
static char a=0;
IEC1CLR = 0x0001;
if (!a && my_port_d6!=PORTDbits.RD6 && PORTDbits.RD6==0) {
start=1;a=1; CNEN = 0x00000400;}
if (my_port_g8!=PORTGbits.RG8 /* && PORTGbits.RG8==1*/) {}
my_port_g8 = PORTGbits.RG8;
my_port_d6 = PORTDbits.RD6;
IFS1CLR = 0x0001;
IEC1SET = 0x0001;
}

void alarm() {
initPWM();
OC1RS+=0x7F; 
int j=0;
for (j=0;j<32*motor_position;j++)
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
while (!alm) {}
initTimer2();
}


void initPWM() {
T2CON = 0x0;
TMR2 = 0x0;
OC1CON = 0x0000;//stop OC1 module
OC1RS = 0;
OC1R = 0;
OC1CON = 0x0006;//OC1 16-bit, Timer 2, in PWM mode w/o FP
PR2 = 0x00FF;
T2CONSET = 0x8000;//start Timer 2
OC1CONSET = 0x8000;//enable OC1 module for PWM generation
}