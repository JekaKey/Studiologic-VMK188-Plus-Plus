#define STM32F40XX

#include "keyboardscan.h"

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

uint16_t lastState_key1=0x00;
uint16_t lastState_key2=0x00;
uint16_t lastState_key3=0x00;
uint16_t lastState_key4=0x00;
uint16_t lastState_key5=0x00;
uint16_t lastState_key6=0x00;
uint16_t lastState_key7=0x00;
uint16_t lastState_key8=0x00;
uint16_t lastState_key9=0x00;
uint16_t lastState_key10=0x00;
uint16_t lastState_key11=0x00;
uint16_t lastState_key12=0x00;
uint16_t lastState_key13=0x00;
uint16_t lastState_key14=0x00;
uint16_t lastState_key15=0x00;
uint16_t lastState_key16=0x00;
uint16_t lastState_key17=0x00;
uint16_t lastState_key18=0x00;
uint16_t lastState_key19=0x00;
uint16_t lastState_key20=0x00;
uint16_t lastState_key21=0x00;
uint16_t lastState_key22=0x00;
uint16_t lastState_key23=0x00;
uint16_t lastState_key24=0x00;
uint16_t lastState_key25=0x00;
uint16_t lastState_key26=0x00;
uint16_t lastState_key27=0x00;
uint16_t lastState_key28=0x00;
uint16_t lastState_key29=0x00;
uint16_t lastState_key30=0x00;
uint16_t lastState_key31=0x00;
uint16_t lastState_key32=0x00;
uint16_t lastState_key33=0x00;
uint16_t lastState_key34=0x00;
uint16_t lastState_key35=0x00;
uint16_t lastState_key36=0x00;
uint16_t lastState_key37=0x00;
uint16_t lastState_key38=0x00;
uint16_t lastState_key39=0x00;
uint16_t lastState_key40=0x00;
uint16_t lastState_key41=0x00;
uint16_t lastState_key42=0x00;
uint16_t lastState_key43=0x00;
uint16_t lastState_key44=0x00;
uint16_t lastState_key45=0x00;
uint16_t lastState_key46=0x00;
uint16_t lastState_key47=0x00;
uint16_t lastState_key48=0x00;
uint16_t lastState_key49=0x00;
uint16_t lastState_key50=0x00;
uint16_t lastState_key51=0x00;
uint16_t lastState_key52=0x00;
uint16_t lastState_key53=0x00;
uint16_t lastState_key54=0x00;
uint16_t lastState_key55=0x00;
uint16_t lastState_key56=0x00;
uint16_t lastState_key57=0x00;
uint16_t lastState_key58=0x00;
uint16_t lastState_key59=0x00;
uint16_t lastState_key60=0x00;
uint16_t lastState_key61=0x00;
uint16_t lastState_key62=0x00;
uint16_t lastState_key63=0x00;
uint16_t lastState_key64=0x00;
uint16_t lastState_key65=0x00;
uint16_t lastState_key66=0x00;
uint16_t lastState_key67=0x00;
uint16_t lastState_key68=0x00;
uint16_t lastState_key69=0x00;
uint16_t lastState_key70=0x00;
uint16_t lastState_key71=0x00;
uint16_t lastState_key72=0x00;
uint16_t lastState_key73=0x00;
uint16_t lastState_key74=0x00;
uint16_t lastState_key75=0x00;
uint16_t lastState_key76=0x00;
uint16_t lastState_key77=0x00;
uint16_t lastState_key78=0x00;
uint16_t lastState_key79=0x00;
uint16_t lastState_key80=0x00;
uint16_t lastState_key81=0x00;
uint16_t lastState_key82=0x00;
uint16_t lastState_key83=0x00;
uint16_t lastState_key84=0x00;
uint16_t lastState_key85=0x00;
uint16_t lastState_key86=0x00;
uint16_t lastState_key87=0x00;
uint16_t lastState_key88=0x00;



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

    GPIOE->BSRRH = GPIO_Pin_15; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d11 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_15; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d11){  //Read second sensors only if some first sensor is pressed

    GPIOE->BSRRH = GPIO_Pin_14; 
    delay(KEY_SWITCH_DELAY);  
    d21 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_14;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d21=0;
     }
