/*
 * pgmspace.h
 *
 *  Created on: 9 sty 2018
 *      Author: Krzysiek
 */

#ifndef PGMSPACE_H_
#define PGMSPACE_H_
#include <avr/pgmspace.h>

// LCD Flash constants
extern const char PROGMEM x80[8]; //¹
extern const char PROGMEM x81[8]; //æ
extern const char PROGMEM x82[8]; //ê
extern const char PROGMEM x83[8]; //³
extern const char PROGMEM x84[8]; //ñ
extern const char PROGMEM x85[8]; //ó
extern const char PROGMEM x86[8]; //œ
extern const char PROGMEM x87[8]; //Ÿ
extern const char PROGMEM x88[8]; //¿
extern const char PROGMEM x89[8]; //ikona zegar
extern const char PROGMEM x8a[8]; //ikona termometr
extern const char PROGMEM x8b[8]; //ikona stopien
extern const char PROGMEM x8c[8]; //ikona chemia
extern const char PROGMEM x8d[8]; //ikona grzanie
extern const char PROGMEM x8e[8]; //ikona filtr on
extern const char PROGMEM x8f[8]; //ikona filtr off
extern const char PROGMEM x90[8]; //ikona pusta
extern const char PROGMEM x91[8]; //ikona "3" [jednostka]
extern const char PROGMEM x92[8]; // male "0" symbolizujace minuty
extern const char PROGMEM x93[8]; // zamalowana kratka
extern const char PROGMEM x94[8]; // podkreslenie
extern const char PROGMEM x95[8]; // ikona dolewania anim1
extern const char PROGMEM x96[8]; // ikona dolewania anim2
extern const char PROGMEM x97[8]; // ikona dolewania anim3
extern const char PROGMEM x98[8]; // ikona dolewania anim4
extern const char PROGMEM x99[8]; // ikona dolewania anim5
extern const char PROGMEM x9a[8]; // ikona dolewania anim6
extern const char PROGMEM x9b[8]; // ikona dolewania anim7
extern const char PROGMEM x9c[8]; // ikona dolewania anim8
extern const char PROGMEM x9d[8]; // ikona dolewania anim9
extern const char PROGMEM x9e[8]; // ikona dolewania anim10
extern const char PROGMEM x9f[8]; // ikona dozowania anim1
extern const char PROGMEM xa0[8]; // ikona dozowania anim2
extern const char PROGMEM xa1[8]; // ikona dozowania anim3
extern const char PROGMEM xa2[8]; // ikona grzania
extern const char PROGMEM xa3[8]; // ikona grzania solarnego
extern const char PROGMEM xa4[8]; // ö
extern const char PROGMEM xa5[8]; // ä
extern const char PROGMEM xa6[8]; // ü
extern const char PROGMEM xa7[8]; // Ü //todo
extern const char PROGMEM xa8[8]; // ß //todo
extern const char PROGMEM xa9[8]; // Ü //todo
extern const char PROGMEM xaa[8]; // ß //todo
extern const char PROGMEM xab[8]; // Ü //todo
extern const char PROGMEM xac[8]; // Ü //todo
extern const char PROGMEM xad[8]; // ß //todo
extern const char PROGMEM xae[8]; // ß //todo
extern const char PROGMEM xaf[8]; // ß //todo
extern const char PROGMEM xb0[8]; // ß //todo
extern const char PROGMEM xb1[8]; // ß //todo

extern const int PROGMEM g_SpecialCharacters[];

#define ICON_CLOCK				0
#define ICON_TEMP				1
#define ICON_DEGREE				2
#define ICON_SENSOR_DETECTED	3
#define ICON_SENSOR_CLEAR		4
#define ICON_EMPTY_SHIELD		5
#define ICON_SHIELD				6
#define ICON_ALARM				7
#define ICON_CLOCK_VAR				&x89
#define ICON_TEMP_VAR				&x8a
#define ICON_DEGREE_VAR				&x8b
#define ICON_SENSOR_DETECTED_VAR	&xac
#define ICON_SENSOR_CLEAR_VAR		&xad
#define ICON_EMPTY_SHIELD_VAR		&xae
#define ICON_SHIELD_VAR				&xaf
#define ICON_ALARM_VAR				&xb0

#endif /* PGMSPACE_H_ */
