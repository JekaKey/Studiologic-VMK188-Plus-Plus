#define STM32F40XX

#include "keyboardscan.h"
#include "usb_midi_io.h"

/* Current port state, first contact */
uint8_t d11 = 0x00;
uint8_t d12 = 0x00;
uint8_t d13 = 0x00;
uint8_t d14 = 0x00;
uint8_t d15 = 0x00;
uint8_t d16 = 0x00;
uint8_t d17 = 0x00;
uint8_t d18 = 0x00;
uint8_t d19 = 0x00;
uint8_t d110 = 0x00;
uint8_t d111 = 0x00;

/* Current port state, second contact */
uint8_t d21 = 0x00;
uint8_t d22 = 0x00;
uint8_t d23 = 0x00;
uint8_t d24 = 0x00;
uint8_t d25 = 0x00;
uint8_t d26 = 0x00;
uint8_t d27 = 0x00;
uint8_t d28 = 0x00;
uint8_t d29 = 0x00;
uint8_t d210 = 0x00;
uint8_t d211 = 0x00;

/* Last state key send in chunk */
uint8_t lastState1 = 0x00;
uint8_t lastState2 = 0x00;
uint8_t lastState3 = 0x00;
uint8_t lastState4 = 0x00;
uint8_t lastState5 = 0x00;
uint8_t lastState6 = 0x00;
uint8_t lastState7 = 0x00;
uint8_t lastState8 = 0x00;
uint8_t lastState9 = 0x00;
uint8_t lastState10 = 0x00;
uint8_t lastState11 = 0x00;

uint8_t lastState_key1=0x0;
uint8_t lastState_key2=0x0;
uint8_t lastState_key3=0x0;
uint8_t lastState_key4=0x0;
uint8_t lastState_key5=0x0;
uint8_t lastState_key6=0x0;
uint8_t lastState_key7=0x0;
uint8_t lastState_key8=0x0;
uint8_t lastState_key9=0x0;
uint8_t lastState_key10=0x0;
uint8_t lastState_key11=0x0;
uint8_t lastState_key12=0x0;
uint8_t lastState_key13=0x0;
uint8_t lastState_key14=0x0;
uint8_t lastState_key15=0x0;
uint8_t lastState_key16=0x0;
uint8_t lastState_key17=0x0;
uint8_t lastState_key18=0x0;
uint8_t lastState_key19=0x0;
uint8_t lastState_key20=0x0;
uint8_t lastState_key21=0x0;
uint8_t lastState_key22=0x0;
uint8_t lastState_key23=0x0;
uint8_t lastState_key24=0x0;
uint8_t lastState_key25=0x0;
uint8_t lastState_key26=0x0;
uint8_t lastState_key27=0x0;
uint8_t lastState_key28=0x0;
uint8_t lastState_key29=0x0;
uint8_t lastState_key30=0x0;
uint8_t lastState_key31=0x0;
uint8_t lastState_key32=0x0;
uint8_t lastState_key33=0x0;
uint8_t lastState_key34=0x0;
uint8_t lastState_key35=0x0;
uint8_t lastState_key36=0x0;
uint8_t lastState_key37=0x0;
uint8_t lastState_key38=0x0;
uint8_t lastState_key39=0x0;
uint8_t lastState_key40=0x0;
uint8_t lastState_key41=0x0;
uint8_t lastState_key42=0x0;
uint8_t lastState_key43=0x0;
uint8_t lastState_key44=0x0;
uint8_t lastState_key45=0x0;
uint8_t lastState_key46=0x0;
uint8_t lastState_key47=0x0;
uint8_t lastState_key48=0x0;
uint8_t lastState_key49=0x0;
uint8_t lastState_key50=0x0;
uint8_t lastState_key51=0x0;
uint8_t lastState_key52=0x0;
uint8_t lastState_key53=0x0;
uint8_t lastState_key54=0x0;
uint8_t lastState_key55=0x0;
uint8_t lastState_key56=0x0;
uint8_t lastState_key57=0x0;
uint8_t lastState_key58=0x0;
uint8_t lastState_key59=0x0;
uint8_t lastState_key60=0x0;
uint8_t lastState_key61=0x0;
uint8_t lastState_key62=0x0;
uint8_t lastState_key63=0x0;
uint8_t lastState_key64=0x0;
uint8_t lastState_key65=0x0;
uint8_t lastState_key66=0x0;
uint8_t lastState_key67=0x0;
uint8_t lastState_key68=0x0;
uint8_t lastState_key69=0x0;
uint8_t lastState_key70=0x0;
uint8_t lastState_key71=0x0;
uint8_t lastState_key72=0x0;
uint8_t lastState_key73=0x0;
uint8_t lastState_key74=0x0;
uint8_t lastState_key75=0x0;
uint8_t lastState_key76=0x0;
uint8_t lastState_key77=0x0;
uint8_t lastState_key78=0x0;
uint8_t lastState_key79=0x0;
uint8_t lastState_key80=0x0;
uint8_t lastState_key81=0x0;
uint8_t lastState_key82=0x0;
uint8_t lastState_key83=0x0;
uint8_t lastState_key84=0x0;
uint8_t lastState_key85=0x0;
uint8_t lastState_key86=0x0;
uint8_t lastState_key87=0x0;
uint8_t lastState_key88=0x0;

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



uint8_t UseHighRes = 1;
uint8_t MidiChannel = 0;


/**
* Расчет velocity и запись в midi буффер
*/

word vel_test=0;
void checkNoteArray(void) {
    //Проверяем буффер считанных клавиш с длительностями
    word vel;
    if (FIFO_COUNT(notes) != 0) {

        curNote = FIFO_FRONT(notes);
        duration = FIFO_FRONT(durations);

        FIFO_POP(durations);
        FIFO_POP(notes);

        if ((curNote & 0x80) == 0) {
           vel = getVelocity_on(duration,note_color(curNote));					
					  if (UseHighRes){
							  /*Send High Res Preffix*/					
							  sendControlChange(0x58, (byte)(vel & 0x7F),MidiChannel); //to midi
							  sendUSB_ControlChange(0x58, (byte)(vel & 0x7F),MidiChannel); //to usb
						 }	
            sendNoteOn(curNote, vel, MidiChannel); //to midi
						sendUSB_NoteOn(curNote, vel, MidiChannel); // to usb
        } else {
            sendNoteOff(curNote & 0x7F, getVelocity_off(duration,note_color(curNote)), MidiChannel); //to midi
            sendUSB_NoteOff(curNote & 0x7F, getVelocity_off(duration,note_color(curNote)), MidiChannel); //to usb
        }

    }
}


