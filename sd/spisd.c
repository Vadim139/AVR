#include <avr/io.h>
#include <util/delay.h>
#include "integer.h"

void init_spi(void)
{

SPCR = 0x50; //setup SPI: Master mode, MSB first, SCK phase low, SCK idle low
SPSR = 0x00;
//PORTB = 0xA4;
//DDRB  |= 0xA4; //MISO line i/p, rest o/p
PORTB |= (1 << 2);
DDRB |= (1 << 2);
//DDRB=(1<<2)|(1<<1); //Port-Direction Setup

}

BYTE rcv_spi(void)
{
BYTE data;

SPDR = 0xff;
while(!(SPSR & (1<<SPIF)));
data = SPDR;

return data;
}

unsigned char xmit_spi (BYTE data)
{
// Start transmission
SPDR = data;

// Wait for transmission complete
while(!(SPSR & (1<<SPIF)));
data = SPDR;

return(data);
}



void dly_100us (void)
{

_delay_us(100);
}
