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
	
	
	
	/* Main code */

/* 1 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note1++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note1 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,1); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note1); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note1 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,1); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note1); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note1 = 0; //Сброс длительности
	} else {
		duration_note1 = 0; //Сброс длительности
	}				

/* 2 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note2++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note2 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,2); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note2); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note2 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,2); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note2); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note2 = 0; //Сброс длительности
	} else {
		duration_note2 = 0; //Сброс длительности
	}				

/* 3 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note3++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note3 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,3); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note3); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note3 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,3); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note3); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note3 = 0; //Сброс длительности
	} else {
		duration_note3 = 0; //Сброс длительности
	}				

/* 4 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note4++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note4 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,4); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note4); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note4 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,4); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note4); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note4 = 0; //Сброс длительности
	} else {
		duration_note4 = 0; //Сброс длительности
	}				

/* 5 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note5++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note5 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,5); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note5); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note5 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,5); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note5); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note5 = 0; //Сброс длительности
	} else {
		duration_note5 = 0; //Сброс длительности
	}				

/* 6 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note6++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note6 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,6); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note6); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note6 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,6); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note6); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note6 = 0; //Сброс длительности
	} else {
		duration_note6 = 0; //Сброс длительности
	}				

/* 7 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note7++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note7 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,7); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note7); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note7 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,7); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note7); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note7 = 0; //Сброс длительности
	} else {
		duration_note7 = 0; //Сброс длительности
	}				

/* 8 key */ 												
																
	if (d11&0x0001) { //Первый контакт 							
	duration_note8++; //Увеличиваем длительность

		if (d21&0x0001) { //Второй контакт

			if (lastState1&0x0001) {
				duration_note8 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,8); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note8); //Добавляем в ФИФО текущую длительность
				
				lastState1 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note8 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState1&0x0001) {							
FIFO_PUSH(notes,8); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note8); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note8 = 0; //Сброс длительности
	} else {
		duration_note8 = 0; //Сброс длительности
	}				

/* 9 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note9++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note9 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,9); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note9); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note9 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,9); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note9); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note9 = 0; //Сброс длительности
	} else {
		duration_note9 = 0; //Сброс длительности
	}				

/* 10 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note10++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note10 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,10); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note10); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note10 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,10); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note10); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note10 = 0; //Сброс длительности
	} else {
		duration_note10 = 0; //Сброс длительности
	}				

/* 11 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note11++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note11 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,11); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note11); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note11 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,11); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note11); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note11 = 0; //Сброс длительности
	} else {
		duration_note11 = 0; //Сброс длительности
	}				

/* 12 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note12++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note12 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,12); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note12); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note12 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,12); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note12); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note12 = 0; //Сброс длительности
	} else {
		duration_note12 = 0; //Сброс длительности
	}				

/* 13 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note13++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note13 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,13); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note13); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note13 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,13); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note13); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note13 = 0; //Сброс длительности
	} else {
		duration_note13 = 0; //Сброс длительности
	}				

/* 14 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note14++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note14 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,14); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note14); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note14 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,14); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note14); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note14 = 0; //Сброс длительности
	} else {
		duration_note14 = 0; //Сброс длительности
	}				

/* 15 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note15++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note15 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,15); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note15); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note15 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,15); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note15); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note15 = 0; //Сброс длительности
	} else {
		duration_note15 = 0; //Сброс длительности
	}				

/* 16 key */ 												
																
	if (d12&0x0001) { //Первый контакт 							
	duration_note16++; //Увеличиваем длительность

		if (d22&0x0001) { //Второй контакт

			if (lastState2&0x0001) {
				duration_note16 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,16); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note16); //Добавляем в ФИФО текущую длительность
				
				lastState2 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note16 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState2&0x0001) {							
FIFO_PUSH(notes,16); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note16); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note16 = 0; //Сброс длительности
	} else {
		duration_note16 = 0; //Сброс длительности
	}				

