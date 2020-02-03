//проверка на буквы
function isWord(chr) {
	let re = RegExp('^[а-яА-ЯёЁa-zA-Z]+$');
	if(!re.test(chr)) {
		return false}
		else
		{return true}
}

//проверка на цифры
function isNumber(chr) {
	let re = RegExp('^[0-9]+$');
	if(!re.test(chr)) {
		return false}
		else
		{return true}
}

//для поиска максимального размера от размеров двух файлов
function fMax(num1, num2) {
	if (num1 > num2) {
		return num1;
	} else {
		return num2;
	}
}

let fs = require("fs");


function main(file1, file2, file3) {
	//читаем файл 1 (для букв)
	let data_letter = fs.readFileSync(file1, {encoding: 'utf-8'}, function(err) {  
		if (err) {  
		  console.error(err);  
		}
	});

	//читаем файл 2 (для цифр)
	let data_number = fs.readFileSync(file2, {encoding: 'utf-8'}, function(err) {  
		if (err) {  
		  console.error(err);  
		}
	});

	let data_result = "";

	//запись в строку с результатом итоговых символов
	for (let i = 0; i < fMax(data_letter.length, data_number.length); i++) {
		if(i < data_letter.length) {
			if (isWord(data_letter[i])) {
				data_result = data_result + data_letter[i];
			}
		}

		if(i < data_number.length) {
			if (isNumber(data_number[i])) {
				data_result = data_result + data_number[i];
			}
		}
	} 

	//запись итога в файл
	fs.writeFileSync(file3, data_result, function(err) {
		if (err) {
			console.error("Write error!");
		} else {
			console.log("Succesful!");
		}
	})
}

main(process.argv[2], process.argv[3], process.argv[4]);