void readKeyState(void) {
      /* 1 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_15; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d11 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_15; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d11&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_14; 
    delay(KEY_SWITCH_DELAY);  
    d21 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_14;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d21=0x0;
     }
if ((d11&0x00FF)|(lastState1&0x00FF)){
	/*1 key */

      if (d11 & 0x0001) {
       if (duration_note1<0xFFFF) duration_note1++;

     	   if (d21&0x0001) { 

		         if (lastState_key1) {
		          	duration_note1 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,21);      
			          FIFO_PUSH(durations, duration_note1);

		        	  lastState_key1 = 0x1;
		           	duration_note1 = 0;  
	          	}

         	}

         }else if (lastState_key1) {	
             FIFO_PUSH(notes,149); 
		          FIFO_PUSH(durations, duration_note1); 
	          	lastState_key1 = 0x0; 
	            duration_note1 = 0x0;
	         }else {
		          duration_note1 = 0x0;
          }

	/*2 key */

      if (d11 & 0x0002) {
       if (duration_note2<0xFFFF) duration_note2++;

     	   if (d21&0x0002) { 

		         if (lastState_key2) {
		          	duration_note2 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,22);      
			          FIFO_PUSH(durations, duration_note2);

		        	  lastState_key2 = 0x1;
		           	duration_note2 = 0;  
	          	}

         	}

         }else if (lastState_key2) {	
             FIFO_PUSH(notes,150); 
		          FIFO_PUSH(durations, duration_note2); 
	          	lastState_key2 = 0x0; 
	            duration_note2 = 0x0;
	         }else {
		          duration_note2 = 0x0;
          }

	/*3 key */

      if (d11 & 0x0004) {
       if (duration_note3<0xFFFF) duration_note3++;

     	   if (d21&0x0004) { 

		         if (lastState_key3) {
		          	duration_note3 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,23);      
			          FIFO_PUSH(durations, duration_note3);

		        	  lastState_key3 = 0x1;
		           	duration_note3 = 0;  
	          	}

         	}

         }else if (lastState_key3) {	
             FIFO_PUSH(notes,151); 
		          FIFO_PUSH(durations, duration_note3); 
	          	lastState_key3 = 0x0; 
	            duration_note3 = 0x0;
	         }else {
		          duration_note3 = 0x0;
          }

	/*4 key */

      if (d11 & 0x0008) {
       if (duration_note4<0xFFFF) duration_note4++;

     	   if (d21&0x0008) { 

		         if (lastState_key4) {
		          	duration_note4 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,24);      
			          FIFO_PUSH(durations, duration_note4);

		        	  lastState_key4 = 0x1;
		           	duration_note4 = 0;  
	          	}

         	}

         }else if (lastState_key4) {	
             FIFO_PUSH(notes,152); 
		          FIFO_PUSH(durations, duration_note4); 
	          	lastState_key4 = 0x0; 
	            duration_note4 = 0x0;
	         }else {
		          duration_note4 = 0x0;
          }

	/*5 key */

      if (d11 & 0x0010) {
       if (duration_note5<0xFFFF) duration_note5++;

     	   if (d21&0x0010) { 

		         if (lastState_key5) {
		          	duration_note5 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,25);      
			          FIFO_PUSH(durations, duration_note5);

		        	  lastState_key5 = 0x1;
		           	duration_note5 = 0;  
	          	}

         	}

         }else if (lastState_key5) {	
             FIFO_PUSH(notes,153); 
		          FIFO_PUSH(durations, duration_note5); 
	          	lastState_key5 = 0x0; 
	            duration_note5 = 0x0;
	         }else {
		          duration_note5 = 0x0;
          }

	/*6 key */

      if (d11 & 0x0020) {
       if (duration_note6<0xFFFF) duration_note6++;

     	   if (d21&0x0020) { 

		         if (lastState_key6) {
		          	duration_note6 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,26);      
			          FIFO_PUSH(durations, duration_note6);

		        	  lastState_key6 = 0x1;
		           	duration_note6 = 0;  
	          	}

         	}

         }else if (lastState_key6) {	
             FIFO_PUSH(notes,154); 
		          FIFO_PUSH(durations, duration_note6); 
	          	lastState_key6 = 0x0; 
	            duration_note6 = 0x0;
	         }else {
		          duration_note6 = 0x0;
          }

	/*7 key */

      if (d11 & 0x0040) {
       if (duration_note7<0xFFFF) duration_note7++;

     	   if (d21&0x0040) { 

		         if (lastState_key7) {
		          	duration_note7 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,27);      
			          FIFO_PUSH(durations, duration_note7);

		        	  lastState_key7 = 0x1;
		           	duration_note7 = 0;  
	          	}

         	}

         }else if (lastState_key7) {	
             FIFO_PUSH(notes,155); 
		          FIFO_PUSH(durations, duration_note7); 
	          	lastState_key7 = 0x0; 
	            duration_note7 = 0x0;
	         }else {
		          duration_note7 = 0x0;
          }

	/*8 key */

      if (d11 & 0x0080) {
       if (duration_note8<0xFFFF) duration_note8++;

     	   if (d21&0x0080) { 

		         if (lastState_key8) {
		          	duration_note8 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,28);      
			          FIFO_PUSH(durations, duration_note8);

		        	  lastState_key8 = 0x1;
		           	duration_note8 = 0;  
	          	}

         	}

         }else if (lastState_key8) {	
             FIFO_PUSH(notes,156); 
		          FIFO_PUSH(durations, duration_note8); 
	          	lastState_key8 = 0x0; 
	            duration_note8 = 0x0;
	         }else {
		          duration_note8 = 0x0;
          }

         lastState1 = d11;
         	}
      /* 2 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_11; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d12 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_11; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d12&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_10; 
    delay(KEY_SWITCH_DELAY);  
    d22 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_10;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d22=0x0;
     }
if ((d12&0x00FF)|(lastState2&0x00FF)){
	/*9 key */

      if (d12 & 0x0001) {
       if (duration_note9<0xFFFF) duration_note9++;

     	   if (d22&0x0001) { 

		         if (lastState_key9) {
		          	duration_note9 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,29);      
			          FIFO_PUSH(durations, duration_note9);

		        	  lastState_key9 = 0x1;
		           	duration_note9 = 0;  
	          	}

         	}

         }else if (lastState_key9) {	
             FIFO_PUSH(notes,157); 
		          FIFO_PUSH(durations, duration_note9); 
	          	lastState_key9 = 0x0; 
	            duration_note9 = 0x0;
	         }else {
		          duration_note9 = 0x0;
          }

	/*10 key */

      if (d12 & 0x0002) {
       if (duration_note10<0xFFFF) duration_note10++;

     	   if (d22&0x0002) { 

		         if (lastState_key10) {
		          	duration_note10 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,30);      
			          FIFO_PUSH(durations, duration_note10);

		        	  lastState_key10 = 0x1;
		           	duration_note10 = 0;  
	          	}

         	}

         }else if (lastState_key10) {	
             FIFO_PUSH(notes,158); 
		          FIFO_PUSH(durations, duration_note10); 
	          	lastState_key10 = 0x0; 
	            duration_note10 = 0x0;
	         }else {
		          duration_note10 = 0x0;
          }

	/*11 key */

      if (d12 & 0x0004) {
       if (duration_note11<0xFFFF) duration_note11++;

     	   if (d22&0x0004) { 

		         if (lastState_key11) {
		          	duration_note11 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,31);      
			          FIFO_PUSH(durations, duration_note11);

		        	  lastState_key11 = 0x1;
		           	duration_note11 = 0;  
	          	}

         	}

         }else if (lastState_key11) {	
             FIFO_PUSH(notes,159); 
		          FIFO_PUSH(durations, duration_note11); 
	          	lastState_key11 = 0x0; 
	            duration_note11 = 0x0;
	         }else {
		          duration_note11 = 0x0;
          }

	/*12 key */

      if (d12 & 0x0008) {
       if (duration_note12<0xFFFF) duration_note12++;

     	   if (d22&0x0008) { 

		         if (lastState_key12) {
		          	duration_note12 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,32);      
			          FIFO_PUSH(durations, duration_note12);

		        	  lastState_key12 = 0x1;
		           	duration_note12 = 0;  
	          	}

         	}

         }else if (lastState_key12) {	
             FIFO_PUSH(notes,160); 
		          FIFO_PUSH(durations, duration_note12); 
	          	lastState_key12 = 0x0; 
	            duration_note12 = 0x0;
	         }else {
		          duration_note12 = 0x0;
          }

	/*13 key */

      if (d12 & 0x0010) {
       if (duration_note13<0xFFFF) duration_note13++;

     	   if (d22&0x0010) { 

		         if (lastState_key13) {
		          	duration_note13 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,33);      
			          FIFO_PUSH(durations, duration_note13);

		        	  lastState_key13 = 0x1;
		           	duration_note13 = 0;  
	          	}

         	}

         }else if (lastState_key13) {	
             FIFO_PUSH(notes,161); 
		          FIFO_PUSH(durations, duration_note13); 
	          	lastState_key13 = 0x0; 
	            duration_note13 = 0x0;
	         }else {
		          duration_note13 = 0x0;
          }

	/*14 key */

      if (d12 & 0x0020) {
       if (duration_note14<0xFFFF) duration_note14++;

     	   if (d22&0x0020) { 

		         if (lastState_key14) {
		          	duration_note14 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,34);      
			          FIFO_PUSH(durations, duration_note14);

		        	  lastState_key14 = 0x1;
		           	duration_note14 = 0;  
	          	}

         	}

         }else if (lastState_key14) {	
             FIFO_PUSH(notes,162); 
		          FIFO_PUSH(durations, duration_note14); 
	          	lastState_key14 = 0x0; 
	            duration_note14 = 0x0;
	         }else {
		          duration_note14 = 0x0;
          }

	/*15 key */

      if (d12 & 0x0040) {
       if (duration_note15<0xFFFF) duration_note15++;

     	   if (d22&0x0040) { 

		         if (lastState_key15) {
		          	duration_note15 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,35);      
			          FIFO_PUSH(durations, duration_note15);

		        	  lastState_key15 = 0x1;
		           	duration_note15 = 0;  
	          	}

         	}

         }else if (lastState_key15) {	
             FIFO_PUSH(notes,163); 
		          FIFO_PUSH(durations, duration_note15); 
	          	lastState_key15 = 0x0; 
	            duration_note15 = 0x0;
	         }else {
		          duration_note15 = 0x0;
          }

	/*16 key */

      if (d12 & 0x0080) {
       if (duration_note16<0xFFFF) duration_note16++;

     	   if (d22&0x0080) { 

		         if (lastState_key16) {
		          	duration_note16 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,36);      
			          FIFO_PUSH(durations, duration_note16);

		        	  lastState_key16 = 0x1;
		           	duration_note16 = 0;  
	          	}

         	}

         }else if (lastState_key16) {	
             FIFO_PUSH(notes,164); 
		          FIFO_PUSH(durations, duration_note16); 
	          	lastState_key16 = 0x0; 
	            duration_note16 = 0x0;
	         }else {
		          duration_note16 = 0x0;
          }

         lastState2 = d12;
         	}
      /* 3 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_13; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d13 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_13; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d13&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_12; 
    delay(KEY_SWITCH_DELAY);  
    d23 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_12;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d23=0x0;
     }
if ((d13&0x00FF)|(lastState3&0x00FF)){
	/*17 key */

      if (d13 & 0x0001) {
       if (duration_note17<0xFFFF) duration_note17++;

     	   if (d23&0x0001) { 

		         if (lastState_key17) {
		          	duration_note17 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,37);      
			          FIFO_PUSH(durations, duration_note17);

		        	  lastState_key17 = 0x1;
		           	duration_note17 = 0;  
	          	}

         	}

         }else if (lastState_key17) {	
             FIFO_PUSH(notes,165); 
		          FIFO_PUSH(durations, duration_note17); 
	          	lastState_key17 = 0x0; 
	            duration_note17 = 0x0;
	         }else {
		          duration_note17 = 0x0;
          }

	/*18 key */

      if (d13 & 0x0002) {
       if (duration_note18<0xFFFF) duration_note18++;

     	   if (d23&0x0002) { 

		         if (lastState_key18) {
		          	duration_note18 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,38);      
			          FIFO_PUSH(durations, duration_note18);

		        	  lastState_key18 = 0x1;
		           	duration_note18 = 0;  
	          	}

         	}

         }else if (lastState_key18) {	
             FIFO_PUSH(notes,166); 
		          FIFO_PUSH(durations, duration_note18); 
	          	lastState_key18 = 0x0; 
	            duration_note18 = 0x0;
	         }else {
		          duration_note18 = 0x0;
          }

	/*19 key */

      if (d13 & 0x0004) {
       if (duration_note19<0xFFFF) duration_note19++;

     	   if (d23&0x0004) { 

		         if (lastState_key19) {
		          	duration_note19 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,39);      
			          FIFO_PUSH(durations, duration_note19);

		        	  lastState_key19 = 0x1;
		           	duration_note19 = 0;  
	          	}

         	}

         }else if (lastState_key19) {	
             FIFO_PUSH(notes,167); 
		          FIFO_PUSH(durations, duration_note19); 
	          	lastState_key19 = 0x0; 
	            duration_note19 = 0x0;
	         }else {
		          duration_note19 = 0x0;
          }

	/*20 key */

      if (d13 & 0x0008) {
       if (duration_note20<0xFFFF) duration_note20++;

     	   if (d23&0x0008) { 

		         if (lastState_key20) {
		          	duration_note20 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,40);      
			          FIFO_PUSH(durations, duration_note20);

		        	  lastState_key20 = 0x1;
		           	duration_note20 = 0;  
	          	}

         	}

         }else if (lastState_key20) {	
             FIFO_PUSH(notes,168); 
		          FIFO_PUSH(durations, duration_note20); 
	          	lastState_key20 = 0x0; 
	            duration_note20 = 0x0;
	         }else {
		          duration_note20 = 0x0;
          }

	/*21 key */

      if (d13 & 0x0010) {
       if (duration_note21<0xFFFF) duration_note21++;

     	   if (d23&0x0010) { 

		         if (lastState_key21) {
		          	duration_note21 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,41);      
			          FIFO_PUSH(durations, duration_note21);

		        	  lastState_key21 = 0x1;
		           	duration_note21 = 0;  
	          	}

         	}

         }else if (lastState_key21) {	
             FIFO_PUSH(notes,169); 
		          FIFO_PUSH(durations, duration_note21); 
	          	lastState_key21 = 0x0; 
	            duration_note21 = 0x0;
	         }else {
		          duration_note21 = 0x0;
          }

	/*22 key */

      if (d13 & 0x0020) {
       if (duration_note22<0xFFFF) duration_note22++;

     	   if (d23&0x0020) { 

		         if (lastState_key22) {
		          	duration_note22 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,42);      
			          FIFO_PUSH(durations, duration_note22);

		        	  lastState_key22 = 0x1;
		           	duration_note22 = 0;  
	          	}

         	}

         }else if (lastState_key22) {	
             FIFO_PUSH(notes,170); 
		          FIFO_PUSH(durations, duration_note22); 
	          	lastState_key22 = 0x0; 
	            duration_note22 = 0x0;
	         }else {
		          duration_note22 = 0x0;
          }

	/*23 key */

      if (d13 & 0x0040) {
       if (duration_note23<0xFFFF) duration_note23++;

     	   if (d23&0x0040) { 

		         if (lastState_key23) {
		          	duration_note23 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,43);      
			          FIFO_PUSH(durations, duration_note23);

		        	  lastState_key23 = 0x1;
		           	duration_note23 = 0;  
	          	}

         	}

         }else if (lastState_key23) {	
             FIFO_PUSH(notes,171); 
		          FIFO_PUSH(durations, duration_note23); 
	          	lastState_key23 = 0x0; 
	            duration_note23 = 0x0;
	         }else {
		          duration_note23 = 0x0;
          }

	/*24 key */

      if (d13 & 0x0080) {
       if (duration_note24<0xFFFF) duration_note24++;

     	   if (d23&0x0080) { 

		         if (lastState_key24) {
		          	duration_note24 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,44);      
			          FIFO_PUSH(durations, duration_note24);

		        	  lastState_key24 = 0x1;
		           	duration_note24 = 0;  
	          	}

         	}

         }else if (lastState_key24) {	
             FIFO_PUSH(notes,172); 
		          FIFO_PUSH(durations, duration_note24); 
	          	lastState_key24 = 0x0; 
	            duration_note24 = 0x0;
	         }else {
		          duration_note24 = 0x0;
          }

         lastState3 = d13;
         	}
      /* 4 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_15; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d14 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_15; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d14&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_14; 
    delay(KEY_SWITCH_DELAY);  
    d24 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_14;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d24=0x0;
     }
if ((d14&0x00FF)|(lastState4&0x00FF)){
	/*25 key */

      if (d14 & 0x0001) {
       if (duration_note25<0xFFFF) duration_note25++;

     	   if (d24&0x0001) { 

		         if (lastState_key25) {
		          	duration_note25 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,45);      
			          FIFO_PUSH(durations, duration_note25);

		        	  lastState_key25 = 0x1;
		           	duration_note25 = 0;  
	          	}

         	}

         }else if (lastState_key25) {	
             FIFO_PUSH(notes,173); 
		          FIFO_PUSH(durations, duration_note25); 
	          	lastState_key25 = 0x0; 
	            duration_note25 = 0x0;
	         }else {
		          duration_note25 = 0x0;
          }

	/*26 key */

      if (d14 & 0x0002) {
       if (duration_note26<0xFFFF) duration_note26++;

     	   if (d24&0x0002) { 

		         if (lastState_key26) {
		          	duration_note26 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,46);      
			          FIFO_PUSH(durations, duration_note26);

		        	  lastState_key26 = 0x1;
		           	duration_note26 = 0;  
	          	}

         	}

         }else if (lastState_key26) {	
             FIFO_PUSH(notes,174); 
		          FIFO_PUSH(durations, duration_note26); 
	          	lastState_key26 = 0x0; 
	            duration_note26 = 0x0;
	         }else {
		          duration_note26 = 0x0;
          }

	/*27 key */

      if (d14 & 0x0004) {
       if (duration_note27<0xFFFF) duration_note27++;

     	   if (d24&0x0004) { 

		         if (lastState_key27) {
		          	duration_note27 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,47);      
			          FIFO_PUSH(durations, duration_note27);

		        	  lastState_key27 = 0x1;
		           	duration_note27 = 0;  
	          	}

         	}

         }else if (lastState_key27) {	
             FIFO_PUSH(notes,175); 
		          FIFO_PUSH(durations, duration_note27); 
	          	lastState_key27 = 0x0; 
	            duration_note27 = 0x0;
	         }else {
		          duration_note27 = 0x0;
          }

	/*28 key */

      if (d14 & 0x0008) {
       if (duration_note28<0xFFFF) duration_note28++;

     	   if (d24&0x0008) { 

		         if (lastState_key28) {
		          	duration_note28 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,48);      
			          FIFO_PUSH(durations, duration_note28);

		        	  lastState_key28 = 0x1;
		           	duration_note28 = 0;  
	          	}

         	}

         }else if (lastState_key28) {	
             FIFO_PUSH(notes,176); 
		          FIFO_PUSH(durations, duration_note28); 
	          	lastState_key28 = 0x0; 
	            duration_note28 = 0x0;
	         }else {
		          duration_note28 = 0x0;
          }

	/*29 key */

      if (d14 & 0x0010) {
       if (duration_note29<0xFFFF) duration_note29++;

     	   if (d24&0x0010) { 

		         if (lastState_key29) {
		          	duration_note29 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,49);      
			          FIFO_PUSH(durations, duration_note29);

		        	  lastState_key29 = 0x1;
		           	duration_note29 = 0;  
	          	}

         	}

         }else if (lastState_key29) {	
             FIFO_PUSH(notes,177); 
		          FIFO_PUSH(durations, duration_note29); 
	          	lastState_key29 = 0x0; 
	            duration_note29 = 0x0;
	         }else {
		          duration_note29 = 0x0;
          }

	/*30 key */

      if (d14 & 0x0020) {
       if (duration_note30<0xFFFF) duration_note30++;

     	   if (d24&0x0020) { 

		         if (lastState_key30) {
		          	duration_note30 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,50);      
			          FIFO_PUSH(durations, duration_note30);

		        	  lastState_key30 = 0x1;
		           	duration_note30 = 0;  
	          	}

         	}

         }else if (lastState_key30) {	
             FIFO_PUSH(notes,178); 
		          FIFO_PUSH(durations, duration_note30); 
	          	lastState_key30 = 0x0; 
	            duration_note30 = 0x0;
	         }else {
		          duration_note30 = 0x0;
          }

	/*31 key */

      if (d14 & 0x0040) {
       if (duration_note31<0xFFFF) duration_note31++;

     	   if (d24&0x0040) { 

		         if (lastState_key31) {
		          	duration_note31 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,51);      
			          FIFO_PUSH(durations, duration_note31);

		        	  lastState_key31 = 0x1;
		           	duration_note31 = 0;  
	          	}

         	}

         }else if (lastState_key31) {	
             FIFO_PUSH(notes,179); 
		          FIFO_PUSH(durations, duration_note31); 
	          	lastState_key31 = 0x0; 
	            duration_note31 = 0x0;
	         }else {
		          duration_note31 = 0x0;
          }

	/*32 key */

      if (d14 & 0x0080) {
       if (duration_note32<0xFFFF) duration_note32++;

     	   if (d24&0x0080) { 

		         if (lastState_key32) {
		          	duration_note32 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,52);      
			          FIFO_PUSH(durations, duration_note32);

		        	  lastState_key32 = 0x1;
		           	duration_note32 = 0;  
	          	}

         	}

         }else if (lastState_key32) {	
             FIFO_PUSH(notes,180); 
		          FIFO_PUSH(durations, duration_note32); 
	          	lastState_key32 = 0x0; 
	            duration_note32 = 0x0;
	         }else {
		          duration_note32 = 0x0;
          }

         lastState4 = d14;
         	}
      /* 5 chunk */ 

    GPIOD->BSRRH = GPIO_Pin_9; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d15 = ~GPIOA->IDR; //Read port state first contact 
    GPIOD->BSRRL = GPIO_Pin_9; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d15&0x00FF){  

    GPIOD->BSRRH = GPIO_Pin_8; 
    delay(KEY_SWITCH_DELAY);  
    d25 = ~GPIOA->IDR; //Read port state second contact 
    GPIOD->BSRRL = GPIO_Pin_8;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d25=0x0;
     }