if ((d11)|(lastState1)){
	/*1 key */

      if (d11 & 0x01) { //check first sensor key1
       duration_note1++; //add one timer tick to note duration

     	   if (d21&0x01) { //check second sensor key1

		         if (lastState_key1) {
		          	duration_note1 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,21); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note1); //send note duration

		        	  lastState_key1 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note1 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key1) {	
               FIFO_PUSH(notes,149); // sent note off
		          FIFO_PUSH(durations, duration_note1);  //sent duration of noteoff
	          	lastState_key1 = 0x0; // remove "sent" bits from last status
	            duration_note1 = 0;
	         }else {
		          duration_note1 = 0;
          }

	/*2 key */

      if (d11 & 0x02) { //check first sensor key2
       duration_note2++; //add one timer tick to note duration

     	   if (d21&0x02) { //check second sensor key2

		         if (lastState_key2) {
		          	duration_note2 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,22); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note2); //send note duration

		        	  lastState_key2 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note2 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key2) {	
               FIFO_PUSH(notes,150); // sent note off
		          FIFO_PUSH(durations, duration_note2);  //sent duration of noteoff
	          	lastState_key2 = 0x0; // remove "sent" bits from last status
	            duration_note2 = 0;
	         }else {
		          duration_note2 = 0;
          }

	/*3 key */

      if (d11 & 0x04) { //check first sensor key3
       duration_note3++; //add one timer tick to note duration

     	   if (d21&0x04) { //check second sensor key3

		         if (lastState_key3) {
		          	duration_note3 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,23); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note3); //send note duration

		        	  lastState_key3 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note3 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key3) {	
               FIFO_PUSH(notes,151); // sent note off
		          FIFO_PUSH(durations, duration_note3);  //sent duration of noteoff
	          	lastState_key3 = 0x0; // remove "sent" bits from last status
	            duration_note3 = 0;
	         }else {
		          duration_note3 = 0;
          }

	/*4 key */

      if (d11 & 0x08) { //check first sensor key4
       duration_note4++; //add one timer tick to note duration

     	   if (d21&0x08) { //check second sensor key4

		         if (lastState_key4) {
		          	duration_note4 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,24); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note4); //send note duration

		        	  lastState_key4 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note4 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key4) {	
               FIFO_PUSH(notes,152); // sent note off
		          FIFO_PUSH(durations, duration_note4);  //sent duration of noteoff
	          	lastState_key4 = 0x0; // remove "sent" bits from last status
	            duration_note4 = 0;
	         }else {
		          duration_note4 = 0;
          }

	/*5 key */

      if (d11 & 0x10) { //check first sensor key5
       duration_note5++; //add one timer tick to note duration

     	   if (d21&0x10) { //check second sensor key5

		         if (lastState_key5) {
		          	duration_note5 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,25); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note5); //send note duration

		        	  lastState_key5 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note5 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key5) {	
               FIFO_PUSH(notes,153); // sent note off
		          FIFO_PUSH(durations, duration_note5);  //sent duration of noteoff
	          	lastState_key5 = 0x0; // remove "sent" bits from last status
	            duration_note5 = 0;
	         }else {
		          duration_note5 = 0;
          }

	/*6 key */

      if (d11 & 0x20) { //check first sensor key6
       duration_note6++; //add one timer tick to note duration

     	   if (d21&0x20) { //check second sensor key6

		         if (lastState_key6) {
		          	duration_note6 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,26); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note6); //send note duration

		        	  lastState_key6 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note6 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key6) {	
               FIFO_PUSH(notes,154); // sent note off
		          FIFO_PUSH(durations, duration_note6);  //sent duration of noteoff
	          	lastState_key6 = 0x0; // remove "sent" bits from last status
	            duration_note6 = 0;
	         }else {
		          duration_note6 = 0;
          }

	/*7 key */

      if (d11 & 0x40) { //check first sensor key7
       duration_note7++; //add one timer tick to note duration

     	   if (d21&0x40) { //check second sensor key7

		         if (lastState_key7) {
		          	duration_note7 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,27); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note7); //send note duration

		        	  lastState_key7 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note7 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key7) {	
               FIFO_PUSH(notes,155); // sent note off
		          FIFO_PUSH(durations, duration_note7);  //sent duration of noteoff
	          	lastState_key7 = 0x0; // remove "sent" bits from last status
	            duration_note7 = 0;
	         }else {
		          duration_note7 = 0;
          }

	/*8 key */

      if (d11 & 0x80) { //check first sensor key8
       duration_note8++; //add one timer tick to note duration

     	   if (d21&0x80) { //check second sensor key8

		         if (lastState_key8) {
		          	duration_note8 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,28); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note8); //send note duration

		        	  lastState_key8 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note8 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key8) {	
               FIFO_PUSH(notes,156); // sent note off
		          FIFO_PUSH(durations, duration_note8);  //sent duration of noteoff
	          	lastState_key8 = 0x0; // remove "sent" bits from last status
	            duration_note8 = 0;
	         }else {
		          duration_note8 = 0;
          }

        lastState1 = d11;
       	}
      /* 2 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_11; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d12 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_11; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d12){  //Read second sensors only if some first sensor is pressed

    GPIOB->BSRRH = GPIO_Pin_10; 
    delay(KEY_SWITCH_DELAY);  
    d22 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_10;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d22=0;
     }
if ((d12)|(lastState2)){
	/*9 key */

      if (d12 & 0x01) { //check first sensor key1
       duration_note9++; //add one timer tick to note duration

     	   if (d22&0x01) { //check second sensor key1

		         if (lastState_key9) {
		          	duration_note9 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,29); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note9); //send note duration

		        	  lastState_key9 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note9 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key9) {	
               FIFO_PUSH(notes,157); // sent note off
		          FIFO_PUSH(durations, duration_note9);  //sent duration of noteoff
	          	lastState_key9 = 0x0; // remove "sent" bits from last status
	            duration_note9 = 0;
	         }else {
		          duration_note9 = 0;
          }

	/*10 key */

      if (d12 & 0x02) { //check first sensor key2
       duration_note10++; //add one timer tick to note duration

     	   if (d22&0x02) { //check second sensor key2

		         if (lastState_key10) {
		          	duration_note10 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,30); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note10); //send note duration

		        	  lastState_key10 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note10 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key10) {	
               FIFO_PUSH(notes,158); // sent note off
		          FIFO_PUSH(durations, duration_note10);  //sent duration of noteoff
	          	lastState_key10 = 0x0; // remove "sent" bits from last status
	            duration_note10 = 0;
	         }else {
		          duration_note10 = 0;
          }

	/*11 key */

      if (d12 & 0x04) { //check first sensor key3
       duration_note11++; //add one timer tick to note duration

     	   if (d22&0x04) { //check second sensor key3

		         if (lastState_key11) {
		          	duration_note11 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,31); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note11); //send note duration

		        	  lastState_key11 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note11 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key11) {	
               FIFO_PUSH(notes,159); // sent note off
		          FIFO_PUSH(durations, duration_note11);  //sent duration of noteoff
	          	lastState_key11 = 0x0; // remove "sent" bits from last status
	            duration_note11 = 0;
	         }else {
		          duration_note11 = 0;
          }

	/*12 key */

      if (d12 & 0x08) { //check first sensor key4
       duration_note12++; //add one timer tick to note duration

     	   if (d22&0x08) { //check second sensor key4

		         if (lastState_key12) {
		          	duration_note12 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,32); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note12); //send note duration

		        	  lastState_key12 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note12 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key12) {	
               FIFO_PUSH(notes,160); // sent note off
		          FIFO_PUSH(durations, duration_note12);  //sent duration of noteoff
	          	lastState_key12 = 0x0; // remove "sent" bits from last status
	            duration_note12 = 0;
	         }else {
		          duration_note12 = 0;
          }

	/*13 key */

      if (d12 & 0x10) { //check first sensor key5
       duration_note13++; //add one timer tick to note duration

     	   if (d22&0x10) { //check second sensor key5

		         if (lastState_key13) {
		          	duration_note13 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,33); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note13); //send note duration

		        	  lastState_key13 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note13 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key13) {	
               FIFO_PUSH(notes,161); // sent note off
		          FIFO_PUSH(durations, duration_note13);  //sent duration of noteoff
	          	lastState_key13 = 0x0; // remove "sent" bits from last status
	            duration_note13 = 0;
	         }else {
		          duration_note13 = 0;
          }

	/*14 key */

      if (d12 & 0x20) { //check first sensor key6
       duration_note14++; //add one timer tick to note duration

     	   if (d22&0x20) { //check second sensor key6

		         if (lastState_key14) {
		          	duration_note14 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,34); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note14); //send note duration

		        	  lastState_key14 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note14 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key14) {	
               FIFO_PUSH(notes,162); // sent note off
		          FIFO_PUSH(durations, duration_note14);  //sent duration of noteoff
	          	lastState_key14 = 0x0; // remove "sent" bits from last status
	            duration_note14 = 0;
	         }else {
		          duration_note14 = 0;
          }

	/*15 key */

      if (d12 & 0x40) { //check first sensor key7
       duration_note15++; //add one timer tick to note duration

     	   if (d22&0x40) { //check second sensor key7

		         if (lastState_key15) {
		          	duration_note15 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,35); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note15); //send note duration

		        	  lastState_key15 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note15 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key15) {	
               FIFO_PUSH(notes,163); // sent note off
		          FIFO_PUSH(durations, duration_note15);  //sent duration of noteoff
	          	lastState_key15 = 0x0; // remove "sent" bits from last status
	            duration_note15 = 0;
	         }else {
		          duration_note15 = 0;
          }

	/*16 key */

      if (d12 & 0x80) { //check first sensor key8
       duration_note16++; //add one timer tick to note duration

     	   if (d22&0x80) { //check second sensor key8

		         if (lastState_key16) {
		          	duration_note16 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,36); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note16); //send note duration

		        	  lastState_key16 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note16 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key16) {	
               FIFO_PUSH(notes,164); // sent note off
		          FIFO_PUSH(durations, duration_note16);  //sent duration of noteoff
	          	lastState_key16 = 0x0; // remove "sent" bits from last status
	            duration_note16 = 0;
	         }else {
		          duration_note16 = 0;
          }

        lastState2 = d12;
       	}
      /* 3 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_13; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d13 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_13; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d13){  //Read second sensors only if some first sensor is pressed

    GPIOB->BSRRH = GPIO_Pin_12; 
    delay(KEY_SWITCH_DELAY);  
    d23 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_12;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d23=0;
     }
if ((d13)|(lastState3)){
	/*17 key */

      if (d13 & 0x01) { //check first sensor key1
       duration_note17++; //add one timer tick to note duration

     	   if (d23&0x01) { //check second sensor key1

		         if (lastState_key17) {
		          	duration_note17 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,37); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note17); //send note duration

		        	  lastState_key17 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note17 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key17) {	
               FIFO_PUSH(notes,165); // sent note off
		          FIFO_PUSH(durations, duration_note17);  //sent duration of noteoff
	          	lastState_key17 = 0x0; // remove "sent" bits from last status
	            duration_note17 = 0;
	         }else {
		          duration_note17 = 0;
          }

	/*18 key */

      if (d13 & 0x02) { //check first sensor key2
       duration_note18++; //add one timer tick to note duration

     	   if (d23&0x02) { //check second sensor key2

		         if (lastState_key18) {
		          	duration_note18 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,38); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note18); //send note duration

		        	  lastState_key18 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note18 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key18) {	
               FIFO_PUSH(notes,166); // sent note off
		          FIFO_PUSH(durations, duration_note18);  //sent duration of noteoff
	          	lastState_key18 = 0x0; // remove "sent" bits from last status
	            duration_note18 = 0;
	         }else {
		          duration_note18 = 0;
          }

	/*19 key */

      if (d13 & 0x04) { //check first sensor key3
       duration_note19++; //add one timer tick to note duration

     	   if (d23&0x04) { //check second sensor key3

		         if (lastState_key19) {
		          	duration_note19 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,39); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note19); //send note duration

		        	  lastState_key19 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note19 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key19) {	
               FIFO_PUSH(notes,167); // sent note off
		          FIFO_PUSH(durations, duration_note19);  //sent duration of noteoff
	          	lastState_key19 = 0x0; // remove "sent" bits from last status
	            duration_note19 = 0;
	         }else {
		          duration_note19 = 0;
          }

	/*20 key */

      if (d13 & 0x08) { //check first sensor key4
       duration_note20++; //add one timer tick to note duration

     	   if (d23&0x08) { //check second sensor key4

		         if (lastState_key20) {
		          	duration_note20 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,40); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note20); //send note duration

		        	  lastState_key20 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note20 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key20) {	
               FIFO_PUSH(notes,168); // sent note off
		          FIFO_PUSH(durations, duration_note20);  //sent duration of noteoff
	          	lastState_key20 = 0x0; // remove "sent" bits from last status
	            duration_note20 = 0;
	         }else {
		          duration_note20 = 0;
          }

	/*21 key */

      if (d13 & 0x10) { //check first sensor key5
       duration_note21++; //add one timer tick to note duration

     	   if (d23&0x10) { //check second sensor key5

		         if (lastState_key21) {
		          	duration_note21 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,41); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note21); //send note duration

		        	  lastState_key21 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note21 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key21) {	
               FIFO_PUSH(notes,169); // sent note off
		          FIFO_PUSH(durations, duration_note21);  //sent duration of noteoff
	          	lastState_key21 = 0x0; // remove "sent" bits from last status
	            duration_note21 = 0;
	         }else {
		          duration_note21 = 0;
          }

	/*22 key */

      if (d13 & 0x20) { //check first sensor key6
       duration_note22++; //add one timer tick to note duration

     	   if (d23&0x20) { //check second sensor key6

		         if (lastState_key22) {
		          	duration_note22 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,42); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note22); //send note duration

		        	  lastState_key22 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note22 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key22) {	
               FIFO_PUSH(notes,170); // sent note off
		          FIFO_PUSH(durations, duration_note22);  //sent duration of noteoff
	          	lastState_key22 = 0x0; // remove "sent" bits from last status
	            duration_note22 = 0;
	         }else {
		          duration_note22 = 0;
          }

	/*23 key */

      if (d13 & 0x40) { //check first sensor key7
       duration_note23++; //add one timer tick to note duration

     	   if (d23&0x40) { //check second sensor key7

		         if (lastState_key23) {
		          	duration_note23 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,43); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note23); //send note duration

		        	  lastState_key23 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note23 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key23) {	
               FIFO_PUSH(notes,171); // sent note off
		          FIFO_PUSH(durations, duration_note23);  //sent duration of noteoff
	          	lastState_key23 = 0x0; // remove "sent" bits from last status
	            duration_note23 = 0;
	         }else {
		          duration_note23 = 0;
          }

	/*24 key */

      if (d13 & 0x80) { //check first sensor key8
       duration_note24++; //add one timer tick to note duration

     	   if (d23&0x80) { //check second sensor key8

		         if (lastState_key24) {
		          	duration_note24 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,44); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note24); //send note duration

		        	  lastState_key24 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note24 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key24) {	
               FIFO_PUSH(notes,172); // sent note off
		          FIFO_PUSH(durations, duration_note24);  //sent duration of noteoff
	          	lastState_key24 = 0x0; // remove "sent" bits from last status
	            duration_note24 = 0;
	         }else {
		          duration_note24 = 0;
          }

        lastState3 = d13;
       	}
      /* 4 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_15; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d14 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_15; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d14){  //Read second sensors only if some first sensor is pressed

    GPIOB->BSRRH = GPIO_Pin_14; 
    delay(KEY_SWITCH_DELAY);  
    d24 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_14;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d24=0;
     }
if ((d14)|(lastState4)){
	/*25 key */

      if (d14 & 0x01) { //check first sensor key1
       duration_note25++; //add one timer tick to note duration

     	   if (d24&0x01) { //check second sensor key1

		         if (lastState_key25) {
		          	duration_note25 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,45); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note25); //send note duration

		        	  lastState_key25 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note25 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key25) {	
               FIFO_PUSH(notes,173); // sent note off
		          FIFO_PUSH(durations, duration_note25);  //sent duration of noteoff
	          	lastState_key25 = 0x0; // remove "sent" bits from last status
	            duration_note25 = 0;
	         }else {
		          duration_note25 = 0;
          }

	/*26 key */

      if (d14 & 0x02) { //check first sensor key2
       duration_note26++; //add one timer tick to note duration

     	   if (d24&0x02) { //check second sensor key2

		         if (lastState_key26) {
		          	duration_note26 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,46); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note26); //send note duration

		        	  lastState_key26 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note26 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key26) {	
               FIFO_PUSH(notes,174); // sent note off
		          FIFO_PUSH(durations, duration_note26);  //sent duration of noteoff
	          	lastState_key26 = 0x0; // remove "sent" bits from last status
	            duration_note26 = 0;
	         }else {
		          duration_note26 = 0;
          }

	/*27 key */

      if (d14 & 0x04) { //check first sensor key3
       duration_note27++; //add one timer tick to note duration

     	   if (d24&0x04) { //check second sensor key3

		         if (lastState_key27) {
		          	duration_note27 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,47); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note27); //send note duration

		        	  lastState_key27 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note27 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key27) {	
               FIFO_PUSH(notes,175); // sent note off
		          FIFO_PUSH(durations, duration_note27);  //sent duration of noteoff
	          	lastState_key27 = 0x0; // remove "sent" bits from last status
	            duration_note27 = 0;
	         }else {
		          duration_note27 = 0;
          }

	/*28 key */

      if (d14 & 0x08) { //check first sensor key4
       duration_note28++; //add one timer tick to note duration

     	   if (d24&0x08) { //check second sensor key4

		         if (lastState_key28) {
		          	duration_note28 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,48); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note28); //send note duration

		        	  lastState_key28 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note28 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key28) {	
               FIFO_PUSH(notes,176); // sent note off
		          FIFO_PUSH(durations, duration_note28);  //sent duration of noteoff
	          	lastState_key28 = 0x0; // remove "sent" bits from last status
	            duration_note28 = 0;
	         }else {
		          duration_note28 = 0;
          }

	/*29 key */

      if (d14 & 0x10) { //check first sensor key5
       duration_note29++; //add one timer tick to note duration

     	   if (d24&0x10) { //check second sensor key5

		         if (lastState_key29) {
		          	duration_note29 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,49); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note29); //send note duration

		        	  lastState_key29 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note29 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key29) {	
               FIFO_PUSH(notes,177); // sent note off
		          FIFO_PUSH(durations, duration_note29);  //sent duration of noteoff
	          	lastState_key29 = 0x0; // remove "sent" bits from last status
	            duration_note29 = 0;
	         }else {
		          duration_note29 = 0;
          }

	/*30 key */

      if (d14 & 0x20) { //check first sensor key6
       duration_note30++; //add one timer tick to note duration

     	   if (d24&0x20) { //check second sensor key6

		         if (lastState_key30) {
		          	duration_note30 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,50); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note30); //send note duration

		        	  lastState_key30 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note30 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key30) {	
               FIFO_PUSH(notes,178); // sent note off
		          FIFO_PUSH(durations, duration_note30);  //sent duration of noteoff
	          	lastState_key30 = 0x0; // remove "sent" bits from last status
	            duration_note30 = 0;
	         }else {
		          duration_note30 = 0;
          }

	/*31 key */

      if (d14 & 0x40) { //check first sensor key7
       duration_note31++; //add one timer tick to note duration

     	   if (d24&0x40) { //check second sensor key7

		         if (lastState_key31) {
		          	duration_note31 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,51); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note31); //send note duration

		        	  lastState_key31 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note31 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key31) {	
               FIFO_PUSH(notes,179); // sent note off
		          FIFO_PUSH(durations, duration_note31);  //sent duration of noteoff
	          	lastState_key31 = 0x0; // remove "sent" bits from last status
	            duration_note31 = 0;
	         }else {
		          duration_note31 = 0;
          }

	/*32 key */

      if (d14 & 0x80) { //check first sensor key8
       duration_note32++; //add one timer tick to note duration

     	   if (d24&0x80) { //check second sensor key8

		         if (lastState_key32) {
		          	duration_note32 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,52); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note32); //send note duration

		        	  lastState_key32 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note32 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key32) {	
               FIFO_PUSH(notes,180); // sent note off
		          FIFO_PUSH(durations, duration_note32);  //sent duration of noteoff
	          	lastState_key32 = 0x0; // remove "sent" bits from last status
	            duration_note32 = 0;
	         }else {
		          duration_note32 = 0;
          }

        lastState4 = d14;
       	}
      /* 5 chunk */ 

    GPIOD->BSRRH = GPIO_Pin_9; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d15 = ~GPIOA->IDR; //Read port state first contact 
    GPIOD->BSRRL = GPIO_Pin_9; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d15){  //Read second sensors only if some first sensor is pressed

    GPIOD->BSRRH = GPIO_Pin_8; 
    delay(KEY_SWITCH_DELAY);  
    d25 = ~GPIOA->IDR; //Read port state second contact 
    GPIOD->BSRRL = GPIO_Pin_8;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d25=0;
     }
