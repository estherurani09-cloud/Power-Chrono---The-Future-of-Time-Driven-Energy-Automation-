# Power-Chrono---The-Future-of-Time-Driven-Energy-Automation-
Project Overview:
Power Chrono is a time-based automation system built on the LPC2148 ARM7 microcontroller. It
controls a device automatically using user-defined ON and OFF schedules. The system includes an
RTC, 16×2 LCD, keypad, and external interrupt menu, making it a complete embedded controller.

Objectives:
* Implement a real-time clock-based control system.
* Allow user input through a keypad.
* Display status and timings on a 16×2 LCD.
* Provide an interrupt-driven menu for editing settings.
* Automatically switch a device ON/OFF based on schedule.

Hardware Requirements:
* LPC2148 ARM7 Microcontroller
* 16×2 LCD Display
* 4×4 Matrix Keypad
* External Interrupt Switch (P0.1)
* ON/OFF Display Switch (P0.2)
* Device/Relay/LED Output (P0.4)
* 12 MHz Crystal and 3.3V Power Supply

Software Modules:
* power_chrono_main.c – Core automation logic
* power_chrono_Interrupt.c – Interrupt service routine & menu
* power_chrone.c – LCD, RTC, keypad, delay functions
* power.h – Function declarations
* power_defines.h – Macros and pin definitions
*  types.h – Data type definitions  

Working:
* Displays real-time time, date, and weekday on an LCD.
* Allows users to edit RTC time/date.
* Allows setting ON and OFF automation times.
* Automatically activates or deactivates a device based on schedule.
* Shows ON/OFF status with custom LCD icons.
* Provides interrupt-driven menu navigation.  

Setup & Usage:
* Open in Keil µVision / ARM IDE
* Compile & flash to LPC2148
* Connect LCD, keypad, switches
* Power the board and operate

Applications
* Home Automation
* Timer-Based Devices
* Mini Projects
* Industrial Time Control