/* 17 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note17++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note17 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,17); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note17); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note17 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,17); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note17); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note17 = 0; //Сброс длительности
	} else {
		duration_note17 = 0; //Сброс длительности
	}				

/* 18 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note18++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note18 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,18); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note18); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note18 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,18); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note18); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note18 = 0; //Сброс длительности
	} else {
		duration_note18 = 0; //Сброс длительности
	}				

/* 19 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note19++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note19 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,19); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note19); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note19 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,19); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note19); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note19 = 0; //Сброс длительности
	} else {
		duration_note19 = 0; //Сброс длительности
	}				

/* 20 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note20++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note20 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,20); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note20); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note20 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,20); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note20); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note20 = 0; //Сброс длительности
	} else {
		duration_note20 = 0; //Сброс длительности
	}				

/* 21 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note21++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note21 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,21); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note21); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note21 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,21); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note21); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note21 = 0; //Сброс длительности
	} else {
		duration_note21 = 0; //Сброс длительности
	}				

/* 22 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note22++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note22 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,22); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note22); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note22 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,22); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note22); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note22 = 0; //Сброс длительности
	} else {
		duration_note22 = 0; //Сброс длительности
	}				

/* 23 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note23++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note23 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,23); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note23); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note23 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,23); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note23); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note23 = 0; //Сброс длительности
	} else {
		duration_note23 = 0; //Сброс длительности
	}				

/* 24 key */ 												
																
	if (d13&0x0001) { //Первый контакт 							
	duration_note24++; //Увеличиваем длительность

		if (d23&0x0001) { //Второй контакт

			if (lastState3&0x0001) {
				duration_note24 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,24); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note24); //Добавляем в ФИФО текущую длительность
				
				lastState3 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note24 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState3&0x0001) {							
FIFO_PUSH(notes,24); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note24); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note24 = 0; //Сброс длительности
	} else {
		duration_note24 = 0; //Сброс длительности
	}				

/* 25 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note25++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note25 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,25); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note25); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note25 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,25); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note25); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note25 = 0; //Сброс длительности
	} else {
		duration_note25 = 0; //Сброс длительности
	}				

/* 26 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note26++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note26 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,26); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note26); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note26 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,26); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note26); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note26 = 0; //Сброс длительности
	} else {
		duration_note26 = 0; //Сброс длительности
	}				

/* 27 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note27++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note27 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,27); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note27); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note27 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,27); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note27); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note27 = 0; //Сброс длительности
	} else {
		duration_note27 = 0; //Сброс длительности
	}				

/* 28 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note28++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note28 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,28); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note28); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note28 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,28); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note28); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note28 = 0; //Сброс длительности
	} else {
		duration_note28 = 0; //Сброс длительности
	}				

/* 29 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note29++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note29 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,29); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note29); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note29 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,29); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note29); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note29 = 0; //Сброс длительности
	} else {
		duration_note29 = 0; //Сброс длительности
	}				

/* 30 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note30++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note30 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,30); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note30); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note30 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,30); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note30); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note30 = 0; //Сброс длительности
	} else {
		duration_note30 = 0; //Сброс длительности
	}				

/* 31 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note31++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note31 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,31); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note31); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note31 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,31); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note31); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note31 = 0; //Сброс длительности
	} else {
		duration_note31 = 0; //Сброс длительности
	}				

/* 32 key */ 												
																
	if (d14&0x0001) { //Первый контакт 							
	duration_note32++; //Увеличиваем длительность

		if (d24&0x0001) { //Второй контакт

			if (lastState4&0x0001) {
				duration_note32 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,32); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note32); //Добавляем в ФИФО текущую длительность
				
				lastState4 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note32 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState4&0x0001) {							
FIFO_PUSH(notes,32); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note32); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note32 = 0; //Сброс длительности
	} else {
		duration_note32 = 0; //Сброс длительности
	}				

/* 33 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note33++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note33 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,33); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note33); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note33 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,33); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note33); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note33 = 0; //Сброс длительности
	} else {
		duration_note33 = 0; //Сброс длительности
	}				

/* 34 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note34++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note34 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,34); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note34); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note34 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,34); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note34); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note34 = 0; //Сброс длительности
	} else {
		duration_note34 = 0; //Сброс длительности
	}				

/* 35 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note35++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note35 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,35); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note35); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note35 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,35); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note35); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note35 = 0; //Сброс длительности
	} else {
		duration_note35 = 0; //Сброс длительности
	}				

/* 36 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note36++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note36 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,36); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note36); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note36 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,36); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note36); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note36 = 0; //Сброс длительности
	} else {
		duration_note36 = 0; //Сброс длительности
	}				

/* 37 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note37++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note37 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,37); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note37); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note37 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,37); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note37); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note37 = 0; //Сброс длительности
	} else {
		duration_note37 = 0; //Сброс длительности
	}				

/* 38 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note38++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note38 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,38); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note38); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note38 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,38); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note38); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note38 = 0; //Сброс длительности
	} else {
		duration_note38 = 0; //Сброс длительности
	}				

/* 39 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note39++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note39 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,39); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note39); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note39 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,39); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note39); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note39 = 0; //Сброс длительности
	} else {
		duration_note39 = 0; //Сброс длительности
	}				

/* 40 key */ 												
																
	if (d15&0x0001) { //Первый контакт 							
	duration_note40++; //Увеличиваем длительность

		if (d25&0x0001) { //Второй контакт

			if (lastState5&0x0001) {
				duration_note40 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,40); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note40); //Добавляем в ФИФО текущую длительность
				
				lastState5 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note40 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState5&0x0001) {							
FIFO_PUSH(notes,40); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note40); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note40 = 0; //Сброс длительности
	} else {
		duration_note40 = 0; //Сброс длительности
	}				

