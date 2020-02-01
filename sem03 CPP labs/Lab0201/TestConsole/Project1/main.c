#define _CRT_SECURE_NO_WARNINGS

#define STARTFILES 6
#define SIZEARGS 10

#include "commands.h"

char *argum[SIZEARGS] = { "m", "c", "s", "@", "t", "e", "fini", "fin", "fout", "fkey" };
char *startFiles[SIZEFILES] = { "iniFile.ini", "input.in","output.out", "key.txt" };

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	draw();
	setText();
	int k = getMenu();
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);
	for (int i = 0; i < SIZEFILES; i++)
		copyFileAddress(startFiles[i], i);
	while (*argv++) {
		int i = STARTFILES;
		if (**argv == '\\') {
			for (i = 0; i < STARTFILES; i++) {
				if (strstr(*argv, argum[i]) == *argv + 1) {
					if (strlen(*argv) != 2) error(1);
					myCommands |= (1 << (i + 1));
					break;
				}
			}
			if (i != STARTFILES) continue;
			for (i; i < SIZEARGS; i++) {
				if (strstr(*argv, argum[i]) == *argv + 1) {
					char *b = *argv + strlen(argum[i]) + 1;
					if (*b++ == '=')
						copyFileAddress(b, i - STARTFILES);
					else
						error(1);
					break;
				}
			}
			if (i == STARTFILES) {
				commands.command |= 1;
				break;
			}
			if (i == SIZEARGS)
				error(1);
		}
		else if (**argv == '!') {
			for (i = 0; i < STARTFILES; i++) {
				if (strstr(*argv, argum[i]) == *argv + 1) {
					cancelCom |= 1 << (i + 1);
					break;
				}
			}
		}
		else
			error(7);
	}
	if (*++argv != NULL) {
		int i = STARTFILES;
		if (**argv == '\\') {
			for (i = 0; i < STARTFILES; i++) {
				if (strstr(*argv, argum[i]) == *argv + 1) {
					if (strlen(*argv) != 2) error(1);
					myCommands |= (1 << (i + 1));
					break;
				}
			}
			if (i == STARTFILES) {
				for (i; i < SIZEARGS; i++) {
					if (strstr(*argv, argum[i]) == *argv + 1) {
						char *b = *argv + strlen(argum[i]) + 1;
						if (*b++ == '=')
							copyFileAddress(b, i - STARTFILES);
						else
							error(1);
						break;
					}
				}
				if (i == STARTFILES) {
					commands.command |= 1;
				}
				if (i == SIZEARGS)
					error(1);
			}
		}
		else if (**argv == '!') {
			for (i = 0; i < STARTFILES; i++) {
				if (strstr(*argv, argum[i]) == *argv + 1) {
					cancelCom |= 1 << (i + 1);
					break;
				}
			}
		}
		else
			error(7);
	}
	getCommand();
	return 0;
}