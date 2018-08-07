/*
 * LCD_SSD1803a.c
 *
 *  Created on: 09-03-2015
 *      Author: Dawid
 */
#include "soft_i2c.h"
#include "LCD_SSD1803a.h"
#include <util/delay.h>
#include "sbit.h"
#include "string.h"
#include <stdlib.h>

#define soft_i2c;

uint8_t contrast = 0x1E;  //0 to 63 19

#ifndef soft_i2c
/***********Write_Command***************/
void Write_Command(uint8_t dat)
{
i2cStart();
i2cWrite(address_write);//78
i2cWrite(0x80);
i2cWrite(dat);
i2cStop();
}


/***********Write_Data******************/
void Write_Data(uint8_t dat1)
{
i2cStart();
i2cWrite(address_write);
i2cWrite(0x40);
i2cWrite(dat1);
i2cStop();
}

void LCDSSD_init(void)
{
	Write_Command(0x01); //Clear dispaly
	_delay_ms(50);

	Write_Command(0x39); //Function SET DL=1 N=1 DH=0 RE=0 IS=1
	Write_Command(0x06); //Entry mode set I/D=1 S=0
	Write_Command(0x0c); //Display on D=1 C=0 B=0
	Write_Command(0x1b); //Internal OSC BS0=1 F[2:0]=011
	Write_Command(0X55); //Power Icon Contrast set ION=0 BON=1 C[5:4]=01
	Write_Command(0x6d); //Follower control DON=1 Rab[2:0]==101=4.4
	Write_Command(0X7F); //Contrast set VOP=C[3:0]=0011

	Write_Command(0x38); //Function SET DL=1 N=1 DH=0 RE=0 IS=0
	Write_Command(0x3e); //Function set DL=1 N=1 RE=1
	Write_Command(0x02); //Power down mode PD=0
	Write_Command(0x05); //Entry mode set BDC=0 BDS=1
	Write_Command(0x09); //Extended function set FW=0 B/W=0 NW=1
	Write_Command(0x1e); //Double hight/bisa/display-dot shift UD[2:1]=11 BS1=1 DH'=0
	Write_Command(0x80); //Set scroll quantity SQ[5:0]=000000
}

//Note on I2C pull up resistors.
//These should not be too low otherwise the display will
//not pull the SDA line low enough to register an ACK.
//Suggest 10K.
// LCD initialize procedure VALUES FOR 3.3V 4x20 SSD1803A
void LCD_Init(void)
{
	L_RES = 0;
	_delay_ms(10);
//	set_pos(5,0);
	L_RES = 1;
  //set reset low
  //wait 10ms
  //set reset high
  _delay_ms(5);
  Write_Command(0x3a);  //8bit,4line,IS=0,RE=1
  Write_Command(0x1e);  //Set BS1 (1/6 bias)
  Write_Command(0x39);  //8bit,4line,IS=1,RE=0
  Write_Command(0x1c);  //Set BS0 (1/6 bias) + osc
  Write_Command(0x79);  //Set contrast lower 4 bits
  Write_Command(0x5d);  //Set ION, BON, contrast bits 4&5
  Write_Command(0x6d);  //Set DON and amp ratio.
  Write_Command(0x0c);  //Set display on
  Write_Command(0x01);  //Clear display

  set_contrast(contrast);

  _delay_ms(50);
}


//void send_command(unsigned char value)
//{
//  Wire.beginTransmission(address_write>>1);  //send start bit and address_write.
//  Wire.send(0x80);                           //send control byte rs=0 (bit 6)
//  Wire.send(value);                          //send control data
//  Wire.endTransmission();                    //send stop bit (transmitting only starts once this function received)
//}

void set_contrast(unsigned char value)
{
	Write_Command(0x39);
	Write_Command(0x70+(contrast&0x0f));        //bits 0 to 3 of contrast register in position 0 to 3
	Write_Command(0x5c+((contrast&0x30)>>4));   //bits 4 and 5 of contrast register in position 0 and 1
}