/* 41 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note41++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note41 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,41); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note41); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note41 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,41); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note41); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note41 = 0; //Сброс длительности
	} else {
		duration_note41 = 0; //Сброс длительности
	}				

/* 42 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note42++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note42 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,42); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note42); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note42 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,42); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note42); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note42 = 0; //Сброс длительности
	} else {
		duration_note42 = 0; //Сброс длительности
	}				

/* 43 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note43++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note43 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,43); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note43); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note43 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,43); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note43); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note43 = 0; //Сброс длительности
	} else {
		duration_note43 = 0; //Сброс длительности
	}				

/* 44 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note44++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note44 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,44); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note44); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note44 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,44); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note44); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note44 = 0; //Сброс длительности
	} else {
		duration_note44 = 0; //Сброс длительности
	}				

/* 45 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note45++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note45 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,45); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note45); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note45 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,45); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note45); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note45 = 0; //Сброс длительности
	} else {
		duration_note45 = 0; //Сброс длительности
	}				

/* 46 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note46++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note46 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,46); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note46); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note46 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,46); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note46); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note46 = 0; //Сброс длительности
	} else {
		duration_note46 = 0; //Сброс длительности
	}				

/* 47 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note47++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note47 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,47); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note47); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note47 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,47); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note47); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note47 = 0; //Сброс длительности
	} else {
		duration_note47 = 0; //Сброс длительности
	}				

/* 48 key */ 												
																
	if (d16&0x0001) { //Первый контакт 							
	duration_note48++; //Увеличиваем длительность

		if (d26&0x0001) { //Второй контакт

			if (lastState6&0x0001) {
				duration_note48 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,48); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note48); //Добавляем в ФИФО текущую длительность
				
				lastState6 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note48 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState6&0x0001) {							
FIFO_PUSH(notes,48); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note48); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note48 = 0; //Сброс длительности
	} else {
		duration_note48 = 0; //Сброс длительности
	}				

/* 49 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note49++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note49 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,49); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note49); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note49 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,49); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note49); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note49 = 0; //Сброс длительности
	} else {
		duration_note49 = 0; //Сброс длительности
	}				

/* 50 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note50++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note50 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,50); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note50); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note50 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,50); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note50); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note50 = 0; //Сброс длительности
	} else {
		duration_note50 = 0; //Сброс длительности
	}				

/* 51 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note51++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note51 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,51); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note51); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note51 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,51); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note51); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note51 = 0; //Сброс длительности
	} else {
		duration_note51 = 0; //Сброс длительности
	}				

/* 52 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note52++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note52 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,52); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note52); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note52 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,52); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note52); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note52 = 0; //Сброс длительности
	} else {
		duration_note52 = 0; //Сброс длительности
	}				

/* 53 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note53++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note53 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,53); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note53); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note53 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,53); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note53); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note53 = 0; //Сброс длительности
	} else {
		duration_note53 = 0; //Сброс длительности
	}				

/* 54 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note54++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note54 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,54); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note54); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note54 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,54); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note54); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note54 = 0; //Сброс длительности
	} else {
		duration_note54 = 0; //Сброс длительности
	}				

/* 55 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note55++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note55 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,55); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note55); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note55 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,55); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note55); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note55 = 0; //Сброс длительности
	} else {
		duration_note55 = 0; //Сброс длительности
	}				

/* 56 key */ 												
																
	if (d17&0x0001) { //Первый контакт 							
	duration_note56++; //Увеличиваем длительность

		if (d27&0x0001) { //Второй контакт

			if (lastState7&0x0001) {
				duration_note56 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,56); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note56); //Добавляем в ФИФО текущую длительность
				
				lastState7 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note56 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState7&0x0001) {							
FIFO_PUSH(notes,56); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note56); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note56 = 0; //Сброс длительности
	} else {
		duration_note56 = 0; //Сброс длительности
	}				

