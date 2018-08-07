/*
 * main.h
 *
 *  Created on: 06-08-2014
 *      Author: Dawid
 */


#ifndef ALARM_SM_MAIN_H_
#define ALARM_SM_MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "my_defs.h"
#include "sbit.h"
#include "lcd_drv.h"
#include "uart.h"
#include "RS485.h"
//#include "keypad.h"
//#include "ds18b20.h"
//#include <avr/pgmspace.h>

//#include "my_defs.h"
//#include "conf.h"
#include "pgmspace.h"


typedef int bool;
#define true 1
#define false 0

#define M_ADDR 0
#define ADDR 1

#define KEYPAD_ALL_INPUT    0
#define KEYPAD_COMMAND_ALL  1
#define KEYPAD_COMMAND_HASH 2
#define KEYPAD_COMMAND_STAR 3

//typedef int bool;
//#define true 1
//#define false 0

#define M_ADDR 254
#define ADDR 252

#endif /* ALARM_SM_MAIN_H_ */