if ((d15&0x00FF)|(lastState5&0x00FF)){
	/*33 key */

      if (d15 & 0x0001) {
       if (duration_note33<0xFFFF) duration_note33++;

     	   if (d25&0x0001) { 

		         if (lastState_key33) {
		          	duration_note33 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,53);      
			          FIFO_PUSH(durations, duration_note33);

		        	  lastState_key33 = 0x1;
		           	duration_note33 = 0;  
	          	}

         	}

         }else if (lastState_key33) {	
             FIFO_PUSH(notes,181); 
		          FIFO_PUSH(durations, duration_note33); 
	          	lastState_key33 = 0x0; 
	            duration_note33 = 0x0;
	         }else {
		          duration_note33 = 0x0;
          }

	/*34 key */

      if (d15 & 0x0002) {
       if (duration_note34<0xFFFF) duration_note34++;

     	   if (d25&0x0002) { 

		         if (lastState_key34) {
		          	duration_note34 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,54);      
			          FIFO_PUSH(durations, duration_note34);

		        	  lastState_key34 = 0x1;
		           	duration_note34 = 0;  
	          	}

         	}

         }else if (lastState_key34) {	
             FIFO_PUSH(notes,182); 
		          FIFO_PUSH(durations, duration_note34); 
	          	lastState_key34 = 0x0; 
	            duration_note34 = 0x0;
	         }else {
		          duration_note34 = 0x0;
          }

	/*35 key */

      if (d15 & 0x0004) {
       if (duration_note35<0xFFFF) duration_note35++;

     	   if (d25&0x0004) { 

		         if (lastState_key35) {
		          	duration_note35 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,55);      
			          FIFO_PUSH(durations, duration_note35);

		        	  lastState_key35 = 0x1;
		           	duration_note35 = 0;  
	          	}

         	}

         }else if (lastState_key35) {	
             FIFO_PUSH(notes,183); 
		          FIFO_PUSH(durations, duration_note35); 
	          	lastState_key35 = 0x0; 
	            duration_note35 = 0x0;
	         }else {
		          duration_note35 = 0x0;
          }

	/*36 key */

      if (d15 & 0x0008) {
       if (duration_note36<0xFFFF) duration_note36++;

     	   if (d25&0x0008) { 

		         if (lastState_key36) {
		          	duration_note36 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,56);      
			          FIFO_PUSH(durations, duration_note36);

		        	  lastState_key36 = 0x1;
		           	duration_note36 = 0;  
	          	}

         	}

         }else if (lastState_key36) {	
             FIFO_PUSH(notes,184); 
		          FIFO_PUSH(durations, duration_note36); 
	          	lastState_key36 = 0x0; 
	            duration_note36 = 0x0;
	         }else {
		          duration_note36 = 0x0;
          }

	/*37 key */

      if (d15 & 0x0010) {
       if (duration_note37<0xFFFF) duration_note37++;

     	   if (d25&0x0010) { 

		         if (lastState_key37) {
		          	duration_note37 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,57);      
			          FIFO_PUSH(durations, duration_note37);

		        	  lastState_key37 = 0x1;
		           	duration_note37 = 0;  
	          	}

         	}

         }else if (lastState_key37) {	
             FIFO_PUSH(notes,185); 
		          FIFO_PUSH(durations, duration_note37); 
	          	lastState_key37 = 0x0; 
	            duration_note37 = 0x0;
	         }else {
		          duration_note37 = 0x0;
          }

	/*38 key */

      if (d15 & 0x0020) {
       if (duration_note38<0xFFFF) duration_note38++;

     	   if (d25&0x0020) { 

		         if (lastState_key38) {
		          	duration_note38 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,58);      
			          FIFO_PUSH(durations, duration_note38);

		        	  lastState_key38 = 0x1;
		           	duration_note38 = 0;  
	          	}

         	}

         }else if (lastState_key38) {	
             FIFO_PUSH(notes,186); 
		          FIFO_PUSH(durations, duration_note38); 
	          	lastState_key38 = 0x0; 
	            duration_note38 = 0x0;
	         }else {
		          duration_note38 = 0x0;
          }

	/*39 key */

      if (d15 & 0x0040) {
       if (duration_note39<0xFFFF) duration_note39++;

     	   if (d25&0x0040) { 

		         if (lastState_key39) {
		          	duration_note39 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,59);      
			          FIFO_PUSH(durations, duration_note39);

		        	  lastState_key39 = 0x1;
		           	duration_note39 = 0;  
	          	}

         	}

         }else if (lastState_key39) {	
             FIFO_PUSH(notes,187); 
		          FIFO_PUSH(durations, duration_note39); 
	          	lastState_key39 = 0x0; 
	            duration_note39 = 0x0;
	         }else {
		          duration_note39 = 0x0;
          }

	/*40 key */

      if (d15 & 0x0080) {
       if (duration_note40<0xFFFF) duration_note40++;

     	   if (d25&0x0080) { 

		         if (lastState_key40) {
		          	duration_note40 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,60);      
			          FIFO_PUSH(durations, duration_note40);

		        	  lastState_key40 = 0x1;
		           	duration_note40 = 0;  
	          	}

         	}

         }else if (lastState_key40) {	
             FIFO_PUSH(notes,188); 
		          FIFO_PUSH(durations, duration_note40); 
	          	lastState_key40 = 0x0; 
	            duration_note40 = 0x0;
	         }else {
		          duration_note40 = 0x0;
          }

         lastState5 = d15;
         	}
      /* 6 chunk */ 

    GPIOC->BSRRH = GPIO_Pin_4; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d16 = ~GPIOA->IDR; //Read port state first contact 
    GPIOC->BSRRL = GPIO_Pin_4; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d16&0x00FF){  

    GPIOC->BSRRH = GPIO_Pin_5; 
    delay(KEY_SWITCH_DELAY);  
    d26 = ~GPIOA->IDR; //Read port state second contact 
    GPIOC->BSRRL = GPIO_Pin_5;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d26=0x0;
     }