/* 57 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note57++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note57 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,57); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note57); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note57 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,57); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note57); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note57 = 0; //Сброс длительности
	} else {
		duration_note57 = 0; //Сброс длительности
	}				

/* 58 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note58++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note58 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,58); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note58); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note58 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,58); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note58); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note58 = 0; //Сброс длительности
	} else {
		duration_note58 = 0; //Сброс длительности
	}				

/* 59 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note59++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note59 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,59); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note59); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note59 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,59); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note59); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note59 = 0; //Сброс длительности
	} else {
		duration_note59 = 0; //Сброс длительности
	}				

/* 60 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note60++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note60 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,60); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note60); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note60 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,60); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note60); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note60 = 0; //Сброс длительности
	} else {
		duration_note60 = 0; //Сброс длительности
	}				

/* 61 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note61++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note61 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,61); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note61); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note61 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,61); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note61); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note61 = 0; //Сброс длительности
	} else {
		duration_note61 = 0; //Сброс длительности
	}				

/* 62 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note62++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note62 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,62); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note62); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note62 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,62); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note62); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note62 = 0; //Сброс длительности
	} else {
		duration_note62 = 0; //Сброс длительности
	}				

/* 63 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note63++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note63 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,63); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note63); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note63 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,63); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note63); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note63 = 0; //Сброс длительности
	} else {
		duration_note63 = 0; //Сброс длительности
	}				

/* 64 key */ 												
																
	if (d18&0x0001) { //Первый контакт 							
	duration_note64++; //Увеличиваем длительность

		if (d28&0x0001) { //Второй контакт

			if (lastState8&0x0001) {
				duration_note64 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,64); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note64); //Добавляем в ФИФО текущую длительность
				
				lastState8 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note64 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState8&0x0001) {							
FIFO_PUSH(notes,64); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note64); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note64 = 0; //Сброс длительности
	} else {
		duration_note64 = 0; //Сброс длительности
	}				

/* 65 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note65++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note65 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,65); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note65); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note65 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,65); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note65); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note65 = 0; //Сброс длительности
	} else {
		duration_note65 = 0; //Сброс длительности
	}				

/* 66 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note66++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note66 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,66); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note66); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note66 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,66); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note66); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note66 = 0; //Сброс длительности
	} else {
		duration_note66 = 0; //Сброс длительности
	}				

/* 67 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note67++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note67 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,67); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note67); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note67 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,67); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note67); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note67 = 0; //Сброс длительности
	} else {
		duration_note67 = 0; //Сброс длительности
	}				

/* 68 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note68++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note68 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,68); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note68); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note68 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,68); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note68); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note68 = 0; //Сброс длительности
	} else {
		duration_note68 = 0; //Сброс длительности
	}				

/* 69 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note69++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note69 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,69); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note69); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note69 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,69); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note69); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note69 = 0; //Сброс длительности
	} else {
		duration_note69 = 0; //Сброс длительности
	}				

/* 70 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note70++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note70 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,70); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note70); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note70 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,70); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note70); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note70 = 0; //Сброс длительности
	} else {
		duration_note70 = 0; //Сброс длительности
	}				

/* 71 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note71++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note71 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,71); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note71); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note71 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,71); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note71); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note71 = 0; //Сброс длительности
	} else {
		duration_note71 = 0; //Сброс длительности
	}				

/* 72 key */ 												
																
	if (d19&0x0001) { //Первый контакт 							
	duration_note72++; //Увеличиваем длительность

		if (d29&0x0001) { //Второй контакт

			if (lastState9&0x0001) {
				duration_note72 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,72); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note72); //Добавляем в ФИФО текущую длительность
				
				lastState9 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note72 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState9&0x0001) {							
FIFO_PUSH(notes,72); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note72); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note72 = 0; //Сброс длительности
	} else {
		duration_note72 = 0; //Сброс длительности
	}				

