/*
 * pgmspace.c
 *
 *  Created on: 9 sty 2018
 *      Author: Krzysiek
 */
#include <avr/pgmspace.h>

/*
 * Predefiniowane ikony LCD.
 * Numerowac kolejne znaki ASCII od znaku 0x80 po kolei.
 * Nastepnie dopisac adres struktury do tablicy g_SpecialCharacters
 */
const char PROGMEM x80[8] = {0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x04, 0x03}; // �
const char PROGMEM x81[8] = {0x02, 0x04, 0x00, 0x0E, 0x10, 0x10, 0x11, 0x0E}; // �
const char PROGMEM x82[8] = {0x00, 0x0E, 0x11, 0x1F, 0x10, 0x1E, 0x08, 0x06}; // �
const char PROGMEM x83[8] = {0x0C, 0x04, 0x06, 0x0C, 0x04, 0x04, 0x0E, 0x00}; // �
const char PROGMEM x84[8] = {0x02, 0x04, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11}; // �
const char PROGMEM x85[8] = {0x02, 0x04, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E}; // �
const char PROGMEM x86[8] = {0x02, 0x04, 0x00, 0x0E, 0x10, 0x0E, 0x01, 0x1E}; // �
const char PROGMEM x87[8] = {0x02, 0x04, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F}; // �
const char PROGMEM x88[8] = {0x04, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00}; // �
const char PROGMEM x89[8] = {0x00, 0x0E, 0x15, 0x15, 0x13, 0x11, 0x0E, 0x00}; // ikona zegar
const char PROGMEM x8a[8] = {0x04, 0x06, 0x04, 0x06, 0x04, 0x06, 0x09, 0x06}; // ikona termometr
const char PROGMEM x8b[8] = {0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00}; // ikona stopien
const char PROGMEM x8c[8] = {0x00, 0x1F, 0x11, 0x0A, 0x0A, 0x04, 0x1F, 0x00}; // ikona chemia
const char PROGMEM x8d[8] = {0x01, 0x02, 0x04, 0x08, 0x1F, 0x02, 0x04, 0x08}; // ikona grzanie
const char PROGMEM x8e[8] = {0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x0F, 0x07, 0x03}; // ikona filtr on
const char PROGMEM x8f[8] = {0x03, 0x05, 0x09, 0x11, 0x11, 0x09, 0x05, 0x03}; // ikona filtr off
const char PROGMEM x90[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // ikona pusta
const char PROGMEM x91[8] = {0x18, 0x04, 0x08, 0x04, 0x18, 0x00, 0x00, 0x00}; // ikona "3" [jednostka]
const char PROGMEM x92[8] = {0x0C, 0x12, 0x12, 0x0C, 0x1F, 0x00, 0x00, 0x00}; // male "0" symbolizujace minuty
const char PROGMEM x93[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}; // zamalowana kratka
const char PROGMEM x94[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}; // podkreslenie
const char PROGMEM x95[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x10, 0x10, 0x10}; // ikona dolewania anim1
const char PROGMEM x96[8] = {0x07, 0x02, 0x0f, 0x08, 0x08, 0x10, 0x10, 0x10}; // ikona dolewania anim2
const char PROGMEM x97[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x18, 0x10, 0x10}; // ikona dolewania anim3
const char PROGMEM x98[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x10, 0x18, 0x10}; // ikona dolewania anim4
const char PROGMEM x99[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x10, 0x10, 0x18}; // ikona dolewania anim5
const char PROGMEM x9a[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x10, 0x10, 0x1F}; // ikona dolewania anim6
const char PROGMEM x9b[8] = {0x07, 0x02, 0x0f, 0x08, 0x08, 0x10, 0x10, 0x1F}; // ikona dolewania anim7
const char PROGMEM x9c[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x18, 0x10, 0x1F}; // ikona dolewania anim8
const char PROGMEM x9d[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x10, 0x18, 0x1F}; // ikona dolewania anim9
const char PROGMEM x9e[8] = {0x07, 0x02, 0x0f, 0x08, 0x00, 0x10, 0x1F, 0x1F}; // ikona dolewania anim10
const char PROGMEM x9f[8] = {0x00, 0x0E, 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x00}; // ikona dozowania anim1
const char PROGMEM xa0[8] = {0x00, 0x0E, 0x0E, 0x15, 0x15, 0x1F, 0x1F, 0x00}; // ikona dozowania anim2
const char PROGMEM xa1[8] = {0x00, 0x0E, 0x0E, 0x15, 0x15, 0x1B, 0x1B, 0x00}; // ikona dozowania anim3
const char PROGMEM xa2[8] = {0x01, 0x02, 0x04, 0x08, 0x1F, 0x02, 0x04, 0x08}; // ikona grzania
const char PROGMEM xa3[8] = {0x06, 0x09, 0x10, 0x08, 0x04, 0x02, 0x11, 0x0E}; // ikona grzania solarnego
const char PROGMEM xa4[8] = {0x00, 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E}; // �
const char PROGMEM xa5[8] = {0x00, 0x0A, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F}; // �
const char PROGMEM xa6[8] = {0x00, 0x0A, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E}; // �
const char PROGMEM xa7[8] = {0x00, 0x0A, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E}; // � todo
const char PROGMEM xa8[8] = {0x00, 0x0A, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E}; // � todo

const char PROGMEM xa9[8] = {0x1F, 0x0E, 0x04, 0x11, 0x0E, 0x00, 0x11, 0x0E}; // sensorDetected1
const char PROGMEM xaa[8] = {0x1F, 0x0E, 0x04, 0x00, 0x00, 0x11, 0x0E, 0x00}; // sensorDetected2
const char PROGMEM xab[8] = {0x1F, 0x0E, 0x04, 0x00, 0x04, 0x11, 0x04, 0x0E}; // sensorDetected3
const char PROGMEM xac[8] = {0x0E, 0x04, 0x00, 0x04, 0x0E, 0x04, 0x04, 0x0A}; // sensorDetected
const char PROGMEM xad[8] = {0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // sensorClear

const char PROGMEM xae[8] = {0x00, 0x1F, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00}; // emptyShield
const char PROGMEM xaf[8] = {0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00}; // fullShield

const char PROGMEM xb0[8] = {0x1F, 0x15, 0x1F, 0x00, 0x1F, 0x1F, 0x0E, 0x0E}; // panic
const char PROGMEM xb1[8] = {0x11, 0x0A, 0x0A, 0x04, 0x0A, 0x0A, 0x11, 0x00}; //

/*
 * Tablica adresow kolejnych znakow specjalnych poczawszy
 * od znaku 0x80 ASCII
 */
const int PROGMEM g_SpecialCharacters[] = {
	&x80, &x81, &x82, &x83, &x84, &x85, &x86, &x87, &x88, &x89,
	&x8a, &x8b, &x8c, &x8d, &x8e, &x8f, &x90, &x91, &x92, &x93,
	&x94, &x95, &x96, &x97, &x98, &x99, &x9a, &x9b, &x9c, &x9d,
	&x9e, &x9f, &xa0, &xa1, &xa2, &xa3, &xa4, &xa5, &xa6, &xa7,
	&xa8, &xa9, &xaa, &xab, &xac, &xad, &xae, &xaf, &xb0, &xb1
};




