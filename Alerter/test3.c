#include "test.h"
#include <plib.h> 

void initTimer2(void);
void initTimer4(void);
void initPort(void);
void DisplayTMR2(void);
void DisplayTMR4(void);
void initCN (void);

long start; 

int main() {
initPort();
LCD_init(); 

LCD_puts(startStr2);

while(1){}
}

void initPort() {
DDPCONbits.JTAGEN = 0; 
TRISD = 0xff40; 
TRISDCLR = 0x00bf; 
TRISC = 0xffeb;
TRISE = 0xff00;
TRISA = 0xff00;
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

//此程序可用，勿改

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
IEC1CLR = 0x0001;
if (my_port_d6!=PORTDbits.RD6 && PORTDbits.RD6==0) {start=1;}

my_port_d6 = PORTDbits.RD6;
IFS1CLR = 0x0001;
IEC1SET = 0x0001;
}