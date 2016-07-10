#ifndef VELOCITY__H
#define VELOCITY__H

#include "stm32f4xx.h"


#define MAXVELOCITY 0x3FFF
#define tick_factor_white_off tick_factor_white *2
#define min_ticks_white_off tick_factor_white_off / MAXVELOCITY
#define max_ticks_white_off tick_factor_white_off*2

#define tick_factor_black_off tick_factor_black *2
#define min_ticks_black_off tick_factor_black_off / MAXVELOCITY
#define max_ticks_black_off tick_factor_black_off*2



/* The structure describes 3 velocity curve defenition node points separately 
for white and black keys. 
The curve is a hyperbola with the formula: Y=A/(x+B)+C, where
x - time period between two sensors of a key (in microseconds)
y - velocity value 0.0..127.0
For white and black keys formula constants A,B,C are different because there is a 
difference in their mechanical behaviour.
*/

/*Definitions of the  values bounding the range where X-values can be changed*/
#define CURVE_X_FACTOR 100
#define MIN_XW1 8 * CURVE_X_FACTOR
//#define MAX_XW1 60 * CURVE_X_FACTOR
//#define MIN_XW2 90 * CURVE_X_FACTOR
//#define MAX_XW2 200 * CURVE_X_FACTOR
//#define MIN_XW3 700 * CURVE_X_FACTOR
#define MAX_XW3 2500 * CURVE_X_FACTOR
#define MIN_XB1 8 * CURVE_X_FACTOR
//#define MAX_XB1 60 * CURVE_X_FACTOR
//#define MIN_XB2 90 * CURVE_X_FACTOR
//#define MAX_XB2 200 * CURVE_X_FACTOR
//#define MIN_XB3 700 * CURVE_X_FACTOR
#define MAX_XB3 2500 * CURVE_X_FACTOR

/**********************************************/
typedef struct {
	uint16_t Crc; //control sum
	uint32_t xw1;
	uint32_t yw1;
	uint32_t xw2;
	uint32_t yw2;
	uint32_t xw3;
	uint32_t yw3;
	uint32_t xb1;
	uint32_t yb1;
	uint32_t xb2;
	uint32_t yb2;
	uint32_t xb3;
	uint32_t yb3;
	} curve_points_type;


/*The function calculates constants A,B,C for black and white keys*/
void calculate_velocity_formula (curve_points_type *cp);

/*Return a color of a key*/
uint16_t note_color (uint16_t note_num);



/*Function calculate velocity for NoteOn*/
uint16_t getVelocity_on (uint16_t tickNum,  uint16_t black);
/*Function calculate velocity for NoteOff*/	
uint16_t getVelocity_off (uint16_t tickNum,  uint16_t black);
	

	
	
/*Set initial values for the velocity formulas parameters*/	
void velocity_init(void);	


#endif
