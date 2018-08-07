/*
 * main.c
 *
 *  Created on: 24-08-2011
 *      Author: Dawid
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define STER PORTB
#define WYS_D PORTD
#define buzzer PORTC
#define SW_DIR DDRC
//Rejestr zapisu (pull-up)
#define SW_W   PORTC
//Rejestr odczytu
#define SW_R   PINC
#define SWA    0
#define SWB    1
#define SWC    2
#define SWD    3
#define SWE    4
volatile char second, secondu, secondu1, sec, secp;
volatile char minute, minuteu, minuteu1, min, minp;
volatile char hour, houru, houru1;
volatile char i1, i3, i8, i7, i6, i5, i2, i4, i21, i22, i23, i41, i42, i43 = 0;
volatile char dni;
volatile char miesiac, rok;
volatile char swiatlo, data, menu, budzik2 = 0;
volatile char budzik1 = 0;
volatile char budz = 0;
volatile char zasilanie = 1;
int zegar_glowny(void);

int main(void) {

	//konfiguracja timera 0
	//			TCCR0 = ((0 << CS00) | (0 << CS01) | (1 << CS02)); // ustawienie timer1 na CTC mode
	//			TIMSK |= (1 << TOIE0); // odblokowanie przerwania CTC
	//			OCR1A = 3906; // ustawienie czêstotliwoœci 10Hz dla kwarcu 8MHz i preskalera 256
	TCCR0 |= _BV(CS02) | _BV(CS00);
	TIMSK |= _BV(TOIE0);
	SFIOR |= _BV(PSR10);

	//konfiguracja timera 1
	TCCR1A = ((0 << WGM11) | (0 << WGM10)); // ustawienie timer1 na CTC mode
	TCCR1B = ((0 << WGM13) | (1 << WGM12) | (1 << CS12)); // ustawienie timer1 na CTC mode
	TIMSK |= (1 << OCIE1A); // odblokowanie przerwania CTC
	sei();
	//  globalne odblokowanie przerwañ
	OCR1A = 3910; // ustawienie czêstotliwoœci 10Hz dla kwarcu 8MHz i preskalera 256

	//	//Przyciski jako wejscia
	SW_DIR &= ~(1 << SWA);
	SW_DIR &= ~(1 << SWB);
	SW_DIR &= ~(1 << SWC);
	SW_DIR &= ~(1 << SWD);
	SW_DIR &= ~(1 << SWE);
	//Tym razem podci¹gamy
	SW_W |= (1 << SWA);
	SW_W |= (1 << SWB);
	SW_W |= (1 << SWC);
	SW_W |= (1 << SWD);
	SW_W |= (1 << SWE);

	//	0 - prawy dolny róg
	//	1 - prawy górny róg
	//	2 - górny
	//	3 - lewy górny
	//	4 - lewy dolny
	//	5 - dolny
	//	6 - srodkowy


	while (1) {

		zegar_glowny();

	}

	return 0;
}

int zegar_glowny() {
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRC = 0b0111111;
	PORTC = 0x00;

	uint8_t i, liczba = 0;
	uint8_t czas = 3;
	char liczbam = 0;
	char liczbam1 = 0;
	char set = 0;
	char it = 1;
	secondu = 1;
	minuteu = 1;
	houru = 1;
	miesiac = 4;
	rok = 4;
	dni = 4;
	minute = 0;
	hour = 0;
	for (;;) {

		if (SW_R & (1 << SWE))
				zasilanie = 1;
			else
				zasilanie = 0;
		if(zasilanie == 0)
			{
			STER &= ~0b11111111;
//			TIMSK &= ~_BV(TOIE0);
//			it = 0;
			}
		if(zasilanie == 1)
		{
//			if(it == 0)
//			{
//			TIMSK = _BV(TOIE0);
//			it = 1;
//			}
		for (i = 0; i < 60; ++i) {

			if (miesiac == 1 || 3 || 5 || 7 || 8 || 10 || 12)
				if (dni == 31) {
					miesiac++;
					dni = 1;
				}

			if (miesiac == 4 || 6 || 9 || 11)
				if (dni == 30) {
					miesiac++;
					dni = 1;
				}
			if (miesiac == 2)
				if (rok / 4 == 0)
					if (dni == 29) {
						miesiac++;
						dni = 1;
					} else if (dni == 28) {
						miesiac++;
						dni = 1;
					}

			if (menu == 0) {

				if (SW_R & (1 << SWA))
					if (i2 == 0) {
						i3++;
						budzik1 = 1;
					}

				if (SW_R & (1 << SWB))
					if (i21 == 0) {
						i21++;
						data = 1;
					}

				if (SW_R & (1 << SWC))
					if (i22 == 0) {
						i22++;
						menu = 1;
					}

				if (SW_R & (1 << SWD))
					if (i23 == 0) {
						i23++;
						budzik1 = 0;
						i3 = 0;
						PORTB &= ~(1 << 6);
						PORTB &= ~(1 << 7);
					}

				if (budzik1 == 0 && data == 0)
					PORTD |= (1 << 7);

				if (i % 6 == 0) {
					if (budzik1 == 1)
						PORTD &= ~(1 << 7);
					if (data == 1)
						liczba = rok % 10;
					else
						liczba = second % 10;
					STER &= ~(1 << 5);
					STER ^= (1 << 0);
				}

				if (i % 6 == 1) {
					if (budzik1 == 1)
					    PORTD |= (1 << 7);
					if (data == 1)
						liczba = rok / 10;
					else
						liczba = second / 10;
					STER &= ~(1 << 0);
					STER ^= (1 << 1);
				}

				if (i % 6 == 2) {

					if (data == 1)
						liczba = miesiac % 10;
					else
						liczba = minute % 10;
					STER &= ~(1 << 1);
					STER ^= (1 << 2);
				}

				if (i % 6 == 3) {
					if (data == 1)
						liczba = miesiac / 10;
					else
						liczba = minute / 10;
					STER &= ~(1 << 2);
					STER ^= (1 << 3);
				}

				if (i % 6 == 4) {
					if (data == 1)
						liczba = dni % 10;
					else
						liczba = hour % 10;
					STER &= ~(1 << 3);
					STER ^= (1 << 4);
				}

				if (i % 6 == 5) {
					if (data == 1)
						liczba = dni / 10;
					else
						liczba = hour / 10;
					STER &= ~(1 << 4);
					STER ^= (1 << 5);
				}
			}

			if (menu == 1) {
				if (SW_R & (1 << SWA))
					if (i2 == 0) {
						i2++;
							if (liczbam1 == 1) {
								if (set == 1) {
									houru--;
									if (houru == 0)
										houru = 24;
								}
								if (set == 2) {
									minuteu--;
									if (minuteu == 0)
										minuteu = 60;
								}
								if (set == 3) {
									secondu--;
									if (secondu == 0)
										secondu = 60;
								}
							} else if (liczbam1 == 2) {
								if (set == 1) {
									houru--;
									if (houru == 0)
										houru = 32;
								}
								if (set == 2) {
									minuteu--;
									if (minuteu == 0)
										minuteu = 13;
								}
								if (set == 3) {
									secondu--;
									if (secondu == 0)
										secondu = 99;
								}
							} else if (liczbam1 == 4) {
								if (set == 1) {
									houru--;
									if (houru == 0)
										houru = 5;
									if(set == 2)
										set = 3;
								}
							} else if (liczbam1 == 6) {
								if (set == 1) {
									houru--;
									if (houru == 0)
										houru = 100;
								}
								if (set == 2) {
									minuteu--;
									if (minuteu == 0)
										minuteu = 100;
								}
								if (set == 3) {
									secondu--;
									if (secondu == 0)
										secondu = 100;
								}
							} else if (liczbam > 1)
								liczbam--;
							else
								liczbam = 6;
					}


						if (SW_R & (1 << SWB))
							if (i21 == 0) {
								i21++;
								if (liczbam1 == 1) {
									if (set == 1) {
										houru++;
										if (houru == 25)
											houru = 1;
									}
									if (set == 2) {
										minuteu++;
										if (minuteu == 60)
											minuteu = 1;
									}
									if (set == 3) {
										secondu++;
										if (secondu == 60)
											secondu = 1;
									}
								} else if (liczbam1 == 2) {
									if (set == 1) {
										houru++;
										if (houru == 32)
											houru = 1;
									}
									if (set == 2) {
										minuteu++;
										if (minuteu == 13)
											minuteu = 1;
									}
									if (set == 3) {
										secondu++;
										if (secondu == 99)
											secondu = 1;
									}
								} else  if (liczbam1 == 4) {
									if (set == 1) {
										houru++;
										if (houru == 5)
											houru = 1;
										if(set == 2)
											set = 3;
									}
								} else if (liczbam1 == 6) {
									if (set == 1) {
										houru++;
										if (houru == 100)
											houru = 1;
									}
									if (set == 2) {
										minuteu++;
										if (minuteu == 100)
											minuteu = 1;
									}
								    if (set == 3) {
									   secondu++;
									   if (secondu == 100)
										secondu = 1;
								    }
								} else if (liczbam < 6)
									liczbam++;
								else
									liczbam = 1;
							}


						if (SW_R & (1 << SWC))
							if (i22 == 0) {
								i22++;
								if (liczbam1 == 1 || 2 || 3) {
									set++;
									if (set == 4) {
										if (liczbam == 1) {
											second = secondu - 1;
											minute = minuteu - 1;
											hour = houru - 1;
											set = 0;
											liczbam1 = 0;
											liczbam = 0;
											secondu = 1;
											minuteu = 1;
											houru = 1;
										} else if (liczbam == 2) {
											rok = secondu - 1;
											miesiac = minuteu - 1;
											dni = houru - 1;
											set = 0;
											liczbam1 = 0;
											liczbam = 0;
											secondu = 1;
											minuteu = 1;
											houru = 1;
										} else if (liczbam == 3) {
											secondu1 = secondu - 1;
											minuteu1 = minuteu - 1;
											houru1 = houru - 1;
											set = 0;
											liczbam1 = 0;
											liczbam = 0;
											secondu = 1;
											minuteu = 1;
											houru = 1;
										} else if (liczbam == 4) {
											budz = houru - 1;
											set = 0;
											liczbam1 = 0;
											liczbam = 0;
											secondu = 1;
											minuteu = 1;
											houru = 1;
										} else if (liczbam == 5) {
											set = 0;
											liczbam1 = 0;
											liczbam = 0;
											secondu = 1;
											minuteu = 1;
											houru = 1;
										} else if (liczbam == 6) {
											minp = 100 * (houru - 1) + (minuteu - 1);
											secp = (60 * minp) + (secondu - 1);
											set = 0;
											liczbam1 = 0;
											liczbam = 0;
											secondu = 1;
											minuteu = 1;
											houru = 1;
										}
									}

								}
								liczbam1 = liczbam;
								if (liczbam1 == 3)
									liczbam1 = 1;
							}


						if (SW_R & (1 << SWD))
							if (i23 == 0) {
								i23++;
								menu = 0;
							}

						if (budzik1 == 0 && data == 0)
							PORTD |= (1 << 7);
						if (menu == 1)
							if (liczbam1 == 1 || 2 || 3) {

								if (i % 6 == 0) {
									if (liczbam1 == 1 || 2) {
										liczba = (secondu - 1) % 10;
									}
									STER &= ~(1 << 5);
									STER ^= (1 << 0);
								}

								if (i % 6 == 1) {
									if (liczbam1 == 1 || 2) {
										liczba = (secondu - 1) / 10;
									}
									STER &= ~(1 << 0);
									STER ^= (1 << 1);
								}

								if (i % 6 == 2) {
									if (liczbam1 == 1 || 2) {
										liczba = (minuteu - 1) % 10;
									}
									if(liczbam1 == 5)
										liczba = min % 10;
									STER &= ~(1 << 1);
									STER ^= (1 << 2);
								}

								if (i % 6 == 3) {
									if (liczbam1 == 1 || 2) {
										liczba = (minuteu - 1) / 10;
									}
									if(liczbam1 == 5)
										liczba = (min % 100) / 10;
									STER &= ~(1 << 2);
									STER ^= (1 << 3);
								}

								if (i % 6 == 4) {
									if (liczbam1 == 1 || 2) {
										liczba = (houru - 1) % 10;
									}
									if(liczbam1 == 5)
										liczba = (min % 1000) / 100;
									STER &= ~(1 << 3);
									STER ^= (1 << 4);
								}
							}
						if (liczbam1 == 0)
							STER &= ~0b111111;
						if (i % 6 == 5) {
							if (menu == 1)
								if (liczbam1 == 1 || 2) {
									liczba = (houru - 1) / 10;
								}
							if(liczbam1 == 5)
									liczba = (min % 10000) / 1000;
							if (liczbam1 == 0)
								liczba = liczbam;
							STER &= ~(1 << 4);
							STER ^= (1 << 5);
						}
					}

				if (liczba == 0) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b01000000;
					//WYS_D = 0b1000000;
					_delay_ms(czas);
				} else if (liczba == 1) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b01111100;
					//WYS_D = 0b1111100;
					_delay_ms(czas);
				} else if (liczba == 2) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b00001001;
					//WYS_D = 0b0001001;
					_delay_ms(czas);
				} else if (liczba == 3) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b00011000;
					//WYS_D = 0b0011000;
					_delay_ms(czas);
				} else if (liczba == 4) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b00110100;
					//WYS_D = 0b0110100;
					_delay_ms(czas);
				} else if (liczba == 5) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b00010010;
					//WYS_D = 0b0010010;
					_delay_ms(czas);
				} else if (liczba == 6) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b00000010;
					//WYS_D = 0b0000010;
					_delay_ms(czas);
				} else if (liczba == 7) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b01111000;
					//WYS_D = 0b1111000;
					_delay_ms(czas);
				} else if (liczba == 8) {
					WYS_D &= ~0b01111111;
					//WYS_D = 0b0000000;
					_delay_ms(czas);
				} else if (liczba == 9) {
					WYS_D &= ~0b01111111;
					WYS_D |= 0b00010000;
					//WYS_D = 0b0010000;
					_delay_ms(czas);
				}

			}
		}
		}
		return 0;
	}

	ISR(TIMER1_COMPA_vect) {
		second++;
		sec++;
		if (second == 60) {
			second = 0;
			minute++;
			if (minute == 60) {
				minute = 0;
				hour++;
				if (hour == 24) {
					dni++;
					hour = 0;
				}
			}
		}
	if (secp > 0)
		if (secp == sec) {
			second++;
			sec = 0;
			if (second == 60) {
				second = 0;
				minute++;
			}
			if (minute == 60) {
				minute = 0;
				hour++;
			}
		}
}

	ISR(SIG_OVERFLOW0)
	{
		if (zasilanie == 1)
		{
		if (i2 == 1) {
			i4++;
			if (i4 == 2) {
				i2 = 0;
				i4 = 0;
			}
		}

		if (i21 == 1) {
			i41++;
			if (i41 == 2) {
				i21 = 0;
				i41 = 0;
			}
		}

		if (i22 == 1) {
			i42++;
			if (i42 == 2) {
				i22 = 0;
				i42 = 0;
			}
		}

		if (i23 == 1) {
			i43++;
			if (i43 == 2) {
				i23 = 0;
				i43 = 0;
			}
		}

		if (budzik1 == 1)
			if (hour == houru1)
				if (minute == minuteu1)
					if (second == secondu1) {
						i3 = 2;
					}

		//	if (budzik1 == 1)
		if (i3 == 2) {
		if (budz == 1) {
			i5++;
			if (i5 == 2) {
				PORTB ^= (1 << 6);
				i5 = 0;
			}
		}
		if (budz == 2) {
			i5++;
			if (i5 == 2) {
				PORTB ^= (1 << 7);
				i5 = 0;
			}
		}
		if (budz == 3) {
			i5++;
			if (i5 == 2) {
				PORTB ^= (1 << 6);
			}
			if (i5 == 4) {
				PORTB ^= (1 << 6);
			}
			if (i5 == 6) {
				PORTB ^= (1 << 7);
			}
			if (i5 == 8) {
				PORTB ^= (1 << 7);
				i5 = 0;
			}
		}
		if (budz == 4) {
			i5++;
			if (i5 == 2) {
				PORTB |= (1 << 6);
				PORTB &= ~(1 << 7);
			}
			if (i5 == 4) {
				PORTB &= ~(1 << 6);
				PORTB |= (1 << 7);
				i5 = 0;
			}
		}

		}

		if (i6 < 10) {
			i6++;
			if (i6 == 2) {
				PORTC ^= (1 << 5);
				i6 = 0;
			}
		}

		if (data == 1) {
			i1++;
			PORTD &= ~(1 << 7);
			if (i1 == 10) {
				data = 0;
				PORTD |= (1 << 7);
				i1 = 0;
			}
		}
		} else if(zasilanie == 0)
		{
			STER &= ~0b11111111;
			PORTC &= ~(1 << 5);
		}
		}


