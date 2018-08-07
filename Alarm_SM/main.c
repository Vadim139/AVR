/*===========================================================================================================================
 * main.c
 *
 *  Created on: 09-02-2012
 *      Author: Krzysztof Szromek
 *      Poligon doswiadczalny w obs³udze uart i RTC (poprzez TWI).
 *      Kod do obs³ugi poszczególnych elementów podzielony na osobne biblioteki.
 *		- uart_lib
 *		- lcd_drv
 *		- keypad
 *
 *      Konfiguracja sprzêtowa:
 *      PD.0 	- RxD
 *      PD.1 	- TxD
 *      PC.0-3 	- ROW_1-4  	- 4 linie wierszy klawiatury matrycowej
 *      PD.2 	- KEYINT 	- przerwanie z klawiatury
 *      PB.0-3 	- LED 		- 4x Ledy
 *
 *===========================================================================================================================*/

//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <stdlib.h>
//#include <string.h>
//#include <util/delay.h>

//#include "my_defs.h"
//#include "sbit.h"
//#include "lcd_drv.h"
#include "main.h"
#include "keypad.h"
//#include "RC522.h"
#include "MFRC522.h"
#include "ds18b20.h"
//#include "uart.h"
//#include "I2C_slave.h"
//#include "main.h"
//#include "lcd_drv.h"
//#include "keypad.h"
#include "uart.h"
#include "variables.h"

void io_init	 (void);
void timer0_init (void);
void timer1_init (void);
void controlLoop (void);
void clearKeypadBuffer (void);
void updateKeypadBuffer (void);
int32_t getKeypadCommand (uint8_t onlyCommand);
void displayMainView (void);
void displaySensors (void);
void beep(uint16_t, int16_t);
void keyBeep();
uint8_t STM32_disarmWithUserPwd(int32_t pwd);
uint8_t STM32_armWithUserPwd(int32_t pwd);
uint8_t STM32_loginWithUserPwd (int32_t pwd);

char buffer[3];
uint8_t ID[6] = {0,0,0,0,0,0};
//extern volatile unsigned char UART_RxHead;
//extern volatile unsigned char UART_RxTail;
////////////////////////
uint8_t Halt = 0;
uint16_t Time;
float Temp_out;
float Temp_in;
uint8_t Alarm_flag = 0;
//////////////////////
/* W tablicy zapisywane bêd¹ dane odczytane z uk³adu ds18b20 */
unsigned char ds18b20_pad[9];

