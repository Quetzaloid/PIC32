#include "LCD.h"
#include <plib.h>

uchar my_ddram_addr;

int main() {
OSCSetPBDIV (OSC_PB_DIV_1); //configure PBDIV so PBCLK = SYSCLK
asm("nop");
MCU_init();
LCD_init();
LCD_puts(startStr1);
LCD_goto(0x40);
LCD_puts(startStr1);
while(1) {}
}

void MCU_init() {
DDPCONbits.JTAGEN = 0; 
TRISA = 0xfffc;
TRISD = 0x0000;
}

void LCD_init() {
DelayMsec(15); //wait for 15 ms
RS = 0; //send command
Data = LCD_IDLE; //function set - 8 bit interface
DelayMsec(5); //wait for 5 ms
Data = LCD_IDLE; //function set - 8 bit interface
DelayUsec(100); //wait for 100 us
Data = LCD_IDLE; //function set
DelayMsec(5);
Data = LCD_IDLE;
DelayUsec(100);
LCD_putchar(LCD_2_LINE_4_BITS);
DelayUsec(40);
LCD_putchar(LCD_DSP_CSR);
DelayUsec(40);
LCD_putchar(LCD_CLR_DSP);
DelayMsec(5);
LCD_putchar(LCD_CSR_INC);

my_ddram_addr=0;
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
RS=0;
LCD_goto(my_ddram_addr);
DelayUsec(40);
RS=1;
LCD_putchar(*p);
DelayUsec(40);
RS=0;
my_ddram_addr=my_ddram_addr+1;
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
my_ddram_addr=addr;
}

void DelayUsec(uchar num) {
int i=9;
for (i=9;i<num;i++) {}
}

void GenMsec() {
int i=0;
for (i=0;i<998;i++) {}
asm("nop");
asm("nop");
}

void DelayMsec(uchar num) {
uchar i;
for (i=0; i<num; i++) {
GenMsec();
}
}