if ((d15)|(lastState5)){
	/*33 key */

      if (d15 & 0x01) { //check first sensor key1
       duration_note33++; //add one timer tick to note duration

     	   if (d25&0x01) { //check second sensor key1

		         if (lastState_key33) {
		          	duration_note33 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,53); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note33); //send note duration

		        	  lastState_key33 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note33 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key33) {	
               FIFO_PUSH(notes,181); // sent note off
		          FIFO_PUSH(durations, duration_note33);  //sent duration of noteoff
	          	lastState_key33 = 0x0; // remove "sent" bits from last status
	            duration_note33 = 0;
	         }else {
		          duration_note33 = 0;
          }

	/*34 key */

      if (d15 & 0x02) { //check first sensor key2
       duration_note34++; //add one timer tick to note duration

     	   if (d25&0x02) { //check second sensor key2

		         if (lastState_key34) {
		          	duration_note34 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,54); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note34); //send note duration

		        	  lastState_key34 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note34 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key34) {	
               FIFO_PUSH(notes,182); // sent note off
		          FIFO_PUSH(durations, duration_note34);  //sent duration of noteoff
	          	lastState_key34 = 0x0; // remove "sent" bits from last status
	            duration_note34 = 0;
	         }else {
		          duration_note34 = 0;
          }

	/*35 key */

      if (d15 & 0x04) { //check first sensor key3
       duration_note35++; //add one timer tick to note duration

     	   if (d25&0x04) { //check second sensor key3

		         if (lastState_key35) {
		          	duration_note35 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,55); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note35); //send note duration

		        	  lastState_key35 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note35 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key35) {	
               FIFO_PUSH(notes,183); // sent note off
		          FIFO_PUSH(durations, duration_note35);  //sent duration of noteoff
	          	lastState_key35 = 0x0; // remove "sent" bits from last status
	            duration_note35 = 0;
	         }else {
		          duration_note35 = 0;
          }

	/*36 key */

      if (d15 & 0x08) { //check first sensor key4
       duration_note36++; //add one timer tick to note duration

     	   if (d25&0x08) { //check second sensor key4

		         if (lastState_key36) {
		          	duration_note36 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,56); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note36); //send note duration

		        	  lastState_key36 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note36 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key36) {	
               FIFO_PUSH(notes,184); // sent note off
		          FIFO_PUSH(durations, duration_note36);  //sent duration of noteoff
	          	lastState_key36 = 0x0; // remove "sent" bits from last status
	            duration_note36 = 0;
	         }else {
		          duration_note36 = 0;
          }

	/*37 key */

      if (d15 & 0x10) { //check first sensor key5
       duration_note37++; //add one timer tick to note duration

     	   if (d25&0x10) { //check second sensor key5

		         if (lastState_key37) {
		          	duration_note37 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,57); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note37); //send note duration

		        	  lastState_key37 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note37 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key37) {	
               FIFO_PUSH(notes,185); // sent note off
		          FIFO_PUSH(durations, duration_note37);  //sent duration of noteoff
	          	lastState_key37 = 0x0; // remove "sent" bits from last status
	            duration_note37 = 0;
	         }else {
		          duration_note37 = 0;
          }

	/*38 key */

      if (d15 & 0x20) { //check first sensor key6
       duration_note38++; //add one timer tick to note duration

     	   if (d25&0x20) { //check second sensor key6

		         if (lastState_key38) {
		          	duration_note38 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,58); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note38); //send note duration

		        	  lastState_key38 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note38 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key38) {	
               FIFO_PUSH(notes,186); // sent note off
		          FIFO_PUSH(durations, duration_note38);  //sent duration of noteoff
	          	lastState_key38 = 0x0; // remove "sent" bits from last status
	            duration_note38 = 0;
	         }else {
		          duration_note38 = 0;
          }

	/*39 key */

      if (d15 & 0x40) { //check first sensor key7
       duration_note39++; //add one timer tick to note duration

     	   if (d25&0x40) { //check second sensor key7

		         if (lastState_key39) {
		          	duration_note39 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,59); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note39); //send note duration

		        	  lastState_key39 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note39 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key39) {	
               FIFO_PUSH(notes,187); // sent note off
		          FIFO_PUSH(durations, duration_note39);  //sent duration of noteoff
	          	lastState_key39 = 0x0; // remove "sent" bits from last status
	            duration_note39 = 0;
	         }else {
		          duration_note39 = 0;
          }

	/*40 key */

      if (d15 & 0x80) { //check first sensor key8
       duration_note40++; //add one timer tick to note duration

     	   if (d25&0x80) { //check second sensor key8

		         if (lastState_key40) {
		          	duration_note40 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,60); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note40); //send note duration

		        	  lastState_key40 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note40 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key40) {	
               FIFO_PUSH(notes,188); // sent note off
		          FIFO_PUSH(durations, duration_note40);  //sent duration of noteoff
	          	lastState_key40 = 0x0; // remove "sent" bits from last status
	            duration_note40 = 0;
	         }else {
		          duration_note40 = 0;
          }

        lastState5 = d15;
       	}
      /* 6 chunk */ 

    GPIOC->BSRRH = GPIO_Pin_4; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d16 = ~GPIOA->IDR; //Read port state first contact 
    GPIOC->BSRRL = GPIO_Pin_4; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d16){  //Read second sensors only if some first sensor is pressed

    GPIOC->BSRRH = GPIO_Pin_5; 
    delay(KEY_SWITCH_DELAY);  
    d26 = ~GPIOA->IDR; //Read port state second contact 
    GPIOC->BSRRL = GPIO_Pin_5;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d26=0;
     }