#define block	0
unsigned char seck[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
volatile char rec = 0;
//volatile char INT = 0;
volatile char buf[20];
volatile uint8_t *blad = 0;
unsigned char roz = 0;
unsigned char status, str[20];
int main(void) {
	int i = 0;

//	LED_DDR_1 = 1;
//	LED_DDR_2 = 1;
//	LED_DDR_3 = 1;
//	LED_DDR_4 = 1;
//	LED_DDR_5 = 1;
//	LED_DDR_6 = 1;
//	LED_DDR_7 = 1;
//	LED_DDR_2 = 1;

	SB_RW_DDR = 0;
	SB_RW = 1;

//	LED_1 = 1;
//	LED_2 = 1;
//	LED_3 = 1;
//	LED_4 = 1;
//	LED_5 = 1;
//	LED_6 = 1;
//	LED_7 = 1;


	io_init();
	timer0_init();
	timer1_init();

	lcd_init();
	LCD_BL = 0;
	keypad_init();


	lcd_define_icon(ICON_CLOCK,ICON_CLOCK_VAR[0]); // clock
	lcd_define_icon(ICON_TEMP,ICON_TEMP_VAR[0]); // temp
	lcd_define_icon(ICON_DEGREE,ICON_DEGREE_VAR[0]); // degree
	lcd_define_icon(ICON_SENSOR_DETECTED,ICON_SENSOR_DETECTED_VAR[0]); // sensor detected
	lcd_define_icon(ICON_SENSOR_CLEAR,ICON_SENSOR_CLEAR_VAR[0]); // sensor clear
	lcd_define_icon(ICON_EMPTY_SHIELD,ICON_EMPTY_SHIELD_VAR[0]); // empty shield
	lcd_define_icon(ICON_SHIELD,ICON_SHIELD_VAR[0]); // shield
	lcd_define_icon(ICON_ALARM,ICON_ALARM_VAR[0]); // alarm

	RS485_Init();

	EICRA = ((0 << ISC01) & (0 << ISC11)); // INT0 executed on falling edge
	EIMSK |= (1 << INT0) | (1 << INT1) ;
//		EICRA = ((1 << ISC01)); // INT1 executed on falling edge
//		EIMSK |= (1 << INT0);
//	lcd_init();
//
//	lcd_blank();
//	lcd_xy(0,0);
//	lcd_puts("STM32");

//	SPIInit();
//	spi_master_init();
//	RC522_Init();
	MFRC522_Init();
	_delay_ms(500);

//	KEYINT = 0;			// set key interrupt pins as input with pull-up
//	KEYINT_DDR = 0;
//
//	ROW_1 = 	0; 		// set row pins as input with pull-up dir == ROWS
//	ROW_DDR_1 =  1;		// 0 when dir == ROWS
//	ROW_2 = 	0;		// 1 when dir == ROWS
//	ROW_DDR_2 =  1;
//	ROW_3 = 	0;
//	ROW_DDR_3 =  1;
//	ROW_4 = 	0;
//	ROW_DDR_4 =  1;
//
//
//	COL_1 = 	0; 		// set column pins as output low when dir == ROWS
//	COL_DDR_1 =  1;		// 1 when dir == ROWS
//	COL_2 = 	0;		// 0 when dir == ROWS
//	COL_DDR_2 =  1;
//	COL_3 = 	0;
//	COL_DDR_3 =  1;




	zmroz(2,1);


		status = MFRC522_Request(PICC_REQIDL,str);
		if(status==MI_OK)
		{
//			lcd_blank();
			lcd_xy(0,0);
			lcd_puts("                ");
			lcd_xy(0,0);
			status = MFRC522_Anticoll(str);
			RS_Check(U_RFID,str,1);
// 			RS_TransferMulti(250,str,5);
			for(unsigned char j=0;j<5;j++)
			{
				lcd_hex(str[j]);
				lcd_putchar(' ');
			}

		}
//		_delay_ms(1000);


		lcd_blank();
		lcd_puts("System started");
		_delay_ms(500);
		sei();
		uart_puts("System started\n\r");

		//wdt_enable(WDTO_2S);
		//wdt_reset();

		while(1){
			if(g_RefreshLCD)
			{
				controlLoop();
				g_RefreshLCD = 0;
			}
			_delay_ms(10);
		}

	return 0;
}

void controlLoop (void) {
	static ScreenState lastScreenState = SS_Startup;

	uint8_t refresh = 0;
	int32_t inputCommand = 0;

	if (lastScreenState != g_ScreenState) {
		refresh = 1;
		lcd_blank();
		lcd_xy(0,1);
		lastScreenState = g_ScreenState;
	}

	updateKeypadBuffer();

	switch (g_ScreenState) {
	case SS_Startup:
		g_InputEnabled = 0;

		uart_puts("ControlLoop_Startup\n\r");
		if (refresh == 1) {
			lcd_puts(" INITIALISATION ");
		}
//		if (!g_Halted) {
		if (t.second > 5) {
			g_ScreenState = SS_MainView_Idle;
		}
		break;
	case SS_MainView_Idle:
		g_InputEnabled = 1;
		g_InputDisplay = 0;

		uart_puts("ControlLoop_MainView_Idle\n\r");
		if (refresh == 1) {
			clearKeypadBuffer();
		}

		displayMainView();

		if ((inputCommand = getKeypadCommand(KEYPAD_COMMAND_HASH)) >= 0) {
			uart_puts("KEYPAD_COMMAND_HASH:");
			UART_sendi(inputCommand);
			uart_puts("\n\r");
			clearKeypadBuffer();
			if(inputCommand==8) { // panic alarm trigger
				g_ScreenState = SS_Panic_Confirm;
			} else if (inputCommand==0) { // both zones arming
				g_ScreenState = SS_MainView_Vigil;
				g_Vigil=3;
			} else if (inputCommand==1) { // zone 1 arming
				g_ScreenState = SS_MainView_Vigil;
				g_Vigil=1;
			} else if (inputCommand==2) { // zone 2 arming
				g_ScreenState = SS_MainView_Vigil;
				g_Vigil=2;
			} else {
				g_Vigil = STM32_armWithUserPwd(inputCommand);
				if(g_Vigil) {
					g_ScreenState = SS_MainView_Vigil;
				}
			}
		} else if ((inputCommand = getKeypadCommand(KEYPAD_COMMAND_STAR)) >= 0) {
			uart_puts("KEYPAD_COMMAND_STAR:");
			UART_sendi(inputCommand);
			uart_puts("\n\r");
			clearKeypadBuffer();
			if(inputCommand==0) { // user logout
				g_LoggedUserID=0;
			} else {
				g_LoggedUserID = STM32_loginWithUserPwd(inputCommand);
				if(g_LoggedUserID) {
					g_ScreenState = SS_Settings;
				}
			}
		} else if(g_newKey && keypad_pressed == KEYSTAR) {
			g_ShowClockTemp ^= 1;
		}
		break;
	case SS_MainView_Vigil:
		g_InputEnabled = 1;
		g_InputDisplay = 0;

		uart_puts("ControlLoop_MainView_Vigil\n\r");
		if (refresh == 1) {
			clearKeypadBuffer();
		}

		displayMainView();

		if ((inputCommand = getKeypadCommand(KEYPAD_COMMAND_HASH)) >= 0) {
			uart_puts("KEYPAD_COMMAND_HASH:");
			UART_sendi(inputCommand);
			uart_puts("\n\r");
			clearKeypadBuffer();
			if(inputCommand==8) { // panic alarm trigger
				g_ScreenState = SS_Panic_Confirm;
			} else if (inputCommand==0) { // both zones arming
				g_ScreenState = SS_MainView_Vigil;
				g_Vigil|=3;
			} else if (inputCommand==1) { // zone 1 arming
				g_ScreenState = SS_MainView_Vigil;
				g_Vigil|=1;
			} else if (inputCommand==2) { // zone 2 arming
				g_ScreenState = SS_MainView_Vigil;
				g_Vigil|=2;
			} else {
				g_Vigil = STM32_disarmWithUserPwd(inputCommand);
				if(g_Vigil)
					g_ScreenState = SS_MainView_Vigil;
				 else
					g_ScreenState = SS_MainView_Idle;
			}
		} else if(g_newKey && keypad_pressed == KEYSTAR) {
			g_ShowClockTemp ^= 1;
		}
		break;
	case SS_MainView_Alarmed:
		g_InputEnabled = 1;
		g_InputDisplay = 0;

		uart_puts("ControlLoop_MainView_Alarmed\n\r");
		if (refresh == 1) {
			beep(2500,-1);
			clearKeypadBuffer();
		}

		displayMainView();

		if ((inputCommand = getKeypadCommand(KEYPAD_COMMAND_HASH)) >= 0) {
			uart_puts("KEYPAD_COMMAND_HASH:");
			UART_sendi(inputCommand);
			uart_puts("\n\r");
			clearKeypadBuffer();
			if ((g_Vigil = STM32_disarmWithUserPwd(inputCommand))) {
				g_Alarmed &= g_Vigil;
				if (g_Alarmed) {
					beep(2500, 0);
					g_ScreenState = SS_MainView_Vigil;
				} else {
					beep(2500, 0);
					g_Panic = 0;
					g_ScreenState = SS_MainView_Idle;
				}
			}
		} else if (g_newKey && keypad_pressed == KEYSTAR) {
			g_ShowClockTemp ^= 1;
		}

		if (keypad_pressed == KEY0) {
			g_ScreenState = SS_MainView_Idle;
			g_Panic = 0;
			g_Alarmed = 0;
			g_Vigil = 0;
		}

		break;
	case SS_Panic_Confirm:
		g_InputEnabled = 1;
		g_InputDisplay = 0;

		uart_puts("ControlLoop_Panic_Confirm\n\r");
		if (refresh == 1) {
			clearKeypadBuffer();
		}

		displayMainView();
		lcd_xy(0,1);
		lcd_puts("* No      Yes #");

		if (g_newKey && keypad_pressed == KEYSTAR) {
			if(g_Vigil)
				g_ScreenState = SS_MainView_Vigil;
			else
				g_ScreenState = SS_MainView_Idle;

		} else if (g_newKey && keypad_pressed == KEYHASH) {
			g_ScreenState = SS_MainView_Alarmed;
			g_Panic = 3;
		}
		break;
	default:
		uart_puts("ControlLoop_default\n\r");
		break;
	}

	g_newKey = 0;
}

void io_init (void) {
//	LED_DDR_1 = 1;
//	LED_DDR_2 = 1;
//	LED_DDR_3 = 1;

	BUZZER_DDR = 1;
//
//	LED_1 = 0;
//	LED_2 = 0;
//	LED_3 = 0;

	BUZZER = 0;

	SB_RW_DDR = 0;
	SB_RW = 1;
}

void timer0_init (void) {
	// With 16MHz clock, prescaller 1/8 and OCR0A=50 results with 40kHz interrupt
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS01) | (0 << CS00);
	OCR0A = 50;
	TIMSK0 = (1 << OCIE0A);
}

