//
//#include <avr/io.h>
//#include <util/delay.h>
//#include "ds18b20.h"
//
//
///**********************************************************/
//
//unsigned char ds18b20_ConvertT(void)
//{
//  if (!OneWireReset()) return 0;
//
//  OneWireWriteByte(0xcc); // SKIP ROM
//  OneWireWriteByte(0x44); // CONVERT T
//
//  return -1;
//}
//
///***********************************************************/
//
//int ds18b20_Read(unsigned char scratchpad[])
//{
//  unsigned char i;
//
//  if (!OneWireReset()) return 0;
//
//  OneWireWriteByte(0xcc); // SKIP ROM
//  OneWireWriteByte(0xbe); // READ SCRATCHPAD
//
//  for(i=0; i<9; i++) scratchpad[i] = OneWireReadByte();
//
//  return 1;
//}
//
///**********************************************************/
//
//void OneWireStrong(char s)
//{
//  if (s)
//  {
//     SET_ONEWIRE_PORT;
//     SET_OUT_ONEWIRE_DDR;
//  }
//  else
//  {
//     SET_IN_ONEWIRE_DDR;
//  }
//}
//
///**********************************************************/
//
//unsigned char OneWireReset()
//{
//  CLR_ONEWIRE_PORT;
//
//  if (!(IS_SET_ONEWIRE_PIN)) return 0;
//
//  SET_OUT_ONEWIRE_DDR;
//  _delay_us(500);
//  SET_IN_ONEWIRE_DDR;
//  _delay_us(70);
//
//  if(!(IS_SET_ONEWIRE_PIN))
//  {
//    _delay_us(500);
//    return(1);
//  }
//
//  _delay_us(500);
//
//return(0);
//}
//
///**********************************************************/
//
//void OneWireWriteByte(unsigned char byte)
//{
//   unsigned char i;
//
//   CLR_ONEWIRE_PORT;
//
//   for (i=0; i<8; i++)
//   {
//     SET_OUT_ONEWIRE_DDR;
//
//     if (byte & 0x01)
//     {
//       _delay_us(7);
//       SET_IN_ONEWIRE_DDR;
//       _delay_us(70);
//     }
//     else
//     {
//        _delay_us(70);
//        SET_IN_ONEWIRE_DDR;
//        _delay_us(7);
//     }
//
//     byte >>= 1;
//   }
//}
//
///***********************************************************/
//
//unsigned char OneWireReadByte(void)
//{
//  unsigned char i, byte = 0;
//
//  SET_IN_ONEWIRE_DDR;
//
//  for (i=0; i<8; i++)
//  {
//     SET_OUT_ONEWIRE_DDR;
//     _delay_us(7);
//     SET_IN_ONEWIRE_DDR;
//     _delay_us(7);
//     byte >>= 1;
//
//     if(IS_SET_ONEWIRE_PIN) byte |= 0x80;
//
//     _delay_us(70);
//  }
//
//  return byte;
//}


#include "ds18b20.h"
#include <math.h>
//#include "lcd_drv.h"
//#include <util/delay.h>
//#include "sbit.h"

uint8_t roz;


/*________________________________________________________________________

		Funkcja resetujaca linie 1 - Wire
________________________________________________________________________*/

uint8_t ow_reset(void)
{
	OW_OUT_LOW();
	OW_DIR_OUT();
	_delay_us(480);
	OW_DIR_IN();
	_delay_us(66);
	_delay_us(480-66);
	return 0;
}

/*________________________________________________________________________

		Funkcja wysyłajaca bit danych
________________________________________________________________________*/

uint8_t ow_bit_io( uint8_t b )
{
	uint8_t sreg;
	OW_DIR_OUT();
	_delay_us(1);
	if ( b )
		OW_DIR_IN();
	_delay_us(15-1-OW_CONF_DELAYOFFSET);
	if( OW_GET_IN() == 0 )
		b = 0;
	_delay_us(60-15);
	OW_DIR_IN();
	return b;
}

/*________________________________________________________________________

		Funkcja wysyłajaca bajt danych
________________________________________________________________________*/

uint8_t ow_byte_wr( uint8_t b )
{
	uint8_t i = 8, j;

	do {
		j = ow_bit_io( b & 1 );
		b >>= 1;
		if( j ) b |= 0x80;
	} while( --i );

	return b;
}

/*________________________________________________________________________

		Funkcja odczytujaca bajt danych
________________________________________________________________________*/

uint8_t ow_byte_rd( void )
{
  return ow_byte_wr( 0xFF );
}


/*________________________________________________________________________

		Funkcja odczytujaca raz temperature
________________________________________________________________________*/

