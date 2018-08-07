/*
 * soft_i2c.c
 *
 *  Created on: 06-05-2015
 *      Author: Dawid
 */
#include "sbit.h"

void SoftI2CInit()
{
	SCL_DDR = 1;
	SDA_DDR = 1;

	SCL = 1;
	SDA = 1;

}
void SoftI2CStart()
{
	SCL = 1;
	SDA = 1;
	_delay_us(5);
	SDA = 0;
	_delay_us(5);
	SCL = 0;
}

void SoftI2CStop()
{
	SDA = 0;
	SCL = 0;
	_delay_us(5);
	SCL = 1;
	_delay_us(5);
	SDA = 1;
	_delay_us(5);
}

void SoftI2C_ACK(void)
{
	SDA = 0;
	_delay_us(10);

	SCL = 1;
  	_delay_us(10);

  	SCL = 0;
  	_delay_us(10);
}

void SoftI2C_NoAck(void)
{
	SDA = 1;
	_delay_us(10);

	SCL = 1;
  	_delay_us(10);

  	SCL = 0;
  	_delay_us(10);
}

uint8_t SoftI2CWriteByte(uint8_t data)
{
//uint8_t ACK_TWI = 0;
//
//	   for(int i = 7 ; i >0 ; i--)   //Petla wysylajaca 8 bitow
//	   {
//
//
//	      if(DATA&(1<<i))      //jezeli 1 to wysli 1 a jezeli 0 to wysli 0
//	      {
//	    	  SDA = 1;
//	      }
//	      else
//	      {
//	    	  SDA = 0;
//	      }
//	      _delay_us(5);
//	      SCL = 1;
//	      _delay_us(4);   // minimalny czas trwania poziomu 1 danych 4
//
//	      SCL = 0;
//	//      _delay_us(5);   // minimalny czas trwania poziomu 0 danych 4.7
//	   }
//	   //Ustawienie jako wejscie aby odczytac ACK lub NACK
//	   SDA = 1;
//	   SDA_DDR = 0;
//
//	   _delay_us(5);
//
//	   // Ustawienie zegara na wysoki stan
//	   SCL = 1;
//
//	   //Sprawdzenie jaki sygnal generuje SLAVE ACK lub NACK
//	   if(SDA_R)
//	      ACK_TWI=1;
//	   else
//	      ACK_TWI=0;
//
//	   _delay_us(5);
//
//
//	   SCL = 0;      //zegar w niskim poziomie
//
//	   SDA_DDR = 1;   //ustawienie portu jako wyjscie
//
//	   _delay_us(5);
//
//	   //Funkcja zwraca potwierdzenie 0 ACK 1 NACK
//	   return ACK_TWI;

	uint8_t i;

		 for(i=0;i<8;i++)
		 {
			 SCL = 0;
			 _delay_us(5);

			if(data & 0x80)
				SDA = 1;
			else
				SDA = 0;

			_delay_us(5);

			SCL = 1;
			_delay_us(5);

			while(SCL_R == 0);

			data=data<<1;
		}

		//The 9th clock (ACK Phase)
		 SCL = 0;
		 _delay_us(5);

		SDA = 1;
		_delay_us(5);

		SCL = 1;
		_delay_us(5);

		uint8_t ack=!(SDA_R);

		SCL = 0;
		_delay_us(5);

		return ack;
	}
//
//	 uint8_t i;
//
//	 for(i=0;i<8;i++)
//	 {
//		 SCL = 0;
//		 _delay_us(5);
//
//		if(data & 0x80)
//			SDA = 1;
//		else
//			SDA = 0;
//
//		_delay_us(5);
//
//		SCL = 1;
//		_delay_us(5);
//
//		while((SCL_R & (1<<SCL))==0);
//
//		data=data<<1;
//	}
//
//	//The 9th clock (ACK Phase)
//	 SCL = 0;
//	 _delay_us(5);
//
//	SDA = 1;
//	_delay_us(5);
//
//	SCL = 1;
//	_delay_us(5);
//
//	uint8_t ack=!(SDA_R & (1<<SDA));
//
//	SCL = 0;
//	_delay_us(5);
//
//	return ack;



uint8_t SoftI2CReadByte(uint8_t ack)
{
	uint8_t data=0x00;
	uint8_t i;

	for(i=0;i<8;i++)
	{

		SCL = 0;
		_delay_us(5);
		SCL = 1;
		_delay_us(5);

		while((SCL_R & (1<<SCL))==0);

		if(SDA_R &(1<<SDA))
			data|=(0x80>>i);

	}

	SCL = 0;
	_delay_us(5);						//Soft_I2C_Put_Ack

	if(ack)
	{
		SDA = 0;
	}
	else
	{
		SDA = 1;
	}
	_delay_us(5);

	SCL = 1;
	_delay_us(5);

	SCL = 0;
	_delay_us(5);

	return data;
}

