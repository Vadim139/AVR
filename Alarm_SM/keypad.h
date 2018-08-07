///*===========================================================================================================================
// * keypad.h
// *
// *  Created on: 10-02-2012
// *      Author: Krzysiek Szromek
// *
// *      Obs³uga klawiatury matrycowej 4x4 oraz 4x1 z sygnalem przerwan od zwartych do masy wierszy.
// *      Wyboru trybu dokonuje sie poprzez ewentualne odkomentowanie KEY_MODE_4x1
// *      Wymaga zdefiniowania: ROW_1..4, ROW_DDR_1..4, ROW_R_1..4,
// *      					  COL_1..4, COL_DDR_1..4, COL_R_1..4,
// *      					  KEYINT, KEYINT_DDR, KEYINT_R.
// *
// *  changelog:
// *  16022012 - dodana obsluga trybu 4x1 (po odkomentowaniu definicji KEY_MODE_4x1)
// *===========================================================================================================================*/
//
//#ifndef KEYPAD_H_
//#define KEYPAD_H_
//
//#include "my_defs.h"
//#include "conf.h"
//
////#define KEY_MODE_4x1
//
//#define KEY1 	1
//#define KEY2 	2
//#define KEY3 	3
//
//#ifndef KEY_MODE_4x1
//#define KEYA 	4
//#define KEY4 	5
//#define KEY5 	6
//#define KEY6 	7
//#define KEYB 	8
//#define KEY7 	9
//#define KEY8 	10
//#define KEY9 	11
//#define KEYC 	12
//#define KEYSTAR 13
//#define KEY0 	14
//#define KEYHASH 15
//#define KEYD    16
//
//#define COLS 	0
//#define ROWS 	1
//#else
//#define KEY4 	4
//#endif
//
//volatile uint8_t keypad_state	= 0;
//volatile uint8_t keypad_pressed	= 0;
//
//#ifndef KEY_MODE_4x1
//void keypad_set_input(int dir){
//	ROW_1 = 	~(ROWS ^ dir); 		// set row pins as input with pull-up dir == ROWS
//	ROW_DDR_1 =  (ROWS ^ dir);		// 0 when dir == ROWS
//	ROW_2 = 	~(ROWS ^ dir);		// 1 when dir == ROWS
//	ROW_DDR_2 =  (ROWS ^ dir);
//	ROW_3 = 	~(ROWS ^ dir);
//	ROW_DDR_3 =  (ROWS ^ dir);
//	ROW_4 = 	~(ROWS ^ dir);
//	ROW_DDR_4 =  (ROWS ^ dir);
//
//
//	COL_1 = 	~(COLS ^ dir); 		// set column pins as output low when dir == ROWS
//	COL_DDR_1 =  (COLS ^ dir);		// 1 when dir == ROWS
//	COL_2 = 	~(COLS ^ dir);		// 0 when dir == ROWS
//	COL_DDR_2 =  (COLS ^ dir);
//	COL_3 = 	~(COLS ^ dir);
//	COL_DDR_3 =  (COLS ^ dir);
////	COL_4 = 	~(COLS ^ dir);
////	COL_DDR_4 =  (COLS ^ dir);
//}
//#endif
//
//void keypad_init(){
//
//#ifndef KEY_MODE_4x1
//	keypad_set_input(ROWS);
//#else
//		ROW_1 = 1; 			// set row pins as input with pull-up
//		ROW_DDR_1 = 0;
//		ROW_2 = 1;
//		ROW_DDR_2 = 0;
//		ROW_3 = 1;
//		ROW_DDR_3 = 0;
//		ROW_4 = 1;
//		ROW_DDR_4 = 0;
//#endif
//
//	KEYINT = 1;			// set key interrupt pins as input with pull-up
//	KEYINT_DDR = 0;
//}
//
//
//void keypad_poll(){
//	keypad_state = (ROW_R_4 << 3) | (ROW_R_3 << 2) | (ROW_R_2 << 1) | (ROW_R_1 << 0);
//
//#ifndef KEY_MODE_4x1
//	keypad_set_input(COLS);
//	_delay_ms(20);
//	keypad_state |= (COL_R_3 << 6) | (COL_R_2 << 5) | (COL_R_1 << 4);// (COL_R_4 << 7) |
//
//	keypad_state = ~keypad_state;
//	if( (keypad_state&0x0F) && (keypad_state&0x70) ) {
//		for(int i=0; i<4; ++i) if( keypad_state & (1<<i) ) 		keypad_pressed  = i*4;
//		for(int i=0; i<3; ++i) if( keypad_state & (1<<(i+4)) )  keypad_pressed += i+1;
//	}
//	else keypad_pressed = 0;
//
//	keypad_set_input(ROWS);
//#else
//	keypad_state = ~keypad_state;
//	if( (keypad_state&0x0F) && (keypad_state&0xF0) ) {							// TODO AND czy tez OR?
//			for(int i=0; i<4; ++i) if( keypad_state & (1<<i) ) 		keypad_pressed  = i+1;
//		}
//		else keypad_pressed = 0;
//#endif
//}
//
//#endif /* KEYPAD_H_ */



