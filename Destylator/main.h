/*
 * main.h
 *
 *  Created on: 14-12-2012
 *      Author: Dawid
 */

#include <avr/io.h>
#include <stdlib.h>
#include "my_defs.h"
#include "sbit.h"
#include "PCF8583.h"


//void puttime(char x, char y, char i) {
//	uint8_t godz, min, sek, hsek;
////	lcd_putchar('a');
//	PCF8583_get_time(&godz, &min, &sek, &hsek);
////	lcd_putchar('b');
//	if (i == 1 || i == 2 || i == 3 || i == 4) {
//		lcd_xy(x, y);
//		if (godz <= 9)
//			lcd_putchar('0');
//		lcd_number(godz);
//		if (i == 2 || i == 3 || i == 4) {
//			lcd_putchar(':');
//			if (min <= 9)
//				lcd_putchar('0');
//			lcd_number(min);
//			if (i == 3 || i == 4) {
//				lcd_putchar(':');
//				if (sek <= 9)
//					lcd_putchar('0');
//				lcd_number(sek);
//				if (i == 4) {
//					lcd_putchar(':');
//					if (hsek <= 9)
//						lcd_putchar('0');
//					lcd_number(hsek);
//				}
//
//			}
//
//		}
//
//	}
////	lcd_putchar('c');
//}
//
//void putdate(char x, char y, char i) {
//	uint8_t mounth, day;
//	uint16_t year;
//
//	PCF8583_get_date(&day, &mounth, &year);
//
//	if (i == 1 || i == 2 || i == 3 || i == 4) {
//		lcd_xy(x, y);
//		if (day <= 9)
//			lcd_putchar('0');
//		lcd_number(day);
//		if (i == 2 || i == 3 || i == 4) {
//			lcd_putchar('.');
//			if (mounth <= 9)
//				lcd_putchar('0');
//			lcd_number(mounth);
//			if (i == 3 || i == 4) {
//				lcd_putchar('.');
//				lcd_lnumber(year);
////				lcd_puts(' r');
//				}
//
//		}
//
//	}
//}

