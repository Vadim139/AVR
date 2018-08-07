/*
 * RS485.cpp
 *
 *  Created on: 16 gru 2017
 *      Author: Vadim
 */

#include "RS485.h"

extern uint16_t Time;
extern float Temp_in;
extern float Temp_out;
extern uint8_t Halt;
extern uint8_t Alarm_flag;
extern uint8_t rqs_proc;

void RS485_Init() {

	MAX_RW_DDR = 1;
	MAX_RW = 0;
	uart_init((UART_BAUD_SELECT((BAUD),xtalCpu)));
}

void RS_Get(uint8_t RQS,uint8_t* data, uint8_t ID)
{
	uint8_t buf[30];
	uint8_t i = 0;
	memset(buf,0,30);
	buf[0] = SEND;
	buf[1] = RQS;

	switch (RQS) {
		case NOU:
			RS_TransferMulti(M_ADDR,buf,2);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case NOS:
			RS_TransferMulti(M_ADDR,buf,2);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case NOG:
			RS_TransferMulti(M_ADDR,buf,2);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case NOO:
			RS_TransferMulti(M_ADDR,buf,2);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case U_NAME:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<20;i++)
				data[i] = uart_getc();
			break;
		case U_ZONES:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<10;i++)
				data[i] = uart_getc();
			break;
		case U_ACCESS_LVL:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case S_NAME:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<20;i++)
				data[i] = uart_getc();
			break;
		case S_ZONE:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case S_IN:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case S_STAT:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case G_NUM:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<10;i++)
				data[i] = uart_getc();
			break;
		case O_TYPE:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case O_STATUS:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[0] = uart_getc();
			break;
		case O_SCHEDULE:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<8;i++)
				data[i] = uart_getc();
			break;
		case WIFI_NAME:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<20;i++)
				data[i] = uart_getc();
			break;
		case WIFI_PASS:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<20;i++)
				data[i] = uart_getc();
			break;
		case NET_PR:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[i] = uart_getc();
			break;
		case NET_ON:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			data[i] = uart_getc();
			break;
		case WATCH:
			buf[2] = ID;
			RS_TransferMulti(M_ADDR,buf,3);
			memset(data,0,30);
			while(!Is_Data())
				_delay_ms(10);
			for(i = 0;i<5;i++)
				data[i] = uart_getc();
			break;
		default:
			break;
	}
}

void RS_Edit(uint8_t RQS,uint8_t* data, uint8_t ID)
{
	uint8_t buf[35];
	uint8_t i = 0;
	memset(buf,0,35);

	buf[33] = RQS;
	buf[34] = ID;

	switch (RQS) {
		case U_NAME:
			memcpy(buf,data,20);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case U_ZONES:
			memcpy(buf,data,10);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case U_ACCESS_LVL:
			memcpy(buf,data,1);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case U_RFID:
			memcpy(buf,data,14);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case U_PIN:
			memcpy(buf,data,5);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case S_NAME:
			memcpy(buf,data,20);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case S_ZONE:
			memcpy(buf,data,1);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case S_IN:
			memcpy(buf,data,1);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case G_NUM:
			memcpy(buf,data,9);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case O_TYPE:
			memcpy(buf,data,1);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case O_SCHEDULE:
			memcpy(buf,data,8);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case WIFI_NAME:
			memcpy(buf,data,19);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case WIFI_PASS:
			memcpy(buf,data,20);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case NET_PR:
			memcpy(buf,data,1);
			RS_TransferMulti(M_ADDR,data,35);
			break;
		case NET_ON:
			memcpy(buf,data,1);
			RS_TransferMulti(M_ADDR,data,35);
			break;

		default:
			break;
	}
}

void RS_Check(uint8_t RQS,uint8_t* data, uint8_t Act)
{
	uint8_t buf[30];
	uint8_t i = 0;
	memset(buf,0,30);

	switch (RQS) {
		case U_RFID:
			data[14] = 0;
			buf[0] = CHECK;
			buf[1] = RQS;
			memcpy(buf+2,data,14);
			buf[strlen(data)+2] = Act;
			RS_TransferMulti(M_ADDR,buf,18);
//			while(!Is_Data())
//				_delay_ms(10);
//			memset(buf,0,30);
//			for(i = 0;i<22;i++)
//				buf[i] = uart_getc();
//			memcpy(data,buf,22);
			break;
		case U_PIN:
			data[4] = 0;
			buf[0] = RQS;
			strcpy(buf+1,data);
			buf[strlen(data)+1] = Act;
			RS_TransferMulti(M_ADDR,buf,7);
			while(!Is_Data())
				_delay_ms(10);
			memset(buf,0,30);
			for(i = 0;i<23;i++)
				buf[i] = uart_getc();
			memcpy(data,buf,23);
			break;
		default:
			break;
	}
}

