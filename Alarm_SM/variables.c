/*
 * variables.c
 *
 *  Created on: 9 sty 2018
 *      Author: Dawid Szromek
 */
#include "variables.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------
// Real Time Clock
volatile struct time t = {0,0,0,0,01,01,2018};
uint16_t hms = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------------
// LCD
struct TCharacter
{
	uint8_t	m_Character;
	uint8_t m_Index;
};
volatile uint8_t  g_RefreshLCD = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------------
// Settings
volatile uint16_t g_BacklightTime_s = 60; // Idle time after which LCD backlight will be switched off
volatile uint8_t  g_MenuTime_s = 20; 	   // Idle time after which main view will be displayed again
volatile uint8_t  g_LogoutTime_s = 30;    // Idle time after which user will be logged off
volatile uint8_t  g_KeypadBeep = 1;

// Runtime
volatile uint8_t  g_LoggedUserID = 0;
volatile ScreenState  g_ScreenState = SS_Startup;
volatile uint8_t  g_Halted = 1;
volatile uint8_t  g_ShowClockTemp = DISPLAY_CLOCK;
volatile uint8_t  g_InputEnabled = 0;
volatile uint8_t  g_InputDisplay = 0;
volatile uint8_t  g_InputMode = INPUT_MODE_NORMAL;
volatile uint8_t  g_Sabotage = 0;
volatile uint8_t  g_Vigil = 0;
volatile uint8_t  g_Alarmed = 0;
volatile uint8_t  g_SilientPanic = 0;
volatile uint8_t  g_Panic = 0;
volatile uint8_t  INT = 0;
volatile uint16_t	g_BacklightTimer_s = 60;  // Time left to disable LCD backlight [seconds]
volatile uint8_t 	g_MenuTimer_s = 20;       // Time left to automatically go back to main view [seconds]
volatile uint8_t 	g_LogoutTimer_s = 30;	 	  // Time left to logout of the user [seconds]
volatile int16_t 	g_BuzzerCycles = 0;
volatile int16_t 	g_BuzzerCntr = 0;
volatile uint16_t 	g_BuzzerHalfPeriod = 0;

// Inputs
volatile uint8_t g_KeypadBuffer[] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
volatile uint16_t g_SensorStates = 0b1010101010;
volatile uint16_t g_SensorZones = 0b1111110000;
volatile uint16_t g_SensorEnabled = 0b1111111111;
volatile uint8_t  g_newKey = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------------