void i2cWriteString(char *str)
{
	while(*str)
	{
	i2cWrite(*str);
	str++;
	}
}

void LCD_xy(char x, char y)
{
	int pos = 0;
	if(y == 0)
	{
		pos = x + 128;

	}else
	if(y == 1)
	{
		pos = x + 32 + 128;

	}else
	if(y == 2)
	{
		pos = x + 64 + 128;
	}else
	if(y == 3)
	{
		pos = x + 96 + 128;
	}
	Write_Command(pos);
}

void clrscr()
{
	  i2cStart();
	  i2cWrite(address_write);//78
	  i2cWrite(0x80);
	  i2cWrite(0x01);
	  i2cStop();
}

void LCD_str(char *str)
{
	i2cStart();
	  i2cWrite(address_write);//78
	  i2cWrite(0x40);
	  i2cWriteString(str);
	  i2cStop();
}

void LCD_int(int num)
{
	char snum[7];
	i2cStart();
	  i2cWrite(address_write);//78
	  i2cWrite(0x40);
	  itoa(num, snum, 10);
	  i2cWriteString(snum);
	  i2cStop();
}

void LCD_int_SM_N(int num, char M, char N, char sign){
	char snum[16]= {0};
	int tmp = 0;
	char* wsk;
	int i;

	if(sign)
		if(num<0) {
			snum[0]='-';
			num=-num;
		} else{
			snum[0]=' ';
		}
    wsk = snum+M+(N>0?1:0)-(sign?0:1); // jesli sa miejsca po przecinku to doliczamy kropke

    tmp = num;
    for(i=0;i<N;++i){
    	*wsk--='0'+num%10;
    	num/=10;
    }
    if(N>0) *wsk--='.';
    if(M>0) *wsk--='0'+num%10;
    num/=10;
    for(i=1;i<M;++i){
		*wsk--=(num>0?'0'+num%10:' ');
		num/=10;
    }

    i2cStart();
	  i2cWrite(address_write);//78
	  i2cWrite(0x40);
	  i2cWriteString(snum);
	  i2cStop();
}

#else

/***********Write_Command***************/
void Write_Command(uint8_t dat)
{
	SoftI2CStart();
	SoftI2CWriteByte(address_write);//78
	SoftI2CWriteByte(0x80);
	SoftI2CWriteByte(dat);
	SoftI2CStop();
}


/***********Write_Data******************/
void Write_Data(uint8_t dat1)
{
	SoftI2CStart();
	SoftI2CWriteByte(address_write);
	SoftI2CWriteByte(0x40);
	SoftI2CWriteByte(dat1);
	SoftI2CStop();
}

void LCDSSD_init(void)
{
	Write_Command(0x01); //Clear dispaly
	_delay_ms(50);

	Write_Command(0x39); //Function SET DL=1 N=1 DH=0 RE=0 IS=1
	Write_Command(0x06); //Entry mode set I/D=1 S=0
	Write_Command(0x0c); //Display on D=1 C=0 B=0
	Write_Command(0x1b); //Internal OSC BS0=1 F[2:0]=011
	Write_Command(0X55); //Power Icon Contrast set ION=0 BON=1 C[5:4]=01
	Write_Command(0x6d); //Follower control DON=1 Rab[2:0]==101=4.4
	Write_Command(0X7F); //Contrast set VOP=C[3:0]=0011

	Write_Command(0x38); //Function SET DL=1 N=1 DH=0 RE=0 IS=0
	Write_Command(0x3e); //Function set DL=1 N=1 RE=1
	Write_Command(0x02); //Power down mode PD=0
	Write_Command(0x05); //Entry mode set BDC=0 BDS=1
	Write_Command(0x09); //Extended function set FW=0 B/W=0 NW=1
	Write_Command(0x1e); //Double hight/bisa/display-dot shift UD[2:1]=11 BS1=1 DH'=0
	Write_Command(0x80); //Set scroll quantity SQ[5:0]=000000
}

