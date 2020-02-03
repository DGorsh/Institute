//проверка на цифры
function isNumber(chr) {
	return RegExp('^[0-9.]+$').test(chr);
}

// Use the JSON parse to clone the data.
function cloneData(data) {
	// Convert the data into a string first
	var jsonString = JSON.stringify(data);
  
	//  Parse the string to create a new instance of the data
	return JSON.parse(jsonString);
  }


//для поиска определителя
function determinant(matrix, size, status, y=0) {
	let tmp = cloneData(matrix);
	if (status) {
		for (let i = 0; i <= size; i++){
			tmp[i].splice(y, 1);
		}
		tmp.shift();
	}
	if (size == 1) {
		return tmp[0][0];
	};
	if (size == 2) {
		return tmp[0][0]*tmp[1][1] - tmp[0][1]*tmp[1][0];
	};
	if (size>2){
		let result = 0;
		for (let i = 0; i<size; i++){
			if ((i+2)%2 === 0) {
				result += tmp[0][i] * determinant(tmp, size-1, true, i);
			} else {
				result -= tmp[0][i] * determinant(tmp, size-1, true, i);
			}

		}
		return result;
	}
}
let fs = require("fs");


function main(file1) {
	//читаем файл 1 (в буффер)
	let data_letter = fs.readFileSync(file1, {encoding: 'utf-8'}, function(err) {  
		if (err) {  
		  console.error(err);  
		}
	});

	for(let i = 0; i<data_letter.length; i++) {
		if (!isNumber(data_letter[i]) & ((data_letter[i] != ' ') & (data_letter[i] != '\n') &
		(data_letter[i] != '\r') & (data_letter[i] != '\r\n'))) 
		{
			console.log(i);
			console.log(data_letter[i]);
			return 1;
		}
	}

	let data_result = "";
	let resnumbers = data_letter.split('\r\n');
	for (let i = 1; i<parseInt(resnumbers[0])+1; i++){
		resnumbers[i] = resnumbers[i].split(' ');
	}
	let matrix = new Array(resnumbers[0]);
	for (let i = 0; i<parseInt(resnumbers[0]); i++){
		matrix[i] = new Array(resnumbers[0]);
		for(let j =0; j<parseInt(resnumbers[0]); j++){
			matrix[i][j] = parseFloat(resnumbers[i+1][j]);
		}
	}
	let size = parseInt(resnumbers[0]);
	delete resnumbers;

	console.log("Entered matrix is:")
	console.log(matrix)

	let result = determinant(matrix, size, false);
	console.log(result);

}

main(process.argv[2]);