//power_defines.h
//lcd_defines.h
//HD44780 Commands 
#define CLEAR_LCD            0x01 
#define RET_CUR_HOME         0x02 
#define SHIFT_CUR_RIGHT      0x06 
#define SHIFT_CUR_LEFT       0x07 
#define DSP_OFF              0x08 
#define DSP_ON_CUR_OFF       0x0c 
#define DSP_ON_CUR_ON        0x0E 
#define DSP_ON_CUR_BLINK     0x0F 
#define SHIFT_DISP_LEFT      0x10 
#define SHIFT_DISP_RIGHT     0x14 
#define MODE_8BIT_1LINE      0x30 
#define MODE_4BIT_1LINE      0x20 
#define MODE_8BIT_2LINE      0x38 
#define MODE_4BIT_2LINE      0x28 
#define GOTO_LINE1_POS0      0x80 
#define GOTO_LINE2_POS0      0xC0 
#define GOTO_LINE3_POS0      0x94 
#define GOTO_LINE4_POS0      0xD4 
#define GOTO_CGRAM_START     0x40 
//macros for LCD pins
#define LCD_MODE 8
#define LCD_DATA 8//@p0.8(d0) to p0.15(d7)
#define LCD_RS   16
#define LCD_RW   17
#define LCD_EN   18

//kpm_defines.h
#define ROW0 16 //p1.16
#define ROW1 17 //p1.17
#define ROW2 18 //p1.18
#define ROW3 19 //p1.19
#define COL0 20 //p1.20
#define COL1 21 //p1.21
#define COL2 22 //p1.22
#define COL3 23 //p1.23

//rtc_defines.h
#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H
// System clock and peripheral clock Macros
#define FOSC 12000000
#define CCLK (5*FOSC)  
#define PCLK (CCLK/4)
// RTC Macros
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)
//CCR register bits 
#define RTC_ENABLE  (1<<0)
#define RTC_RESET   (1<<1)
#define RTC_CLKSRC  (1<<4)
#define _LPC2148
#endif

//defines.h 
#define SETBIT(WORD,BIT) WORD|=1<<BIT
#define CLRBIT(WORD,BIT) WORD&=~(1<<BIT)
#define READBIT(WORD,BIT) (WORD>>BIT)&1
#define WRITEBIT(WORD,BIT,BITLEVEL) (BITLEVEL)?(SETBIT(WORD,BIT)):(CLRBIT(WORD,BIT))
#define READWRITEBIT(DWORD,DBIT,SWORD,SBIT) (DWORD=(DWORD&~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT))
#define WRITEBYTE(WORD,BITSTARTPOS,BYTE) WORD=((WORD&~(0XFF<<BITSTARTPOS))|(BYTE<<BITSTARTPOS))
#define WRITE2PORTBIT(PORTNO,BITPOS,BITLEVEL) ((PORTNO==0)?(BITLEVEL?(IOSET0=1<<BITPOS):(IOCLR0=1<<BITPOS)):(BITLEVEL?(IOSET1=1<<BITPOS):(IOCLR1=1<<BITPOS)))
#define WRITENIBBLE(WORD,BITSTARTPOS,NIBBLE) (WORD=(WORD&~(15<<BITSTARTPOS))|(NIBBLE<<BITSTARTPOS))
#define READNIBBLE(WORD,BITSTARTPOS) ((WORD>>BITSTARTPOS)&15)

//pin_function_defines.h
//each pin function set
#define PIN_FUNC1 0
#define PIN_FUNC2 1
#define PIN_FUNC3 2
#define PIN_FUNC4 3
