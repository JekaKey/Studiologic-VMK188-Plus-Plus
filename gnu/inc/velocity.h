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
The curve ia a hyperbola with the formula: Y=A/(x+B)+C, where 
x - time period between two sensors of a key (in microseconds)
y - velocity value 0..127
For white and black keys formula constants A,B,C are different because there is a 
difference in their mechanical behaviour.
*/

typedef struct {
	double xw1;
	double yw1;
	double xw2;
	double yw2;
	double xw3;
	double yw3;
	double xb1;
	double yb1;
	double xb2;
	double yb2;
	double xb3;
	double yb3;
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
void init_velocity(void);	