if ((d16&0x00FF)|(lastState6&0x00FF)){
	/*41 key */

      if (d16 & 0x0001) {
       if (duration_note41<0xFFFF) duration_note41++;

     	   if (d26&0x0001) { 

		         if (lastState_key41) {
		          	duration_note41 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,61);      
			          FIFO_PUSH(durations, duration_note41);

		        	  lastState_key41 = 0x1;
		           	duration_note41 = 0;  
	          	}

         	}

         }else if (lastState_key41) {	
             FIFO_PUSH(notes,189); 
		          FIFO_PUSH(durations, duration_note41); 
	          	lastState_key41 = 0x0; 
	            duration_note41 = 0x0;
	         }else {
		          duration_note41 = 0x0;
          }

	/*42 key */

      if (d16 & 0x0002) {
       if (duration_note42<0xFFFF) duration_note42++;

     	   if (d26&0x0002) { 

		         if (lastState_key42) {
		          	duration_note42 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,62);      
			          FIFO_PUSH(durations, duration_note42);

		        	  lastState_key42 = 0x1;
		           	duration_note42 = 0;  
	          	}

         	}

         }else if (lastState_key42) {	
             FIFO_PUSH(notes,190); 
		          FIFO_PUSH(durations, duration_note42); 
	          	lastState_key42 = 0x0; 
	            duration_note42 = 0x0;
	         }else {
		          duration_note42 = 0x0;
          }

	/*43 key */

      if (d16 & 0x0004) {
       if (duration_note43<0xFFFF) duration_note43++;

     	   if (d26&0x0004) { 

		         if (lastState_key43) {
		          	duration_note43 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,63);      
			          FIFO_PUSH(durations, duration_note43);

		        	  lastState_key43 = 0x1;
		           	duration_note43 = 0;  
	          	}

         	}

         }else if (lastState_key43) {	
             FIFO_PUSH(notes,191); 
		          FIFO_PUSH(durations, duration_note43); 
	          	lastState_key43 = 0x0; 
	            duration_note43 = 0x0;
	         }else {
		          duration_note43 = 0x0;
          }

	/*44 key */

      if (d16 & 0x0008) {
       if (duration_note44<0xFFFF) duration_note44++;

     	   if (d26&0x0008) { 

		         if (lastState_key44) {
		          	duration_note44 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,64);      
			          FIFO_PUSH(durations, duration_note44);

		        	  lastState_key44 = 0x1;
		           	duration_note44 = 0;  
	          	}

         	}

         }else if (lastState_key44) {	
             FIFO_PUSH(notes,192); 
		          FIFO_PUSH(durations, duration_note44); 
	          	lastState_key44 = 0x0; 
	            duration_note44 = 0x0;
	         }else {
		          duration_note44 = 0x0;
          }

	/*45 key */

      if (d16 & 0x0010) {
       if (duration_note45<0xFFFF) duration_note45++;

     	   if (d26&0x0010) { 

		         if (lastState_key45) {
		          	duration_note45 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,65);      
			          FIFO_PUSH(durations, duration_note45);

		        	  lastState_key45 = 0x1;
		           	duration_note45 = 0;  
	          	}

         	}

         }else if (lastState_key45) {	
             FIFO_PUSH(notes,193); 
		          FIFO_PUSH(durations, duration_note45); 
	          	lastState_key45 = 0x0; 
	            duration_note45 = 0x0;
	         }else {
		          duration_note45 = 0x0;
          }

	/*46 key */

      if (d16 & 0x0020) {
       if (duration_note46<0xFFFF) duration_note46++;

     	   if (d26&0x0020) { 

		         if (lastState_key46) {
		          	duration_note46 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,66);      
			          FIFO_PUSH(durations, duration_note46);

		        	  lastState_key46 = 0x1;
		           	duration_note46 = 0;  
	          	}

         	}

         }else if (lastState_key46) {	
             FIFO_PUSH(notes,194); 
		          FIFO_PUSH(durations, duration_note46); 
	          	lastState_key46 = 0x0; 
	            duration_note46 = 0x0;
	         }else {
		          duration_note46 = 0x0;
          }

	/*47 key */

      if (d16 & 0x0040) {
       if (duration_note47<0xFFFF) duration_note47++;

     	   if (d26&0x0040) { 

		         if (lastState_key47) {
		          	duration_note47 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,67);      
			          FIFO_PUSH(durations, duration_note47);

		        	  lastState_key47 = 0x1;
		           	duration_note47 = 0;  
	          	}

         	}

         }else if (lastState_key47) {	
             FIFO_PUSH(notes,195); 
		          FIFO_PUSH(durations, duration_note47); 
	          	lastState_key47 = 0x0; 
	            duration_note47 = 0x0;
	         }else {
		          duration_note47 = 0x0;
          }

	/*48 key */

      if (d16 & 0x0080) {
       if (duration_note48<0xFFFF) duration_note48++;

     	   if (d26&0x0080) { 

		         if (lastState_key48) {
		          	duration_note48 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,68);      
			          FIFO_PUSH(durations, duration_note48);

		        	  lastState_key48 = 0x1;
		           	duration_note48 = 0;  
	          	}

         	}

         }else if (lastState_key48) {	
             FIFO_PUSH(notes,196); 
		          FIFO_PUSH(durations, duration_note48); 
	          	lastState_key48 = 0x0; 
	            duration_note48 = 0x0;
	         }else {
		          duration_note48 = 0x0;
          }

         lastState6 = d16;
         	}
      /* 7 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_0; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d17 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_0; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d17&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_1; 
    delay(KEY_SWITCH_DELAY);  
    d27 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_1;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d27=0x0;
     }
if ((d17&0x00FF)|(lastState7&0x00FF)){
	/*49 key */

      if (d17 & 0x0001) {
       if (duration_note49<0xFFFF) duration_note49++;

     	   if (d27&0x0001) { 

		         if (lastState_key49) {
		          	duration_note49 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,69);      
			          FIFO_PUSH(durations, duration_note49);

		        	  lastState_key49 = 0x1;
		           	duration_note49 = 0;  
	          	}

         	}

         }else if (lastState_key49) {	
             FIFO_PUSH(notes,197); 
		          FIFO_PUSH(durations, duration_note49); 
	          	lastState_key49 = 0x0; 
	            duration_note49 = 0x0;
	         }else {
		          duration_note49 = 0x0;
          }

	/*50 key */

      if (d17 & 0x0002) {
       if (duration_note50<0xFFFF) duration_note50++;

     	   if (d27&0x0002) { 

		         if (lastState_key50) {
		          	duration_note50 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,70);      
			          FIFO_PUSH(durations, duration_note50);

		        	  lastState_key50 = 0x1;
		           	duration_note50 = 0;  
	          	}

         	}

         }else if (lastState_key50) {	
             FIFO_PUSH(notes,198); 
		          FIFO_PUSH(durations, duration_note50); 
	          	lastState_key50 = 0x0; 
	            duration_note50 = 0x0;
	         }else {
		          duration_note50 = 0x0;
          }

	/*51 key */

      if (d17 & 0x0004) {
       if (duration_note51<0xFFFF) duration_note51++;

     	   if (d27&0x0004) { 

		         if (lastState_key51) {
		          	duration_note51 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,71);      
			          FIFO_PUSH(durations, duration_note51);

		        	  lastState_key51 = 0x1;
		           	duration_note51 = 0;  
	          	}

         	}

         }else if (lastState_key51) {	
             FIFO_PUSH(notes,199); 
		          FIFO_PUSH(durations, duration_note51); 
	          	lastState_key51 = 0x0; 
	            duration_note51 = 0x0;
	         }else {
		          duration_note51 = 0x0;
          }

	/*52 key */

      if (d17 & 0x0008) {
       if (duration_note52<0xFFFF) duration_note52++;

     	   if (d27&0x0008) { 

		         if (lastState_key52) {
		          	duration_note52 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,72);      
			          FIFO_PUSH(durations, duration_note52);

		        	  lastState_key52 = 0x1;
		           	duration_note52 = 0;  
	          	}

         	}

         }else if (lastState_key52) {	
             FIFO_PUSH(notes,200); 
		          FIFO_PUSH(durations, duration_note52); 
	          	lastState_key52 = 0x0; 
	            duration_note52 = 0x0;
	         }else {
		          duration_note52 = 0x0;
          }

	/*53 key */

      if (d17 & 0x0010) {
       if (duration_note53<0xFFFF) duration_note53++;

     	   if (d27&0x0010) { 

		         if (lastState_key53) {
		          	duration_note53 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,73);      
			          FIFO_PUSH(durations, duration_note53);

		        	  lastState_key53 = 0x1;
		           	duration_note53 = 0;  
	          	}

         	}

         }else if (lastState_key53) {	
             FIFO_PUSH(notes,201); 
		          FIFO_PUSH(durations, duration_note53); 
	          	lastState_key53 = 0x0; 
	            duration_note53 = 0x0;
	         }else {
		          duration_note53 = 0x0;
          }

	/*54 key */

      if (d17 & 0x0020) {
       if (duration_note54<0xFFFF) duration_note54++;

     	   if (d27&0x0020) { 

		         if (lastState_key54) {
		          	duration_note54 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,74);      
			          FIFO_PUSH(durations, duration_note54);

		        	  lastState_key54 = 0x1;
		           	duration_note54 = 0;  
	          	}

         	}

         }else if (lastState_key54) {	
             FIFO_PUSH(notes,202); 
		          FIFO_PUSH(durations, duration_note54); 
	          	lastState_key54 = 0x0; 
	            duration_note54 = 0x0;
	         }else {
		          duration_note54 = 0x0;
          }

	/*55 key */

      if (d17 & 0x0040) {
       if (duration_note55<0xFFFF) duration_note55++;

     	   if (d27&0x0040) { 

		         if (lastState_key55) {
		          	duration_note55 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,75);      
			          FIFO_PUSH(durations, duration_note55);

		        	  lastState_key55 = 0x1;
		           	duration_note55 = 0;  
	          	}

         	}

         }else if (lastState_key55) {	
             FIFO_PUSH(notes,203); 
		          FIFO_PUSH(durations, duration_note55); 
	          	lastState_key55 = 0x0; 
	            duration_note55 = 0x0;
	         }else {
		          duration_note55 = 0x0;
          }

	/*56 key */

      if (d17 & 0x0080) {
       if (duration_note56<0xFFFF) duration_note56++;

     	   if (d27&0x0080) { 

		         if (lastState_key56) {
		          	duration_note56 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,76);      
			          FIFO_PUSH(durations, duration_note56);

		        	  lastState_key56 = 0x1;
		           	duration_note56 = 0;  
	          	}

         	}

         }else if (lastState_key56) {	
             FIFO_PUSH(notes,204); 
		          FIFO_PUSH(durations, duration_note56); 
	          	lastState_key56 = 0x0; 
	            duration_note56 = 0x0;
	         }else {
		          duration_note56 = 0x0;
          }

         lastState7 = d17;
         	}
      /* 8 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_7; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d18 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_7; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d18&0x00FF){  

    GPIOB->BSRRH = GPIO_Pin_2; 
    delay(KEY_SWITCH_DELAY);  
    d28 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_2;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d28=0x0;
     }
if ((d18&0x00FF)|(lastState8&0x00FF)){
	/*57 key */

      if (d18 & 0x0001) {
       if (duration_note57<0xFFFF) duration_note57++;

     	   if (d28&0x0001) { 

		         if (lastState_key57) {
		          	duration_note57 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,77);      
			          FIFO_PUSH(durations, duration_note57);

		        	  lastState_key57 = 0x1;
		           	duration_note57 = 0;  
	          	}

         	}

         }else if (lastState_key57) {	
             FIFO_PUSH(notes,205); 
		          FIFO_PUSH(durations, duration_note57); 
	          	lastState_key57 = 0x0; 
	            duration_note57 = 0x0;
	         }else {
		          duration_note57 = 0x0;
          }

	/*58 key */

      if (d18 & 0x0002) {
       if (duration_note58<0xFFFF) duration_note58++;

     	   if (d28&0x0002) { 

		         if (lastState_key58) {
		          	duration_note58 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,78);      
			          FIFO_PUSH(durations, duration_note58);

		        	  lastState_key58 = 0x1;
		           	duration_note58 = 0;  
	          	}

         	}

         }else if (lastState_key58) {	
             FIFO_PUSH(notes,206); 
		          FIFO_PUSH(durations, duration_note58); 
	          	lastState_key58 = 0x0; 
	            duration_note58 = 0x0;
	         }else {
		          duration_note58 = 0x0;
          }

	/*59 key */

      if (d18 & 0x0004) {
       if (duration_note59<0xFFFF) duration_note59++;

     	   if (d28&0x0004) { 

		         if (lastState_key59) {
		          	duration_note59 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,79);      
			          FIFO_PUSH(durations, duration_note59);

		        	  lastState_key59 = 0x1;
		           	duration_note59 = 0;  
	          	}

         	}

         }else if (lastState_key59) {	
             FIFO_PUSH(notes,207); 
		          FIFO_PUSH(durations, duration_note59); 
	          	lastState_key59 = 0x0; 
	            duration_note59 = 0x0;
	         }else {
		          duration_note59 = 0x0;
          }

	/*60 key */

      if (d18 & 0x0008) {
       if (duration_note60<0xFFFF) duration_note60++;

     	   if (d28&0x0008) { 

		         if (lastState_key60) {
		          	duration_note60 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,80);      
			          FIFO_PUSH(durations, duration_note60);

		        	  lastState_key60 = 0x1;
		           	duration_note60 = 0;  
	          	}

         	}

         }else if (lastState_key60) {	
             FIFO_PUSH(notes,208); 
		          FIFO_PUSH(durations, duration_note60); 
	          	lastState_key60 = 0x0; 
	            duration_note60 = 0x0;
	         }else {
		          duration_note60 = 0x0;
          }

	/*61 key */

      if (d18 & 0x0010) {
       if (duration_note61<0xFFFF) duration_note61++;

     	   if (d28&0x0010) { 

		         if (lastState_key61) {
		          	duration_note61 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,81);      
			          FIFO_PUSH(durations, duration_note61);

		        	  lastState_key61 = 0x1;
		           	duration_note61 = 0;  
	          	}

         	}

         }else if (lastState_key61) {	
             FIFO_PUSH(notes,209); 
		          FIFO_PUSH(durations, duration_note61); 
	          	lastState_key61 = 0x0; 
	            duration_note61 = 0x0;
	         }else {
		          duration_note61 = 0x0;
          }

	/*62 key */

      if (d18 & 0x0020) {
       if (duration_note62<0xFFFF) duration_note62++;

     	   if (d28&0x0020) { 

		         if (lastState_key62) {
		          	duration_note62 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,82);      
			          FIFO_PUSH(durations, duration_note62);

		        	  lastState_key62 = 0x1;
		           	duration_note62 = 0;  
	          	}

         	}

         }else if (lastState_key62) {	
             FIFO_PUSH(notes,210); 
		          FIFO_PUSH(durations, duration_note62); 
	          	lastState_key62 = 0x0; 
	            duration_note62 = 0x0;
	         }else {
		          duration_note62 = 0x0;
          }

	/*63 key */

      if (d18 & 0x0040) {
       if (duration_note63<0xFFFF) duration_note63++;

     	   if (d28&0x0040) { 

		         if (lastState_key63) {
		          	duration_note63 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,83);      
			          FIFO_PUSH(durations, duration_note63);

		        	  lastState_key63 = 0x1;
		           	duration_note63 = 0;  
	          	}

         	}

         }else if (lastState_key63) {	
             FIFO_PUSH(notes,211); 
		          FIFO_PUSH(durations, duration_note63); 
	          	lastState_key63 = 0x0; 
	            duration_note63 = 0x0;
	         }else {
		          duration_note63 = 0x0;
          }

	/*64 key */

      if (d18 & 0x0080) {
       if (duration_note64<0xFFFF) duration_note64++;

     	   if (d28&0x0080) { 

		         if (lastState_key64) {
		          	duration_note64 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,84);      
			          FIFO_PUSH(durations, duration_note64);

		        	  lastState_key64 = 0x1;
		           	duration_note64 = 0;  
	          	}

         	}

         }else if (lastState_key64) {	
             FIFO_PUSH(notes,212); 
		          FIFO_PUSH(durations, duration_note64); 
	          	lastState_key64 = 0x0; 
	            duration_note64 = 0x0;
	         }else {
		          duration_note64 = 0x0;
          }

         lastState8 = d18;
         	}
      /* 9 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_9; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d19 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_9; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d19&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_8; 
    delay(KEY_SWITCH_DELAY);  
    d29 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_8;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d29=0x0;
     }
if ((d19&0x00FF)|(lastState9&0x00FF)){
	/*65 key */

      if (d19 & 0x0001) {
       if (duration_note65<0xFFFF) duration_note65++;

     	   if (d29&0x0001) { 

		         if (lastState_key65) {
		          	duration_note65 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,85);      
			          FIFO_PUSH(durations, duration_note65);

		        	  lastState_key65 = 0x1;
		           	duration_note65 = 0;  
	          	}

         	}

         }else if (lastState_key65) {	
             FIFO_PUSH(notes,213); 
		          FIFO_PUSH(durations, duration_note65); 
	          	lastState_key65 = 0x0; 
	            duration_note65 = 0x0;
	         }else {
		          duration_note65 = 0x0;
          }

	/*66 key */

      if (d19 & 0x0002) {
       if (duration_note66<0xFFFF) duration_note66++;

     	   if (d29&0x0002) { 

		         if (lastState_key66) {
		          	duration_note66 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,86);      
			          FIFO_PUSH(durations, duration_note66);

		        	  lastState_key66 = 0x1;
		           	duration_note66 = 0;  
	          	}

         	}

         }else if (lastState_key66) {	
             FIFO_PUSH(notes,214); 
		          FIFO_PUSH(durations, duration_note66); 
	          	lastState_key66 = 0x0; 
	            duration_note66 = 0x0;
	         }else {
		          duration_note66 = 0x0;
          }

	/*67 key */

      if (d19 & 0x0004) {
       if (duration_note67<0xFFFF) duration_note67++;

     	   if (d29&0x0004) { 

		         if (lastState_key67) {
		          	duration_note67 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,87);      
			          FIFO_PUSH(durations, duration_note67);

		        	  lastState_key67 = 0x1;
		           	duration_note67 = 0;  
	          	}

         	}

         }else if (lastState_key67) {	
             FIFO_PUSH(notes,215); 
		          FIFO_PUSH(durations, duration_note67); 
	          	lastState_key67 = 0x0; 
	            duration_note67 = 0x0;
	         }else {
		          duration_note67 = 0x0;
          }

	/*68 key */

      if (d19 & 0x0008) {
       if (duration_note68<0xFFFF) duration_note68++;

     	   if (d29&0x0008) { 

		         if (lastState_key68) {
		          	duration_note68 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,88);      
			          FIFO_PUSH(durations, duration_note68);

		        	  lastState_key68 = 0x1;
		           	duration_note68 = 0;  
	          	}

         	}

         }else if (lastState_key68) {	
             FIFO_PUSH(notes,216); 
		          FIFO_PUSH(durations, duration_note68); 
	          	lastState_key68 = 0x0; 
	            duration_note68 = 0x0;
	         }else {
		          duration_note68 = 0x0;
          }

	/*69 key */

      if (d19 & 0x0010) {
       if (duration_note69<0xFFFF) duration_note69++;

     	   if (d29&0x0010) { 

		         if (lastState_key69) {
		          	duration_note69 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,89);      
			          FIFO_PUSH(durations, duration_note69);

		        	  lastState_key69 = 0x1;
		           	duration_note69 = 0;  
	          	}

         	}

         }else if (lastState_key69) {	
             FIFO_PUSH(notes,217); 
		          FIFO_PUSH(durations, duration_note69); 
	          	lastState_key69 = 0x0; 
	            duration_note69 = 0x0;
	         }else {
		          duration_note69 = 0x0;
          }

	/*70 key */

      if (d19 & 0x0020) {
       if (duration_note70<0xFFFF) duration_note70++;

     	   if (d29&0x0020) { 

		         if (lastState_key70) {
		          	duration_note70 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,90);      
			          FIFO_PUSH(durations, duration_note70);

		        	  lastState_key70 = 0x1;
		           	duration_note70 = 0;  
	          	}

         	}

         }else if (lastState_key70) {	
             FIFO_PUSH(notes,218); 
		          FIFO_PUSH(durations, duration_note70); 
	          	lastState_key70 = 0x0; 
	            duration_note70 = 0x0;
	         }else {
		          duration_note70 = 0x0;
          }

	/*71 key */

      if (d19 & 0x0040) {
       if (duration_note71<0xFFFF) duration_note71++;

     	   if (d29&0x0040) { 

		         if (lastState_key71) {
		          	duration_note71 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,91);      
			          FIFO_PUSH(durations, duration_note71);

		        	  lastState_key71 = 0x1;
		           	duration_note71 = 0;  
	          	}

         	}

         }else if (lastState_key71) {	
             FIFO_PUSH(notes,219); 
		          FIFO_PUSH(durations, duration_note71); 
	          	lastState_key71 = 0x0; 
	            duration_note71 = 0x0;
	         }else {
		          duration_note71 = 0x0;
          }

	/*72 key */

      if (d19 & 0x0080) {
       if (duration_note72<0xFFFF) duration_note72++;

     	   if (d29&0x0080) { 

		         if (lastState_key72) {
		          	duration_note72 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,92);      
			          FIFO_PUSH(durations, duration_note72);

		        	  lastState_key72 = 0x1;
		           	duration_note72 = 0;  
	          	}

         	}

         }else if (lastState_key72) {	
             FIFO_PUSH(notes,220); 
		          FIFO_PUSH(durations, duration_note72); 
	          	lastState_key72 = 0x0; 
	            duration_note72 = 0x0;
	         }else {
		          duration_note72 = 0x0;
          }

         lastState9 = d19;
         	}
      /* 10 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_12; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d110 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_12; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d110&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_10; 
    delay(KEY_SWITCH_DELAY);  
    d210 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_10;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d210=0x0;
     }
if ((d110&0x00FF)|(lastState10&0x00FF)){
	/*73 key */

      if (d110 & 0x0001) {
       if (duration_note73<0xFFFF) duration_note73++;

     	   if (d210&0x0001) { 

		         if (lastState_key73) {
		          	duration_note73 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,93);      
			          FIFO_PUSH(durations, duration_note73);

		        	  lastState_key73 = 0x1;
		           	duration_note73 = 0;  
	          	}

         	}

         }else if (lastState_key73) {	
             FIFO_PUSH(notes,221); 
		          FIFO_PUSH(durations, duration_note73); 
	          	lastState_key73 = 0x0; 
	            duration_note73 = 0x0;
	         }else {
		          duration_note73 = 0x0;
          }

	/*74 key */

      if (d110 & 0x0002) {
       if (duration_note74<0xFFFF) duration_note74++;

     	   if (d210&0x0002) { 

		         if (lastState_key74) {
		          	duration_note74 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,94);      
			          FIFO_PUSH(durations, duration_note74);

		        	  lastState_key74 = 0x1;
		           	duration_note74 = 0;  
	          	}

         	}

         }else if (lastState_key74) {	
             FIFO_PUSH(notes,222); 
		          FIFO_PUSH(durations, duration_note74); 
	          	lastState_key74 = 0x0; 
	            duration_note74 = 0x0;
	         }else {
		          duration_note74 = 0x0;
          }

	/*75 key */

      if (d110 & 0x0004) {
       if (duration_note75<0xFFFF) duration_note75++;

     	   if (d210&0x0004) { 

		         if (lastState_key75) {
		          	duration_note75 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,95);      
			          FIFO_PUSH(durations, duration_note75);

		        	  lastState_key75 = 0x1;
		           	duration_note75 = 0;  
	          	}

         	}

         }else if (lastState_key75) {	
             FIFO_PUSH(notes,223); 
		          FIFO_PUSH(durations, duration_note75); 
	          	lastState_key75 = 0x0; 
	            duration_note75 = 0x0;
	         }else {
		          duration_note75 = 0x0;
          }

	/*76 key */

      if (d110 & 0x0008) {
       if (duration_note76<0xFFFF) duration_note76++;

     	   if (d210&0x0008) { 

		         if (lastState_key76) {
		          	duration_note76 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,96);      
			          FIFO_PUSH(durations, duration_note76);

		        	  lastState_key76 = 0x1;
		           	duration_note76 = 0;  
	          	}

         	}

         }else if (lastState_key76) {	
             FIFO_PUSH(notes,224); 
		          FIFO_PUSH(durations, duration_note76); 
	          	lastState_key76 = 0x0; 
	            duration_note76 = 0x0;
	         }else {
		          duration_note76 = 0x0;
          }

	/*77 key */

      if (d110 & 0x0010) {
       if (duration_note77<0xFFFF) duration_note77++;

     	   if (d210&0x0010) { 

		         if (lastState_key77) {
		          	duration_note77 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,97);      
			          FIFO_PUSH(durations, duration_note77);

		        	  lastState_key77 = 0x1;
		           	duration_note77 = 0;  
	          	}

         	}

         }else if (lastState_key77) {	
             FIFO_PUSH(notes,225); 
		          FIFO_PUSH(durations, duration_note77); 
	          	lastState_key77 = 0x0; 
	            duration_note77 = 0x0;
	         }else {
		          duration_note77 = 0x0;
          }

	/*78 key */

      if (d110 & 0x0020) {
       if (duration_note78<0xFFFF) duration_note78++;

     	   if (d210&0x0020) { 

		         if (lastState_key78) {
		          	duration_note78 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,98);      
			          FIFO_PUSH(durations, duration_note78);

		        	  lastState_key78 = 0x1;
		           	duration_note78 = 0;  
	          	}

         	}

         }else if (lastState_key78) {	
             FIFO_PUSH(notes,226); 
		          FIFO_PUSH(durations, duration_note78); 
	          	lastState_key78 = 0x0; 
	            duration_note78 = 0x0;
	         }else {
		          duration_note78 = 0x0;
          }

	/*79 key */

      if (d110 & 0x0040) {
       if (duration_note79<0xFFFF) duration_note79++;

     	   if (d210&0x0040) { 

		         if (lastState_key79) {
		          	duration_note79 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,99);      
			          FIFO_PUSH(durations, duration_note79);

		        	  lastState_key79 = 0x1;
		           	duration_note79 = 0;  
	          	}

         	}

         }else if (lastState_key79) {	
             FIFO_PUSH(notes,227); 
		          FIFO_PUSH(durations, duration_note79); 
	          	lastState_key79 = 0x0; 
	            duration_note79 = 0x0;
	         }else {
		          duration_note79 = 0x0;
          }

	/*80 key */

      if (d110 & 0x0080) {
       if (duration_note80<0xFFFF) duration_note80++;

     	   if (d210&0x0080) { 

		         if (lastState_key80) {
		          	duration_note80 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,100);      
			          FIFO_PUSH(durations, duration_note80);

		        	  lastState_key80 = 0x1;
		           	duration_note80 = 0;  
	          	}

         	}

         }else if (lastState_key80) {	
             FIFO_PUSH(notes,228); 
		          FIFO_PUSH(durations, duration_note80); 
	          	lastState_key80 = 0x0; 
	            duration_note80 = 0x0;
	         }else {
		          duration_note80 = 0x0;
          }

         lastState10 = d110;
         	}
      /* 11 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_11; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d111 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_11; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    if (d111&0x00FF){  

    GPIOE->BSRRH = GPIO_Pin_13; 
    delay(KEY_SWITCH_DELAY);  
    d211 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_13;  

     GPIOA->MODER |= 0x00005555;	//PA0-8 Áóäóò âûõîäàìè
     GPIOA->ODR = 0x00FF;		//Âûñîêèé óðîâåíü íà PA0-8;
     GPIOA->MODER &= 0xFFFF0000;	//PA0-8 Áóäóò âõîäàìè

    }else{ 
         d211=0x0;
     }
if ((d111&0x00FF)|(lastState11&0x00FF)){
	/*81 key */

      if (d111 & 0x0001) {
       if (duration_note81<0xFFFF) duration_note81++;

     	   if (d211&0x0001) { 

		         if (lastState_key81) {
		          	duration_note81 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,101);      
			          FIFO_PUSH(durations, duration_note81);

		        	  lastState_key81 = 0x1;
		           	duration_note81 = 0;  
	          	}

         	}

         }else if (lastState_key81) {	
             FIFO_PUSH(notes,229); 
		          FIFO_PUSH(durations, duration_note81); 
	          	lastState_key81 = 0x0; 
	            duration_note81 = 0x0;
	         }else {
		          duration_note81 = 0x0;
          }

	/*82 key */

      if (d111 & 0x0002) {
       if (duration_note82<0xFFFF) duration_note82++;

     	   if (d211&0x0002) { 

		         if (lastState_key82) {
		          	duration_note82 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,102);      
			          FIFO_PUSH(durations, duration_note82);

		        	  lastState_key82 = 0x1;
		           	duration_note82 = 0;  
	          	}

         	}

         }else if (lastState_key82) {	
             FIFO_PUSH(notes,230); 
		          FIFO_PUSH(durations, duration_note82); 
	          	lastState_key82 = 0x0; 
	            duration_note82 = 0x0;
	         }else {
		          duration_note82 = 0x0;
          }

	/*83 key */

      if (d111 & 0x0004) {
       if (duration_note83<0xFFFF) duration_note83++;

     	   if (d211&0x0004) { 

		         if (lastState_key83) {
		          	duration_note83 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,103);      
			          FIFO_PUSH(durations, duration_note83);

		        	  lastState_key83 = 0x1;
		           	duration_note83 = 0;  
	          	}

         	}

         }else if (lastState_key83) {	
             FIFO_PUSH(notes,231); 
		          FIFO_PUSH(durations, duration_note83); 
	          	lastState_key83 = 0x0; 
	            duration_note83 = 0x0;
	         }else {
		          duration_note83 = 0x0;
          }

	/*84 key */

      if (d111 & 0x0008) {
       if (duration_note84<0xFFFF) duration_note84++;

     	   if (d211&0x0008) { 

		         if (lastState_key84) {
		          	duration_note84 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,104);      
			          FIFO_PUSH(durations, duration_note84);

		        	  lastState_key84 = 0x1;
		           	duration_note84 = 0;  
	          	}

         	}

         }else if (lastState_key84) {	
             FIFO_PUSH(notes,232); 
		          FIFO_PUSH(durations, duration_note84); 
	          	lastState_key84 = 0x0; 
	            duration_note84 = 0x0;
	         }else {
		          duration_note84 = 0x0;
          }

	/*85 key */

      if (d111 & 0x0010) {
       if (duration_note85<0xFFFF) duration_note85++;

     	   if (d211&0x0010) { 

		         if (lastState_key85) {
		          	duration_note85 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,105);      
			          FIFO_PUSH(durations, duration_note85);

		        	  lastState_key85 = 0x1;
		           	duration_note85 = 0;  
	          	}

         	}

         }else if (lastState_key85) {	
             FIFO_PUSH(notes,233); 
		          FIFO_PUSH(durations, duration_note85); 
	          	lastState_key85 = 0x0; 
	            duration_note85 = 0x0;
	         }else {
		          duration_note85 = 0x0;
          }

	/*86 key */

      if (d111 & 0x0020) {
       if (duration_note86<0xFFFF) duration_note86++;

     	   if (d211&0x0020) { 

		         if (lastState_key86) {
		          	duration_note86 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,106);      
			          FIFO_PUSH(durations, duration_note86);

		        	  lastState_key86 = 0x1;
		           	duration_note86 = 0;  
	          	}

         	}

         }else if (lastState_key86) {	
             FIFO_PUSH(notes,234); 
		          FIFO_PUSH(durations, duration_note86); 
	          	lastState_key86 = 0x0; 
	            duration_note86 = 0x0;
	         }else {
		          duration_note86 = 0x0;
          }

	/*87 key */

      if (d111 & 0x0040) {
       if (duration_note87<0xFFFF) duration_note87++;

     	   if (d211&0x0040) { 

		         if (lastState_key87) {
		          	duration_note87 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,107);      
			          FIFO_PUSH(durations, duration_note87);

		        	  lastState_key87 = 0x1;
		           	duration_note87 = 0;  
	          	}

         	}

         }else if (lastState_key87) {	
             FIFO_PUSH(notes,235); 
		          FIFO_PUSH(durations, duration_note87); 
	          	lastState_key87 = 0x0; 
	            duration_note87 = 0x0;
	         }else {
		          duration_note87 = 0x0;
          }

	/*88 key */

      if (d111 & 0x0080) {
       if (duration_note88<0xFFFF) duration_note88++;

     	   if (d211&0x0080) { 

		         if (lastState_key88) {
		          	duration_note88 = 0;
	          	} else {
	 	          	FIFO_PUSH(notes,108);      
			          FIFO_PUSH(durations, duration_note88);

		        	  lastState_key88 = 0x1;
		           	duration_note88 = 0;  
	          	}

         	}

         }else if (lastState_key88) {	
             FIFO_PUSH(notes,236); 
		          FIFO_PUSH(durations, duration_note88); 
	          	lastState_key88 = 0x0; 
	            duration_note88 = 0x0;
	         }else {
		          duration_note88 = 0x0;
          }

         lastState11 = d111;
         	}

}
