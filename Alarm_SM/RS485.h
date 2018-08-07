/*
 * RS485.h
 *
 *  Created on: 16 gru 2017
 *      Author: Vadim
 */

#include "main.h"
//#include "Timer.h"

#ifndef RS485_H_
#define RS485_H_

// Commands
#define	 INIT			254
#define  HALT			1
#define  RUN			2
#define  CLR_SCREEN 	3
#define  LCD_PUTS		4
#define  ALARM_ON		5
#define  ALARM_OFF		6
#define  DATA			7
#define  SEND			10
#define  CHECK			11
#define  ADD			12
#define  UPDATE			13
#define  SAVE			14
#define	 DELETE			15
#define  CANCEL			16
#define  TIME			17
#define  TEMP			18

// Data
#define  USER			21
#define  SENSOR			22
#define  OUTPUT			23
#define  GSM			24
#define	 NOU			25	//Numbers of users
#define  NOS			26
#define  NOG			27
#define  NOO			28
#define  U_NAME			29
#define  U_ACCESS_LVL	30
#define  U_ZONES		31
#define  U_RFID			32
#define  U_PIN			33
#define  S_NAME			34
#define  S_ZONE			35
#define  S_IN			36
#define  S_STAT			37
#define  G_NUM			38
#define  O_TYPE			39
#define  O_STATUS		40
#define  O_SCHEDULE		41
#define  WIFI_NAME		42
#define  WIFI_PASS		43
#define  NET_PR			44
#define  NET_ON			45
#define  WATCH			46

void RS485_Init();
void RS_Process();
void RS_Get(uint8_t RQS,uint8_t* data, uint8_t ID);
void RS_Edit(uint8_t RQS,uint8_t* data, uint8_t ID);
void RS_Check(uint8_t RQS,uint8_t* data, uint8_t Act);
void RS_Add(uint8_t RQS);
void RS_Del(uint8_t RQS, uint8_t ID);
void RS_Save();
void RS_Cancel();

uint8_t RS_Transfer(uint8_t addr, uint8_t data);
uint8_t RS_TransferMulti(uint8_t addr, uint8_t* data, uint8_t size);
uint8_t RS_Receive();
uint8_t RS_Receive_Multi(uint8_t* data);
void MAX_EnableWrite();
void MAX_DisableWrite();


#endif /* RS485_H_ */
