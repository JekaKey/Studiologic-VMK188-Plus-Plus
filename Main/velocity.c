#include "velocity.h"
#include "timer.h" 


/*Velocity curve formulas parameters for white & black keys*/  
static double Aw, Bw, Cw, Ab, Bb, Cb;

void calculate_velocity_formula (curve_points_type *cp) {
	double x1,y1,x2,y2,x3,y3,z;
	/*Calculate parameters for white keys*/
	x1=cp->xw1/TIMER_TIMPERIOD;
	y1=cp->yw1;
	x2=cp->xw2/TIMER_TIMPERIOD;
	y2=cp->yw2;
	x3=cp->xw3/TIMER_TIMPERIOD;
	y3=cp->yw3;
	z=(y2-y1)*(x1-x3)/((y3-y1)*(x1-x2));
	Bw=(x3-z*x2)/(z-1);
	Aw=(y2-y1)*(x1+Bw)*(x2+Bw)/(x1-x2);
	Cw=y2-Aw/(x2+Bw);

	/*Calculate parameters for black keys*/
	x1=cp->xb1/TIMER_TIMPERIOD;
	y1=cp->yb1;
	x2=cp->xb2/TIMER_TIMPERIOD;
	y2=cp->yb2;
	x3=cp->xb3/TIMER_TIMPERIOD;
	y3=cp->yb3;
	z=(y2-y1)*(x1-x3)/((y3-y1)*(x1-x2));
	Bb=(x3-z*x2)/(z-1);
	Ab=(y2-y1)*(x1+Bb)*(x2+Bb)/(x1-x2);
	Cb=y2-Ab/(x2+Bb);
}


uint16_t note_color (uint16_t note_num) {
	
	return (0x0001 << ((note_num-21) % 12))&0x0A52;	
}

#if defined HIGHRES
uint16_t getVelocity_on (uint16_t tickNum,  uint16_t black) {
   uint16_t vel;
	
	if (black) {
    vel=(uint16_t)(Ab/( tickNum+Bb)+Cb);
  } else {
		vel=(uint16_t)(Aw/( tickNum+Bw)+Cw);
	}	
	if (vel>MAXVELOCITY) return MAXVELOCITY;
	if (vel<=0) return 0;	
	return vel;		
}

uint16_t getVelocity_off (uint16_t tickNum,  uint16_t black) {
uint16_t vel;
	
	if (black) {

    vel=(uint16_t)(Ab*2 / (tickNum));
		
  } else {
 
    vel=(uint16_t)(Aw*2 / (tickNum));		
  }  
	if (vel>MAXVELOCITY) return MAXVELOCITY;
	if (vel<=0) return 0;	
  return vel;
}

#else
uint8_t getVelocity_on (uint16_t tickNum,  uint16_t black) {
   uint8_t vel;
	
	if (black) {
    vel=(uint8_t)(Ab/( tickNum+Bb)+Cb);
  } else {
		vel=(uint8_t)(Aw/( tickNum+Bw)+Cw);
	}	
	if (vel>MAXVELOCITY) return MAXVELOCITY;
	if (vel<=0) return 0;	
	return vel;		
}

uint8_t getVelocity_off (uint16_t tickNum,  uint16_t black) {
uint8_t vel;
	
	if (black) {

    vel=(uint8_t)(Ab / (tickNum));
		
  } else {
 
    vel=(uint8_t)(Aw / (tickNum));		
  }  
	if (vel>MAXVELOCITY) return MAXVELOCITY;
	if (vel<=0) return 0;	
  return vel; 
  }


#endif


/*This structure normally should be initialized by the info saved in the flash memory.
Here it reproduces the data from the old Fatar VMK188 velocity curve  */

#if defined HIGHRES
static curve_points_type curve_points={3600,125*0x80,20000,31*0x80,101400,1*0x80,
                               3000,118*0x80,20600,20*0x80,75000,1*0x80}; 
#else
static curve_points_type curve_points={3600,125,20000,31,101400,1,
                               3000,118,20600,20,75000,1}; 
#endif
   

void init_velocity(void){
	calculate_velocity_formula (&curve_points);
}	
