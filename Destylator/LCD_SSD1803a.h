/*
 * LCD_SSD1803a.h
 *
 *  Created on: 09-03-2015
 *      Author: Dawid
 */

#ifndef LCD_SSD1803A_H_
#define LCD_SSD1803A_H_

#define SSD1803_adr 0x0111100
#define address_write 0x78    //address_write including write bit
#define address_read  0x79    //address_write including read bit



void LCD_Init(void);
void send_command(unsigned char value);
void set_contrast(unsigned char value);
void Write_Command(uint8_t dat);
void Write_Data(uint8_t dat1);
void LCDSSD_init(void);
void i2cWriteString(char *str);
void LCD_xy(char x, char y);
void clrscr();
void LCD_str(char *str);
void LCD_int(int num);
void LCD_int_SM_N(int num, char M, char N, char sign);

//Commands


#endif /* LCD_SSD1803A_H_ */
