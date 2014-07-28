/************************************************************************
* test.h
* Header file for the all tests of the equipments
************************************************************************/
#include <p32xxxx.h>
#pragma config FPBDIV = DIV_1
/* define data types */
typedef unsigned char uchar;
/* define gloabal variables */
long my_port_d6; 
long my_port_d13; 
long my_port_g8; 
double echo_time;
double echo_time4;
/* define macros for LCD instructions*/
#define LCD_IDLE 0x33
#define LCD_2_LINE_4_BITS 0x28
#define LCD_2_LINE_8_BITS 0x38
#define LCD_DSP_CSR 0x0c
#define LCD_CLR_DSP 0x01
#define LCD_CSR_INC 0x06
#define LCD_SFT_MOV 0x14
/* define macros for interfacing ports*/
#define RS PORTCbits.RC2
#define E  PORTCbits.RC4
#define Data PORTE //use PORTA<7:4>
/* define constant */
const uchar startStr1[] = "Digital Clock";
const uchar startStr2[] = "SJTU JI - 000";
const uchar startStr3[] = "A";
int ref_distance1[9];
int ref_distance2[9];
int cur_distance1[9];
int cur_distance2[9];
const uchar Pstr0[] = "South";
const uchar Pstr1[] = "South-22.5-West";
const uchar Pstr2[] = "South-45-West";
const uchar Pstr3[] = "South-67.5-West";
const uchar Pstr4[] = "West";
const uchar Pstr5[] = "North-67.5d-West";
const uchar Pstr6[] = "North-45-West";
const uchar Pstr7[] = "North-22.5-West";
const uchar Pstr8[] = "North";
const uchar Pstr9[] = "North-22.5-East";
const uchar Pstr10[] = "North-45-East";
const uchar Pstr11[] = "North-67.5-East";
const uchar Pstr12[] = "East";
const uchar Pstr13[] = "South-67.5-East";
const uchar Pstr14[] = "South-45-East";
const uchar Pstr15[] = "South-22.5-East";
char first;
/* Function prototypes */
void MCU_init(void);
void LCD_init(void);
void LCD_putchar(uchar c);
void LCD_puts(const uchar *s);
void LCD_goto(uchar addr);
void GenMsec(void);
void DelayUsec(uchar num);
void DelayMsec(uchar num);
void DelayMotor(void);
void initIntGlobal(void);
void initCN(void);
void initPort(void);
/*****************end of test.h**********************/
/**/
void DelayUsec(uchar num) {
int i=9;
for (i=9;i<num;i++) {}
}

/**/
void GenMsec() {
int i=0;
for (i=0;i<998;i++) {}
asm("nop");
asm("nop");
}

/**/
void DelayMsec(uchar num) {
uchar i;
for (i=0; i<num; i++) {
GenMsec();
}
}

/**/
void initIntGlobal() {
INTCONbits.MVEC = 1;
asm("ei");
}

void MCU_init() {
}

void LCD_init() {
DelayMsec(8); 
RS = 0; 
Data = LCD_IDLE;
DelayMsec(8); 
Data = LCD_IDLE; 
DelayMsec(8); 
Data = LCD_IDLE; 
DelayMsec(8);
Data = LCD_IDLE;
DelayMsec(8); 
LCD_putchar(LCD_2_LINE_4_BITS);
DelayMsec(8); 
LCD_putchar(LCD_DSP_CSR);
DelayMsec(5); 
LCD_putchar(LCD_CLR_DSP);
DelayMsec(6);
LCD_putchar(LCD_CSR_INC);
}

void LCD_putchar(uchar c) {
E = 1;
Data = c; 
E = 0; 
E = 1;
Data <<= 4; 
E = 0; 
}

void LCD_puts(const uchar *s) {
uchar *p=s;

while (*p) {
RS=1;
LCD_putchar(*p);
DelayMsec(5); 
RS=0;
p++;
}
}

void LCD_goto(uchar addr) {
E=1;
RS=0;
Data=0x80+addr;
E=0;
E=1;
RS=0;
Data<<=4;
E=0;
}

void DelayMotor()
{
int k;
for(k=0; k<180; k++){}
}