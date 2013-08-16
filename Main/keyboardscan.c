#define STM32F40XX

#include "keyboardscan.h"

/* Current port state, first contact */
uint16_t d11 = 0x00;
uint16_t d12 = 0x00;
uint16_t d13 = 0x00;
uint16_t d14 = 0x00;
uint16_t d15 = 0x00;
uint16_t d16 = 0x00;
uint16_t d17 = 0x00;
uint16_t d18 = 0x00;
uint16_t d19 = 0x00;
uint16_t d110 = 0x00;
uint16_t d111 = 0x00;

/* Current port state, second contact */
uint16_t d21 = 0x00;
uint16_t d22 = 0x00;
uint16_t d23 = 0x00;
uint16_t d24 = 0x00;
uint16_t d25 = 0x00;
uint16_t d26 = 0x00;
uint16_t d27 = 0x00;
uint16_t d28 = 0x00;
uint16_t d29 = 0x00;
uint16_t d210 = 0x00;
uint16_t d211 = 0x00;

/* Last state key send in chunk */
uint16_t lastState1 = 0x00;
uint16_t lastState2 = 0x00;
uint16_t lastState3 = 0x00;
uint16_t lastState4 = 0x00;
uint16_t lastState5 = 0x00;
uint16_t lastState6 = 0x00;
uint16_t lastState7 = 0x00;
uint16_t lastState8 = 0x00;
uint16_t lastState9 = 0x00;
uint16_t lastState10 = 0x00;
uint16_t lastState11 = 0x00;


/* Variables */
uint16_t duration_note1 = 0;
uint16_t duration_note2 = 0;
uint16_t duration_note3 = 0;
uint16_t duration_note4 = 0;
uint16_t duration_note5 = 0;
uint16_t duration_note6 = 0;
uint16_t duration_note7 = 0;
uint16_t duration_note8 = 0;
uint16_t duration_note9 = 0;
uint16_t duration_note10 = 0;
uint16_t duration_note11 = 0;
uint16_t duration_note12 = 0;
uint16_t duration_note13 = 0;
uint16_t duration_note14 = 0;
uint16_t duration_note15 = 0;
uint16_t duration_note16 = 0;
uint16_t duration_note17 = 0;
uint16_t duration_note18 = 0;
uint16_t duration_note19 = 0;
uint16_t duration_note20 = 0;
uint16_t duration_note21 = 0;
uint16_t duration_note22 = 0;
uint16_t duration_note23 = 0;
uint16_t duration_note24 = 0;
uint16_t duration_note25 = 0;
uint16_t duration_note26 = 0;
uint16_t duration_note27 = 0;
uint16_t duration_note28 = 0;
uint16_t duration_note29 = 0;
uint16_t duration_note30 = 0;
uint16_t duration_note31 = 0;
uint16_t duration_note32 = 0;
uint16_t duration_note33 = 0;
uint16_t duration_note34 = 0;
uint16_t duration_note35 = 0;
uint16_t duration_note36 = 0;
uint16_t duration_note37 = 0;
uint16_t duration_note38 = 0;
uint16_t duration_note39 = 0;
uint16_t duration_note40 = 0;
uint16_t duration_note41 = 0;
uint16_t duration_note42 = 0;
uint16_t duration_note43 = 0;
uint16_t duration_note44 = 0;
uint16_t duration_note45 = 0;
uint16_t duration_note46 = 0;
uint16_t duration_note47 = 0;
uint16_t duration_note48 = 0;
uint16_t duration_note49 = 0;
uint16_t duration_note50 = 0;
uint16_t duration_note51 = 0;
uint16_t duration_note52 = 0;
uint16_t duration_note53 = 0;
uint16_t duration_note54 = 0;
uint16_t duration_note55 = 0;
uint16_t duration_note56 = 0;
uint16_t duration_note57 = 0;
uint16_t duration_note58 = 0;
uint16_t duration_note59 = 0;
uint16_t duration_note60 = 0;
uint16_t duration_note61 = 0;
uint16_t duration_note62 = 0;
uint16_t duration_note63 = 0;
uint16_t duration_note64 = 0;
uint16_t duration_note65 = 0;
uint16_t duration_note66 = 0;
uint16_t duration_note67 = 0;
uint16_t duration_note68 = 0;
uint16_t duration_note69 = 0;
uint16_t duration_note70 = 0;
uint16_t duration_note71 = 0;
uint16_t duration_note72 = 0;
uint16_t duration_note73 = 0;
uint16_t duration_note74 = 0;
uint16_t duration_note75 = 0;
uint16_t duration_note76 = 0;
uint16_t duration_note77 = 0;
uint16_t duration_note78 = 0;
uint16_t duration_note79 = 0;
uint16_t duration_note80 = 0;
uint16_t duration_note81 = 0;
uint16_t duration_note82 = 0;
uint16_t duration_note83 = 0;
uint16_t duration_note84 = 0;
uint16_t duration_note85 = 0;
uint16_t duration_note86 = 0;
uint16_t duration_note87 = 0;
uint16_t duration_note88 = 0;

uint8_t curNote;
uint16_t duration;

//Пересчет тиков в велосити
//velocity=round(a/(x1+b)+c)
uint8_t getVelocity(uint16_t tickNum) {

    uint8_t velocity;

    if (tickNum >= 990)
        return 0;

    if (tickNum <= 36)
        return 127;

    velocity = ((10500 / (tickNum + 41)) - 9);

    return velocity;
}

/**
* Расчет velocity и запись в midi буффер
*/
void checkNoteArray(void) {
    //Проверяем буффер считанных клавиш с длительностями

    if (FIFO_COUNT(notes) != 0) {

        curNote = FIFO_FRONT(notes);
        duration = FIFO_FRONT(durations);

        FIFO_POP(durations);
        FIFO_POP(notes);

        if ((curNote & 0x80) == 0) {
            sendNoteOn(curNote, getVelocity(duration), 0);
        } else {
            sendNoteOff(curNote & 0x7F, 70, 0);
        }

    }
}

