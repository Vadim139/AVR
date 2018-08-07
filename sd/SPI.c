/*
 * SPI.h
 *
 *  Created on: 04-02-2013
 *      Author: Dawid
 */
//#define SPI_H_
#ifndef SPI_H_
#define SPI_H_
#define byte unsigned char
byte n=0;
byte s1,s2;
byte r,g,b;

#endif /* SPI_H_ */

#include <avr/io.h>
#include "SPI.h"
#include <util/delay.h>

//#define WriteSpiData(byte data) sendData(byte data)
//#define WriteSpiCommand(byte command) sendCMD(byte data)
void InitSPI(void)
{
	_delay_ms(100);
//DDRB = (1<<PB4)|(1<<PB5) | (1<<PB7);	 // Set MOSI , SCK , and SS output
//PORTB |= (1 << 4);
//SPCR = ( (1<<SPE)|(1<<MSTR) | (0<<SPR1) |(0<<SPR0));	// Enable SPI, Master, set clock rate
//SPSR &= ~(1<<SPI2X);
//DDRB |= (1 << 3);
//PORTB |= (1 << 3);
SPIDDR=(1<<SDA)|(1<<CLK)|(1<<CS)|(1<<RESET); //Port-Direction Setup
SPCR = 0x00;
//SPCR = ( (0<<SPR1) |(0<<SPR0));	// set clock rate
//SPSR |= (0<<SPI2X);
}
void nop(void)
{
	asm volatile("nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	::);
}

void WriteByteSPI(unsigned char Byte)
{

SPDR = Byte;					//Load byte to Data register
while(!(SPSR & (1<<SPIF))); 	// Wait for transmission complete

}

char ReadByteSPI(char addr)
{
	SPDR = addr;					//Load byte to Data register
	while(!(SPSR & (1<<SPIF))); 	// Wait for transmission complete
	addr=SPDR;
	return addr;
}

void WriteSpiCommand(uint8_t data)
{
//command = (command & (~0x0100));
//SPDR = command;					//Load byte to Data register
//while(!(SPSR & (1<<SPIF))); 	// Wait for transmission complete


	  CLK0
	  SDA0
//	  nop();//1 for cmd
	  CLK1

	  shiftBits(data);
}

void WriteSpiData(uint8_t data)
{
//data = (data | 0x0100);
//SPDR = data;					//Load byte to Data register
//while(!(SPSR & (1<<SPIF))); 	// Wait for transmission complete

	  CLK0
	  SDA1  //1 for param
//	  nop();
	  CLK1

	  shiftBits(data);

}



void shiftBits(byte b) {

  CLK0
  if ((b&128)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&64)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&32)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&16)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&8)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&4)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&2)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&1)!=0) SDA1 else SDA0
  CLK1

}




//send data
void sendData(byte data) {

  CLK0
  SDA1      //1 for param
//  nop();
  CLK1

  shiftBits(data);
}

//send cmd
void sendCMD(byte data) {

  CLK0
  SDA0                                                 //1 for cmd
//  nop();
  CLK1

  shiftBits(data);
}

//converts a 3*8Bit-RGB-Pixel to the 2-Byte-RGBRGB Format of the Display
void setPixel(byte r,byte g,byte b) {
#ifdef MODE565
   sendData((r&248)|g>>5);
   sendData((g&7)<<5|b>>3);
#else
  if (n==0) {
    s1=(r & 240) | (g>>4);
    s2=(b & 240);
    n=1;
  } else {
    n=0;
    sendData(s1);
    sendData(s2|(r>>4));
    sendData((g&240) | (b>>4));
  }
#endif
}