if ((d16)|(lastState6)){
	/*41 key */

      if (d16 & 0x01) { //check first sensor key1
       duration_note41++; //add one timer tick to note duration

     	   if (d26&0x01) { //check second sensor key1

		         if (lastState_key41) {
		          	duration_note41 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,61); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note41); //send note duration

		        	  lastState_key41 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note41 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key41) {	
               FIFO_PUSH(notes,189); // sent note off
		          FIFO_PUSH(durations, duration_note41);  //sent duration of noteoff
	          	lastState_key41 = 0x0; // remove "sent" bits from last status
	            duration_note41 = 0;
	         }else {
		          duration_note41 = 0;
          }

	/*42 key */

      if (d16 & 0x02) { //check first sensor key2
       duration_note42++; //add one timer tick to note duration

     	   if (d26&0x02) { //check second sensor key2

		         if (lastState_key42) {
		          	duration_note42 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,62); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note42); //send note duration

		        	  lastState_key42 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note42 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key42) {	
               FIFO_PUSH(notes,190); // sent note off
		          FIFO_PUSH(durations, duration_note42);  //sent duration of noteoff
	          	lastState_key42 = 0x0; // remove "sent" bits from last status
	            duration_note42 = 0;
	         }else {
		          duration_note42 = 0;
          }

	/*43 key */

      if (d16 & 0x04) { //check first sensor key3
       duration_note43++; //add one timer tick to note duration

     	   if (d26&0x04) { //check second sensor key3

		         if (lastState_key43) {
		          	duration_note43 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,63); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note43); //send note duration

		        	  lastState_key43 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note43 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key43) {	
               FIFO_PUSH(notes,191); // sent note off
		          FIFO_PUSH(durations, duration_note43);  //sent duration of noteoff
	          	lastState_key43 = 0x0; // remove "sent" bits from last status
	            duration_note43 = 0;
	         }else {
		          duration_note43 = 0;
          }

	/*44 key */

      if (d16 & 0x08) { //check first sensor key4
       duration_note44++; //add one timer tick to note duration

     	   if (d26&0x08) { //check second sensor key4

		         if (lastState_key44) {
		          	duration_note44 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,64); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note44); //send note duration

		        	  lastState_key44 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note44 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key44) {	
               FIFO_PUSH(notes,192); // sent note off
		          FIFO_PUSH(durations, duration_note44);  //sent duration of noteoff
	          	lastState_key44 = 0x0; // remove "sent" bits from last status
	            duration_note44 = 0;
	         }else {
		          duration_note44 = 0;
          }

	/*45 key */

      if (d16 & 0x10) { //check first sensor key5
       duration_note45++; //add one timer tick to note duration

     	   if (d26&0x10) { //check second sensor key5

		         if (lastState_key45) {
		          	duration_note45 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,65); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note45); //send note duration

		        	  lastState_key45 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note45 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key45) {	
               FIFO_PUSH(notes,193); // sent note off
		          FIFO_PUSH(durations, duration_note45);  //sent duration of noteoff
	          	lastState_key45 = 0x0; // remove "sent" bits from last status
	            duration_note45 = 0;
	         }else {
		          duration_note45 = 0;
          }

	/*46 key */

      if (d16 & 0x20) { //check first sensor key6
       duration_note46++; //add one timer tick to note duration

     	   if (d26&0x20) { //check second sensor key6

		         if (lastState_key46) {
		          	duration_note46 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,66); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note46); //send note duration

		        	  lastState_key46 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note46 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key46) {	
               FIFO_PUSH(notes,194); // sent note off
		          FIFO_PUSH(durations, duration_note46);  //sent duration of noteoff
	          	lastState_key46 = 0x0; // remove "sent" bits from last status
	            duration_note46 = 0;
	         }else {
		          duration_note46 = 0;
          }

	/*47 key */

      if (d16 & 0x40) { //check first sensor key7
       duration_note47++; //add one timer tick to note duration

     	   if (d26&0x40) { //check second sensor key7

		         if (lastState_key47) {
		          	duration_note47 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,67); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note47); //send note duration

		        	  lastState_key47 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note47 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key47) {	
               FIFO_PUSH(notes,195); // sent note off
		          FIFO_PUSH(durations, duration_note47);  //sent duration of noteoff
	          	lastState_key47 = 0x0; // remove "sent" bits from last status
	            duration_note47 = 0;
	         }else {
		          duration_note47 = 0;
          }

	/*48 key */

      if (d16 & 0x80) { //check first sensor key8
       duration_note48++; //add one timer tick to note duration

     	   if (d26&0x80) { //check second sensor key8

		         if (lastState_key48) {
		          	duration_note48 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,68); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note48); //send note duration

		        	  lastState_key48 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note48 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key48) {	
               FIFO_PUSH(notes,196); // sent note off
		          FIFO_PUSH(durations, duration_note48);  //sent duration of noteoff
	          	lastState_key48 = 0x0; // remove "sent" bits from last status
	            duration_note48 = 0;
	         }else {
		          duration_note48 = 0;
          }

        lastState6 = d16;
       	}
      /* 7 chunk */ 

    GPIOB->BSRRH = GPIO_Pin_0; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d17 = ~GPIOA->IDR; //Read port state first contact 
    GPIOB->BSRRL = GPIO_Pin_0; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d17){  //Read second sensors only if some first sensor is pressed

    GPIOB->BSRRH = GPIO_Pin_1; 
    delay(KEY_SWITCH_DELAY);  
    d27 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_1;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d27=0;
     }