void timer1_init (void) {
	TCCR1A = 0;
	// With 16MHz clock, prescaller 1/1024 and OCR1A=15625 results with 1Hz interrupt
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC with 1/1024 prescaller
	OCR1A = 15625;
//	// With 16MHz clock, prescaller 1/256 and OCR1A=31250 results with 2Hz interrupt
//	TCCR1B = (1 << WGM12) | (1 << CS12) | (0 << CS10); // CTC with 1/256 prescaller
//	OCR1A = 31250;
	TIMSK1 = (1 << OCIE1A);
}

// Interrupt responsible for sabotage input
ISR(INT1_vect)
{
	g_Sabotage = ~SB_RW_R;
//	LED_1 = 1;
}

// Interrupt responsible for keypanel input
ISR(PCINT2_vect) {

}

// Interrupt responsible for buzzer generating
ISR (TIMER0_COMPA_vect) {
	if (g_BuzzerCycles != 0) {
		if (g_BuzzerCntr == 0) {
			if (BUZZER_R == 0)
				BUZZER = 1;
			else {
				BUZZER = 0;
				if (g_BuzzerCycles > 0) {
					--g_BuzzerCycles;
				}
			}
			g_BuzzerCntr = g_BuzzerHalfPeriod;
		} else
			--g_BuzzerCntr;
	} else
		g_BuzzerCntr = 0;
}