void readKeyState(void) {

      /* 1 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_15; 
    Delay(KEY_SWITCH_DELAY); 
    d11 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_15; 
    Delay(KEY_SWITCH_DELAY);  
    if (d11&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_14; 
    Delay(KEY_SWITCH_DELAY);  
    d21 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_14;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d21=0;
     }
	/*1 key */

      if (d11 & 0x0001) {
       duration_note1++;

     	   if (d21&0x0001) { 

		         if (lastState1&0x0001) {
		          	duration_note1 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,21);      
			          FIFO_PUSH(durations, duration_note1);

		        	  lastState1 ^=0x0001;   
		           	duration_note1 = 0;  
	          	}

         	}

         }else if (lastState1&0x0001) {	
             FIFO_PUSH(notes,149); 
		          FIFO_PUSH(durations, duration_note1); 
	          	lastState1 &= 0xFFFE; 
	            duration_note1 = 0;
	         }else {
		          duration_note1 = 0;
          }

	/*2 key */

      if (d11 & 0x0002) {
       duration_note2++;

     	   if (d21&0x0002) { 

		         if (lastState1&0x0002) {
		          	duration_note2 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,22);      
			          FIFO_PUSH(durations, duration_note2);

		        	  lastState1 ^=0x0002;   
		           	duration_note2 = 0;  
	          	}

         	}

         }else if (lastState1&0x0002) {	
             FIFO_PUSH(notes,150); 
		          FIFO_PUSH(durations, duration_note2); 
	          	lastState1 &= 0xFFFD; 
	            duration_note2 = 0;
	         }else {
		          duration_note2 = 0;
          }

	/*3 key */

      if (d11 & 0x0004) {
       duration_note3++;

     	   if (d21&0x0004) { 

		         if (lastState1&0x0004) {
		          	duration_note3 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,23);      
			          FIFO_PUSH(durations, duration_note3);

		        	  lastState1 ^=0x0004;   
		           	duration_note3 = 0;  
	          	}

         	}

         }else if (lastState1&0x0004) {	
             FIFO_PUSH(notes,151); 
		          FIFO_PUSH(durations, duration_note3); 
	          	lastState1 &= 0xFFFB; 
	            duration_note3 = 0;
	         }else {
		          duration_note3 = 0;
          }

	/*4 key */

      if (d11 & 0x0008) {
       duration_note4++;

     	   if (d21&0x0008) { 

		         if (lastState1&0x0008) {
		          	duration_note4 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,24);      
			          FIFO_PUSH(durations, duration_note4);

		        	  lastState1 ^=0x0008;   
		           	duration_note4 = 0;  
	          	}

         	}

         }else if (lastState1&0x0008) {	
             FIFO_PUSH(notes,152); 
		          FIFO_PUSH(durations, duration_note4); 
	          	lastState1 &= 0xFFF7; 
	            duration_note4 = 0;
	         }else {
		          duration_note4 = 0;
          }

	/*5 key */

      if (d11 & 0x0010) {
       duration_note5++;

     	   if (d21&0x0010) { 

		         if (lastState1&0x0010) {
		          	duration_note5 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,25);      
			          FIFO_PUSH(durations, duration_note5);

		        	  lastState1 ^=0x0010;   
		           	duration_note5 = 0;  
	          	}

         	}

         }else if (lastState1&0x0010) {	
             FIFO_PUSH(notes,153); 
		          FIFO_PUSH(durations, duration_note5); 
	          	lastState1 &= 0xFFEF; 
	            duration_note5 = 0;
	         }else {
		          duration_note5 = 0;
          }

	/*6 key */

      if (d11 & 0x0020) {
       duration_note6++;

     	   if (d21&0x0020) { 

		         if (lastState1&0x0020) {
		          	duration_note6 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,26);      
			          FIFO_PUSH(durations, duration_note6);

		        	  lastState1 ^=0x0020;   
		           	duration_note6 = 0;  
	          	}

         	}

         }else if (lastState1&0x0020) {	
             FIFO_PUSH(notes,154); 
		          FIFO_PUSH(durations, duration_note6); 
	          	lastState1 &= 0xFFDF; 
	            duration_note6 = 0;
	         }else {
		          duration_note6 = 0;
          }

	/*7 key */

      if (d11 & 0x0040) {
       duration_note7++;

     	   if (d21&0x0040) { 

		         if (lastState1&0x0040) {
		          	duration_note7 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,27);      
			          FIFO_PUSH(durations, duration_note7);

		        	  lastState1 ^=0x0040;   
		           	duration_note7 = 0;  
	          	}

         	}

         }else if (lastState1&0x0040) {	
             FIFO_PUSH(notes,155); 
		          FIFO_PUSH(durations, duration_note7); 
	          	lastState1 &= 0xFFBF; 
	            duration_note7 = 0;
	         }else {
		          duration_note7 = 0;
          }

	/*8 key */

      if (d11 & 0x0080) {
       duration_note8++;

     	   if (d21&0x0080) { 

		         if (lastState1&0x0080) {
		          	duration_note8 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,28);      
			          FIFO_PUSH(durations, duration_note8);

		        	  lastState1 ^=0x0080;   
		           	duration_note8 = 0;  
	          	}

         	}

         }else if (lastState1&0x0080) {	
             FIFO_PUSH(notes,156); 
		          FIFO_PUSH(durations, duration_note8); 
	          	lastState1 &= 0xFF7F; 
	            duration_note8 = 0;
	         }else {
		          duration_note8 = 0;
          }

      /* 2 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_11; 
    Delay(KEY_SWITCH_DELAY); 
    d12 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_11; 
    Delay(KEY_SWITCH_DELAY);  
    if (d12&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_10; 
    Delay(KEY_SWITCH_DELAY);  
    d22 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_10;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d22=0;
     }
	/*9 key */

      if (d12 & 0x0001) {
       duration_note9++;

     	   if (d22&0x0001) { 

		         if (lastState2&0x0001) {
		          	duration_note9 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,29);      
			          FIFO_PUSH(durations, duration_note9);

		        	  lastState2 ^=0x0001;   
		           	duration_note9 = 0;  
	          	}

         	}

         }else if (lastState2&0x0001) {	
             FIFO_PUSH(notes,157); 
		          FIFO_PUSH(durations, duration_note9); 
	          	lastState2 &= 0xFFFE; 
	            duration_note9 = 0;
	         }else {
		          duration_note9 = 0;
          }

	/*10 key */

      if (d12 & 0x0002) {
       duration_note10++;

     	   if (d22&0x0002) { 

		         if (lastState2&0x0002) {
		          	duration_note10 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,30);      
			          FIFO_PUSH(durations, duration_note10);

		        	  lastState2 ^=0x0002;   
		           	duration_note10 = 0;  
	          	}

         	}

         }else if (lastState2&0x0002) {	
             FIFO_PUSH(notes,158); 
		          FIFO_PUSH(durations, duration_note10); 
	          	lastState2 &= 0xFFFD; 
	            duration_note10 = 0;
	         }else {
		          duration_note10 = 0;
          }

	/*11 key */

      if (d12 & 0x0004) {
       duration_note11++;

     	   if (d22&0x0004) { 

		         if (lastState2&0x0004) {
		          	duration_note11 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,31);      
			          FIFO_PUSH(durations, duration_note11);

		        	  lastState2 ^=0x0004;   
		           	duration_note11 = 0;  
	          	}

         	}

         }else if (lastState2&0x0004) {	
             FIFO_PUSH(notes,159); 
		          FIFO_PUSH(durations, duration_note11); 
	          	lastState2 &= 0xFFFB; 
	            duration_note11 = 0;
	         }else {
		          duration_note11 = 0;
          }

	/*12 key */

      if (d12 & 0x0008) {
       duration_note12++;

     	   if (d22&0x0008) { 

		         if (lastState2&0x0008) {
		          	duration_note12 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,32);      
			          FIFO_PUSH(durations, duration_note12);

		        	  lastState2 ^=0x0008;   
		           	duration_note12 = 0;  
	          	}

         	}

         }else if (lastState2&0x0008) {	
             FIFO_PUSH(notes,160); 
		          FIFO_PUSH(durations, duration_note12); 
	          	lastState2 &= 0xFFF7; 
	            duration_note12 = 0;
	         }else {
		          duration_note12 = 0;
          }

	/*13 key */

      if (d12 & 0x0010) {
       duration_note13++;

     	   if (d22&0x0010) { 

		         if (lastState2&0x0010) {
		          	duration_note13 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,33);      
			          FIFO_PUSH(durations, duration_note13);

		        	  lastState2 ^=0x0010;   
		           	duration_note13 = 0;  
	          	}

         	}

         }else if (lastState2&0x0010) {	
             FIFO_PUSH(notes,161); 
		          FIFO_PUSH(durations, duration_note13); 
	          	lastState2 &= 0xFFEF; 
	            duration_note13 = 0;
	         }else {
		          duration_note13 = 0;
          }

	/*14 key */

      if (d12 & 0x0020) {
       duration_note14++;

     	   if (d22&0x0020) { 

		         if (lastState2&0x0020) {
		          	duration_note14 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,34);      
			          FIFO_PUSH(durations, duration_note14);

		        	  lastState2 ^=0x0020;   
		           	duration_note14 = 0;  
	          	}

         	}

         }else if (lastState2&0x0020) {	
             FIFO_PUSH(notes,162); 
		          FIFO_PUSH(durations, duration_note14); 
	          	lastState2 &= 0xFFDF; 
	            duration_note14 = 0;
	         }else {
		          duration_note14 = 0;
          }

	/*15 key */

      if (d12 & 0x0040) {
       duration_note15++;

     	   if (d22&0x0040) { 

		         if (lastState2&0x0040) {
		          	duration_note15 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,35);      
			          FIFO_PUSH(durations, duration_note15);

		        	  lastState2 ^=0x0040;   
		           	duration_note15 = 0;  
	          	}

         	}

         }else if (lastState2&0x0040) {	
             FIFO_PUSH(notes,163); 
		          FIFO_PUSH(durations, duration_note15); 
	          	lastState2 &= 0xFFBF; 
	            duration_note15 = 0;
	         }else {
		          duration_note15 = 0;
          }

	/*16 key */

      if (d12 & 0x0080) {
       duration_note16++;

     	   if (d22&0x0080) { 

		         if (lastState2&0x0080) {
		          	duration_note16 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,36);      
			          FIFO_PUSH(durations, duration_note16);

		        	  lastState2 ^=0x0080;   
		           	duration_note16 = 0;  
	          	}

         	}

         }else if (lastState2&0x0080) {	
             FIFO_PUSH(notes,164); 
		          FIFO_PUSH(durations, duration_note16); 
	          	lastState2 &= 0xFF7F; 
	            duration_note16 = 0;
	         }else {
		          duration_note16 = 0;
          }

      /* 3 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_13; 
    Delay(KEY_SWITCH_DELAY); 
    d13 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_13; 
    Delay(KEY_SWITCH_DELAY);  
    if (d13&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_12; 
    Delay(KEY_SWITCH_DELAY);  
    d23 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_12;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d23=0;
     }
	/*17 key */

      if (d13 & 0x0001) {
       duration_note17++;

     	   if (d23&0x0001) { 

		         if (lastState3&0x0001) {
		          	duration_note17 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,37);      
			          FIFO_PUSH(durations, duration_note17);

		        	  lastState3 ^=0x0001;   
		           	duration_note17 = 0;  
	          	}

         	}

         }else if (lastState3&0x0001) {	
             FIFO_PUSH(notes,165); 
		          FIFO_PUSH(durations, duration_note17); 
	          	lastState3 &= 0xFFFE; 
	            duration_note17 = 0;
	         }else {
		          duration_note17 = 0;
          }

	/*18 key */

      if (d13 & 0x0002) {
       duration_note18++;

     	   if (d23&0x0002) { 

		         if (lastState3&0x0002) {
		          	duration_note18 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,38);      
			          FIFO_PUSH(durations, duration_note18);

		        	  lastState3 ^=0x0002;   
		           	duration_note18 = 0;  
	          	}

         	}

         }else if (lastState3&0x0002) {	
             FIFO_PUSH(notes,166); 
		          FIFO_PUSH(durations, duration_note18); 
	          	lastState3 &= 0xFFFD; 
	            duration_note18 = 0;
	         }else {
		          duration_note18 = 0;
          }

	/*19 key */

      if (d13 & 0x0004) {
       duration_note19++;

     	   if (d23&0x0004) { 

		         if (lastState3&0x0004) {
		          	duration_note19 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,39);      
			          FIFO_PUSH(durations, duration_note19);

		        	  lastState3 ^=0x0004;   
		           	duration_note19 = 0;  
	          	}

         	}

         }else if (lastState3&0x0004) {	
             FIFO_PUSH(notes,167); 
		          FIFO_PUSH(durations, duration_note19); 
	          	lastState3 &= 0xFFFB; 
	            duration_note19 = 0;
	         }else {
		          duration_note19 = 0;
          }

	/*20 key */

      if (d13 & 0x0008) {
       duration_note20++;

     	   if (d23&0x0008) { 

		         if (lastState3&0x0008) {
		          	duration_note20 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,40);      
			          FIFO_PUSH(durations, duration_note20);

		        	  lastState3 ^=0x0008;   
		           	duration_note20 = 0;  
	          	}

         	}

         }else if (lastState3&0x0008) {	
             FIFO_PUSH(notes,168); 
		          FIFO_PUSH(durations, duration_note20); 
	          	lastState3 &= 0xFFF7; 
	            duration_note20 = 0;
	         }else {
		          duration_note20 = 0;
          }

	/*21 key */

      if (d13 & 0x0010) {
       duration_note21++;

     	   if (d23&0x0010) { 

		         if (lastState3&0x0010) {
		          	duration_note21 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,41);      
			          FIFO_PUSH(durations, duration_note21);

		        	  lastState3 ^=0x0010;   
		           	duration_note21 = 0;  
	          	}

         	}

         }else if (lastState3&0x0010) {	
             FIFO_PUSH(notes,169); 
		          FIFO_PUSH(durations, duration_note21); 
	          	lastState3 &= 0xFFEF; 
	            duration_note21 = 0;
	         }else {
		          duration_note21 = 0;
          }

	/*22 key */

      if (d13 & 0x0020) {
       duration_note22++;

     	   if (d23&0x0020) { 

		         if (lastState3&0x0020) {
		          	duration_note22 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,42);      
			          FIFO_PUSH(durations, duration_note22);

		        	  lastState3 ^=0x0020;   
		           	duration_note22 = 0;  
	          	}

         	}

         }else if (lastState3&0x0020) {	
             FIFO_PUSH(notes,170); 
		          FIFO_PUSH(durations, duration_note22); 
	          	lastState3 &= 0xFFDF; 
	            duration_note22 = 0;
	         }else {
		          duration_note22 = 0;
          }

	/*23 key */

      if (d13 & 0x0040) {
       duration_note23++;

     	   if (d23&0x0040) { 

		         if (lastState3&0x0040) {
		          	duration_note23 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,43);      
			          FIFO_PUSH(durations, duration_note23);

		        	  lastState3 ^=0x0040;   
		           	duration_note23 = 0;  
	          	}

         	}

         }else if (lastState3&0x0040) {	
             FIFO_PUSH(notes,171); 
		          FIFO_PUSH(durations, duration_note23); 
	          	lastState3 &= 0xFFBF; 
	            duration_note23 = 0;
	         }else {
		          duration_note23 = 0;
          }

	/*24 key */

      if (d13 & 0x0080) {
       duration_note24++;

     	   if (d23&0x0080) { 

		         if (lastState3&0x0080) {
		          	duration_note24 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,44);      
			          FIFO_PUSH(durations, duration_note24);

		        	  lastState3 ^=0x0080;   
		           	duration_note24 = 0;  
	          	}

         	}

         }else if (lastState3&0x0080) {	
             FIFO_PUSH(notes,172); 
		          FIFO_PUSH(durations, duration_note24); 
	          	lastState3 &= 0xFF7F; 
	            duration_note24 = 0;
	         }else {
		          duration_note24 = 0;
          }

      /* 4 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_15; 
    Delay(KEY_SWITCH_DELAY); 
    d14 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_15; 
    Delay(KEY_SWITCH_DELAY);  
    if (d14&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_14; 
    Delay(KEY_SWITCH_DELAY);  
    d24 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_14;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d24=0;
     }
	/*25 key */

      if (d14 & 0x0001) {
       duration_note25++;

     	   if (d24&0x0001) { 

		         if (lastState4&0x0001) {
		          	duration_note25 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,45);      
			          FIFO_PUSH(durations, duration_note25);

		        	  lastState4 ^=0x0001;   
		           	duration_note25 = 0;  
	          	}

         	}

         }else if (lastState4&0x0001) {	
             FIFO_PUSH(notes,173); 
		          FIFO_PUSH(durations, duration_note25); 
	          	lastState4 &= 0xFFFE; 
	            duration_note25 = 0;
	         }else {
		          duration_note25 = 0;
          }

	/*26 key */

      if (d14 & 0x0002) {
       duration_note26++;

     	   if (d24&0x0002) { 

		         if (lastState4&0x0002) {
		          	duration_note26 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,46);      
			          FIFO_PUSH(durations, duration_note26);

		        	  lastState4 ^=0x0002;   
		           	duration_note26 = 0;  
	          	}

         	}

         }else if (lastState4&0x0002) {	
             FIFO_PUSH(notes,174); 
		          FIFO_PUSH(durations, duration_note26); 
	          	lastState4 &= 0xFFFD; 
	            duration_note26 = 0;
	         }else {
		          duration_note26 = 0;
          }

	/*27 key */

      if (d14 & 0x0004) {
       duration_note27++;

     	   if (d24&0x0004) { 

		         if (lastState4&0x0004) {
		          	duration_note27 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,47);      
			          FIFO_PUSH(durations, duration_note27);

		        	  lastState4 ^=0x0004;   
		           	duration_note27 = 0;  
	          	}

         	}

         }else if (lastState4&0x0004) {	
             FIFO_PUSH(notes,175); 
		          FIFO_PUSH(durations, duration_note27); 
	          	lastState4 &= 0xFFFB; 
	            duration_note27 = 0;
	         }else {
		          duration_note27 = 0;
          }

	/*28 key */

      if (d14 & 0x0008) {
       duration_note28++;

     	   if (d24&0x0008) { 

		         if (lastState4&0x0008) {
		          	duration_note28 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,48);      
			          FIFO_PUSH(durations, duration_note28);

		        	  lastState4 ^=0x0008;   
		           	duration_note28 = 0;  
	          	}

         	}

         }else if (lastState4&0x0008) {	
             FIFO_PUSH(notes,176); 
		          FIFO_PUSH(durations, duration_note28); 
	          	lastState4 &= 0xFFF7; 
	            duration_note28 = 0;
	         }else {
		          duration_note28 = 0;
          }

	/*29 key */

      if (d14 & 0x0010) {
       duration_note29++;

     	   if (d24&0x0010) { 

		         if (lastState4&0x0010) {
		          	duration_note29 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,49);      
			          FIFO_PUSH(durations, duration_note29);

		        	  lastState4 ^=0x0010;   
		           	duration_note29 = 0;  
	          	}

         	}

         }else if (lastState4&0x0010) {	
             FIFO_PUSH(notes,177); 
		          FIFO_PUSH(durations, duration_note29); 
	          	lastState4 &= 0xFFEF; 
	            duration_note29 = 0;
	         }else {
		          duration_note29 = 0;
          }

	/*30 key */

      if (d14 & 0x0020) {
       duration_note30++;

     	   if (d24&0x0020) { 

		         if (lastState4&0x0020) {
		          	duration_note30 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,50);      
			          FIFO_PUSH(durations, duration_note30);

		        	  lastState4 ^=0x0020;   
		           	duration_note30 = 0;  
	          	}

         	}

         }else if (lastState4&0x0020) {	
             FIFO_PUSH(notes,178); 
		          FIFO_PUSH(durations, duration_note30); 
	          	lastState4 &= 0xFFDF; 
	            duration_note30 = 0;
	         }else {
		          duration_note30 = 0;
          }

	/*31 key */

      if (d14 & 0x0040) {
       duration_note31++;

     	   if (d24&0x0040) { 

		         if (lastState4&0x0040) {
		          	duration_note31 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,51);      
			          FIFO_PUSH(durations, duration_note31);

		        	  lastState4 ^=0x0040;   
		           	duration_note31 = 0;  
	          	}

         	}

         }else if (lastState4&0x0040) {	
             FIFO_PUSH(notes,179); 
		          FIFO_PUSH(durations, duration_note31); 
	          	lastState4 &= 0xFFBF; 
	            duration_note31 = 0;
	         }else {
		          duration_note31 = 0;
          }

	/*32 key */

      if (d14 & 0x0080) {
       duration_note32++;

     	   if (d24&0x0080) { 

		         if (lastState4&0x0080) {
		          	duration_note32 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,52);      
			          FIFO_PUSH(durations, duration_note32);

		        	  lastState4 ^=0x0080;   
		           	duration_note32 = 0;  
	          	}

         	}

         }else if (lastState4&0x0080) {	
             FIFO_PUSH(notes,180); 
		          FIFO_PUSH(durations, duration_note32); 
	          	lastState4 &= 0xFF7F; 
	            duration_note32 = 0;
	         }else {
		          duration_note32 = 0;
          }

      /* 5 chunk */ 

    GPIOD->BSRRH = GPIO_Pin_9; 
    Delay(KEY_SWITCH_DELAY); 
    d15 = ~GPIOA->IDR; //Read port state first contact 
    GPIOD->BSRRL = GPIO_Pin_9; 
    Delay(KEY_SWITCH_DELAY);  
    if (d15&0x00FF){  

    GPIOD->BSRRH = GPIO_Pin_8; 
    Delay(KEY_SWITCH_DELAY);  
    d25 = ~GPIOA->IDR; //Read port state second contact 
    GPIOD->BSRRL = GPIO_Pin_8;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d25=0;
     }
	/*33 key */

      if (d15 & 0x0001) {
       duration_note33++;

     	   if (d25&0x0001) { 

		         if (lastState5&0x0001) {
		          	duration_note33 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,53);      
			          FIFO_PUSH(durations, duration_note33);

		        	  lastState5 ^=0x0001;   
		           	duration_note33 = 0;  
	          	}

         	}

         }else if (lastState5&0x0001) {	
             FIFO_PUSH(notes,181); 
		          FIFO_PUSH(durations, duration_note33); 
	          	lastState5 &= 0xFFFE; 
	            duration_note33 = 0;
	         }else {
		          duration_note33 = 0;
          }

	/*34 key */

      if (d15 & 0x0002) {
       duration_note34++;

     	   if (d25&0x0002) { 

		         if (lastState5&0x0002) {
		          	duration_note34 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,54);      
			          FIFO_PUSH(durations, duration_note34);

		        	  lastState5 ^=0x0002;   
		           	duration_note34 = 0;  
	          	}

         	}

         }else if (lastState5&0x0002) {	
             FIFO_PUSH(notes,182); 
		          FIFO_PUSH(durations, duration_note34); 
	          	lastState5 &= 0xFFFD; 
	            duration_note34 = 0;
	         }else {
		          duration_note34 = 0;
          }

	/*35 key */

      if (d15 & 0x0004) {
       duration_note35++;

     	   if (d25&0x0004) { 

		         if (lastState5&0x0004) {
		          	duration_note35 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,55);      
			          FIFO_PUSH(durations, duration_note35);

		        	  lastState5 ^=0x0004;   
		           	duration_note35 = 0;  
	          	}

         	}

         }else if (lastState5&0x0004) {	
             FIFO_PUSH(notes,183); 
		          FIFO_PUSH(durations, duration_note35); 
	          	lastState5 &= 0xFFFB; 
	            duration_note35 = 0;
	         }else {
		          duration_note35 = 0;
          }

	/*36 key */

      if (d15 & 0x0008) {
       duration_note36++;

     	   if (d25&0x0008) { 

		         if (lastState5&0x0008) {
		          	duration_note36 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,56);      
			          FIFO_PUSH(durations, duration_note36);

		        	  lastState5 ^=0x0008;   
		           	duration_note36 = 0;  
	          	}

         	}

         }else if (lastState5&0x0008) {	
             FIFO_PUSH(notes,184); 
		          FIFO_PUSH(durations, duration_note36); 
	          	lastState5 &= 0xFFF7; 
	            duration_note36 = 0;
	         }else {
		          duration_note36 = 0;
          }

	/*37 key */

      if (d15 & 0x0010) {
       duration_note37++;

     	   if (d25&0x0010) { 

		         if (lastState5&0x0010) {
		          	duration_note37 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,57);      
			          FIFO_PUSH(durations, duration_note37);

		        	  lastState5 ^=0x0010;   
		           	duration_note37 = 0;  
	          	}

         	}

         }else if (lastState5&0x0010) {	
             FIFO_PUSH(notes,185); 
		          FIFO_PUSH(durations, duration_note37); 
	          	lastState5 &= 0xFFEF; 
	            duration_note37 = 0;
	         }else {
		          duration_note37 = 0;
          }

	/*38 key */

      if (d15 & 0x0020) {
       duration_note38++;

     	   if (d25&0x0020) { 

		         if (lastState5&0x0020) {
		          	duration_note38 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,58);      
			          FIFO_PUSH(durations, duration_note38);

		        	  lastState5 ^=0x0020;   
		           	duration_note38 = 0;  
	          	}

         	}

         }else if (lastState5&0x0020) {	
             FIFO_PUSH(notes,186); 
		          FIFO_PUSH(durations, duration_note38); 
	          	lastState5 &= 0xFFDF; 
	            duration_note38 = 0;
	         }else {
		          duration_note38 = 0;
          }

	/*39 key */

      if (d15 & 0x0040) {
       duration_note39++;

     	   if (d25&0x0040) { 

		         if (lastState5&0x0040) {
		          	duration_note39 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,59);      
			          FIFO_PUSH(durations, duration_note39);

		        	  lastState5 ^=0x0040;   
		           	duration_note39 = 0;  
	          	}

         	}

         }else if (lastState5&0x0040) {	
             FIFO_PUSH(notes,187); 
		          FIFO_PUSH(durations, duration_note39); 
	          	lastState5 &= 0xFFBF; 
	            duration_note39 = 0;
	         }else {
		          duration_note39 = 0;
          }

	/*40 key */

      if (d15 & 0x0080) {
       duration_note40++;

     	   if (d25&0x0080) { 

		         if (lastState5&0x0080) {
		          	duration_note40 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,60);      
			          FIFO_PUSH(durations, duration_note40);

		        	  lastState5 ^=0x0080;   
		           	duration_note40 = 0;  
	          	}

         	}

         }else if (lastState5&0x0080) {	
             FIFO_PUSH(notes,188); 
		          FIFO_PUSH(durations, duration_note40); 
	          	lastState5 &= 0xFF7F; 
	            duration_note40 = 0;
	         }else {
		          duration_note40 = 0;
          }

      /* 6 chunk */ 

    GPIOC->BSRRH = GPIO_Pin_4; 
    Delay(KEY_SWITCH_DELAY); 
    d16 = ~GPIOA->IDR; //Read port state first contact 
    GPIOC->BSRRL = GPIO_Pin_4; 
    Delay(KEY_SWITCH_DELAY);  
    if (d16&0x00FF){  

    GPIOC->BSRRH = GPIO_Pin_5; 
    Delay(KEY_SWITCH_DELAY);  
    d26 = ~GPIOA->IDR; //Read port state second contact 
    GPIOC->BSRRL = GPIO_Pin_5;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d26=0;
     }
	/*41 key */

      if (d16 & 0x0001) {
       duration_note41++;

     	   if (d26&0x0001) { 

		         if (lastState6&0x0001) {
		          	duration_note41 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,61);      
			          FIFO_PUSH(durations, duration_note41);

		        	  lastState6 ^=0x0001;   
		           	duration_note41 = 0;  
	          	}

         	}

         }else if (lastState6&0x0001) {	
             FIFO_PUSH(notes,189); 
		          FIFO_PUSH(durations, duration_note41); 
	          	lastState6 &= 0xFFFE; 
	            duration_note41 = 0;
	         }else {
		          duration_note41 = 0;
          }

	/*42 key */

      if (d16 & 0x0002) {
       duration_note42++;

     	   if (d26&0x0002) { 

		         if (lastState6&0x0002) {
		          	duration_note42 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,62);      
			          FIFO_PUSH(durations, duration_note42);

		        	  lastState6 ^=0x0002;   
		           	duration_note42 = 0;  
	          	}

         	}

         }else if (lastState6&0x0002) {	
             FIFO_PUSH(notes,190); 
		          FIFO_PUSH(durations, duration_note42); 
	          	lastState6 &= 0xFFFD; 
	            duration_note42 = 0;
	         }else {
		          duration_note42 = 0;
          }

	/*43 key */

      if (d16 & 0x0004) {
       duration_note43++;

     	   if (d26&0x0004) { 

		         if (lastState6&0x0004) {
		          	duration_note43 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,63);      
			          FIFO_PUSH(durations, duration_note43);

		        	  lastState6 ^=0x0004;   
		           	duration_note43 = 0;  
	          	}

         	}

         }else if (lastState6&0x0004) {	
             FIFO_PUSH(notes,191); 
		          FIFO_PUSH(durations, duration_note43); 
	          	lastState6 &= 0xFFFB; 
	            duration_note43 = 0;
	         }else {
		          duration_note43 = 0;
          }

	/*44 key */

      if (d16 & 0x0008) {
       duration_note44++;

     	   if (d26&0x0008) { 

		         if (lastState6&0x0008) {
		          	duration_note44 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,64);      
			          FIFO_PUSH(durations, duration_note44);

		        	  lastState6 ^=0x0008;   
		           	duration_note44 = 0;  
	          	}

         	}

         }else if (lastState6&0x0008) {	
             FIFO_PUSH(notes,192); 
		          FIFO_PUSH(durations, duration_note44); 
	          	lastState6 &= 0xFFF7; 
	            duration_note44 = 0;
	         }else {
		          duration_note44 = 0;
          }

	/*45 key */

      if (d16 & 0x0010) {
       duration_note45++;

     	   if (d26&0x0010) { 

		         if (lastState6&0x0010) {
		          	duration_note45 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,65);      
			          FIFO_PUSH(durations, duration_note45);

		        	  lastState6 ^=0x0010;   
		           	duration_note45 = 0;  
	          	}

         	}

         }else if (lastState6&0x0010) {	
             FIFO_PUSH(notes,193); 
		          FIFO_PUSH(durations, duration_note45); 
	          	lastState6 &= 0xFFEF; 
	            duration_note45 = 0;
	         }else {
		          duration_note45 = 0;
          }

	/*46 key */

      if (d16 & 0x0020) {
       duration_note46++;

     	   if (d26&0x0020) { 

		         if (lastState6&0x0020) {
		          	duration_note46 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,66);      
			          FIFO_PUSH(durations, duration_note46);

		        	  lastState6 ^=0x0020;   
		           	duration_note46 = 0;  
	          	}

         	}

         }else if (lastState6&0x0020) {	
             FIFO_PUSH(notes,194); 
		          FIFO_PUSH(durations, duration_note46); 
	          	lastState6 &= 0xFFDF; 
	            duration_note46 = 0;
	         }else {
		          duration_note46 = 0;
          }

	/*47 key */

      if (d16 & 0x0040) {
       duration_note47++;

     	   if (d26&0x0040) { 

		         if (lastState6&0x0040) {
		          	duration_note47 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,67);      
			          FIFO_PUSH(durations, duration_note47);

		        	  lastState6 ^=0x0040;   
		           	duration_note47 = 0;  
	          	}

         	}

         }else if (lastState6&0x0040) {	
             FIFO_PUSH(notes,195); 
		          FIFO_PUSH(durations, duration_note47); 
	          	lastState6 &= 0xFFBF; 
	            duration_note47 = 0;
	         }else {
		          duration_note47 = 0;
          }

	/*48 key */

      if (d16 & 0x0080) {
       duration_note48++;

     	   if (d26&0x0080) { 

		         if (lastState6&0x0080) {
		          	duration_note48 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,68);      
			          FIFO_PUSH(durations, duration_note48);

		        	  lastState6 ^=0x0080;   
		           	duration_note48 = 0;  
	          	}

         	}

         }else if (lastState6&0x0080) {	
             FIFO_PUSH(notes,196); 
		          FIFO_PUSH(durations, duration_note48); 
	          	lastState6 &= 0xFF7F; 
	            duration_note48 = 0;
	         }else {
		          duration_note48 = 0;
          }

      /* 7 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_0; 
    Delay(KEY_SWITCH_DELAY); 
    d17 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_0; 
    Delay(KEY_SWITCH_DELAY);  
    if (d17&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_1; 
    Delay(KEY_SWITCH_DELAY);  
    d27 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_1;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d27=0;
     }
	/*49 key */

      if (d17 & 0x0001) {
       duration_note49++;

     	   if (d27&0x0001) { 

		         if (lastState7&0x0001) {
		          	duration_note49 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,69);      
			          FIFO_PUSH(durations, duration_note49);

		        	  lastState7 ^=0x0001;   
		           	duration_note49 = 0;  
	          	}

         	}

         }else if (lastState7&0x0001) {	
             FIFO_PUSH(notes,197); 
		          FIFO_PUSH(durations, duration_note49); 
	          	lastState7 &= 0xFFFE; 
	            duration_note49 = 0;
	         }else {
		          duration_note49 = 0;
          }

	/*50 key */

      if (d17 & 0x0002) {
       duration_note50++;

     	   if (d27&0x0002) { 

		         if (lastState7&0x0002) {
		          	duration_note50 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,70);      
			          FIFO_PUSH(durations, duration_note50);

		        	  lastState7 ^=0x0002;   
		           	duration_note50 = 0;  
	          	}

         	}

         }else if (lastState7&0x0002) {	
             FIFO_PUSH(notes,198); 
		          FIFO_PUSH(durations, duration_note50); 
	          	lastState7 &= 0xFFFD; 
	            duration_note50 = 0;
	         }else {
		          duration_note50 = 0;
          }

	/*51 key */

      if (d17 & 0x0004) {
       duration_note51++;

     	   if (d27&0x0004) { 

		         if (lastState7&0x0004) {
		          	duration_note51 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,71);      
			          FIFO_PUSH(durations, duration_note51);

		        	  lastState7 ^=0x0004;   
		           	duration_note51 = 0;  
	          	}

         	}

         }else if (lastState7&0x0004) {	
             FIFO_PUSH(notes,199); 
		          FIFO_PUSH(durations, duration_note51); 
	          	lastState7 &= 0xFFFB; 
	            duration_note51 = 0;
	         }else {
		          duration_note51 = 0;
          }

	/*52 key */

      if (d17 & 0x0008) {
       duration_note52++;

     	   if (d27&0x0008) { 

		         if (lastState7&0x0008) {
		          	duration_note52 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,72);      
			          FIFO_PUSH(durations, duration_note52);

		        	  lastState7 ^=0x0008;   
		           	duration_note52 = 0;  
	          	}

         	}

         }else if (lastState7&0x0008) {	
             FIFO_PUSH(notes,200); 
		          FIFO_PUSH(durations, duration_note52); 
	          	lastState7 &= 0xFFF7; 
	            duration_note52 = 0;
	         }else {
		          duration_note52 = 0;
          }

	/*53 key */

      if (d17 & 0x0010) {
       duration_note53++;

     	   if (d27&0x0010) { 

		         if (lastState7&0x0010) {
		          	duration_note53 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,73);      
			          FIFO_PUSH(durations, duration_note53);

		        	  lastState7 ^=0x0010;   
		           	duration_note53 = 0;  
	          	}

         	}

         }else if (lastState7&0x0010) {	
             FIFO_PUSH(notes,201); 
		          FIFO_PUSH(durations, duration_note53); 
	          	lastState7 &= 0xFFEF; 
	            duration_note53 = 0;
	         }else {
		          duration_note53 = 0;
          }

	/*54 key */

      if (d17 & 0x0020) {
       duration_note54++;

     	   if (d27&0x0020) { 

		         if (lastState7&0x0020) {
		          	duration_note54 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,74);      
			          FIFO_PUSH(durations, duration_note54);

		        	  lastState7 ^=0x0020;   
		           	duration_note54 = 0;  
	          	}

         	}

         }else if (lastState7&0x0020) {	
             FIFO_PUSH(notes,202); 
		          FIFO_PUSH(durations, duration_note54); 
	          	lastState7 &= 0xFFDF; 
	            duration_note54 = 0;
	         }else {
		          duration_note54 = 0;
          }

	/*55 key */

      if (d17 & 0x0040) {
       duration_note55++;

     	   if (d27&0x0040) { 

		         if (lastState7&0x0040) {
		          	duration_note55 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,75);      
			          FIFO_PUSH(durations, duration_note55);

		        	  lastState7 ^=0x0040;   
		           	duration_note55 = 0;  
	          	}

         	}

         }else if (lastState7&0x0040) {	
             FIFO_PUSH(notes,203); 
		          FIFO_PUSH(durations, duration_note55); 
	          	lastState7 &= 0xFFBF; 
	            duration_note55 = 0;
	         }else {
		          duration_note55 = 0;
          }

	/*56 key */

      if (d17 & 0x0080) {
       duration_note56++;

     	   if (d27&0x0080) { 

		         if (lastState7&0x0080) {
		          	duration_note56 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,76);      
			          FIFO_PUSH(durations, duration_note56);

		        	  lastState7 ^=0x0080;   
		           	duration_note56 = 0;  
	          	}

         	}

         }else if (lastState7&0x0080) {	
             FIFO_PUSH(notes,204); 
		          FIFO_PUSH(durations, duration_note56); 
	          	lastState7 &= 0xFF7F; 
	            duration_note56 = 0;
	         }else {
		          duration_note56 = 0;
          }

      /* 8 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_7; 
    Delay(KEY_SWITCH_DELAY); 
    d18 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_7; 
    Delay(KEY_SWITCH_DELAY);  
    if (d18&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_2; 
    Delay(KEY_SWITCH_DELAY);  
    d28 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_2;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d28=0;
     }
	/*57 key */

      if (d18 & 0x0001) {
       duration_note57++;

     	   if (d28&0x0001) { 

		         if (lastState8&0x0001) {
		          	duration_note57 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,77);      
			          FIFO_PUSH(durations, duration_note57);

		        	  lastState8 ^=0x0001;   
		           	duration_note57 = 0;  
	          	}

         	}

         }else if (lastState8&0x0001) {	
             FIFO_PUSH(notes,205); 
		          FIFO_PUSH(durations, duration_note57); 
	          	lastState8 &= 0xFFFE; 
	            duration_note57 = 0;
	         }else {
		          duration_note57 = 0;
          }

	/*58 key */

      if (d18 & 0x0002) {
       duration_note58++;

     	   if (d28&0x0002) { 

		         if (lastState8&0x0002) {
		          	duration_note58 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,78);      
			          FIFO_PUSH(durations, duration_note58);

		        	  lastState8 ^=0x0002;   
		           	duration_note58 = 0;  
	          	}

         	}

         }else if (lastState8&0x0002) {	
             FIFO_PUSH(notes,206); 
		          FIFO_PUSH(durations, duration_note58); 
	          	lastState8 &= 0xFFFD; 
	            duration_note58 = 0;
	         }else {
		          duration_note58 = 0;
          }

	/*59 key */

      if (d18 & 0x0004) {
       duration_note59++;

     	   if (d28&0x0004) { 

		         if (lastState8&0x0004) {
		          	duration_note59 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,79);      
			          FIFO_PUSH(durations, duration_note59);

		        	  lastState8 ^=0x0004;   
		           	duration_note59 = 0;  
	          	}

         	}

         }else if (lastState8&0x0004) {	
             FIFO_PUSH(notes,207); 
		          FIFO_PUSH(durations, duration_note59); 
	          	lastState8 &= 0xFFFB; 
	            duration_note59 = 0;
	         }else {
		          duration_note59 = 0;
          }

	/*60 key */

      if (d18 & 0x0008) {
       duration_note60++;

     	   if (d28&0x0008) { 

		         if (lastState8&0x0008) {
		          	duration_note60 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,80);      
			          FIFO_PUSH(durations, duration_note60);

		        	  lastState8 ^=0x0008;   
		           	duration_note60 = 0;  
	          	}

         	}

         }else if (lastState8&0x0008) {	
             FIFO_PUSH(notes,208); 
		          FIFO_PUSH(durations, duration_note60); 
	          	lastState8 &= 0xFFF7; 
	            duration_note60 = 0;
	         }else {
		          duration_note60 = 0;
          }

	/*61 key */

      if (d18 & 0x0010) {
       duration_note61++;

     	   if (d28&0x0010) { 

		         if (lastState8&0x0010) {
		          	duration_note61 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,81);      
			          FIFO_PUSH(durations, duration_note61);

		        	  lastState8 ^=0x0010;   
		           	duration_note61 = 0;  
	          	}

         	}

         }else if (lastState8&0x0010) {	
             FIFO_PUSH(notes,209); 
		          FIFO_PUSH(durations, duration_note61); 
	          	lastState8 &= 0xFFEF; 
	            duration_note61 = 0;
	         }else {
		          duration_note61 = 0;
          }

	/*62 key */

      if (d18 & 0x0020) {
       duration_note62++;

     	   if (d28&0x0020) { 

		         if (lastState8&0x0020) {
		          	duration_note62 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,82);      
			          FIFO_PUSH(durations, duration_note62);

		        	  lastState8 ^=0x0020;   
		           	duration_note62 = 0;  
	          	}

         	}

         }else if (lastState8&0x0020) {	
             FIFO_PUSH(notes,210); 
		          FIFO_PUSH(durations, duration_note62); 
	          	lastState8 &= 0xFFDF; 
	            duration_note62 = 0;
	         }else {
		          duration_note62 = 0;
          }

	/*63 key */

      if (d18 & 0x0040) {
       duration_note63++;

     	   if (d28&0x0040) { 

		         if (lastState8&0x0040) {
		          	duration_note63 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,83);      
			          FIFO_PUSH(durations, duration_note63);

		        	  lastState8 ^=0x0040;   
		           	duration_note63 = 0;  
	          	}

         	}

         }else if (lastState8&0x0040) {	
             FIFO_PUSH(notes,211); 
		          FIFO_PUSH(durations, duration_note63); 
	          	lastState8 &= 0xFFBF; 
	            duration_note63 = 0;
	         }else {
		          duration_note63 = 0;
          }

	/*64 key */

      if (d18 & 0x0080) {
       duration_note64++;

     	   if (d28&0x0080) { 

		         if (lastState8&0x0080) {
		          	duration_note64 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,84);      
			          FIFO_PUSH(durations, duration_note64);

		        	  lastState8 ^=0x0080;   
		           	duration_note64 = 0;  
	          	}

         	}

         }else if (lastState8&0x0080) {	
             FIFO_PUSH(notes,212); 
		          FIFO_PUSH(durations, duration_note64); 
	          	lastState8 &= 0xFF7F; 
	            duration_note64 = 0;
	         }else {
		          duration_note64 = 0;
          }

      /* 9 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_9; 
    Delay(KEY_SWITCH_DELAY); 
    d19 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_9; 
    Delay(KEY_SWITCH_DELAY);  
    if (d19&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_8; 
    Delay(KEY_SWITCH_DELAY);  
    d29 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_8;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d29=0;
     }
	/*65 key */

      if (d19 & 0x0001) {
       duration_note65++;

     	   if (d29&0x0001) { 

		         if (lastState9&0x0001) {
		          	duration_note65 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,85);      
			          FIFO_PUSH(durations, duration_note65);

		        	  lastState9 ^=0x0001;   
		           	duration_note65 = 0;  
	          	}

         	}

         }else if (lastState9&0x0001) {	
             FIFO_PUSH(notes,213); 
		          FIFO_PUSH(durations, duration_note65); 
	          	lastState9 &= 0xFFFE; 
	            duration_note65 = 0;
	         }else {
		          duration_note65 = 0;
          }

	/*66 key */

      if (d19 & 0x0002) {
       duration_note66++;

     	   if (d29&0x0002) { 

		         if (lastState9&0x0002) {
		          	duration_note66 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,86);      
			          FIFO_PUSH(durations, duration_note66);

		        	  lastState9 ^=0x0002;   
		           	duration_note66 = 0;  
	          	}

         	}

         }else if (lastState9&0x0002) {	
             FIFO_PUSH(notes,214); 
		          FIFO_PUSH(durations, duration_note66); 
	          	lastState9 &= 0xFFFD; 
	            duration_note66 = 0;
	         }else {
		          duration_note66 = 0;
          }

	/*67 key */

      if (d19 & 0x0004) {
       duration_note67++;

     	   if (d29&0x0004) { 

		         if (lastState9&0x0004) {
		          	duration_note67 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,87);      
			          FIFO_PUSH(durations, duration_note67);

		        	  lastState9 ^=0x0004;   
		           	duration_note67 = 0;  
	          	}

         	}

         }else if (lastState9&0x0004) {	
             FIFO_PUSH(notes,215); 
		          FIFO_PUSH(durations, duration_note67); 
	          	lastState9 &= 0xFFFB; 
	            duration_note67 = 0;
	         }else {
		          duration_note67 = 0;
          }

	/*68 key */

      if (d19 & 0x0008) {
       duration_note68++;

     	   if (d29&0x0008) { 

		         if (lastState9&0x0008) {
		          	duration_note68 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,88);      
			          FIFO_PUSH(durations, duration_note68);

		        	  lastState9 ^=0x0008;   
		           	duration_note68 = 0;  
	          	}

         	}

         }else if (lastState9&0x0008) {	
             FIFO_PUSH(notes,216); 
		          FIFO_PUSH(durations, duration_note68); 
	          	lastState9 &= 0xFFF7; 
	            duration_note68 = 0;
	         }else {
		          duration_note68 = 0;
          }

	/*69 key */

      if (d19 & 0x0010) {
       duration_note69++;

     	   if (d29&0x0010) { 

		         if (lastState9&0x0010) {
		          	duration_note69 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,89);      
			          FIFO_PUSH(durations, duration_note69);

		        	  lastState9 ^=0x0010;   
		           	duration_note69 = 0;  
	          	}

         	}

         }else if (lastState9&0x0010) {	
             FIFO_PUSH(notes,217); 
		          FIFO_PUSH(durations, duration_note69); 
	          	lastState9 &= 0xFFEF; 
	            duration_note69 = 0;
	         }else {
		          duration_note69 = 0;
          }

	/*70 key */

      if (d19 & 0x0020) {
       duration_note70++;

     	   if (d29&0x0020) { 

		         if (lastState9&0x0020) {
		          	duration_note70 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,90);      
			          FIFO_PUSH(durations, duration_note70);

		        	  lastState9 ^=0x0020;   
		           	duration_note70 = 0;  
	          	}

         	}

         }else if (lastState9&0x0020) {	
             FIFO_PUSH(notes,218); 
		          FIFO_PUSH(durations, duration_note70); 
	          	lastState9 &= 0xFFDF; 
	            duration_note70 = 0;
	         }else {
		          duration_note70 = 0;
          }

	/*71 key */

      if (d19 & 0x0040) {
       duration_note71++;

     	   if (d29&0x0040) { 

		         if (lastState9&0x0040) {
		          	duration_note71 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,91);      
			          FIFO_PUSH(durations, duration_note71);

		        	  lastState9 ^=0x0040;   
		           	duration_note71 = 0;  
	          	}

         	}

         }else if (lastState9&0x0040) {	
             FIFO_PUSH(notes,219); 
		          FIFO_PUSH(durations, duration_note71); 
	          	lastState9 &= 0xFFBF; 
	            duration_note71 = 0;
	         }else {
		          duration_note71 = 0;
          }

	/*72 key */

      if (d19 & 0x0080) {
       duration_note72++;

     	   if (d29&0x0080) { 

		         if (lastState9&0x0080) {
		          	duration_note72 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,92);      
			          FIFO_PUSH(durations, duration_note72);

		        	  lastState9 ^=0x0080;   
		           	duration_note72 = 0;  
	          	}

         	}

         }else if (lastState9&0x0080) {	
             FIFO_PUSH(notes,220); 
		          FIFO_PUSH(durations, duration_note72); 
	          	lastState9 &= 0xFF7F; 
	            duration_note72 = 0;
	         }else {
		          duration_note72 = 0;
          }

      /* 10 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_12; 
    Delay(KEY_SWITCH_DELAY); 
    d110 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_12; 
    Delay(KEY_SWITCH_DELAY);  
    if (d110&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_10; 
    Delay(KEY_SWITCH_DELAY);  
    d210 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_10;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d210=0;
     }
	/*73 key */

      if (d110 & 0x0001) {
       duration_note73++;

     	   if (d210&0x0001) { 

		         if (lastState10&0x0001) {
		          	duration_note73 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,93);      
			          FIFO_PUSH(durations, duration_note73);

		        	  lastState10 ^=0x0001;   
		           	duration_note73 = 0;  
	          	}

         	}

         }else if (lastState10&0x0001) {	
             FIFO_PUSH(notes,221); 
		          FIFO_PUSH(durations, duration_note73); 
	          	lastState10 &= 0xFFFE; 
	            duration_note73 = 0;
	         }else {
		          duration_note73 = 0;
          }

	/*74 key */

      if (d110 & 0x0002) {
       duration_note74++;

     	   if (d210&0x0002) { 

		         if (lastState10&0x0002) {
		          	duration_note74 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,94);      
			          FIFO_PUSH(durations, duration_note74);

		        	  lastState10 ^=0x0002;   
		           	duration_note74 = 0;  
	          	}

         	}

         }else if (lastState10&0x0002) {	
             FIFO_PUSH(notes,222); 
		          FIFO_PUSH(durations, duration_note74); 
	          	lastState10 &= 0xFFFD; 
	            duration_note74 = 0;
	         }else {
		          duration_note74 = 0;
          }

	/*75 key */

      if (d110 & 0x0004) {
       duration_note75++;

     	   if (d210&0x0004) { 

		         if (lastState10&0x0004) {
		          	duration_note75 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,95);      
			          FIFO_PUSH(durations, duration_note75);

		        	  lastState10 ^=0x0004;   
		           	duration_note75 = 0;  
	          	}

         	}

         }else if (lastState10&0x0004) {	
             FIFO_PUSH(notes,223); 
		          FIFO_PUSH(durations, duration_note75); 
	          	lastState10 &= 0xFFFB; 
	            duration_note75 = 0;
	         }else {
		          duration_note75 = 0;
          }

	/*76 key */

      if (d110 & 0x0008) {
       duration_note76++;

     	   if (d210&0x0008) { 

		         if (lastState10&0x0008) {
		          	duration_note76 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,96);      
			          FIFO_PUSH(durations, duration_note76);

		        	  lastState10 ^=0x0008;   
		           	duration_note76 = 0;  
	          	}

         	}

         }else if (lastState10&0x0008) {	
             FIFO_PUSH(notes,224); 
		          FIFO_PUSH(durations, duration_note76); 
	          	lastState10 &= 0xFFF7; 
	            duration_note76 = 0;
	         }else {
		          duration_note76 = 0;
          }

	/*77 key */

      if (d110 & 0x0010) {
       duration_note77++;

     	   if (d210&0x0010) { 

		         if (lastState10&0x0010) {
		          	duration_note77 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,97);      
			          FIFO_PUSH(durations, duration_note77);

		        	  lastState10 ^=0x0010;   
		           	duration_note77 = 0;  
	          	}

         	}

         }else if (lastState10&0x0010) {	
             FIFO_PUSH(notes,225); 
		          FIFO_PUSH(durations, duration_note77); 
	          	lastState10 &= 0xFFEF; 
	            duration_note77 = 0;
	         }else {
		          duration_note77 = 0;
          }

	/*78 key */

      if (d110 & 0x0020) {
       duration_note78++;

     	   if (d210&0x0020) { 

		         if (lastState10&0x0020) {
		          	duration_note78 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,98);      
			          FIFO_PUSH(durations, duration_note78);

		        	  lastState10 ^=0x0020;   
		           	duration_note78 = 0;  
	          	}

         	}

         }else if (lastState10&0x0020) {	
             FIFO_PUSH(notes,226); 
		          FIFO_PUSH(durations, duration_note78); 
	          	lastState10 &= 0xFFDF; 
	            duration_note78 = 0;
	         }else {
		          duration_note78 = 0;
          }

	/*79 key */

      if (d110 & 0x0040) {
       duration_note79++;

     	   if (d210&0x0040) { 

		         if (lastState10&0x0040) {
		          	duration_note79 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,99);      
			          FIFO_PUSH(durations, duration_note79);

		        	  lastState10 ^=0x0040;   
		           	duration_note79 = 0;  
	          	}

         	}

         }else if (lastState10&0x0040) {	
             FIFO_PUSH(notes,227); 
		          FIFO_PUSH(durations, duration_note79); 
	          	lastState10 &= 0xFFBF; 
	            duration_note79 = 0;
	         }else {
		          duration_note79 = 0;
          }

	/*80 key */

      if (d110 & 0x0080) {
       duration_note80++;

     	   if (d210&0x0080) { 

		         if (lastState10&0x0080) {
		          	duration_note80 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,100);      
			          FIFO_PUSH(durations, duration_note80);

		        	  lastState10 ^=0x0080;   
		           	duration_note80 = 0;  
	          	}

         	}

         }else if (lastState10&0x0080) {	
             FIFO_PUSH(notes,228); 
		          FIFO_PUSH(durations, duration_note80); 
	          	lastState10 &= 0xFF7F; 
	            duration_note80 = 0;
	         }else {
		          duration_note80 = 0;
          }

      /* 11 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_13; 
    Delay(KEY_SWITCH_DELAY); 
    d111 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_13; 
    Delay(KEY_SWITCH_DELAY);  
    if (d111&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_11; 
    Delay(KEY_SWITCH_DELAY);  
    d211 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_11;  
    Delay(KEY_SWITCH_DELAY);  
    }else{ 
         d211=0;
     }
	/*81 key */

      if (d111 & 0x0001) {
       duration_note81++;

     	   if (d211&0x0001) { 

		         if (lastState11&0x0001) {
		          	duration_note81 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,101);      
			          FIFO_PUSH(durations, duration_note81);

		        	  lastState11 ^=0x0001;   
		           	duration_note81 = 0;  
	          	}

         	}

         }else if (lastState11&0x0001) {	
             FIFO_PUSH(notes,229); 
		          FIFO_PUSH(durations, duration_note81); 
	          	lastState11 &= 0xFFFE; 
	            duration_note81 = 0;
	         }else {
		          duration_note81 = 0;
          }

	/*82 key */

      if (d111 & 0x0002) {
       duration_note82++;

     	   if (d211&0x0002) { 

		         if (lastState11&0x0002) {
		          	duration_note82 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,102);      
			          FIFO_PUSH(durations, duration_note82);

		        	  lastState11 ^=0x0002;   
		           	duration_note82 = 0;  
	          	}

         	}

         }else if (lastState11&0x0002) {	
             FIFO_PUSH(notes,230); 
		          FIFO_PUSH(durations, duration_note82); 
	          	lastState11 &= 0xFFFD; 
	            duration_note82 = 0;
	         }else {
		          duration_note82 = 0;
          }

	/*83 key */

      if (d111 & 0x0004) {
       duration_note83++;

     	   if (d211&0x0004) { 

		         if (lastState11&0x0004) {
		          	duration_note83 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,103);      
			          FIFO_PUSH(durations, duration_note83);

		        	  lastState11 ^=0x0004;   
		           	duration_note83 = 0;  
	          	}

         	}

         }else if (lastState11&0x0004) {	
             FIFO_PUSH(notes,231); 
		          FIFO_PUSH(durations, duration_note83); 
	          	lastState11 &= 0xFFFB; 
	            duration_note83 = 0;
	         }else {
		          duration_note83 = 0;
          }

	/*84 key */

      if (d111 & 0x0008) {
       duration_note84++;

     	   if (d211&0x0008) { 

		         if (lastState11&0x0008) {
		          	duration_note84 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,104);      
			          FIFO_PUSH(durations, duration_note84);

		        	  lastState11 ^=0x0008;   
		           	duration_note84 = 0;  
	          	}

         	}

         }else if (lastState11&0x0008) {	
             FIFO_PUSH(notes,232); 
		          FIFO_PUSH(durations, duration_note84); 
	          	lastState11 &= 0xFFF7; 
	            duration_note84 = 0;
	         }else {
		          duration_note84 = 0;
          }

	/*85 key */

      if (d111 & 0x0010) {
       duration_note85++;

     	   if (d211&0x0010) { 

		         if (lastState11&0x0010) {
		          	duration_note85 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,105);      
			          FIFO_PUSH(durations, duration_note85);

		        	  lastState11 ^=0x0010;   
		           	duration_note85 = 0;  
	          	}

         	}

         }else if (lastState11&0x0010) {	
             FIFO_PUSH(notes,233); 
		          FIFO_PUSH(durations, duration_note85); 
	          	lastState11 &= 0xFFEF; 
	            duration_note85 = 0;
	         }else {
		          duration_note85 = 0;
          }

	/*86 key */

      if (d111 & 0x0020) {
       duration_note86++;

     	   if (d211&0x0020) { 

		         if (lastState11&0x0020) {
		          	duration_note86 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,106);      
			          FIFO_PUSH(durations, duration_note86);

		        	  lastState11 ^=0x0020;   
		           	duration_note86 = 0;  
	          	}

         	}

         }else if (lastState11&0x0020) {	
             FIFO_PUSH(notes,234); 
		          FIFO_PUSH(durations, duration_note86); 
	          	lastState11 &= 0xFFDF; 
	            duration_note86 = 0;
	         }else {
		          duration_note86 = 0;
          }

	/*87 key */

      if (d111 & 0x0040) {
       duration_note87++;

     	   if (d211&0x0040) { 

		         if (lastState11&0x0040) {
		          	duration_note87 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,107);      
			          FIFO_PUSH(durations, duration_note87);

		        	  lastState11 ^=0x0040;   
		           	duration_note87 = 0;  
	          	}

         	}

         }else if (lastState11&0x0040) {	
             FIFO_PUSH(notes,235); 
		          FIFO_PUSH(durations, duration_note87); 
	          	lastState11 &= 0xFFBF; 
	            duration_note87 = 0;
	         }else {
		          duration_note87 = 0;
          }

	/*88 key */

      if (d111 & 0x0080) {
       duration_note88++;

     	   if (d211&0x0080) { 

		         if (lastState11&0x0080) {
		          	duration_note88 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,108);      
			          FIFO_PUSH(durations, duration_note88);

		        	  lastState11 ^=0x0080;   
		           	duration_note88 = 0;  
	          	}

         	}

         }else if (lastState11&0x0080) {	
             FIFO_PUSH(notes,236); 
		          FIFO_PUSH(durations, duration_note88); 
	          	lastState11 &= 0xFF7F; 
	            duration_note88 = 0;
	         }else {
		          duration_note88 = 0;
          }

    /*************************************************************************/
}


