/*
 * NTC.c
 *
 *  Created on: 13-03-2015
 *      Author: Krzysiek
 *
 *      Sprawdzone parametry ADC:
 *      Zakres=0..5V  Prescaler = 1024  freqADC=100Hz
 */
#include "NTC.h"

const uint16_t R2_ntc=1974;//[4] = {10180, 10000, 10170, 10000};

// A1 - wspó³czynniki aproksymacji wielomianem 5st dla obliczania temperatury
//      w przedziale rezystancji termistora 0 - 3500R (dok³adnosc do 1stC)
const float A1[6] = {-1.7410e-12,  4.2499e-09,  -4.4298e-06,   2.2676e-03,  -7.3266e-01,   2.2804e02};

//	A2 - wspó³czynniki aproksymacji wielomianem 5st dla obliczania temperatury
//       w przedziale rezystancji termistora 3500 - 35000R (dok³adnosc do 1stC)
const float A2[6] = {-4.1177e-15,  3.2052e-11,  -1.0227e-07,   1.7441e-04,  -1.8103e-01,   1.6630e02};

//	A2 - wspó³czynniki aproksymacji wielomianem 5st dla obliczania temperatury
//       w przedziale rezystancji termistora 3500 - 35000R (dok³adnosc do 1stC)
const float A3[6] = {-2.7723e-18,  9.1079e-14,  -1.2118e-09,   8.4967e-06,  -3.5785e-02,   1.1066e02};

//  A3 - wspó³czynniki aproksymacji wielomianem 5st dla obliczania temperatury
//       w przedziale rezystancji termistora 35000R> (dok³adnosc do 1stC)
const float A4[6] = {          0,  1.0773e-16,  -9.5576e-12,   3.3866e-07,  -6.5219e-03,   6.4840e+01};

/*
 * calcTemp
 */
double calcTemp(const float p_A[6], double R){
	return 100*(((((p_A[0]*R+p_A[1])*R+p_A[2])*R+p_A[3])*R+p_A[4])*R+p_A[5]);
}

/*
 * calcResistance
 */
uint32_t calcResistance(uint16_t ADC_val, uint8_t ch, uint8_t Vref){
	//return (float)1024*R2_NTC/(float)ADC_val-R2_NTC;
	if(Vref == 1)
	return   (float)R2_ntc/(2*1024.0/ADC_val-1);
	else
	return   (float)R2_ntc/(1024.0/ADC_val-1);
}

/*
 * calcNTC
 * Oblicza temperaturê wed³ug wartosci ADC
 */
int16_t calcNTC(const uint16_t ADCvalue, uint8_t ch, uint8_t Vref){
	uint32_t R;
	int16_t temp;
	if( ADCvalue != 0 && ch < 6){
		if(Vref == 1)
			R = calcResistance(ADCvalue,ch,1);
		else
			R = calcResistance(ADCvalue,ch,0);

		if(R < 600){
			temp = calcTemp(A1,R);
		} else if(R == 10000)
			temp = 250;
		else if(R < 2000){
			temp = calcTemp(A2,R);
		} else if(R < 9000){
			temp = calcTemp(A3,R);
		} else{
			temp = calcTemp(A4,R);
		}
	}
	else{
		temp = 9999;
	}
	return temp;
}
