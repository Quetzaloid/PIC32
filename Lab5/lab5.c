#include <p32xxxx.h>
#include <plib.h>

#define LCD_IDLE 0x33
#define LCD_2_LINE_4_BITS 0x28
#define LCD_2_LINE_8_BITS 0x38
#define LCD_DSP_CSR 0x0c
#define LCD_CLR_DSP 0x01
#define LCD_CSR_INC 0x06
#define LCD_SFT_MOV 0x14

#define RS PORTCbits.RC1
#define E  PORTCbits.RC2
#define Data PORTD //use PORTD<7:4>
typedef unsigned char uchar;
struct bits {
unsigned timer2_done : 1;
} flags;

const uchar startStr1[] = "DigitalVoltmeter";
const uchar startStr2[] = "SJTU JI - 000";
const uchar startStr3[] = "A";

long ADCValue;

void MCU_init(void);
void LCD_init(void);
void LCD_putchar(uchar c);
void LCD_puts(const uchar *s);
void LCD_goto(uchar addr);
void GenMsec(void);
void DelayUsec(uchar num);
void DelayMsec(uchar num);
void initADC(void);

main(){

TRISC = 0xfff0;
TRISD = 0x0000;
LCD_init();
//*Test for LCD*/
/*-----------------
LCD_puts(startStr1);
LCD_goto(0x40);
LCD_puts(startStr2);
while (1) {}
//*/
///*-----------------
initADC();
while(1) {
AD1CON1SET=0x0002;
DelayMsec(2);
AD1CON1CLR=0x0002;
while (!(AD1CON1 & 0x0001));
ADCValue = ADC1BUF0;
double Vtg=3.3*ADCValue/1024;
int x=100*Vtg;
int x1=x/100; x-=x1*100;
int x2=x/10;  x-=x2*10;
int x3=x;
uchar startStr4[14];
startStr4[0]=x1+48;
startStr4[1]='.';
startStr4[2]=x2+48;
startStr4[3]=x3+48;
startStr4[4]='V';
startStr4[5]=' ';
startStr4[6]=' ';
startStr4[7]=' ';
startStr4[8]=' ';
startStr4[9]=' ';
startStr4[10]=' ';
startStr4[11]=' ';
startStr4[12]=' ';
startStr4[13]=' ';
LCD_puts(startStr1);
LCD_goto(0x40);
LCD_puts(startStr4);
}//while
//*/
}//main

void initADC() {
TRISB = 0xffff;
AD1PCFG = 0x0fffB;
AD1CHS = 0x00020000;
//AD1CON1SET = 0x0300;
AD1CSSL = 0;
AD1CON2 = 0;
AD1CON3 = 0x0002;
AD1CON1SET=0x8000;
}

void DelayMsec(uchar num) {
uchar i;
for (i=0; i<num; i++) {
GenMsec();
}
}

void GenMsec() {
int i=0;
for (i=0;i<998;i++) {}
asm("nop");
asm("nop");
}

void MCU_init() {
}

void LCD_init() {
DelayMsec(8); //wait for 15 ms
RS = 0; //send command
Data = LCD_IDLE; //function set - 8 bit interface
DelayMsec(8); //wait for 5 ms
Data = LCD_IDLE; //function set - 8 bit interface
DelayMsec(8); //wait for 100 us
Data = LCD_IDLE; //function set
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
Data = c; //sending higher nibble
E = 0; 
E = 1;
Data <<= 4; //sending lower nibble through higher 4 ports
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

void DelayUsec(uchar num) {
int i=9;
for (i=9;i<num;i++) {}
}