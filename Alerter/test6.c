#include "test.h"
#include <plib.h> 

void initTimer2(void);
void initTimer4(void);
void initPort(void);
void DisplayTMR2(void);
void DisplayTMR4(void);
void initCN(void);
void alarm(void);
void initPWM(void);

long start; 
int a,b,c, a1,b1,c1;
char tmr2,tmr4;

int main() {
a=0;b=0;c=0;
a1=0;b1=0;c1=0;
tmr2=0;
tmr4=4;
first=1;
start=0;
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
for (j=0;j<32;j++)
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
///////////////////////////////////////////////////////////////////////////////////////////
TMR2=0; TMR4=0;
PORTDSET=0x0021;
DelayUsec(15);
PORTDCLR=0x0021;
DelayMsec(16);
a=TMR2; a1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0021;
DelayUsec(15);
PORTDCLR=0x0021;
DelayMsec(16);
b=TMR2; b1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0021;
DelayUsec(15);
PORTDCLR=0x0021;
DelayMsec(16);
c=TMR2; c1=TMR4;

DisplayTMR2();
DisplayTMR4();
if ( (a<80000 || a1<60000 || b<60000 || b1<60000 || c<60000 || c1<60000)&& (b-c>500 
|| c-b>500 || b1-c1>500 || c1-b1>500 || a-b>500 || b-a>500 ||
a1-b1>500 || b1-a1>500 || a-c>500 || c-a>500 || a1-c1>500 || c1-a1>500 ))
{PORTDbits.RD7=1;}
DelayMsec(20);
PORTDbits.RD7=0;
///////////////////////////////////////////////////////////////////////////////////////////
} 
first=0;

for (i=7;i>=0;i--)
{
for (j=0;j<32;j++)
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
///////////////////////////////////////////////////////////////////////////////////////////
TMR2=0; TMR4=0;
PORTDSET=0x0021;
DelayUsec(15);
PORTDCLR=0x0021;
DelayMsec(16);
a=TMR2; a1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0021;
DelayUsec(15);
PORTDCLR=0x0021;
DelayMsec(16);
b=TMR2; b1=TMR4;

TMR2=0; TMR4=0;
PORTDSET=0x0021;
DelayUsec(15);
PORTDCLR=0x0021;
DelayMsec(16);
c=TMR2; c1=TMR4;

DisplayTMR2();
DisplayTMR4();
if ( (a<60000 || a1<60000 || b<60000 || b1<60000 || c<60000 || c1<60000)&& (b-c>500 
|| c-b>500 || b1-c1>500 || c1-b1>500 || a-b>500 || b-a>500 ||
a1-b1>500 || b1-a1>500 || a-c>500 || c-a>500 || a1-c1>500 || c1-a1>500 ))
{PORTDbits.RD7=1;}
DelayMsec(20);
PORTDbits.RD7=0;
///////////////////////////////////////////////////////////////////////////////////////////
}
}
}
}

void initPort() {
TRISD = 0xff40; 
TRISDCLR = 0x00bf; 
TRISC = 0xffeb;
TRISE = 0xff00;
PORTCCLR = 0x0001f;
}

void DisplayTMR2() {
if (!tmr2) {echo_time=TMR2;}
else {tmr2=0;}
uchar str1[6];
int i=0;
int p=1;
for (i=0;i<5;i++) 
{
int temp=echo_time/10;
int digit=echo_time-temp*10;
str1[4-i]=digit+48;
echo_time-=digit;
echo_time/=10;
}
str1[5]=NULL;
LCD_goto(0x0);
LCD_puts(str1);
}

void DisplayTMR4() {
if (!tmr4) {echo_time4=TMR4;}
else {tmr4=0;}
uchar str1[6];
int i=0;
int p=1;
for (i=0;i<5;i++) 
{
int temp=echo_time4/10;
int digit=echo_time4-temp*10;
str1[4-i]=digit+48;
echo_time4-=digit;
echo_time4/=10;
}
str1[5]=NULL;
LCD_goto(0x40);
LCD_puts(str1);
}

void initTimer2() {
T2CON = 0x0; 
T2CONSET = 0x0080; 
TMR2 = 0x0;
PR2 = 0xFFFF; 
T2CONSET = 0x8000;

IPC2SET = 0x0000001C;//Set priority level = 7
IPC2SET = 0x00000001;//Set subpriority level = 1
IFS0CLR = 0x00000100;//Clear Timer interrupts
IEC0SET = 0x00000100;//Enable Timer interrupts
}

void initTimer4() {
T4CON = 0x0;
T4CONSET = 0x0080; 
TMR4 = 0x0;
PR4 = 0xFFFF; 
T4CONSET = 0x8000;

IPC4SET = 0x0000001C;//Set priority level = 7
IPC4SET = 0x00000001;//Set subpriority level = 1
IFS0CLR = 0x00010000;//Clear Timer interrupts
IEC0SET = 0x00010000;//Enable Timer interrupts
}

void initCN () {
asm("di");
CNCON = 0x8000;
CNEN = 0x00008000;
my_port_d6 = PORTDbits.RD6;

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
if (!a && my_port_d6!=PORTDbits.RD6 && PORTDbits.RD6==0) {start=1;a=1;}

my_port_d6 = PORTDbits.RD6;
IFS1CLR = 0x0001;
IEC1SET = 0x0001;
}

void alarm() {
}

void initPWM() {
/*OC1CON = 0x0000;      //stop OC1 module
OC1RS = 0;
OC1R = 0;
OC1CON = 0x0006;      //OC1 16-bit, Timer 2, in PWM mode w/o FP
PR2 = 0x00FF;
T2CONSET = 0x8000;    //start Timer 2
OC1CONSET = 0x8000;   //enable OC1 module for PWM generation*/
}

#pragma interrupt T2_ISR ipl7 vector 8
void T2_ISR (void) {
tmr2=1;
echo_time=TMR2;
IFS0CLR = 0x00000100;// Clear timer 2 interrupt flag
}

#pragma interrupt T4_ISR ipl7 vector 16
void T4_ISR (void) {
tmr4=1;
echo_time4=65500;
IFS0CLR = 0x00010000;// Clear timer 4 interrupt flag
}