/*===========================================================================================================================
 * keypad.h
 *
 *  Created on: 10-02-2012
 *      Author: Krzysiek Szromek
 *
 *      Obs³uga klawiatury matrycowej 4x4 oraz 4x1 z sygnalem przerwan od zwartych do masy wierszy.
 *      Wyboru trybu dokonuje sie poprzez ewentualne odkomentowanie KEY_MODE_4x1
 *      Wymaga zdefiniowania: ROW_1..4, ROW_DDR_1..4, ROW_R_1..4,
 *      					  COL_1..4, COL_DDR_1..4, COL_R_1..4,
 *      					  KEYINT, KEYINT_DDR, KEYINT_R.
 *
 *  changelog:
 *  16022012 - dodana obsluga trybu 4x1 (po odkomentowaniu definicji KEY_MODE_4x1)
 *===========================================================================================================================*/

#ifndef KEYPAD_H_
#define KEYPAD_H_

//#include "my_defs.h"
#include "main.h"
//#include "sbit.h"

//#define KEY_MODE_4x1

#define KEY1 	1
#define KEY2 	2
#define KEY3 	3
#define KEY4 	4

#ifndef KEY_MODE_4x1
//#define KEYA 	4
//#define KEY4 	5
#define KEY5 	5//6
#define KEY6 	6//7
//#define KEYB 	8
#define KEY7 	7//9
#define KEY8 	8//10
#define KEY9 	9//11
//#define KEYC 	12
#define KEYSTAR 10//13
#define KEY0 	11//14
#define KEYHASH 12//15
//#define KEYD    16

#define COLS 	0
#define ROWS 	1
#endif

volatile uint8_t keypad_state	= 0;
volatile uint8_t keypad_pressed	= 0;

#ifndef KEY_MODE_4x1
void keypad_set_input(int dir){
	ROW_1 = 	~(ROWS ^ dir); 		// set row pins as input with pull-up dir == ROWS
	ROW_DDR_1 =  (ROWS ^ dir);		// 0 when dir == ROWS
	ROW_2 = 	~(ROWS ^ dir);		// 1 when dir == ROWS
	ROW_DDR_2 =  (ROWS ^ dir);
	ROW_3 = 	~(ROWS ^ dir);
	ROW_DDR_3 =  (ROWS ^ dir);
	ROW_4 = 	~(ROWS ^ dir);
	ROW_DDR_4 =  (ROWS ^ dir);


	COL_1 = 	~(COLS ^ dir); 		// set column pins as output low when dir == ROWS
	COL_DDR_1 =  (COLS ^ dir);		// 1 when dir == ROWS
	COL_2 = 	~(COLS ^ dir);		// 0 when dir == ROWS
	COL_DDR_2 =  (COLS ^ dir);
	COL_3 = 	~(COLS ^ dir);
	COL_DDR_3 =  (COLS ^ dir);
//	COL_4 = 	~(COLS ^ dir);
//	COL_DDR_4 =  (COLS ^ dir);
}
#endif

void keypad_init(){

#ifndef KEY_MODE_4x1
	keypad_set_input(ROWS);
#else
		ROW_1 = 1; 			// set row pins as input with pull-up
		ROW_DDR_1 = 0;
		ROW_2 = 1;
		ROW_DDR_2 = 0;
		ROW_3 = 1;
		ROW_DDR_3 = 0;
		ROW_4 = 1;
		ROW_DDR_4 = 0;
#endif

	KEYINT = 1;			// set key interrupt pins as input with pull-up
	KEYINT_DDR = 0;
}


void keypad_poll(){
	keypad_state = (ROW_R_4 << 3) | (ROW_R_3 << 2) | (ROW_R_2 << 1) | (ROW_R_1 << 0);

#ifndef KEY_MODE_4x1
	keypad_set_input(COLS);
	_delay_ms(20);
	keypad_state |= (COL_R_3 << 6) | (COL_R_2 << 5) | (COL_R_1 << 4); //(COL_R_4 << 7) |

	keypad_state = ~keypad_state;
	if( (keypad_state&0x0F) && (keypad_state&0x70) ) {
		for(int i=0; i<4; ++i) if( keypad_state & (1<<i) ) 		keypad_pressed  = i*3;
		for(int i=0; i<3; ++i) if( keypad_state & (1<<(i+4)) )  keypad_pressed += i+1;
	}
	else keypad_pressed = 0;

	keypad_set_input(ROWS);
#else
	keypad_state = ~keypad_state;
	if( (keypad_state&0x0F) && (keypad_state&0xF0) ) {							// TODO AND czy tez OR?
			for(int i=0; i<4; ++i) if( keypad_state & (1<<i) ) 		keypad_pressed  = i+1;
		}
		else keypad_pressed = 0;
#endif
}

#endif /* KEYPAD_H_ */