if ((d17)|(lastState7)){
	/*49 key */

      if (d17 & 0x01) { //check first sensor key1
       duration_note49++; //add one timer tick to note duration

     	   if (d27&0x01) { //check second sensor key1

		         if (lastState_key49) {
		          	duration_note49 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,69); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note49); //send note duration

		        	  lastState_key49 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note49 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key49) {	
               FIFO_PUSH(notes,197); // sent note off
		          FIFO_PUSH(durations, duration_note49);  //sent duration of noteoff
	          	lastState_key49 = 0x0; // remove "sent" bits from last status
	            duration_note49 = 0;
	         }else {
		          duration_note49 = 0;
          }

	/*50 key */

      if (d17 & 0x02) { //check first sensor key2
       duration_note50++; //add one timer tick to note duration

     	   if (d27&0x02) { //check second sensor key2

		         if (lastState_key50) {
		          	duration_note50 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,70); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note50); //send note duration

		        	  lastState_key50 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note50 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key50) {	
               FIFO_PUSH(notes,198); // sent note off
		          FIFO_PUSH(durations, duration_note50);  //sent duration of noteoff
	          	lastState_key50 = 0x0; // remove "sent" bits from last status
	            duration_note50 = 0;
	         }else {
		          duration_note50 = 0;
          }

	/*51 key */

      if (d17 & 0x04) { //check first sensor key3
       duration_note51++; //add one timer tick to note duration

     	   if (d27&0x04) { //check second sensor key3

		         if (lastState_key51) {
		          	duration_note51 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,71); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note51); //send note duration

		        	  lastState_key51 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note51 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key51) {	
               FIFO_PUSH(notes,199); // sent note off
		          FIFO_PUSH(durations, duration_note51);  //sent duration of noteoff
	          	lastState_key51 = 0x0; // remove "sent" bits from last status
	            duration_note51 = 0;
	         }else {
		          duration_note51 = 0;
          }

	/*52 key */

      if (d17 & 0x08) { //check first sensor key4
       duration_note52++; //add one timer tick to note duration

     	   if (d27&0x08) { //check second sensor key4

		         if (lastState_key52) {
		          	duration_note52 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,72); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note52); //send note duration

		        	  lastState_key52 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note52 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key52) {	
               FIFO_PUSH(notes,200); // sent note off
		          FIFO_PUSH(durations, duration_note52);  //sent duration of noteoff
	          	lastState_key52 = 0x0; // remove "sent" bits from last status
	            duration_note52 = 0;
	         }else {
		          duration_note52 = 0;
          }

	/*53 key */

      if (d17 & 0x10) { //check first sensor key5
       duration_note53++; //add one timer tick to note duration

     	   if (d27&0x10) { //check second sensor key5

		         if (lastState_key53) {
		          	duration_note53 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,73); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note53); //send note duration

		        	  lastState_key53 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note53 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key53) {	
               FIFO_PUSH(notes,201); // sent note off
		          FIFO_PUSH(durations, duration_note53);  //sent duration of noteoff
	          	lastState_key53 = 0x0; // remove "sent" bits from last status
	            duration_note53 = 0;
	         }else {
		          duration_note53 = 0;
          }

	/*54 key */

      if (d17 & 0x20) { //check first sensor key6
       duration_note54++; //add one timer tick to note duration

     	   if (d27&0x20) { //check second sensor key6

		         if (lastState_key54) {
		          	duration_note54 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,74); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note54); //send note duration

		        	  lastState_key54 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note54 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key54) {	
               FIFO_PUSH(notes,202); // sent note off
		          FIFO_PUSH(durations, duration_note54);  //sent duration of noteoff
	          	lastState_key54 = 0x0; // remove "sent" bits from last status
	            duration_note54 = 0;
	         }else {
		          duration_note54 = 0;
          }

	/*55 key */

      if (d17 & 0x40) { //check first sensor key7
       duration_note55++; //add one timer tick to note duration

     	   if (d27&0x40) { //check second sensor key7

		         if (lastState_key55) {
		          	duration_note55 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,75); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note55); //send note duration

		        	  lastState_key55 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note55 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key55) {	
               FIFO_PUSH(notes,203); // sent note off
		          FIFO_PUSH(durations, duration_note55);  //sent duration of noteoff
	          	lastState_key55 = 0x0; // remove "sent" bits from last status
	            duration_note55 = 0;
	         }else {
		          duration_note55 = 0;
          }

	/*56 key */

      if (d17 & 0x80) { //check first sensor key8
       duration_note56++; //add one timer tick to note duration

     	   if (d27&0x80) { //check second sensor key8

		         if (lastState_key56) {
		          	duration_note56 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,76); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note56); //send note duration

		        	  lastState_key56 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note56 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key56) {	
               FIFO_PUSH(notes,204); // sent note off
		          FIFO_PUSH(durations, duration_note56);  //sent duration of noteoff
	          	lastState_key56 = 0x0; // remove "sent" bits from last status
	            duration_note56 = 0;
	         }else {
		          duration_note56 = 0;
          }

        lastState7 = d17;
       	}
      /* 8 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_7; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d18 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_7; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d18){  //Read second sensors only if some first sensor is pressed

    GPIOB->BSRRH = GPIO_Pin_2; 
    delay(KEY_SWITCH_DELAY);  
    d28 = ~GPIOA->IDR; //Read port state second contact 
    GPIOB->BSRRL = GPIO_Pin_2;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d28=0;
     }
if ((d18)|(lastState8)){
	/*57 key */

      if (d18 & 0x01) { //check first sensor key1
       duration_note57++; //add one timer tick to note duration

     	   if (d28&0x01) { //check second sensor key1

		         if (lastState_key57) {
		          	duration_note57 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,77); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note57); //send note duration

		        	  lastState_key57 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note57 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key57) {	
               FIFO_PUSH(notes,205); // sent note off
		          FIFO_PUSH(durations, duration_note57);  //sent duration of noteoff
	          	lastState_key57 = 0x0; // remove "sent" bits from last status
	            duration_note57 = 0;
	         }else {
		          duration_note57 = 0;
          }

	/*58 key */

      if (d18 & 0x02) { //check first sensor key2
       duration_note58++; //add one timer tick to note duration

     	   if (d28&0x02) { //check second sensor key2

		         if (lastState_key58) {
		          	duration_note58 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,78); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note58); //send note duration

		        	  lastState_key58 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note58 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key58) {	
               FIFO_PUSH(notes,206); // sent note off
		          FIFO_PUSH(durations, duration_note58);  //sent duration of noteoff
	          	lastState_key58 = 0x0; // remove "sent" bits from last status
	            duration_note58 = 0;
	         }else {
		          duration_note58 = 0;
          }

	/*59 key */

      if (d18 & 0x04) { //check first sensor key3
       duration_note59++; //add one timer tick to note duration

     	   if (d28&0x04) { //check second sensor key3

		         if (lastState_key59) {
		          	duration_note59 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,79); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note59); //send note duration

		        	  lastState_key59 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note59 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key59) {	
               FIFO_PUSH(notes,207); // sent note off
		          FIFO_PUSH(durations, duration_note59);  //sent duration of noteoff
	          	lastState_key59 = 0x0; // remove "sent" bits from last status
	            duration_note59 = 0;
	         }else {
		          duration_note59 = 0;
          }

	/*60 key */

      if (d18 & 0x08) { //check first sensor key4
       duration_note60++; //add one timer tick to note duration

     	   if (d28&0x08) { //check second sensor key4

		         if (lastState_key60) {
		          	duration_note60 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,80); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note60); //send note duration

		        	  lastState_key60 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note60 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key60) {	
               FIFO_PUSH(notes,208); // sent note off
		          FIFO_PUSH(durations, duration_note60);  //sent duration of noteoff
	          	lastState_key60 = 0x0; // remove "sent" bits from last status
	            duration_note60 = 0;
	         }else {
		          duration_note60 = 0;
          }

	/*61 key */

      if (d18 & 0x10) { //check first sensor key5
       duration_note61++; //add one timer tick to note duration

     	   if (d28&0x10) { //check second sensor key5

		         if (lastState_key61) {
		          	duration_note61 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,81); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note61); //send note duration

		        	  lastState_key61 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note61 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key61) {	
               FIFO_PUSH(notes,209); // sent note off
		          FIFO_PUSH(durations, duration_note61);  //sent duration of noteoff
	          	lastState_key61 = 0x0; // remove "sent" bits from last status
	            duration_note61 = 0;
	         }else {
		          duration_note61 = 0;
          }

	/*62 key */

      if (d18 & 0x20) { //check first sensor key6
       duration_note62++; //add one timer tick to note duration

     	   if (d28&0x20) { //check second sensor key6

		         if (lastState_key62) {
		          	duration_note62 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,82); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note62); //send note duration

		        	  lastState_key62 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note62 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key62) {	
               FIFO_PUSH(notes,210); // sent note off
		          FIFO_PUSH(durations, duration_note62);  //sent duration of noteoff
	          	lastState_key62 = 0x0; // remove "sent" bits from last status
	            duration_note62 = 0;
	         }else {
		          duration_note62 = 0;
          }

	/*63 key */

      if (d18 & 0x40) { //check first sensor key7
       duration_note63++; //add one timer tick to note duration

     	   if (d28&0x40) { //check second sensor key7

		         if (lastState_key63) {
		          	duration_note63 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,83); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note63); //send note duration

		        	  lastState_key63 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note63 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key63) {	
               FIFO_PUSH(notes,211); // sent note off
		          FIFO_PUSH(durations, duration_note63);  //sent duration of noteoff
	          	lastState_key63 = 0x0; // remove "sent" bits from last status
	            duration_note63 = 0;
	         }else {
		          duration_note63 = 0;
          }

	/*64 key */

      if (d18 & 0x80) { //check first sensor key8
       duration_note64++; //add one timer tick to note duration

     	   if (d28&0x80) { //check second sensor key8

		         if (lastState_key64) {
		          	duration_note64 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,84); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note64); //send note duration

		        	  lastState_key64 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note64 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key64) {	
               FIFO_PUSH(notes,212); // sent note off
		          FIFO_PUSH(durations, duration_note64);  //sent duration of noteoff
	          	lastState_key64 = 0x0; // remove "sent" bits from last status
	            duration_note64 = 0;
	         }else {
		          duration_note64 = 0;
          }

        lastState8 = d18;
       	}
      /* 9 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_9; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d19 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_9; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d19){  //Read second sensors only if some first sensor is pressed

    GPIOE->BSRRH = GPIO_Pin_8; 
    delay(KEY_SWITCH_DELAY);  
    d29 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_8;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d29=0;
     }
if ((d19)|(lastState9)){
	/*65 key */

      if (d19 & 0x01) { //check first sensor key1
       duration_note65++; //add one timer tick to note duration

     	   if (d29&0x01) { //check second sensor key1

		         if (lastState_key65) {
		          	duration_note65 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,85); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note65); //send note duration

		        	  lastState_key65 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note65 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key65) {	
               FIFO_PUSH(notes,213); // sent note off
		          FIFO_PUSH(durations, duration_note65);  //sent duration of noteoff
	          	lastState_key65 = 0x0; // remove "sent" bits from last status
	            duration_note65 = 0;
	         }else {
		          duration_note65 = 0;
          }

	/*66 key */

      if (d19 & 0x02) { //check first sensor key2
       duration_note66++; //add one timer tick to note duration

     	   if (d29&0x02) { //check second sensor key2

		         if (lastState_key66) {
		          	duration_note66 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,86); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note66); //send note duration

		        	  lastState_key66 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note66 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key66) {	
               FIFO_PUSH(notes,214); // sent note off
		          FIFO_PUSH(durations, duration_note66);  //sent duration of noteoff
	          	lastState_key66 = 0x0; // remove "sent" bits from last status
	            duration_note66 = 0;
	         }else {
		          duration_note66 = 0;
          }

	/*67 key */

      if (d19 & 0x04) { //check first sensor key3
       duration_note67++; //add one timer tick to note duration

     	   if (d29&0x04) { //check second sensor key3

		         if (lastState_key67) {
		          	duration_note67 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,87); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note67); //send note duration

		        	  lastState_key67 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note67 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key67) {	
               FIFO_PUSH(notes,215); // sent note off
		          FIFO_PUSH(durations, duration_note67);  //sent duration of noteoff
	          	lastState_key67 = 0x0; // remove "sent" bits from last status
	            duration_note67 = 0;
	         }else {
		          duration_note67 = 0;
          }

	/*68 key */

      if (d19 & 0x08) { //check first sensor key4
       duration_note68++; //add one timer tick to note duration

     	   if (d29&0x08) { //check second sensor key4

		         if (lastState_key68) {
		          	duration_note68 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,88); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note68); //send note duration

		        	  lastState_key68 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note68 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key68) {	
               FIFO_PUSH(notes,216); // sent note off
		          FIFO_PUSH(durations, duration_note68);  //sent duration of noteoff
	          	lastState_key68 = 0x0; // remove "sent" bits from last status
	            duration_note68 = 0;
	         }else {
		          duration_note68 = 0;
          }

	/*69 key */

      if (d19 & 0x10) { //check first sensor key5
       duration_note69++; //add one timer tick to note duration

     	   if (d29&0x10) { //check second sensor key5

		         if (lastState_key69) {
		          	duration_note69 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,89); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note69); //send note duration

		        	  lastState_key69 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note69 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key69) {	
               FIFO_PUSH(notes,217); // sent note off
		          FIFO_PUSH(durations, duration_note69);  //sent duration of noteoff
	          	lastState_key69 = 0x0; // remove "sent" bits from last status
	            duration_note69 = 0;
	         }else {
		          duration_note69 = 0;
          }

	/*70 key */

      if (d19 & 0x20) { //check first sensor key6
       duration_note70++; //add one timer tick to note duration

     	   if (d29&0x20) { //check second sensor key6

		         if (lastState_key70) {
		          	duration_note70 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,90); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note70); //send note duration

		        	  lastState_key70 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note70 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key70) {	
               FIFO_PUSH(notes,218); // sent note off
		          FIFO_PUSH(durations, duration_note70);  //sent duration of noteoff
	          	lastState_key70 = 0x0; // remove "sent" bits from last status
	            duration_note70 = 0;
	         }else {
		          duration_note70 = 0;
          }

	/*71 key */

      if (d19 & 0x40) { //check first sensor key7
       duration_note71++; //add one timer tick to note duration

     	   if (d29&0x40) { //check second sensor key7

		         if (lastState_key71) {
		          	duration_note71 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,91); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note71); //send note duration

		        	  lastState_key71 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note71 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key71) {	
               FIFO_PUSH(notes,219); // sent note off
		          FIFO_PUSH(durations, duration_note71);  //sent duration of noteoff
	          	lastState_key71 = 0x0; // remove "sent" bits from last status
	            duration_note71 = 0;
	         }else {
		          duration_note71 = 0;
          }

	/*72 key */

      if (d19 & 0x80) { //check first sensor key8
       duration_note72++; //add one timer tick to note duration

     	   if (d29&0x80) { //check second sensor key8

		         if (lastState_key72) {
		          	duration_note72 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,92); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note72); //send note duration

		        	  lastState_key72 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note72 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key72) {	
               FIFO_PUSH(notes,220); // sent note off
		          FIFO_PUSH(durations, duration_note72);  //sent duration of noteoff
	          	lastState_key72 = 0x0; // remove "sent" bits from last status
	            duration_note72 = 0;
	         }else {
		          duration_note72 = 0;
          }

        lastState9 = d19;
       	}
      /* 10 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_12; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d110 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_12; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d110){  //Read second sensors only if some first sensor is pressed

    GPIOE->BSRRH = GPIO_Pin_10; 
    delay(KEY_SWITCH_DELAY);  
    d210 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_10;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d210=0;
     }
if ((d110)|(lastState10)){
	/*73 key */

      if (d110 & 0x01) { //check first sensor key1
       duration_note73++; //add one timer tick to note duration

     	   if (d210&0x01) { //check second sensor key1

		         if (lastState_key73) {
		          	duration_note73 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,93); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note73); //send note duration

		        	  lastState_key73 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note73 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key73) {	
               FIFO_PUSH(notes,221); // sent note off
		          FIFO_PUSH(durations, duration_note73);  //sent duration of noteoff
	          	lastState_key73 = 0x0; // remove "sent" bits from last status
	            duration_note73 = 0;
	         }else {
		          duration_note73 = 0;
          }

	/*74 key */

      if (d110 & 0x02) { //check first sensor key2
       duration_note74++; //add one timer tick to note duration

     	   if (d210&0x02) { //check second sensor key2

		         if (lastState_key74) {
		          	duration_note74 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,94); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note74); //send note duration

		        	  lastState_key74 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note74 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key74) {	
               FIFO_PUSH(notes,222); // sent note off
		          FIFO_PUSH(durations, duration_note74);  //sent duration of noteoff
	          	lastState_key74 = 0x0; // remove "sent" bits from last status
	            duration_note74 = 0;
	         }else {
		          duration_note74 = 0;
          }

	/*75 key */

      if (d110 & 0x04) { //check first sensor key3
       duration_note75++; //add one timer tick to note duration

     	   if (d210&0x04) { //check second sensor key3

		         if (lastState_key75) {
		          	duration_note75 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,95); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note75); //send note duration

		        	  lastState_key75 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note75 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key75) {	
               FIFO_PUSH(notes,223); // sent note off
		          FIFO_PUSH(durations, duration_note75);  //sent duration of noteoff
	          	lastState_key75 = 0x0; // remove "sent" bits from last status
	            duration_note75 = 0;
	         }else {
		          duration_note75 = 0;
          }

	/*76 key */

      if (d110 & 0x08) { //check first sensor key4
       duration_note76++; //add one timer tick to note duration

     	   if (d210&0x08) { //check second sensor key4

		         if (lastState_key76) {
		          	duration_note76 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,96); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note76); //send note duration

		        	  lastState_key76 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note76 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key76) {	
               FIFO_PUSH(notes,224); // sent note off
		          FIFO_PUSH(durations, duration_note76);  //sent duration of noteoff
	          	lastState_key76 = 0x0; // remove "sent" bits from last status
	            duration_note76 = 0;
	         }else {
		          duration_note76 = 0;
          }

	/*77 key */

      if (d110 & 0x10) { //check first sensor key5
       duration_note77++; //add one timer tick to note duration

     	   if (d210&0x10) { //check second sensor key5

		         if (lastState_key77) {
		          	duration_note77 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,97); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note77); //send note duration

		        	  lastState_key77 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note77 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key77) {	
               FIFO_PUSH(notes,225); // sent note off
		          FIFO_PUSH(durations, duration_note77);  //sent duration of noteoff
	          	lastState_key77 = 0x0; // remove "sent" bits from last status
	            duration_note77 = 0;
	         }else {
		          duration_note77 = 0;
          }

	/*78 key */

      if (d110 & 0x20) { //check first sensor key6
       duration_note78++; //add one timer tick to note duration

     	   if (d210&0x20) { //check second sensor key6

		         if (lastState_key78) {
		          	duration_note78 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,98); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note78); //send note duration

		        	  lastState_key78 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note78 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key78) {	
               FIFO_PUSH(notes,226); // sent note off
		          FIFO_PUSH(durations, duration_note78);  //sent duration of noteoff
	          	lastState_key78 = 0x0; // remove "sent" bits from last status
	            duration_note78 = 0;
	         }else {
		          duration_note78 = 0;
          }

	/*79 key */

      if (d110 & 0x40) { //check first sensor key7
       duration_note79++; //add one timer tick to note duration

     	   if (d210&0x40) { //check second sensor key7

		         if (lastState_key79) {
		          	duration_note79 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,99); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note79); //send note duration

		        	  lastState_key79 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note79 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key79) {	
               FIFO_PUSH(notes,227); // sent note off
		          FIFO_PUSH(durations, duration_note79);  //sent duration of noteoff
	          	lastState_key79 = 0x0; // remove "sent" bits from last status
	            duration_note79 = 0;
	         }else {
		          duration_note79 = 0;
          }

	/*80 key */

      if (d110 & 0x80) { //check first sensor key8
       duration_note80++; //add one timer tick to note duration

     	   if (d210&0x80) { //check second sensor key8

		         if (lastState_key80) {
		          	duration_note80 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,100); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note80); //send note duration

		        	  lastState_key80 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note80 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key80) {	
               FIFO_PUSH(notes,228); // sent note off
		          FIFO_PUSH(durations, duration_note80);  //sent duration of noteoff
	          	lastState_key80 = 0x0; // remove "sent" bits from last status
	            duration_note80 = 0;
	         }else {
		          duration_note80 = 0;
          }

        lastState10 = d110;
       	}
      /* 11 chunk */ 

    GPIOE->BSRRH = GPIO_Pin_11; //Pin to zero
    delay(KEY_SWITCH_DELAY); 
    d111 = ~GPIOA->IDR; //Read port state first contact 
    GPIOE->BSRRL = GPIO_Pin_11; //Pin to 1

     GPIOA->MODER |= 0x00005555;	//Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input
    delay(KEY_SWITCH_DELAY); 

    if (d111){  //Read second sensors only if some first sensor is pressed

    GPIOE->BSRRH = GPIO_Pin_13; 
    delay(KEY_SWITCH_DELAY);  
    d211 = ~GPIOA->IDR; //Read port state second contact 
    GPIOE->BSRRL = GPIO_Pin_13;  

     GPIOA->MODER |= 0x00005555;	////Switch to output
     GPIOA->ODR = 0x00FF;		//Set high level to PA0-7 to discharge the bus
     GPIOA->MODER &= 0xFFFF0000;	//Switch PA0-7 to input

    }else{ 
         d211=0;
     }