// Interrupt responsible for timed tasks scheluding
ISR (TIMER1_COMPA_vect)
{
//	LED_2 = ~LED_2;

	// Temporarily, update clock
	if (++t.second==60) { // RTC
		t.second=0;

		if (++t.minute==60)  {
			t.minute=0;

			if (++t.hour==24) {
				t.hour=0;

				if (++t.day==32) {
					t.month++;
					t.day=1;
				} else if (t.day==31) {
					if ((t.month==4) || (t.month==6) || (t.month==9) || (t.month==11)) {
						t.month++;
						t.day=1;
					}
				} else if (t.day==30) {
					if(t.month==2) {
						t.month++;
						t.day=1;
					}
				} else if (t.day==29)  {
					if((t.month==2)) {// && (not_leap())) {
						t.month++;
						t.day=1;
					}
				} if (t.month==13) {
					t.month=1;
					t.year++;
				}
			}
		}
	}

	// Decrement timers
	if(g_BacklightTimer_s) {
		LCD_BL = 0;
		--g_BacklightTimer_s;
	} else
		LCD_BL = 1;
	if(g_MenuTimer_s) --g_MenuTimer_s;
	if(g_LogoutTimer_s) --g_LogoutTimer_s;

	g_RefreshLCD = 1;
}

void clearKeypadBuffer (void){
	for (uint8_t var = 0; var < 10; ++var) {
		g_KeypadBuffer[var] = 0;
	}
}

