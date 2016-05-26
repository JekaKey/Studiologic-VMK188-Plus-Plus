#include "velocity.h"
#include "timer.h" 
#include "presets.h"
#include "keyboardscan.h"

/*Velocity curve formulas parameters for white & black keys*/
static double Aw, Bw, Cw, Ab, Bb, Cb;

void calculate_velocity_formula(curve_points_type *cp) {
	double x1, y1, x2, y2, x3, y3, z, t;
	t=(double)(TIMER_TIMPERIOD);
	/*Calculate parameters for white keys*/
	x1 = (double)(cp->xw1) / t; //Calculation in ticks of the timer
	y1 = (double)(cp->yw1);
	x2 = (double)(cp->xw2) / t; //Calculation in ticks of the timer
	y2 = (double)(cp->yw2);
	x3 = (double)(cp->xw3) / t; //Calculation in ticks of the timer
	y3 = (double)(cp->yw3);
	z = (y2 - y1) * (x1 - x3) / ((y3 - y1) * (x1 - x2));
	Bw = (x3 - z * x2) / (z - 1);
	Aw = (y2 - y1) * (x1 + Bw) * (x2 + Bw) / (x1 - x2);
	Cw = y2 - Aw / (x2 + Bw);

	/*Calculate parameters for black keys*/
	x1 = (double)(cp->xb1) / t; //Calculation in ticks of the timer
	y1 = (double)(cp->yb1);
	x2 = (double)(cp->xb2) / t; //Calculation in ticks of the timer
	y2 = (double)(cp->yb2);
	x3 = (double)(cp->xb3) / t; //Calculation in ticks of the timer
	y3 = (double)(cp->yb3);
	z = (y2 - y1) * (x1 - x3) / ((y3 - y1) * (x1 - x2));
	Bb = (x3 - z * x2) / (z - 1);
	Ab = (y2 - y1) * (x1 + Bb) * (x2 + Bb) / (x1 - x2);
	Cb = y2 - Ab / (x2 + Bb);

}



/*Find a color of a key with number "note_num"*/
uint16_t note_color(uint16_t note_num) {
	return (0x01 << (note_num % 12)) & 0b010101001010;//apply piano keyboard octave pattern from right to left
}

uint16_t getVelocity_on(uint16_t tickNum, uint16_t black) {
	uint16_t vel;

	if (black) {
		vel = (uint16_t)(Ab / (tickNum + Bb) + Cb);
	} else {
		vel = (uint16_t)(Aw / (tickNum + Bw) + Cw);
	}
	if (vel > MAXVELOCITY)
		return MAXVELOCITY;
	if (vel <= 0)
		return 0;
	return vel;
}

uint16_t getVelocity_off(uint16_t tickNum, uint16_t black) {
	uint16_t vel;

	if (black) {

		vel = (uint16_t)(Ab * 1.5 / (tickNum));

	} else {

		vel = (uint16_t)(Aw * 1.5 / (tickNum));
	}
	if (vel > MAXVELOCITY)
		return MAXVELOCITY;
	if (vel <= 0)
		return 0;
	return vel;
}
