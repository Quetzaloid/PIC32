#include <p32xxxx.h>
#include <plib.h>
/* Global variables */
unsigned int acc = 20;//acc determines the acceleration rate
/* Function prototypes */
void initIntGlobal (void);
void initTimer (void);
void initPWM (void);
/* Timer54 ISR */
#pragma interrupt T54_ISR ipl7 vector 20
void T54_ISR (void) {
acc = -acc;//increase or decrease motor speed
IFS0CLR = 0x00100000;//Clear timer 5 interrupt flag
}
/* Timer2 ISR -handling OC-PWM module operations */
#pragma interrupt PWM_ISR ipl3 vector 8
void PWM_ISR (void) {
static int pwm = 0;//variable duty cycle
pwm += acc;//duty cycle increments or decrements by +/-acc
if (pwm<0) pwm = 0;
else if (pwm>PR2) pwm = PR2;
OC1RS = pwm;//update duty cycle register
IFS0CLR = 0x0100;//clear Timer 2 interrupt flag
}
/* Configure interrupt globally */
void initIntGlobal() {
INTCONbits.MVEC = 1;// Enable multiple vector interrupt
asm("ei");// Enable all interrupts
}
/* Initialize timer to create period of accelerating and decelerating */
void initTimer() {
T4CON = 0x0;//stop Timer 4
T5CON = 0x0;//stop Timer 5
T4CONSET = 0x0008;//32-bit mode, prescaler 1:1, PBCLK
IPC5SET = 0x0000001F;//priority level 7, subpriority level 3
IFS0CLR = 0x00100000;//clear Timer 5 interrupt flag
IEC0SET = 0x00100000;//enable Timer 5:4 interrupt
TMR4 = 0x0;//clear Timer 5:4
PR4 = 0x000006FF;//accelerating and decelerating period is:
//0x700*1/PBCLK(8MHz) = 224 us
T4CONSET = 0x8000;//start timer
}
/* Initialize OC module and timer base -Timer 2 */
void initPWM() {
OC1CON = 0x0000;//stop OC1 module
OC1RS = 0;//initialize duty cycle register
OC1R = 0;//initialize OC1R register for the first time
OC1CON = 0x0006;//OC1 16-bit, Timer 2, in PWM mode w/o FP
PR2 = 0x00FF;//PWM signal period = 0x100*1/PBCLK = 32 us
//Thus, PWM Frequency = 32.25 kHz
IFS0CLR = 0x00000100;//clear Timer 2 interrupt
IEC0SET = 0x00000100;//enable Timer 2 interrupt
IPC2SET = 0x0000000F;//Timer 2 interrupt priority 3, subpriority 3
T2CONSET = 0x8000;//start Timer 2
OC1CONSET = 0x8000;//enable OC1 module for PWM generation
}
/* main function */
int main() {
OSCSetPBDIV (OSC_PB_DIV_1); //configure PBDIV so PBCLK = SYSCLK
initIntGlobal();
initTimer();
initPWM();
while (1);
}