void updateKeypadBuffer(void) {
	if (g_newKey && keypad_pressed) {
		for (uint8_t var = 0; var < 10; ++var) {
			if(g_KeypadBuffer[var] == 0) {
				g_KeypadBuffer[var] = keypad_pressed;
				return;
			}
		}
		beep(300,1000);
		clearKeypadBuffer();
	}
}

int32_t getKeypadCommand (uint8_t whatKind){
	int32_t retVal = 0;
	uint8_t keypadChar = 0;
	int8_t var = 0;
	int8_t max = 0;

	for (var = 0; var < 10; ++var) {
		keypadChar = g_KeypadBuffer[var];
		if(keypadChar == 0) {
			if(whatKind==KEYPAD_ALL_INPUT)
				break;
			else
				return -1;
		} else if(keypadChar == KEYSTAR) {
			if(whatKind==KEYPAD_ALL_INPUT || whatKind==KEYPAD_COMMAND_ALL || whatKind==KEYPAD_COMMAND_STAR)
				break;
			else
				return -1;
		} else if(keypadChar == KEYHASH) {
			if(whatKind==KEYPAD_ALL_INPUT || whatKind==KEYPAD_COMMAND_ALL || whatKind==KEYPAD_COMMAND_HASH)
				break;
			else
				return -1;
		}
	}

	if(var==0 || var==10)
		return -1;

	max = var;

	for (var=0; var < max; ++var) {
		keypadChar = g_KeypadBuffer[var];
		if(keypadChar==11)
			keypadChar=0;
		retVal = 10*retVal + keypadChar;
	}

	return retVal;
}

void displayMainView(void) {

	if (g_ShowClockTemp == DISPLAY_CLOCK) {
		lcd_draw_icon(ICON_CLOCK, 5, 0);
		lcd_xy(6, 0);
//		lcd_putchar(48+t.hour/10);
//		lcd_putchar(48+t.hour%10);
//		lcd_putchar(':');
		lcd_putchar(48 + t.minute / 10);
		lcd_putchar(48 + t.minute % 10);
		lcd_putchar(':');
		lcd_putchar(48 + t.second / 10);
		lcd_putchar(48 + t.second % 10);
	} else if (g_ShowClockTemp == DISPLAY_TEMP) {
		lcd_draw_icon(ICON_TEMP, 10, 0);
		lcd_xy(5, 0);
		lcd_puts("-21.7");
		lcd_draw_icon(ICON_DEGREE, 10, 0);
	}

	if (!((g_Alarmed & 1) || (g_Panic & 1))) {
		if (g_Vigil & 1) {
			lcd_draw_icon(ICON_SHIELD, 1, 0);
		} else {
			lcd_xy(0, 0);
			lcd_puts("  ");
		}
	} else {
		if ((g_Vigil & 1) && t.second % 2) {
			lcd_draw_icon(ICON_SHIELD, 1, 0);
		} else {
			lcd_xy(1, 0);
			lcd_putchar(' ');
		}
		if (t.second % 2) {
			lcd_draw_icon(ICON_ALARM, 0, 0);
		} else {
			lcd_xy(0, 0);
			lcd_putchar(' ');
		}
	}

	if (!((g_Alarmed & 2) || (g_Panic & 2))) {
		if (g_Vigil & 2) {
			lcd_draw_icon(ICON_SHIELD, 14, 0);
		} else {
			lcd_xy(14, 0);
			lcd_puts(" ");
		}
	} else {
		if ((g_Vigil & 2) && t.second % 2) {
			lcd_draw_icon(ICON_SHIELD, 14, 0);
		} else {
			lcd_xy(14, 0);
			lcd_putchar(' ');
		}
		if (t.second % 2) {
			lcd_draw_icon(ICON_ALARM, 15, 0);
		} else {
			lcd_xy(15, 0);
			lcd_putchar(' ');
		}
	}

	displaySensors();
}