/* 73 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note73++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note73 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,73); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note73); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note73 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,73); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note73); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note73 = 0; //Сброс длительности
	} else {
		duration_note73 = 0; //Сброс длительности
	}				

/* 74 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note74++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note74 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,74); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note74); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note74 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,74); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note74); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note74 = 0; //Сброс длительности
	} else {
		duration_note74 = 0; //Сброс длительности
	}				

/* 75 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note75++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note75 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,75); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note75); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note75 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,75); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note75); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note75 = 0; //Сброс длительности
	} else {
		duration_note75 = 0; //Сброс длительности
	}				

/* 76 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note76++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note76 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,76); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note76); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note76 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,76); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note76); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note76 = 0; //Сброс длительности
	} else {
		duration_note76 = 0; //Сброс длительности
	}				

/* 77 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note77++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note77 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,77); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note77); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note77 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,77); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note77); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note77 = 0; //Сброс длительности
	} else {
		duration_note77 = 0; //Сброс длительности
	}				

/* 78 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note78++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note78 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,78); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note78); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note78 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,78); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note78); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note78 = 0; //Сброс длительности
	} else {
		duration_note78 = 0; //Сброс длительности
	}				

/* 79 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note79++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note79 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,79); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note79); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note79 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,79); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note79); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note79 = 0; //Сброс длительности
	} else {
		duration_note79 = 0; //Сброс длительности
	}				

/* 80 key */ 												
																
	if (d110&0x0001) { //Первый контакт 							
	duration_note80++; //Увеличиваем длительность

		if (d210&0x0001) { //Второй контакт

			if (lastState10&0x0001) {
				duration_note80 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,80); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note80); //Добавляем в ФИФО текущую длительность
				
				lastState10 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note80 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState10&0x0001) {							
FIFO_PUSH(notes,80); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note80); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note80 = 0; //Сброс длительности
	} else {
		duration_note80 = 0; //Сброс длительности
	}				

/* 81 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note81++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note81 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,81); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note81); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x1; //Устанавливаем прошлый статус как отправлен
				duration_note81 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,81); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note81); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFE; //Убираем статус отправки с бита
		duration_note81 = 0; //Сброс длительности
	} else {
		duration_note81 = 0; //Сброс длительности
	}				

/* 82 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note82++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note82 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,82); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note82); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x2; //Устанавливаем прошлый статус как отправлен
				duration_note82 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,82); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note82); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFD; //Убираем статус отправки с бита
		duration_note82 = 0; //Сброс длительности
	} else {
		duration_note82 = 0; //Сброс длительности
	}				

/* 83 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note83++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note83 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,83); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note83); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x4; //Устанавливаем прошлый статус как отправлен
				duration_note83 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,83); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note83); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFFB; //Убираем статус отправки с бита
		duration_note83 = 0; //Сброс длительности
	} else {
		duration_note83 = 0; //Сброс длительности
	}				

/* 84 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note84++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note84 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,84); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note84); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x8; //Устанавливаем прошлый статус как отправлен
				duration_note84 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,84); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note84); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFF7; //Убираем статус отправки с бита
		duration_note84 = 0; //Сброс длительности
	} else {
		duration_note84 = 0; //Сброс длительности
	}				

/* 85 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note85++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note85 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,85); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note85); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x10; //Устанавливаем прошлый статус как отправлен
				duration_note85 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,85); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note85); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFEF; //Убираем статус отправки с бита
		duration_note85 = 0; //Сброс длительности
	} else {
		duration_note85 = 0; //Сброс длительности
	}				

/* 86 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note86++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note86 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,86); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note86); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x20; //Устанавливаем прошлый статус как отправлен
				duration_note86 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,86); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note86); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFDF; //Убираем статус отправки с бита
		duration_note86 = 0; //Сброс длительности
	} else {
		duration_note86 = 0; //Сброс длительности
	}				

/* 87 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note87++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note87 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,87); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note87); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x40; //Устанавливаем прошлый статус как отправлен
				duration_note87 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,87); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note87); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFFBF; //Убираем статус отправки с бита
		duration_note87 = 0; //Сброс длительности
	} else {
		duration_note87 = 0; //Сброс длительности
	}				

/* 88 key */ 												
																
	if (d111&0x0001) { //Первый контакт 							
	duration_note88++; //Увеличиваем длительность

		if (d211&0x0001) { //Второй контакт

			if (lastState11&0x0001) {
				duration_note88 = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,88); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note88); //Добавляем в ФИФО текущую длительность
				
				lastState11 ^= 0x80; //Устанавливаем прошлый статус как отправлен
				duration_note88 = 0; //Сбрасываем длительность
			}

		}																
 																
    } else if (lastState11&0x0001) {							
FIFO_PUSH(notes,88); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note88); //Добавляем в ФИФО текущую длительность
		lastState1 &= 0xFF7F; //Убираем статус отправки с бита
		duration_note88 = 0; //Сброс длительности
	} else {
		duration_note88 = 0; //Сброс длительности
	}				
