///*
//   Plik ds18b20.h
//
//   (xyz.isgreat.org)
//*/
//
//#ifndef DS18B20_H
//#define DS18B20_H
//
///* DS18B20 przy³¹czony do portu  PD7 AVRa  */
//#define SET_ONEWIRE_PORT     PORTD  |=  _BV(7)
//#define CLR_ONEWIRE_PORT     PORTD  &= ~_BV(7)
//#define IS_SET_ONEWIRE_PIN   PIND   &   _BV(7)
//#define SET_OUT_ONEWIRE_DDR  DDRD   |=  _BV(7)
//#define SET_IN_ONEWIRE_DDR   DDRD   &= ~_BV(7)
//
//unsigned char ds18b20_ConvertT(void);
//int ds18b20_Read(unsigned char []);
//void OneWireStrong(char);
//unsigned char OneWireReset(void);
//void OneWireWriteByte(unsigned char);
//unsigned char OneWireReadByte(void);
//
//#endif

//#include <avr/io.h>
//#include <inttypes.h>
//#include <stdlib.h>
//#include <stdio.h>
#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"
#define T1 7
#define T2 7
#define T3 7
#define T4 7
//#define OW_PIN  			PC2
#define OW_IN   			PIND
#define OW_OUT  			PORTD
#define OW_DDR  			DDRD
#define OW_CONF_DELAYOFFSET 0

uint8_t OW_PIN;
//#define F_OSC 8000000]
#define OW_CONF_CYCLESPERACCESS 13
//#define OW_CONF_DELAYOFFSET ( (uint16_t)( ((OW_CONF_CYCLESPERACCESS)*1000000L) / F_OSC  ) )

uint8_t ow_reset(void);
uint8_t ow_bit_io( uint8_t b );
uint8_t ow_byte_wr( uint8_t b );
uint8_t ow_byte_rd( void );
unsigned char DS18B20_ConvertT( uint8_t *blad, uint8_t T);
void DS18B20_showtemp(char p1, char p2, char mpp, uint8_t *blad, uint8_t T);
uint8_t zmroz(uint8_t rozp, uint8_t T);

#define OW_GET_IN()   ( OW_IN & (1<<OW_PIN)) //ustawia na pa 1 jedynke
#define OW_OUT_LOW()  ( OW_OUT &= (~(1 << OW_PIN)) )  // ustawia 0 na pinie 1
#define OW_OUT_HIGH() ( OW_OUT |= (1 << OW_PIN) )
#define OW_DIR_IN()   ( OW_DDR &= (~(1 << OW_PIN )) )
#define OW_DIR_OUT()  ( OW_DDR |= (1 << OW_PIN))





#endif /* KEYPAD_H_ */
