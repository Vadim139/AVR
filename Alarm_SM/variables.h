/*
 * variables.h
 *
 *  Created on: 9 sty 2018
 *      Author: Dawid Szromek
 */
#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "main.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------
// Real Time Clock
struct time
{
	uint8_t  second;
	uint16_t hm;
	uint8_t  minute;
	uint8_t  hour;
	uint16_t day;
	uint16_t month;
	uint16_t year;
};
extern volatile struct time t;
extern uint16_t  hms;
//---------------------------------------------------------------------------------------------------------------------------------------------------
// LCD
struct TCharacter;
extern volatile uint8_t  g_RefreshLCD;

//---------------------------------------------------------------------------------------------------------------------------------------------------
// Settings
extern volatile uint16_t g_BacklightTime_s; // Idle time after which LCD backlight will be switched off
extern volatile uint8_t  g_MenuTime_s; 	   // Idle time after which main view will be displayed again
extern volatile uint8_t  g_LogoutTime_s;    // Idle time after which user will be logged off
extern volatile uint8_t g_KeypadBeep;

// Runtime
// \/ niepotrzebne definy
#define INPUT_MODE_NORMAL   0
#define INPUT_MODE_PASSWORD 1

#define DISPLAY_CLOCK   1
#define DISPLAY_TEMP    0

typedef enum screenState {
	SS_Startup,
	SS_MainView_Idle,
	SS_MainView_Vigil,
	SS_MainView_Alarmed,
	SS_Panic_Confirm,
	SS_SilientPanic_Confirm,
	SS_Settings
} ScreenState;

extern volatile uint8_t  g_Halted;

extern volatile uint8_t  g_LoggedUserID;
extern volatile ScreenState  g_ScreenState;
extern volatile uint8_t  g_ShowClockTemp;
extern volatile uint8_t  g_InputEnabled;
extern volatile uint8_t  g_InputDisplay;
extern volatile uint8_t  g_InputMode;
extern volatile uint8_t  g_Sabotage;
extern volatile uint8_t  g_Vigil;
extern volatile uint8_t  g_Alarmed;
extern volatile uint8_t  g_SilientPanic;
extern volatile uint8_t  g_Panic;
extern volatile uint8_t  INT;
extern volatile uint16_t g_BacklightTimer_s;  // Time left to disable LCD backlight [seconds]
extern volatile uint8_t  g_MenuTimer_s;       // Time left to automatically go back to main view [seconds]
extern volatile uint8_t  g_LogoutTimer_s;	 // Time left to logout of the user [seconds]
extern volatile int16_t g_BuzzerCycles;
extern volatile int16_t g_BuzzerCntr;
extern volatile uint16_t g_BuzzerHalfPeriod;
//---------------------------------------------------------------------------------------------------------------------------------------------------


// Inputs
extern volatile uint8_t  g_KeypadBuffer[10];
extern volatile uint16_t g_SensorStates;
extern volatile uint16_t g_SensorZones;
extern volatile uint16_t g_SensorEnabled;
extern volatile uint8_t  g_newKey;


#endif /* VARIABLES_H_ */
