#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<locale.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#include "drawMenu.h"

#define SIZEARGINI 10
#define SIZEFILES 4
#define SERRORS 7
#define SIZE 256
#define STARTFILESINI 7

void menu();
void exitCom();
void help();
void task();
void student();
void getCommand();
void rc4();
void iniFile();
void mail();
void spec();

void copyFileAddress(char*, int);
void freeFilesAddress();

void error(int);
int getMenu(void);

struct commands {
	int command;
	char *sFiles[SIZEFILES];
}commands;

int cancelCom = 0;
int commandsIni = 0;
int myCommands = 0;

char *COM[SIZEARGINI] = { "MENU", "SPECIFICATION", "STUDENT", "MAIL", "TASK", "EXECUTE", "HELP", "IN", "OUT", "KEY" };
FILE *fLog;
char *Errors[SERRORS] = { "Несуществующий аргумент", "Ошибка открытия входного файла", "Ошибка открытия выходного файла", 
"Ошибка открытия файла с ключом", "Ошибка открытия файла инициализации", "Некорректная запись файла инициализации", "Отсутствует // или !" };

void(*ptr[SIZEFUNC])() = { iniFile, menu, spec, student, mail, task, rc4, help, exitCom };

void getCommand() {
	if (!(commands.command & 1)) {
		commands.command &= ~(cancelCom);
	}
	for (int i = 0; i < SIZEFUNC; i++) {
		if ((commands.command >> i) & 1) {
			system("cls");
			ptr[i]();
			if (i != 0)
				_getch();
		}
	}
}

void menu() {
	draw();
	setText();
	int k = getMenu();
	system("cls");
	if (k) {
		ptr[k + 1]();
		_getch();
		system("cls");
	}
	else return;
	menu();
}

void exitCom() {
	printf("Не забудь надеть шапку!");
	_getch();
	exit(1);
}

void help() {
	printf("Бог в помощь\n");
}

void task() {
	printf(" А ТЗ НЕ БЫЛО!!!!!");
}

void rc4() {
	FILE* fIn, *fOut, *fKey;
	if (!(fIn = fopen(commands.sFiles[1], "r")))
		error(2);
	char c, input[SIZE] = { 0 }, *in = input, key[SIZE] = { 0 }, *k = key, result[SIZE] = { 0 };
	while ((c = fgetc(fIn)) != EOF)
		*in++ = c;
	*in = 0;
	if (!(fKey = fopen(commands.sFiles[3], "r")))
		error(4);
	while ((c = fgetc(fKey)) != EOF)
		*k++ = c;
	*k = 0;
	int start[SIZE] = { 0 };
	int lenKey = strlen(key);
	for (int i = 0; i < SIZE; i++) {
		start[i] = i;
	}
	int j = 0;
	for (int i = 0; i < SIZE; i++) {
		j = (j + start[i] + key[i % lenKey]) % SIZE;
		int tmp = start[i];
		start[i] = start[j];
		start[j] = tmp;
	}
	int x = 0, y = 0;
	for (int i = 0; i < strlen(input); i++) {
		x = (x + 1) % SIZE;
		y = (y + start[x]) % SIZE;
		int tmp = start[x];
		start[x] = start[y];
		start[y] = tmp;
		result[i] = start[(start[x] + start[y]) % SIZE] ^ input[i];
	}
	printf("Шифрование завершено");
	fclose(fIn);
	if (!(fOut = fopen(commands.sFiles[2], "w")))
		error(3);
	fprintf(fOut, "%s", result);
	fclose(fOut);
	fclose(fKey);
}

void iniFile() {
	FILE *fIni;
	if (!(fIni = fopen(commands.sFiles[0], "r")))
		error(5);
	char buf[SIZE] = { 0 }, *b = buf, c;
	while ((c = fgetc(fIni)) != EOF) {
		if (c != '=') {
			if (!isspace(c))
				*b++ = toupper(c);
		}
		else {
			*b = 0;
			b = buf;
			int i;
			for (i = 0; i < SIZEARGINI; i++) {
				if (!strcmp(buf, COM[i])) {
					if ((c = fgetc(fIni)) != '1' && c != '0')
						error(6);
					break;
				}
			}
			if (i == SIZEARGINI) error(6);
			if (i < STARTFILESINI) {
				if (c == '1')
					commandsIni |= (1 << (i + 1));
				else
					commandsIni &= ~(1 << (i + 1));
			}
			else {
				while ((c = fgetc(fIni)) != EOF && c != ';')
					*b++ = c;
				*b = 0;
				copyFileAddress(buf, i - STARTFILESINI + 1);
			}
			b = buf;
			*b = 0;
			if (c == EOF) return;
		}
	}
	if (strlen(buf)) error(6);
	commands.command &= commandsIni;
	myCommands |= commandsIni;
	myCommands &= ~(cancelCom);
	commands.command |= myCommands;
	commands.command &= ~(cancelCom);
}

void error(int n) {
	printf("%s\n", Errors[n - 1]);
	_getch();
	exit(n);
}

void student() {
	printf("Краснопеев Михаил Владимирович");
}

void mail() {
	printf("m_krasnopeev@mail.ru");
}

void spec() {
	printf("Символ ! отменяет флаг");
}

void copyFileAddress(char *b, int k) {
	commands.sFiles[k] = (char*)malloc(sizeof(char*) * strlen(b));
	strcpy(commands.sFiles[k], b);
}

void freeFilesAddress() {
	for (int i = 0; i < SIZEFILES; i++) {
		free(commands.sFiles[i]);
	}
}