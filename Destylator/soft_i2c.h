/*
 * soft_i2c.h
 *
 *  Created on: 06-05-2015
 *      Author: Dawid
 */
#include <stdint.h>
#ifndef SOFT_I2C_H_
#define SOFT_I2C_H_

void SoftI2CInit();
void SoftI2CStart();
void SoftI2CStop();
void SoftI2C_ACK(void);
void SoftI2C_NoAck(void);
uint8_t SoftI2CWriteByte(uint8_t data);
uint8_t SoftI2CReadByte(uint8_t ack);


#endif /* SOFT_I2C_H_ */

