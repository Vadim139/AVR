#ifndef _main_h_
#define _main_h_

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "my_defs.h"

//#define XTAL	16e6
//#define F_CPU   XTAL

#include <avr/io.h>
#include <util/delay.h>

// uart
#define	UART_RxD		SBIT( PORTD, 0 )
#define	UART_RxD_R		SBIT( PIND, 0 )
#define	UART_RxD_DDR	SBIT( DDRD, 0 )

#define	UART_TxD		SBIT( PORTD, 1 )
#define	UART_TxD_R		SBIT( PIND, 1 )
#define	UART_TxD_DDR	SBIT( DDRD, 1 )

#define	MAX_RW			SBIT( PORTD, 4 )
#define	MAX_RW_R		SBIT( PIND, 4 )
#define	MAX_RW_DDR		SBIT( DDRD, 4 )

// RFID
#define	RFID_SCK		SBIT( PORTB, 7 )
#define	RFID_SCK_R		SBIT( PINB, 7 )
#define	RFID_SCK_DDR	SBIT( DDRB, 7 )

#define	RFID_MISO		SBIT( PORTB, 6 )
#define	RFID_MISO_R		SBIT( PINB, 6 )
#define	RFID_MISO_DDR	SBIT( DDRB, 6 )

#define	RFID_MOSI		SBIT( PORTB, 5 )
#define	RFID_MOSI_R		SBIT( PINB, 5 )
#define	RFID_MOSI_DDR	SBIT( DDRB, 5 )

#define	RFID_CS			SBIT( PORTB, 4 )
#define	RFID_CS_R		SBIT( PINB, 4 )
#define	RFID_CS_DDR		SBIT( DDRB, 4 )

// DS1820
#define	DS_TEMP			SBIT( PORTD, 7 )
#define	DS_TEMP_R		SBIT( PIND, 7 )
#define	DS_TEMP_DDR		SBIT( DDRD, 7 )

//
// klawiatura
#define	ROW_1		SBIT( PORTC, 0 )
#define	ROW_R_1		SBIT( PINC, 0 )
#define	ROW_DDR_1	SBIT( DDRC, 0 )

#define	ROW_2		SBIT( PORTC, 1 )
#define	ROW_R_2		SBIT( PINC, 1 )
#define	ROW_DDR_2	SBIT( DDRC, 1 )

#define	ROW_3		SBIT( PORTB, 3 )
#define	ROW_R_3		SBIT( PINB, 3 )
#define	ROW_DDR_3	SBIT( DDRB, 3 )

#define	ROW_4		SBIT( PORTB, 2 )
#define	ROW_R_4		SBIT( PINB, 2 )
#define	ROW_DDR_4	SBIT( DDRB, 2 )

#define	COL_1		SBIT( PORTB, 1 )
#define	COL_R_1		SBIT( PINB, 1 )
#define	COL_DDR_1	SBIT( DDRB, 1 )

#define	COL_2		SBIT( PORTB, 0 )
#define	COL_R_2		SBIT( PINB, 0 )
#define	COL_DDR_2	SBIT( DDRB, 0 )

#define	COL_3		SBIT( PORTC, 6 )
#define	COL_R_3		SBIT( PINC, 6 )
#define	COL_DDR_3	SBIT( DDRC, 6 )

//#define	COL_4		SBIT( PORTC, 7 )
//#define	COL_R_4		SBIT( PINC, 7 )
//#define	COL_DDR_4	SBIT( DDRC, 7 )

#define	KEYINT		SBIT( PORTD, 2 )
#define	KEYINT_R	SBIT( PIND, 2 )
#define	KEYINT_DDR 	SBIT( DDRD, 2 )

// sabota¿
#define	SB_RW		SBIT( PORTD, 3 )
#define	SB_RW_R		SBIT( PIND, 3 )
#define	SB_RW_DDR	SBIT( DDRD, 3 )

// ledy
//#define	LED_1		SBIT( PORTD, 5 )
//#define	LED_DDR_1	SBIT( DDRD, 5 )

// buzzer
#define	BUZZER		SBIT( PORTB, 5 )
#define	BUZZER_R	SBIT( PINB, 5 )
#define	BUZZER_DDR	SBIT( DDRB, 5 )
//#define	LED_2		SBIT( PORTD, 6 )
//#define	LED_DDR_2	SBIT( DDRD, 6 )

// ledy
//#define	LED_3		SBIT( PORTD, 4 )
//#define	LED_DDR_3	SBIT( DDRD, 4 )
//
//#define	LED_4		SBIT( PORTA, 7 )
//#define	LED_DDR_4	SBIT( DDRA, 7 )
//
//// ledy
//#define	LED_5		SBIT( PORTB, 2 )
//#define	LED_DDR_5	SBIT( DDRB, 2 )
//
//#define	LED_6		SBIT( PORTB, 3 )
//#define	LED_DDR_6	SBIT( DDRB, 3 )
//
//// ledy
//#define	LED_7		SBIT( PORTB, 4 )
//#define	LED_DDR_7	SBIT( DDRB, 4 )

//#define	LED_5		SBIT( PORTD, 5 )
//#define	LED_DDR_5	SBIT( DDRD, 5 )

// lcd
#define	LCD_D4		SBIT( PORTA, 5 )
#define	LCD_DDR_D4	SBIT( DDRA, 5 )

#define	LCD_D5		SBIT( PORTA, 4 )
#define	LCD_DDR_D5	SBIT( DDRA, 4 )

#define	LCD_D6		SBIT( PORTA, 3 )
#define	LCD_DDR_D6	SBIT( DDRA, 3 )

#define	LCD_D7		SBIT( PORTA, 2 )
#define	LCD_DDR_D7	SBIT( DDRA, 2 )

#define	LCD_RS		SBIT( PORTA, 7 )
#define	LCD_DDR_RS	SBIT( DDRA, 7 )

#define	LCD_E0		SBIT( PORTA, 6 )
#define	LCD_DDR_E0	SBIT( DDRA, 6 )

#define	LCD_BL		SBIT( PORTA, 1 )
#define	LCD_DDR_BL	SBIT( DDRA, 1 )

#endif


