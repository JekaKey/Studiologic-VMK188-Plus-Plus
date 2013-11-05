#include "velocity.h"
#include "timer.h" 
#include "presets.h"

int test = 1;

/*Velocity curve formulas parameters for white & black keys*/
static double Aw, Bw, Cw, Ab, Bb, Cb;

void calculate_velocity_formula(curve_points_type *cp) {
	double x1, y1, x2, y2, x3, y3, z;
	/*Calculate parameters for white keys*/
	x1 = cp->xw1 / TIMER_TIMPERIOD; //Calculation in ticks of the timer
	y1 = cp->yw1;
	x2 = cp->xw2 / TIMER_TIMPERIOD; //Calculation in ticks of the timer
	y2 = cp->yw2;
	x3 = cp->xw3 / TIMER_TIMPERIOD; //Calculation in ticks of the timer
	y3 = cp->yw3;
	z = (y2 - y1) * (x1 - x3) / ((y3 - y1) * (x1 - x2));
	Bw = (x3 - z * x2) / (z - 1);
	Aw = (y2 - y1) * (x1 + Bw) * (x2 + Bw) / (x1 - x2);
	Cw = y2 - Aw / (x2 + Bw);

	/*Calculate parameters for black keys*/
	x1 = cp->xb1 / TIMER_TIMPERIOD; //Calculation in ticks of the timer
	y1 = cp->yb1;
	x2 = cp->xb2 / TIMER_TIMPERIOD; //Calculation in ticks of the timer
	y2 = cp->yb2;
	x3 = cp->xb3 / TIMER_TIMPERIOD; //Calculation in ticks of the timer
	y3 = cp->yb3;
	z = (y2 - y1) * (x1 - x3) / ((y3 - y1) * (x1 - x2));
	Bb = (x3 - z * x2) / (z - 1);
	Ab = (y2 - y1) * (x1 + Bb) * (x2 + Bb) / (x1 - x2);
	Cb = y2 - Ab / (x2 + Bb);
}

/*Find a color of a key with number "note_num"*/
uint16_t note_color(uint16_t note_num) {
	//TODO: Reduce 21 for simplifys
	return (0x0001 << ((note_num - 21) % 12)) & 0x0A52;
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

		vel = (uint16_t)(Ab * 2 / (tickNum));

	} else {

		vel = (uint16_t)(Aw * 2 / (tickNum));
	}
	if (vel > MAXVELOCITY)
		return MAXVELOCITY;
	if (vel <= 0)
		return 0;
	return vel;
}

/*This structure normally should be initialized by the info saved in the flash memory.
 Here it reproduces the data from the old Studiologic VMK188 Plus velocity curve  */

static curve_points_type curve_points = { 3600, 125 * 0x80, 20000, 31 * 0x80,
		101400, 1 * 0x80, 3000, 118 * 0x80, 20600, 20 * 0x80, 75000, 1 * 0x80 };

void velocity_init(void) {
	calculate_velocity_formula(&curve_points);
}
