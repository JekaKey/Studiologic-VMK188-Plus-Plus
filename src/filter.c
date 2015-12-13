#include "filter.h"



filter_storage_t filter_storage[NUMBER_OF_BUFFERS];


/****Simple median filter only for 3 values*****/
uint16_t median(uint16_t* a) {
	if (a[0] < a[1]) {
		if (a[1] < a[2]) {
			return a[1];
		} else {
			if (a[0] < a[2]) {
				return a[0];
			} else {
				return a[2];
			}
		}
	} else {
		if (a[1] > a[2]) {
			return a[1];
		} else {
			if (a[0] > a[2]) {
				return a[2];
			} else {
				return a[0];
			}
		}

	}

}



void median_filter_init(void){
	for(uint8_t i=0; i<NUMBER_OF_BUFFERS; i++){
		filter_storage[i].datpoint=filter_storage[i].buffer;
		filter_storage[i].big.point=&(filter_storage[i].small);
		filter_storage[i].big.value = 0;
		filter_storage[i].small.value = STOPPER;
		filter_storage[i].small.point = NULL_POINTER;
		for (uint8_t j=0; j<MEDIAN_FILTER_SIZE; j++){
			filter_storage[i].buffer[j].value=0;
			filter_storage[i].buffer[j].point=NULL_POINTER;
		}
	}
}


uint16_t median_filter(uint16_t value, filter_storage_t * buff) {
	struct pair *successor; /* Pointer to successor of replaced data item */
	struct pair *scan; /* Pointer used to scan down the sorted list */
	struct pair *scanold; /* Previous value of scan */
	struct pair *median; /* Pointer to median */
	uint16_t i;

	if (value == STOPPER) {
		value = STOPPER + 1; /* No stoppers allowed. */
	}

	if ((++buff->datpoint - buff->buffer) >= MEDIAN_FILTER_SIZE) {
		buff->datpoint = buff->buffer; /* Increment and wrap data in pointer.*/
	}

	buff->datpoint->value = value; /* Copy in new value */
	successor = buff->datpoint->point; /* Save pointer to old value's successor */
	median = &(buff->big); /* Median initially to first in chain */
	scanold = NULL_POINTER; /* Scanold initially null. */
	scan = &(buff->big); /* Points to pointer to first (largest) datum in chain */

	/* Handle chain-out of first item in chain as special case */
	if (scan->point == buff->datpoint) {
		scan->point = successor;
	}
	scanold = scan; /* Save this pointer and   */
	scan = scan->point; /* step down chain */

	/* Loop through the chain, normal loop exit via break. */
	for (i = 0; i < MEDIAN_FILTER_SIZE; ++i) {
		/* Handle odd-numbered item in chain  */
		if (scan->point == buff->datpoint) {
			scan->point = successor; /* Chain out the old value.*/
		}

		if (scan->value < value) /* If value is larger than scanned value,*/
		{
			buff->datpoint->point = scanold->point; /* Chain it in here.  */
			scanold->point = buff->datpoint; /* Mark it chained in. */
			value = STOPPER;
		};

		/* Step median pointer down chain after doing odd-numbered element */
		median = median->point; /* Step median pointer.  */
		if (scan == &(buff->small)) {
			break; /* Break at end of chain  */
		}
		scanold = scan; /* Save this pointer and   */
		scan = scan->point; /* step down chain */

		/* Handle even-numbered item in chain.  */
		if (scan->point == buff->datpoint) {
			scan->point = successor;
		}

		if (scan->value < value) {
			buff->datpoint->point = scanold->point;
			scanold->point = buff->datpoint;
			value = STOPPER;
		}

		if (scan == &(buff->small)) {
			break;
		}

		scanold = scan;
		scan = scan->point;
	}
	return median->value;
}