void RS_Add(uint8_t RQS)
{
	uint8_t data[3];
	data[2] = 0;

	data[0] = ADD;
	data[1] = RQS;

	RS_TransferMulti(M_ADDR,data,2);
}

void RS_Del(uint8_t RQS, uint8_t ID)
{
	uint8_t data[4];
	data[3] = 0;

	data[0] = ADD;
	data[1] = RQS;
	data[2] = ID;

	RS_TransferMulti(M_ADDR,data,3);
}

void RS_Save()
{
	RS_Transfer(M_ADDR,SAVE);
}

void RS_Cancel()
{
	RS_Transfer(M_ADDR,CANCEL);
}


void RS_Process()
{
	uint8_t x,y,i = 0;
	char buf[20];
	memset(buf,0,20);
	rqs_proc = 1;
	if(uart_getc() == ADDR)
	{
		_delay_ms(20);
		switch (uart_getc()) {
			case INIT:
				RS_Transfer(254,250);

				break;
			case HALT:
				Halt = 1;

				break;
			case RUN:
				Halt = 0;

				break;
			case CLR_SCREEN:
				lcd_blank();
				lcd_xy(0,0);

				break;
			case LCD_PUTS:
				x = RS_Receive();
				y = RS_Receive();

				RS_Receive_Multi(buf);

//				lcd_blank();
				lcd_xy(x,y);
				lcd_puts(buf);

				break;
			case TIME:
				RS_Receive_Multi(buf);

				lcd_xy(0,1);
				lcd_puts(buf);
				Time = atoi(buf);
				break;
			case TEMP:
				RS_Receive_Multi(buf);

//				Temp_out = atof(buf);

				memset(buf,0,20);

				sprintf(buf,"%0.1f",Temp_in);
				RS_TransferMulti(M_ADDR,buf,6);

				break;
			case ALARM_ON:
				Alarm_flag = 1;
				break;
			case ALARM_OFF:
				Alarm_flag = 0;
				break;
			default:
				break;
		}
	}
	rqs_proc = 0;
}

uint8_t RS_Transfer(uint8_t addr, uint8_t data)
{
	MAX_EnableWrite();
	_delay_ms(20);

	if(addr != 0){
		uart_putc(addr);
		_delay_us(20);
	}
	uart_putc(data);
	_delay_us(20);

	if(addr != 0){
		uart_putc(addr);
	}

	_delay_ms(20);

	MAX_DisableWrite();
	_delay_ms(20);
	return 0;

}

uint8_t RS_TransferMulti(uint8_t addr, uint8_t* data, uint8_t size)
{
	MAX_EnableWrite();
	_delay_ms(20);
	uart_putc(addr);
	_delay_us(20);

	for(int i = 0; i < size; i++){
		uart_putc(data[i]);
		_delay_us(20);
	}
	uart_putc(addr);
	_delay_ms(20);
	MAX_DisableWrite();
	_delay_ms(20);
	return 0;

}

uint8_t RS_Receive()
{
	uint8_t rec = 0;

	if(Is_Data())
		rec = uart_getc();
//	while(USART_GetFlagStatus(RC_USART, USART_FLAG_) == RESET);
//	delay_ms(20);

	return rec;

}

uint8_t RS_Receive_Multi(uint8_t* data)
{
	uint8_t i = 0;

	while(!Is_Data());
	_delay_ms(10);

	while(Is_Data()){
		data[i] = uart_getc();
		_delay_us(10);
		i++;
	}
//	while(USART_GetFlagStatus(RC_USART, USART_FLAG_) == RESET);
//	delay_ms(20);
	data[i] = 0;
	return i;

}

void MAX_EnableWrite()
{
    // Set slave SS pin low
	MAX_RW = 1;
}

void MAX_DisableWrite()
{
    // Set slave SS pin high
	MAX_RW = 0;
}


