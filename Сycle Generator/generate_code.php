<?php
/* Generate code w/o loops */

ob_start();

/* Generate variables */
echo '/* Variables */'.PHP_EOL;

for ($i=1; $i<=88; $i++) {
	echo "uint16_t duration_note$i = 0;".PHP_EOL;
}

echo '	'.PHP_EOL;
echo '	'.PHP_EOL;
echo '	'.PHP_EOL;
echo '	/* Main code */'.PHP_EOL;


$note = 0;
for ($i=1; $i<=11; $i++) {

	$mask = 1;

	for ($j=1; $j<=8; $j++) {
		$note++;
		$maskHex = sprintf("0x%X", $mask);
		$maskHexNot = sprintf("%X", ~$mask);

		$maskHexNot = "0x".substr($maskHexNot, -4 , 4);

		echo PHP_EOL;
		echo "/* $note key */ 												".PHP_EOL;
		echo "																".PHP_EOL;	
		echo "	if (d1$i&0x0001) { //Первый контакт 							".PHP_EOL;
		echo "	duration_note$note++; //Увеличиваем длительность

		if (d2$i&0x0001) { //Второй контакт

			if (lastState$i&0x0001) {
				duration_note$note = 0; //Пока нажат второй контакт, сбрасываем длительность
			} else {
				FIFO_PUSH(notes,$note); //Добавляем в ФИФО текущую ноту
				FIFO_PUSH(durations, duration_note$note); //Добавляем в ФИФО текущую длительность
				
				lastState$i ^= $maskHex; //Устанавливаем прошлый статус как отправлен
				duration_note$note = 0; //Сбрасываем длительность
			}

		}																".PHP_EOL;
		echo " 																".PHP_EOL;
		echo "    } else if (lastState$i&0x0001) {							".PHP_EOL;
		echo "FIFO_PUSH(notes,$note); //Добавляем в ФИФО текущую ноту
		FIFO_PUSH(durations, duration_note$note); //Добавляем в ФИФО текущую длительность
		lastState1 &= $maskHexNot; //Убираем статус отправки с бита
		duration_note$note = 0; //Сброс длительности
	} else {
		duration_note$note = 0; //Сброс длительности
	}				".PHP_EOL;


	$mask = $mask *2;
}
}

$content = ob_get_contents();  

ob_end_clean(); 

$fp = fopen("code.c", "w");
$test = fwrite($fp, $content); // Запись в файл
if ($test) echo 'ok!'.PHP_EOL;
else echo 'false!'.PHP_EOL;
fclose($fp); //Закрытие файла

?>