void DS18B20_showtemp(char p1, char p2, char mpp, uint8_t *blad, uint8_t T) {

	float temp = 0;
	char buf[8], minus;
	uint8_t temp1, temp2;

	if (*blad == 1) {  // Sprawdzanie czy przerwanie zewnętrzne
		lcd_xy(0, 1);  // nie przerwało pracy czujnika.
		lcd_blank(16);
		*blad = 0;
	}

//	switch (T) {
//		case 1:
//			OW_PIN = T1;
//			break;
//		case 2:
//			OW_PIN = T2;
//			break;
//		case 3:
//			OW_PIN = T3;
//			break;
//		case 4:
//			OW_PIN = T4;
//			break;
//		default:
//			break;
//	}
//
////	Rozpoczęcie pomiaru temperatury
//
//	ow_reset();
//	ow_byte_wr(0xCC);
//	ow_byte_wr(0x44);
//
//	if (roz == 1) {
//		_delay_ms(94);
//
//	} else if (roz == 2) {
//		_delay_ms(188);
//
//	} else if (roz == 3) {
//		_delay_ms(250);
//		_delay_ms(125);
//
//	} else if (roz == 4) {
//		_delay_ms(250);
//		_delay_ms(250);
//		_delay_ms(250);
//	}

//	Pobranie temp z czujnika

	ow_reset();
	ow_byte_wr(0xCC);
	ow_byte_wr(0xBE);
	temp1 = ow_byte_rd();
	temp2 = ow_byte_rd();

	minus = (temp2 >> 7);
	temp2 = temp2 & 0x07;

	ow_reset();

	temp = (temp1 + (temp2 * 256)) / (float) 16; // Przeliczenie temperatury

	if (minus) {   // Przeliczenie temperatury w przypadku wartoci ujemnych
		if (temp > 127) {
			temp1 = (temp1 & 0x0F);
			temp = 1.0 - (temp1 / (float) 16);
		} else if (temp > 112 && temp <= 127){
			temp = 16.0 - (temp1 / (float) 16);
		} else if (temp <= 112){
			temp = 128.0 - temp;
		}
	}

	dtostrf(temp, 1, mpp, buf); //zamienia ASCI na stringa

//	Wyswietlenie temperatury na LCD

	lcd_xy(p1, p2);
//	lcd_puts("T");
//	lcd_cyfra(T);
//	lcd_puts(":");

	if (temp > 99 || temp < 10) {
		lcd_xy(6, 1);
//		lcd_blank(9);
	}
	lcd_xy(p1, p2);

	if (minus)
		lcd_putchar('-');

	lcd_puts(buf);
	lcd_xy(p1 + 3 + mpp, p2);

	if (*blad == 1)  // Zapobiegnięcie niepoprawnemu wyswietleniu temp po przerwaniu
		return ;

//	lcd_puts("C");
	lcd_xy(p1 + 3, p2);

return ;
}

unsigned char DS18B20_ConvertT( uint8_t *blad, uint8_t T)
{
	if (*blad == 1) {  // Sprawdzanie czy przerwanie zewnętrzne
		lcd_xy(0, 1);  // nie przerwało pracy czujnika.
		lcd_blank(16);
		*blad = 0;
	}

	switch (T) {
		case 1:
			OW_PIN = T1;
			break;
		case 2:
			OW_PIN = T2;
			break;
		case 3:
			OW_PIN = T3;
			break;
		case 4:
			OW_PIN = T4;
			break;
		default:
			break;
	}

//	Rozpoczęcie pomiaru temperatury

	ow_reset();
	ow_byte_wr(0xCC);
	ow_byte_wr(0x44);

  return -1;
}

uint8_t zmroz(uint8_t rozp, uint8_t T)  // (zmiana rozdzielczosci)
{
	roz = rozp;  // zapis wartoci rozp (rozdzielczosci podanej) do zmiennej globalnej

	switch (T) {
		case 1:
			OW_PIN = T1;
			break;
		case 2:
			OW_PIN = T2;
			break;
		case 3:
			OW_PIN = T3;
			break;
		case 4:
			OW_PIN = T4;
			break;
		default:
			break;
	}
	ow_reset();
	ow_byte_wr(0xCC);
	ow_byte_wr(0x4E);
	ow_byte_wr(0x00);
	ow_byte_wr(0x00);

	if (roz == 1) {
		ow_byte_wr(0x1F);
	} else if (roz == 2) {
		ow_byte_wr(0x3F);
	} else if (roz == 3) {
		ow_byte_wr(0x5F);
	} else if (roz == 4) {
		ow_byte_wr(0x7F);
	}
	ow_reset();
	ow_byte_wr(0x48);
	ow_reset();

	return roz;
}
