#include <p32xxxx.h>
#include <plib.h>

/* Global variables */
long my_port_d6;
int pd=0;

/* Function prototypes */
void initIntGlobal (void);
void initPort (void);
void initCN (void);
void initPWM (void);
void initTimer3 (void);

/* main function */
int main() {
OSCSetPBDIV (OSC_PB_DIV_1); //configure PBDIV so PBCLK = SYSCLK
initIntGlobal();
initPort();
//initCN();
initTimer3();
initPWM();
while (1);
}

void initIntGlobal() {
INTCONbits.MVEC = 1;
asm("ei");
}

void initPort () {
//DDPCONbits.JTAGEN = 0;
TRISD = 0xfffe;
}

void initCN () {
asm("di");
CNCON = 0x8000;//Enable Change Notice module
CNEN = 0x00000040;//Enable individual CN pins
//CNPUE = 0x000020C0;//Enable weak pull ups for pins CN1, CN4 and CN18
my_port_d6 = PORTDbits.RD6;

IPC6SET = 0x00140000;//Set priority level = 5
IPC6SET = 0x00030000;//Set subpriority level = 3
IFS1CLR = 0x0001;//Clear interrupt flag
IEC1SET = 0x0001;//Enable Change Notice interrupts
asm("ei");
}

#pragma interrupt CN_ISR ipl5 vector 26
void CN_ISR (void) {
IEC1CLR = 0x0001;//disable interrupt
static int brighter = 0b1;
static int n = 0;
if (n == 6) {brighter = !brighter; n = 0;}
if (my_port_d6!=PORTDbits.RD6 && PORTDbits.RD6==0) {
if (brighter) {OC1RS+=0x2A; n++;}
else {OC1RS-=0x2A; n++;}
}
my_port_d6 = PORTDbits.RD6;
IFS1CLR = 0x0001;//clear interrupt flag
IEC1SET = 0x0001;//re-enable interrupt
}


void initPWM() {
OC1CON = 0x0000;//stop OC1 module
OC1RS = 0;
OC1R = 0;
OC1CON = 0x0006;//OC1 16-bit, Timer 2, in PWM mode w/o FP
PR2 = 0x00FF;
T2CONSET = 0x8000;//start Timer 2
OC1CONSET = 0x8000;//enable OC1 module for PWM generation
}


void initTimer3 () {
T3CON = 0x0020; 
TMR3 = 0x0;
PR3 = 0x0100;
T3CONSET = 0x8000; 
IPC3SET = 0x0000001C;//Set priority level = 7
IPC3SET = 0x00000001;//Set subpriority level = 1
IFS0CLR = 0x00001000;
IEC0SET = 0x00001000;
}


#pragma interrupt TMR3_ISR ipl7 vector 12
void TMR3_ISR (void) {
pd=!pd;
static int brighter = 0b1;
static int n = 0;
if (n == 6) {brighter = !brighter; n = 0;}
if (pd==0) {
if (brighter) {OC1RS+=0x2A; n++;}
else {OC1RS-=0x2A; n++;}
}
IFS0CLR = 0x00001000;
}
