//power_main.c                                                              
#include<LPC214x.h>                                                         
#include "types.h"                                                                                                                                                                   
#include "power_defines.h"                                                                                                                 
#include "power.h"                                                                                                                                      
#define EINT0_VIC_CHNO  14                                                  
//#define EINT0_STATUS_LED  16//@P1.16                                      
#define LED      4 //@po.4                                                 
#define ONOFF_SW 2 //@p0.2                                                                                                                              
void eint0_isr(void) __irq;                                                
static s32 hour,min,sec,date,month,year,day;                                
s32 on_hour,on_min,off_hour,off_min,flag;                                   
u8 cgramLUT[25]={0x0E,0x1F,0x1F,0x1F,0x0E,0x0A,0x0A,0x0A,0x04,0x04,0x0E,0x0E,0x0E,0x1F,0x04,0x04,0x0E,0x0E,0x11,0x11,0x15,0x0E,0x0A,0x0A};

int main()
{
//device to be controlled
IODIR0|=1<<LED;
//Initializations of LCD,Keypad,RTC
InitLCD();
Init_KPM();
RTC_Init();

//cfg p0.1 pin as EINT inputpin
CfgPortPinFunc(0,1,PIN_FUNC4);
//cfg VIC as peripheral
//cfg EINT0 as irq types default allareirq
//VIC IntSelect=0;
//enable EINT0 via VIC
VICIntEnable=1<<EINT0_VIC_CHNO;
	//load eint0 isr addr
VICVectAddr0=(u32) eint0_isr;
//cfg external interrupt peripheral, allow/enable EINT0,default all are enabled
//EXTINT=0;
//cfg EINT0 as edge triggered
EXTMODE=1<<0;
//def all are falling edge triggered
//EXTPOLAR=0;
//cfg EINT0 status LED asgpio out

while(1)
{
//Get and display the current time on LCD
GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
GetRTCDateInfo(&date,&month,&year);
DisplayRTCDate(date,month,year);
GetRTCDay(&day);
DisplayRTCDay(day);

if((HOUR>on_hour || (HOUR==on_hour&&MIN>=on_min)) && (HOUR<off_hour || (HOUR==off_hour && MIN<off_min)))
{
//to on device between set time
IOSET0|=1<<LED;
CmdLCD(GOTO_LINE1_POS0+11);
StrLCD("DEV:");
//character to show device on
BuildCGRAM(cgramLUT,24);
CmdLCD(GOTO_LINE1_POS0+15);
CharLCD(0);
}
else
{
//to off device 
IOCLR0|=1<<LED;
CmdLCD(GOTO_LINE1_POS0+11);
StrLCD("DEV:");
//character to show off device status
BuildCGRAM(cgramLUT,24);
CmdLCD(GOTO_LINE1_POS0+15);
CharLCD(2);
}
//block to display set on-off time if switch pressed 
if(READBIT(IOPIN0,ONOFF_SW)==0)
{
	//statements for on time
 CmdLCD(CLEAR_LCD);
 CmdLCD(GOTO_LINE1_POS0);                                                   
 StrLCD("ONTIME:");
 CmdLCD(GOTO_LINE1_POS0+7);
 U32LCD(on_hour);
 CmdLCD(GOTO_LINE1_POS0+9);
 CharLCD(':');
 CmdLCD(GOTO_LINE1_POS0+10);
 U32LCD(on_min);
//statements to display off time
 CmdLCD(GOTO_LINE2_POS0);
 StrLCD("OFTIME:");
 CmdLCD(GOTO_LINE2_POS0+7);
 U32LCD(off_hour);
 CmdLCD(GOTO_LINE2_POS0+9);
 CharLCD(':');
 CmdLCD(GOTO_LINE2_POS0+10);
 U32LCD(off_min);
 delay_s(3);
 while(READBIT(IOPIN0,ONOFF_SW)==0);
 CmdLCD(CLEAR_LCD);
}
if(flag)
{
	//menu function
edit_menu();
CmdLCD(CLEAR_LCD);
flag=0;
}
//block of statements to display alarm when time is set
if(on_hour)
{
BuildCGRAM(cgramLUT,24);
CmdLCD(GOTO_LINE1_POS0+9);
CharLCD(1);
}
//statements for incorrect on-off time
if(on_hour>=off_hour && on_min>off_min)
{                                                                                                                                                                                                                                   
  CmdLCD(CLEAR_LCD);
  CmdLCD(GOTO_LINE1_POS0);                                                    
	StrLCD("ONTIME>OFFTIME");                                                   
	CmdLCD(GOTO_LINE2_POS0);
  StrLCD("Enter again");
  delay_s(1);
  edit_onoff_time();
}
}
}
