#ifndef _main_h_
#define _main_h_

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "my_defs.h"

#include <avr/io.h>
#include <util/delay.h>
//

#define	SW_1		SBIT( PORTB, 3 )
#define	SW_DDR_1	SBIT( DDRB, 3 )
#define	SWpin_1		SBIT( PINB, 3 )

#define	SW_2		SBIT( PORTB, 2 )
#define	SW_DDR_2	SBIT( DDRB, 2 )
#define	SWpin_2		SBIT( PINB, 2 )

#define	ADC_1		SBIT( PORTB, 4 )
#define	ADC_DDR_1	SBIT( DDRB, 4 )
#define	ADCin_1		SBIT( PINB, 4 )

#define	LED_1		SBIT( PORTB, 0 )
#define	LED_DDR_1	SBIT( DDRB, 0 )

#define	LED_2		SBIT( PORTB, 1 )
#define	LED_DDR_2	SBIT( DDRB, 1 ) //(czer)



//// klawiatura
//#define	ROW_1		SBIT( PORTC, 0 )
//#define	ROW_R_1		SBIT( PINC, 0 )
//#define	ROW_DDR_1	SBIT( DDRC, 0 )
//
//#define	ROW_2		SBIT( PORTC, 1 )
//#define	ROW_R_2		SBIT( PINC, 1 )
//#define	ROW_DDR_2	SBIT( DDRC, 1 )
//
//#define	ROW_3		SBIT( PORTC, 2 )
//#define	ROW_R_3		SBIT( PINC, 2 )
//#define	ROW_DDR_3	SBIT( DDRC, 2 )
//
//#define	ROW_4		SBIT( PORTC, 3 )
//#define	ROW_R_4		SBIT( PINC, 3 )
//#define	ROW_DDR_4	SBIT( DDRC, 3 )
//
//#define	COL_1		SBIT( PORTC, 4 )
//#define	COL_R_1		SBIT( PINC, 4 )
//#define	COL_DDR_1	SBIT( DDRC, 4 )
//
//#define	COL_2		SBIT( PORTC, 5 )
//#define	COL_R_2		SBIT( PINC, 5 )
//#define	COL_DDR_2	SBIT( DDRC, 5 )
//
//#define	COL_3		SBIT( PORTC, 6 )
//#define	COL_R_3		SBIT( PINC, 6 )
//#define	COL_DDR_3	SBIT( DDRC, 6 )
//
//#define	COL_4		SBIT( PORTC, 7 )
//#define	COL_R_4		SBIT( PINC, 7 )
//#define	COL_DDR_4	SBIT( DDRC, 7 )
//
//#define	KEYINT		SBIT( PORTD, 2 )
//#define	KEYINT_R	SBIT( PIND, 2 )
//#define	KEYINT_DDR 	SBIT( DDRD, 2 )

// ledy
//#define	LED_1		SBIT( PORTD, 0 )
//#define	LED_DDR_1	SBIT( DDRD, 0 )
//
//#define	LED_2		SBIT( PORTD, 1 )
//#define	LED_DDR_2	SBIT( DDRD, 1 )

//#define	EN_3		SBIT( PORTD, 2 )
//#define	EN_DDR_3	SBIT( DDRD, 2 )
//#define	ENpin_3		SBIT( PIND, 2 )
//
//#define	EN_4		SBIT( PORTD, 3 )
//#define	EN_DDR_4	SBIT( DDRD, 3 )
//#define	ENpin_4		SBIT( PIND, 3 )
//
//#define	EN_5		SBIT( PORTD, 4 )
//#define	EN_DDR_5	SBIT( DDRD, 4 )
//#define	ENpin_5		SBIT( PIND, 4 )

//#define	LED_5		SBIT( PORTD, 4 )
//#define	LED_DDR_5	SBIT( DDRD, 4 )
//
//#define	LED_6		SBIT( PORTD, 5 )
//#define	LED_DDR_6	SBIT( DDRD, 5 )
//
//#define	LED_7		SBIT( PORTD, 6 )
//#define	LED_DDR_7	SBIT( DDRD, 6 )
//
//#define	LED_8		SBIT( PORTD, 7 )
//#define	LED_DDR_8	SBIT( DDRD, 7 )
//
//// lcd
//#define	LCD_D4		SBIT( PORTB, 2 )
//#define	LCD_DDR_D4	SBIT( DDRB, 2 )
//
//#define	LCD_D5		SBIT( PORTB, 3 )
//#define	LCD_DDR_D5	SBIT( DDRB, 3 )
//
//#define	LCD_D6		SBIT( PORTB, 4 )
//#define	LCD_DDR_D6	SBIT( DDRB, 4 )
//
//#define	LCD_D7		SBIT( PORTB, 5 )
//#define	LCD_DDR_D7	SBIT( DDRB, 5 )
//
//#define	LCD_RS		SBIT( PORTB, 0 )
//#define	LCD_DDR_RS	SBIT( DDRB, 0 )
//
//#define	LCD_E0		SBIT( PORTB, 1 )
//#define	LCD_DDR_E0	SBIT( DDRB, 1 )

//// uart
//#define	UART_RxD		SBIT( PORTD, 1 )
//#define	UART_RxD_R		SBIT( PIND, 1 )
//#define	UART_RxD_DDR	SBIT( DDRD, 1 )
//
//#define	UART_TxD		SBIT( PORTD, 0 )
//#define	UART_TxD_R		SBIT( PIND, 0 )
//#define	UART_TxD_DDR	SBIT( DDRD, 0 )

//// twi
//#define	TWI_SDA			SBIT( PORTC, 4 )
//#define	TWI_SDA_R		SBIT( PINC, 4 )
//#define	TWI_SDA_DDR		SBIT( DDRC, 4 )
//
//#define	TWI_SCK			SBIT( PORTC, 5 )
//#define	TWI_SCK_R		SBIT( PINC, 5 )
//#define	TWI_SCK_DDR		SBIT( DDRC, 5 )

// Wiatraki
//#define	MOT_1		SBIT( PORTC, 0 )
//#define	MOT_DDR_1	SBIT( DDRC, 0 )
//
//#define	MOT_2		SBIT( PORTC, 1 )
//#define	MOT_DDR_2	SBIT( DDRC, 1 )
//
//#define	MOT_3		SBIT( PORTC, 2 )
//#define	MOT_DDR_3	SBIT( DDRC, 2 )
//
//#define	MOT_4		SBIT( PORTC, 3 )
//#define	MOT_DDR_4	SBIT( DDRC, 3 )
//
//#define	MOT_5		SBIT( PORTC, 4 )
//#define	MOT_DDR_5	SBIT( DDRC, 4 )
//
//#define	MOT_6		SBIT( PORTC, 5 )
//#define	MOT_DDR_6	SBIT( DDRC, 5 )
//
//#define	MOT_7		SBIT( PORTD, 5 )
//#define	MOT_DDR_7	SBIT( DDRD, 5 )
//
//#define	MOT_8		SBIT( PORTD, 6 )
//#define	MOT_DDR_8	SBIT( DDRD, 6 )

#endif


