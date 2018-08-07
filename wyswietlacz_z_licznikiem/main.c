/*
 * main.c
 *
 *  Created on: 21-08-2011
 *      Author: Dawid
 */

#include <avr/io.h>
#include <util/delay.h>
#define STER PORTB
#define WYS_D PORTD
int wyswietlacz_1(void);

int main(void) {
	//	DDRB = 0xFF;
	//	PORTB = 0x02;
	//	DDRD = 0xFF;
	//	PORTD = 0x00;
	//	uint8_t l = 0;
	//	uint8_t i = 0;
	//	uint16_t czas = 10;


	//	0 - prawy dolny róg
	//	1 - prawy górny róg
	//	2 - górny
	//	3 - lewy górny
	//	4 - lewy dolny
	//	5 - dolny
	//	6 - srodkowy


	while (1) {

		wyswietlacz_1();
		//	  for(l = 0;l<100;l++)
		//	  {
		//
		//		  for(i=0; i<100; ++i){
		//			  if(i%2==1){
		//				  STER = 0x02;
		//
		//				  if (l%10==0){
		//				  		WYS_D = 0b1000000;
		//				  		_delay_ms(czas);}
		//				  		else if (l%10==1){
		//				  			WYS_D = 0b1111100;
		//				  		  _delay_ms(czas);}
		//				  		else if (l%10==2){
		//				  					WYS_D = 0b0001001;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==3){
		//				  					WYS_D = 0b0011000;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==4){
		//				  					WYS_D = 0b0110100;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==5){
		//				  					WYS_D = 0b0010010;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==6){
		//				  					WYS_D = 0b0000010;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==7){
		//				  					WYS_D = 0b1111000;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==8){
		//				  					WYS_D = 0b0000000;
		//				  				  _delay_ms(czas);}
		//				  		else if (l%10==9){
		//				  					WYS_D = 0b0010000;
		//				  				  _delay_ms(czas);}
		//
		//			  } else{
		//				  STER = 0x04;
		//				  if (l/10==0){
		//				  		WYS_D = 0b1000000;
		//				  		_delay_ms(czas);}
		//				  		else if (l/10==1){
		//				  			WYS_D = 0b1111100;
		//				  		  _delay_ms(czas);}
		//				  		else if (l/10==2){
		//				  					WYS_D = 0b0001001;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==3){
		//				  					WYS_D = 0b0011000;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==4){
		//				  					WYS_D = 0b0110100;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==5){
		//				  					WYS_D = 0b0010010;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==6){
		//				  					WYS_D = 0b0000010;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==7){
		//				  					WYS_D = 0b1111000;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==8){
		//				  					WYS_D = 0b0000000;
		//				  				  _delay_ms(czas);}
		//				  		else if (l/10==9){
		//				  					WYS_D = 0b0010000;
		//				  				  _delay_ms(czas);}
		//
		//			  }
		//		  }


		//
		//		  if (STER == 0b00000010)
		//			  {STER ^= (1<<1);
		//		  STER ^= (1<<2);}
		//		  else{
		//		     STER ^= (1<<2);
		//		     STER ^= (1<<1);}

		//	  _delay_ms(1000);
		//	  }

	}

	return 0;
}

int wyswietlacz_1() {
	DDRB = 0xFF;
	PORTB = 0x02;
	DDRD = 0xFF;
	PORTD = 0x00;
	uint8_t l = 0;
	uint8_t i = 0;
	uint16_t czas = 10;

	for (l = 0; l < 100; l++) {

		for (i = 0; i < 100; ++i) {
			if (i % 2 == 1) {
				STER = 0x02;

				if (l % 10 == 0) {
					WYS_D = 0b1000000;
					_delay_ms(czas);
				} else if (l % 10 == 1) {
					WYS_D = 0b1111100;
					_delay_ms(czas);
				} else if (l % 10 == 2) {
					WYS_D = 0b0001001;
					_delay_ms(czas);
				} else if (l % 10 == 3) {
					WYS_D = 0b0011000;
					_delay_ms(czas);
				} else if (l % 10 == 4) {
					WYS_D = 0b0110100;
					_delay_ms(czas);
				} else if (l % 10 == 5) {
					WYS_D = 0b0010010;
					_delay_ms(czas);
				} else if (l % 10 == 6) {
					WYS_D = 0b0000010;
					_delay_ms(czas);
				} else if (l % 10 == 7) {
					WYS_D = 0b1111000;
					_delay_ms(czas);
				} else if (l % 10 == 8) {
					WYS_D = 0b0000000;
					_delay_ms(czas);
				} else if (l % 10 == 9) {
					WYS_D = 0b0010000;
					_delay_ms(czas);
				}

			} else {
				STER = 0x04;
				if (l / 10 == 0) {
					WYS_D = 0b1000000;
					_delay_ms(czas);
				} else if (l / 10 == 1) {
					WYS_D = 0b1111100;
					_delay_ms(czas);
				} else if (l / 10 == 2) {
					WYS_D = 0b0001001;
					_delay_ms(czas);
				} else if (l / 10 == 3) {
					WYS_D = 0b0011000;
					_delay_ms(czas);
				} else if (l / 10 == 4) {
					WYS_D = 0b0110100;
					_delay_ms(czas);
				} else if (l / 10 == 5) {
					WYS_D = 0b0010010;
					_delay_ms(czas);
				} else if (l / 10 == 6) {
					WYS_D = 0b0000010;
					_delay_ms(czas);
				} else if (l / 10 == 7) {
					WYS_D = 0b1111000;
					_delay_ms(czas);
				} else if (l / 10 == 8) {
					WYS_D = 0b0000000;
					_delay_ms(czas);
				} else if (l / 10 == 9) {
					WYS_D = 0b0010000;
					_delay_ms(czas);
				}

			}
		}
	}
	return 0;
}

