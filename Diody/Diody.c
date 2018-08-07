/*******************************************************************************/
/*					            	                                           */
/*                           www.microSENSE.pl                                 */
/*                                                                             */
/* Program demonsturjacy dzialanie diod oraz przyciskow.                       */
/* This program show how to use LEDs and switches.                             */
/* Polaczenia w pliku conf.h (Connections in conf.h file)                      */
/*******************************************************************************/
// wewnetrzny zegar 1MHz (internal oscillator 1MHz)
// LEDs
// PB0 - LD0
// PB1 - LD1
// PB2 - LD2
// PB3 - LD3
// PB4 - LD4
// PB5 - LD5
// PB6 - LD6
// PB7 - LD7
// Switches
// PD4 - SW4
// PD5 - SW5
// PD6 - SW6
// PD7 - SW7

#include <avr/io.h>
#include "conf.h"
#include <util/delay.h>


//delay 1s
void delay1s(void)
{
	uint8_t i;
	for(i=0;i<100;i++)
	{
		_delay_ms(10);
	}
}


int main(void)
{
Dir_LED = 0xFF;
Dir_SW  = 0x00;
Port_LED = 0x00;


while(1)
{

	if(~bit_is_clear(Port_SW, SW7) & ~bit_is_clear(Port_SW, SW6) & ~bit_is_clear(Port_SW, SW5) & ~bit_is_clear(Port_SW, SW4))
	{
	Port_LED &= 0x00;
	}

	if(bit_is_clear(Port_SW, SW7))
	{
	Port_LED |= 0xFF;
	delay1s();
		while(bit_is_clear(Port_SW, SW7))
		{
		Port_LED ^= 0xFF;
		delay1s();
		}
	}

	if(bit_is_clear(Port_SW, SW6))
	{
	Port_LED |= 0x55;
	delay1s();
		while(bit_is_clear(Port_SW, SW6))
		{
		Port_LED ^= 0xFF;
		delay1s();
		}
	}

	if(bit_is_clear(Port_SW, SW5))
	{
	Port_LED |= 0x33;
	delay1s();
		while(bit_is_clear(Port_SW, SW5))
		{
		Port_LED ^= 0xFF;
		delay1s();
		}
	}

	if(bit_is_clear(Port_SW, SW4))
	{
	Port_LED |= 0x0F;
	delay1s();
		while(bit_is_clear(Port_SW, SW4))
		{
		Port_LED ^= 0xFF;
		delay1s();
		}
	}
}

return 0;
}