void displaySensors(void) {
	uint8_t idx = 0;
	uint8_t lcd_x = 0;
	uint8_t sensorCountPerZone[2] = { 0, 0 };

	lcd_xy(0,1);
	lcd_puts("                ");

	for (idx = 0; idx < 10; ++idx) {
		if (g_SensorEnabled & (1 << idx)) {
			++sensorCountPerZone[g_SensorZones & (1 << idx) ? 0 : 1];
		}
	}

	for (idx = 0; idx < 10; ++idx) {
		if (g_SensorEnabled & g_SensorZones & (1 << idx)) {
			lcd_draw_icon((g_SensorStates & (1 << idx) ? ICON_SENSOR_DETECTED : ICON_SENSOR_CLEAR), lcd_x++, 1);
		}
	}

	lcd_x = 16 - sensorCountPerZone[1];
	for (idx = 0; idx < 10; ++idx) {
		if (g_SensorEnabled & ~g_SensorZones & (1 << idx)) {
			lcd_draw_icon((g_SensorStates & (1 << idx) ? ICON_SENSOR_DETECTED : ICON_SENSOR_CLEAR), lcd_x++, 1);
		}
	}
}

void keyBeep() {
	if (g_KeypadBeep != 0 && g_BuzzerCycles >= 0)
		beep(2200, 1000);
}

void beep(uint16_t freq, int16_t time_ms) {
	if (time_ms < 0)
		g_BuzzerCycles = -1;
	else
		g_BuzzerCycles = time_ms * freq / 1000;

	g_BuzzerHalfPeriod = 20000 / freq;
}

uint8_t STM32_disarmWithUserPwd(int32_t pwd) {
	// dummy
	return 0;
}

uint8_t STM32_armWithUserPwd (int32_t pwd){
	// dummy
	return 0;
}

uint8_t STM32_loginWithUserPwd (int32_t pwd){
	// dummy
	return 0;
}


ISR(INT0_vect) {
	uint8_t last_keypad_pressed;
	g_RefreshLCD = 1;
//	EIMSK &= (0 << INT0);
//	PCICR &= ~(1 << PCIE2);
	last_keypad_pressed = keypad_pressed;
	keypad_poll();

	if (g_InputEnabled && keypad_pressed != last_keypad_pressed) {
		switch (keypad_pressed) {
		case KEY1:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY2:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY3:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY4:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY5:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY6:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY7:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY8:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY9:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEYSTAR:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		case KEY0:
			keyBeep();
			g_Sabotage = 0; //TODO remove
//			LED_3 = ~LED_3;
			break;
		case KEYHASH:
			keyBeep();
//			LED_3 = ~LED_3;
			break;
		default:
			break;
		}
		g_newKey = 1;
	}

	_delay_ms(50);
	g_BacklightTimer_s = g_BacklightTime_s;
//	PCIFR |= (1 << PCIF2);
//	PCICR |= (1 << PCIE2);

//	EIFR = 0;
//	EIMSK |= (1 << INT0);
}

//ISR(INT1_vect)
//{
//	PORTD ^=(1<<5);
//	_delay_ms(100);
//}


//ISR(TIMER0_OVF_vect)
//{
//
//}
//
//ISR(TIMER1_COMPA_vect) {
//	DS18B20_showtemp(7,1,2,&blad,1);
//	DS18B20_ConvertT(&blad,1);
////		if(!RC522_Check((uint8_t*)ID)){
////			if(ID[0] != 0)
////				RS_TransferMulti(250,ID,5);
////		}
////	PORTD ^=(1<<5);
////	PORTA ^=(1<<1);
////	uart_puts("No input!\n\r");
//}

