#include <p32xxxx.h>

#define LCD_IDLE 0x33
#define LCD_2_LINE_4_BITS 0x28
#define LCD_2_LINE_8_BITS 0x38
#define LCD_DSP_CSR 0x0c
#define LCD_CLR_DSP 0x01
#define LCD_CSR_INC 0x06
#define LCD_SFT_MOV 0x14

#define RS PORTAbits.RA0
#define E  PORTAbits.RA1
#define Data PORTD //use PORTD<7:4>
typedef unsigned char uchar;
struct bits {
unsigned timer2_done : 1;
} flags;

const uchar startStr1[] = "Digital Clock";
const uchar startStr2[] = "SJTU JI - LAB3";
const uchar startStr3[] = "A";

void MCU_init(void);
void LCD_init(void);
void LCD_putchar(uchar c);
void LCD_puts(const uchar *s);
void LCD_goto(uchar addr);
void GenMsec(void);
void DelayUsec(uchar num);
void DelayMsec(uchar num);


