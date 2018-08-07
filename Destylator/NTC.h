/*
 * NTC.h
 *
 *  Created on: 13-03-2015
 *      Author: Krzysiek
 */
#include <stdint.h>
#ifndef NTC_H_
#define NTC_H_

// R2_NTC - wartosc rezystora pomiarowego dla termistora
//#define R2_NTC_INIT {(uint8_t)10180, (uint8_t)10000, (uint8_t)10170, (uint8_t)10000}

double calcTemp(const float p_A[6], double R);
uint32_t calcResistance(uint16_t ADC_val, uint8_t ch, uint8_t Vref);
int16_t calcNTC(const uint16_t ADCvalue, uint8_t ch, uint8_t Vref);

#endif /* NTC_H_ */
