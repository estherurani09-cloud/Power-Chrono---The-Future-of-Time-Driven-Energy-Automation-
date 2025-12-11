#include "types.h"
//power.h
//declarations for main title 
void edit_menu(void);
void edit_rtc(void);
void edit_onoff_time(void);

//delay.h
//declarations for delays
void delay_us(u32);
void delay_ms(u32);
void delay_s(u32);

//lcd.h
//declarations for LCD
void WriteLCD(u8 byte);
void CmdLCD(u8 cmdByte);
void InitLCD(void);
void CharLCD(u8 asciiVal);
void StrLCD(s8 *);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32 fn,u8 nDP);
void BuildCGRAM(u8 *,u8);

//kpm.h-declarations for Keypad
void Init_KPM(void);
u32 ColScan(void);
u32 RowCheck(void);
u32 ColCheck(void);
u32 KeyScan(void);
void Readnum(s32 *num);

//rtc.h-declarations for Real time clock
#ifndef RTC_H
#define RTC_H
void RTC_Init(void);
void GetRTCTimeInfo(s32 *,s32 *,s32 *);
void DisplayRTCTime(u32,u32,u32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);
void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);
void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);
#endif

//pin_connect_block.h
void CfgPortPinFunc(u32 portNo,u32 pinNo,u32 pinFunc);
