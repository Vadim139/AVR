/*
 * SPI.h
 *
 *  Created on: 20-02-2013
 *      Author: Dawid
 */


#define SPIPORT PORTB
#define SPIDDR DDRB
#define CS 4
#define CLK 7
#define SDA 5

#define RESET 3

#define cbi(reg, bit) (reg&=~(1<<bit))
#define sbi(reg, bit) (reg|= (1<<bit))

#define CS0 cbi(SPIPORT,CS);
#define CS1 sbi(SPIPORT,CS);
#define CLK0 cbi(SPIPORT,CLK);
#define CLK1 sbi(SPIPORT,CLK);
#define SDA0 cbi(SPIPORT,SDA);
#define SDA1 sbi(SPIPORT,SDA);
#define RESET0 cbi(SPIPORT,RESET);
#define RESET1 sbi(SPIPORT,RESET);

#define byte unsigned char


#ifndef SPI_H_
#define SPI_H_

void InitSPI(void);
void WriteByteSPI(unsigned char Byte);
char ReadByteSPI(char addr);
void WriteSpiCommand(uint8_t command);
void WriteSpiData(uint8_t data);


#endif /* SPI_H_ */