//Note on I2C pull up resistors.
//These should not be too low otherwise the display will
//not pull the SDA line low enough to register an ACK.
//Suggest 10K.
// LCD initialize procedure VALUES FOR 3.3V 4x20 SSD1803A
void LCD_Init(void)
{
	L_RES = 0;
	_delay_ms(10);
//	set_pos(5,0);
	L_RES = 1;
  //set reset low
  //wait 10ms
  //set reset high
  _delay_ms(5);
  Write_Command(0x3a);  //8bit,4line,IS=0,RE=1
  Write_Command(0x1e);  //Set BS1 (1/6 bias)
  Write_Command(0x39);  //8bit,4line,IS=1,RE=0
  Write_Command(0x1c);  //Set BS0 (1/6 bias) + osc
  Write_Command(0x79);  //Set contrast lower 4 bits
  Write_Command(0x5d);  //Set ION, BON, contrast bits 4&5
  Write_Command(0x6d);  //Set DON and amp ratio.
  Write_Command(0x0c);  //Set display on
  Write_Command(0x01);  //Clear display

  set_contrast(contrast);

  _delay_ms(50);
}


//void send_command(unsigned char value)
//{
//  Wire.beginTransmission(address_write>>1);  //send start bit and address_write.
//  Wire.send(0x80);                           //send control byte rs=0 (bit 6)
//  Wire.send(value);                          //send control data
//  Wire.endTransmission();                    //send stop bit (transmitting only starts once this function received)
//}

void set_contrast(unsigned char value)
{
	Write_Command(0x39);
	Write_Command(0x70+(contrast&0x0f));        //bits 0 to 3 of contrast register in position 0 to 3
	Write_Command(0x5c+((contrast&0x30)>>4));   //bits 4 and 5 of contrast register in position 0 and 1
}

void i2cWriteString(char *str)
{
	while(*str)
	{
		SoftI2CWriteByte(*str);
		str++;
	}
}

void LCD_xy(char x, char y)
{
	int pos = 0;
	if(y == 0)
	{
		pos = x + 128;

	}else
	if(y == 1)
	{
		pos = x + 32 + 128;

	}else
	if(y == 2)
	{
		pos = x + 64 + 128;
	}else
	if(y == 3)
	{
		pos = x + 96 + 128;
	}
	Write_Command(pos);
}

void clrscr()
{
	SoftI2CStart();
	SoftI2CWriteByte(address_write);//78
	SoftI2CWriteByte(0x80);
	SoftI2CWriteByte(0x01);
	SoftI2CStop();
}

void LCD_str(char *str)
{
	SoftI2CStart();
	SoftI2CWriteByte(address_write);//78
	SoftI2CWriteByte(0x40);
	i2cWriteString(str);
	SoftI2CStop();
}

void LCD_int(int num)
{
	char snum[7];
	SoftI2CStart();
	SoftI2CWriteByte(address_write);//78
	SoftI2CWriteByte(0x40);
	itoa(num, snum, 10);
	i2cWriteString(snum);
	SoftI2CStop();
}

void LCD_int_SM_N(int num, char M, char N, char sign){
	char snum[16]= {0};
	int tmp = 0;
	char* wsk;
	int i;

	if(sign)
		if(num<0) {
			snum[0]='-';
			num=-num;
		} else{
			snum[0]=' ';
		}
    wsk = snum+M+(N>0?1:0)-(sign?0:1); // jesli sa miejsca po przecinku to doliczamy kropke

    tmp = num;
    for(i=0;i<N;++i){
    	*wsk--='0'+num%10;
    	num/=10;
    }
    if(N>0) *wsk--='.';
    if(M>0) *wsk--='0'+num%10;
    num/=10;
    for(i=1;i<M;++i){
		*wsk--=(num>0?'0'+num%10:' ');
		num/=10;
    }

    SoftI2CStart();
    SoftI2CWriteByte(address_write);//78
    SoftI2CWriteByte(0x40);
	i2cWriteString(snum);
	SoftI2CStop();
}
#endif

