//power_interrupt.c
#include <LPC214x.h>
#include "types.h"
#include "power.h"
#include "power_defines.h"
//global variables for RTC edits
s32 rhour,rmin,rsec,rdate,rmonth,ryear,rday;
//External variables declared in another file
extern s32 on_hour,on_min,off_hour,off_min,flag;
/*INTERRUPT SERVICE ROUTINE : EINT0*/
void eint0_isr(void) __irq
{
//set interrupt flag to indicate interrupt occured
flag=1;
//clear EINT0 status in external interrupt peripheral	
EXTINT=1<<0;
//clear EINT0 status in VIC
VICVectAddr=0;
}
 /*EDIT MENU – Main menu displayed after interrupt*/
void edit_menu()
{
u32 opt;
CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("Interrupt raised");
delay_s(1);
//Menu to choose
MENU1:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1.ED.RTC");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("2.ED.ONOFF3.EXIT");
opt=KeyScan();
delay_ms(200);
switch(opt)
{
case 1:edit_rtc();
return;
case 2:edit_onoff_time();
return;
case 3:return;
default:StrLCD("sel cor opt");
}
goto MENU1;
}
/**EDIT RTC – Change Time, Day, Date, Month, Year**/
void edit_rtc()
{
u32 op;
MENU2:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1.HH:MM:SS 2.DAY");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("3.DATE 4.EXIT");
op=KeyScan();
delay_ms(200);
switch(op)
{
//Edit Hour, Min, Sec
case 1:
HR:CmdLCD(CLEAR_LCD);
   CmdLCD(GOTO_LINE1_POS0);
   StrLCD("E.Hour(0 to 23)");
   CmdLCD(GOTO_LINE2_POS0);
   Readnum(&rhour);
   HOUR=rhour;
   if(rhour<0 || rhour>23)
   {
         CmdLCD(CLEAR_LCD);
     StrLCD("Invalid hour");
		 delay_s(1);
         goto HR;
   }
MINS:CmdLCD(CLEAR_LCD);
         CmdLCD(GOTO_LINE1_POS0);
     StrLCD("E.Min(0 to 59)");
     CmdLCD(GOTO_LINE2_POS0);
         Readnum(&rmin);
         MIN=rmin;
         if(rmin<0 || rmin>59)
        {
         CmdLCD(CLEAR_LCD);
     StrLCD("Invalid min");
         delay_s(1);
         goto MINS;
    }
SECS:CmdLCD(CLEAR_LCD);
         CmdLCD(GOTO_LINE1_POS0);
     StrLCD("E.Sec(0 to 59)");
         CmdLCD(GOTO_LINE2_POS0);
         Readnum(&rsec);
         SEC=rsec;
         if(rsec<0 || rsec>59)
         {
         CmdLCD(CLEAR_LCD);
     StrLCD("Invalid SECS");
         delay_s(1);
         goto SECS;
     }
				  break;
// Edit Day (0–6)
case 2:
week:CmdLCD(CLEAR_LCD);
     CmdLCD(GOTO_LINE1_POS0);
     StrLCD("E.Day(0 to 6)");
     CmdLCD(GOTO_LINE2_POS0);
         Readnum(&rday);
         DOW=rday;
     if(rday<0 || rday>6)
        {
         CmdLCD(CLEAR_LCD);
         StrLCD("Invalid day");
         delay_s(1);
         goto week;
    }
 break;
// Edit Date, Month, Year
case 3:
DT:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("E.Date(1 to 31)");
CmdLCD(GOTO_LINE2_POS0);
Readnum(&rdate);
DOM=rdate;
if(rdate<1 || rdate>31)
{
CmdLCD(CLEAR_LCD);
StrLCD("Invalid date");
delay_s(1);
goto DT;
}
MTH:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("E.Month(1 to 12)");
CmdLCD(GOTO_LINE2_POS0);
Readnum(&rmonth);
MONTH=rmonth;
if(rmonth<1 || rmonth>12)
{
CmdLCD(CLEAR_LCD);
StrLCD("Invalid month");
delay_s(1);
goto MTH;
}
YR:CmdLCD(CLEAR_LCD);
   CmdLCD(GOTO_LINE1_POS0);
   StrLCD("E.Year(1 to 4095)");
                 CmdLCD(GOTO_LINE2_POS0);
     Readnum(&ryear);
         YEAR=ryear;
     if(ryear<1 || ryear>4095)
     {
     CmdLCD(CLEAR_LCD);
     StrLCD("Invalid year");
         delay_s(1);
     goto YR;
     }
     break;
case 4:return;
default:CmdLCD(CLEAR_LCD);StrLCD("Sel cor opt");
}
goto MENU2;
}
/** EDIT ON/OFF TIME – Set On Time & Off Time **/
void edit_onoff_time(void)
{
  u32 op;
ONOFFMENU:CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.E.ONTIME3.EXIT");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("2.E.OFF TIME");
        op=KeyScan();
        delay_ms(200);
	// Edit ON time
        if(op==1)
        {
  OHR:CmdLCD(CLEAR_LCD);
      CmdLCD(GOTO_LINE1_POS0);
      StrLCD("ON HOUR(0 TO 23)");
      CmdLCD(GOTO_LINE2_POS0);
      Readnum(&on_hour);
      if(on_hour<0 || on_hour>23)
      {
       CmdLCD(CLEAR_LCD);
       StrLCD("Invalid Hour");
       goto OHR;
      }
        OMN:CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
         StrLCD("ON MIN(0 TO 59)");
         CmdLCD(GOTO_LINE2_POS0);
          Readnum(&on_min);
                if(on_min<0 || on_min>59)
                {
                  CmdLCD(CLEAR_LCD);
                  StrLCD("Invalid MINS");
                  goto OMN;
                }
				}
				 // Edit OFF time
	             else if(op==2)
              {
                OFHR:CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("OF HOUR(0 TO 23)");
                CmdLCD(GOTO_LINE2_POS0);
                Readnum(&off_hour);
                if(off_hour<0 || off_hour>23)
                {
                CmdLCD(CLEAR_LCD);
                StrLCD("Invalid Hour");
                goto OFHR;
                }
                OFMN:CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("OF MIN(0 TO 59)");
                CmdLCD(GOTO_LINE2_POS0);
                Readnum(&off_min);
                if(off_min<0 || off_min>59)
                {
                 CmdLCD(CLEAR_LCD);
                 StrLCD("Invalid MINS");
                 goto OFMN;
								}
					      else if(op==3)
               {
                return;
               }
						 }
				//to choose correct opt for wrong one
        else
        {
         CmdLCD(CLEAR_LCD);
         StrLCD("Sel cor opt");
         delay_s(1);
        }

       goto ONOFFMENU;
}