if ((d111)|(lastState11)){
	/*81 key */

      if (d111 & 0x01) { //check first sensor key1
       duration_note81++; //add one timer tick to note duration

     	   if (d211&0x01) { //check second sensor key1

		         if (lastState_key81) {
		          	duration_note81 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,101); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note81); //send note duration

		        	  lastState_key81 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note81 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key81) {	
               FIFO_PUSH(notes,229); // sent note off
		          FIFO_PUSH(durations, duration_note81);  //sent duration of noteoff
	          	lastState_key81 = 0x0; // remove "sent" bits from last status
	            duration_note81 = 0;
	         }else {
		          duration_note81 = 0;
          }

	/*82 key */

      if (d111 & 0x02) { //check first sensor key2
       duration_note82++; //add one timer tick to note duration

     	   if (d211&0x02) { //check second sensor key2

		         if (lastState_key82) {
		          	duration_note82 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,102); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note82); //send note duration

		        	  lastState_key82 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note82 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key82) {	
               FIFO_PUSH(notes,230); // sent note off
		          FIFO_PUSH(durations, duration_note82);  //sent duration of noteoff
	          	lastState_key82 = 0x0; // remove "sent" bits from last status
	            duration_note82 = 0;
	         }else {
		          duration_note82 = 0;
          }

	/*83 key */

      if (d111 & 0x04) { //check first sensor key3
       duration_note83++; //add one timer tick to note duration

     	   if (d211&0x04) { //check second sensor key3

		         if (lastState_key83) {
		          	duration_note83 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,103); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note83); //send note duration

		        	  lastState_key83 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note83 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key83) {	
               FIFO_PUSH(notes,231); // sent note off
		          FIFO_PUSH(durations, duration_note83);  //sent duration of noteoff
	          	lastState_key83 = 0x0; // remove "sent" bits from last status
	            duration_note83 = 0;
	         }else {
		          duration_note83 = 0;
          }

	/*84 key */

      if (d111 & 0x08) { //check first sensor key4
       duration_note84++; //add one timer tick to note duration

     	   if (d211&0x08) { //check second sensor key4

		         if (lastState_key84) {
		          	duration_note84 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,104); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note84); //send note duration

		        	  lastState_key84 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note84 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key84) {	
               FIFO_PUSH(notes,232); // sent note off
		          FIFO_PUSH(durations, duration_note84);  //sent duration of noteoff
	          	lastState_key84 = 0x0; // remove "sent" bits from last status
	            duration_note84 = 0;
	         }else {
		          duration_note84 = 0;
          }

	/*85 key */

      if (d111 & 0x10) { //check first sensor key5
       duration_note85++; //add one timer tick to note duration

     	   if (d211&0x10) { //check second sensor key5

		         if (lastState_key85) {
		          	duration_note85 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,105); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note85); //send note duration

		        	  lastState_key85 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note85 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key85) {	
               FIFO_PUSH(notes,233); // sent note off
		          FIFO_PUSH(durations, duration_note85);  //sent duration of noteoff
	          	lastState_key85 = 0x0; // remove "sent" bits from last status
	            duration_note85 = 0;
	         }else {
		          duration_note85 = 0;
          }

	/*86 key */

      if (d111 & 0x20) { //check first sensor key6
       duration_note86++; //add one timer tick to note duration

     	   if (d211&0x20) { //check second sensor key6

		         if (lastState_key86) {
		          	duration_note86 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,106); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note86); //send note duration

		        	  lastState_key86 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note86 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key86) {	
               FIFO_PUSH(notes,234); // sent note off
		          FIFO_PUSH(durations, duration_note86);  //sent duration of noteoff
	          	lastState_key86 = 0x0; // remove "sent" bits from last status
	            duration_note86 = 0;
	         }else {
		          duration_note86 = 0;
          }

	/*87 key */

      if (d111 & 0x40) { //check first sensor key7
       duration_note87++; //add one timer tick to note duration

     	   if (d211&0x40) { //check second sensor key7

		         if (lastState_key87) {
		          	duration_note87 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,107); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note87); //send note duration

		        	  lastState_key87 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note87 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key87) {	
               FIFO_PUSH(notes,235); // sent note off
		          FIFO_PUSH(durations, duration_note87);  //sent duration of noteoff
	          	lastState_key87 = 0x0; // remove "sent" bits from last status
	            duration_note87 = 0;
	         }else {
		          duration_note87 = 0;
          }

	/*88 key */

      if (d111 & 0x80) { //check first sensor key8
       duration_note88++; //add one timer tick to note duration

     	   if (d211&0x80) { //check second sensor key8

		         if (lastState_key88) {
		          	duration_note88 = 0; //if second sensor pressed before then set duration to 0
	          	} else {
	 	          	FIFO_PUSH(notes,108); // if second sensor just pressed then send note
			          FIFO_PUSH(durations, duration_note88); //send note duration

		        	  lastState_key88 = 0x1; //set last status as "sent" (key bit to 0)
		           	duration_note88 = 0;  //duration to zero
	          	}

         	}

         }else if (lastState_key88) {	
               FIFO_PUSH(notes,236); // sent note off
		          FIFO_PUSH(durations, duration_note88);  //sent duration of noteoff
	          	lastState_key88 = 0x0; // remove "sent" bits from last status
	            duration_note88 = 0;
	         }else {
		          duration_note88 = 0;
          }

        lastState11 = d111;
       	}

}
