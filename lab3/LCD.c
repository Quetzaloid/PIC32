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

const uchar startStr1[] = "Digital Clock";
const uchar startStr2[] = "SJTU JI - 000";
const uchar startStr3[] = "A";

void MCU_init(void);
void LCD_init(void);
void LCD_putchar(uchar c);
void LCD_puts(const uchar *s);
void LCD_goto(uchar addr);
void GenMsec(void);
void DelayUsec(uchar num);
void DelayMsec(uchar num);
uchar my_ddram_addr;

int main() {
//DDPCONbits.JTAGEN = 0; 
//OSCSetPBDIV (OSC_PB_DIV_1); //configure PBDIV so PBCLK = SYSCLK
//asm("nop");

TRISC = 0xfff0;
TRISD = 0x0000;
//MCU_init();
LCD_init();
LCD_puts(startStr1);
LCD_goto(0x40);
LCD_puts(startStr2);
while(1) {}
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
//RS=0;
//LCD_goto(my_ddram_addr);
//DelayMsec(5); 
RS=1;
LCD_putchar(*p);
DelayMsec(5); 
RS=0;
//my_ddram_addr=my_ddram_addr+1;
p++;
}
/*E=1;
RS=1;
LCD_putchar(65);
DelayMsec(5); 
RS=0;
E=0;*/
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
//my_ddram_addr=addr;
}

void DelayUsec(uchar num) {
int i=9;
for (i=9;i<num;i++) {}
}

void GenMsec() {
int i=0;
for (i=0;i<998;i++) {}
//asm("nop");
//asm("nop");
}

void DelayMsec(uchar num) {
uchar i;
for (i=0; i<num; i++) {
GenMsec();
}
}


