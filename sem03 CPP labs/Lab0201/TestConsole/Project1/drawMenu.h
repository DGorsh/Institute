#include<Windows.h>

#define startTableX 10
#define SIZEFUNC 9
#define startTableY 5
#define endTableX 60
#define endTableY 30
#define SIZEX 2
#define SIZEY 4

#define RED 4
#define YELLOW 6
#define SIZEMENU SIZEX * SIZEY

#define CODEARROWS 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

char *varMenu[SIZEMENU] = { "Продолжение", "Спецификация", "Студент", "Меил", "Задание", "Шифрование", "Помощь", "Выход" };

int countY = (endTableY - startTableY) - (endTableY - startTableY) % SIZEY;
int countX = (endTableX - startTableX) - (endTableX - startTableX) % SIZEX;
int sizeStr = (endTableY - startTableY) / SIZEY;
int sizeCol = (endTableX - startTableX) / SIZEX;

HANDLE h;

void draw(void);
void setText(void);

void draw() {
	COORD posit;
	int x = 0;
	int y = 0;
	for (int i = 0; i <= countY; i++) {
		posit.X = startTableX;
		x = 0;
		posit.Y = startTableY + i;
		SetConsoleCursorPosition(h, posit);
		for (int j = 0; j <= countX; j++) {
			if (i == y || j == x) {
				SetConsoleTextAttribute(h, (WORD)(RED << 4 | 9));
				if (j == x) x += sizeCol;
				printf(" ");
				SetConsoleTextAttribute(h, (WORD)(YELLOW << 4 | 9));
			}
			else 
				printf(" ");
		}
		if (y == i) y += sizeStr;
	}
}

void setText() {
	COORD posit;
	int k = 0;
	SetConsoleTextAttribute(h, (WORD)(YELLOW << 4 | 0));
	posit.Y = startTableY + (sizeStr - 1) / 2;
	for (int i = 1; i <= SIZEY; i++) {
		int x = startTableX;
		for (int j = 1; j <= SIZEX; j++) {
			posit.X = x + (sizeCol - strlen(varMenu[k])) / 2;
			x += sizeCol;
			SetConsoleCursorPosition(h, posit);
			printf("%s", varMenu[k++]);
			SetConsoleTextAttribute(h, (WORD)(RED << 4 | 0));
			if (k != SIZEMENU)
				printf("(F%d)", SIZEMENU - k);
			else
				printf("(Esc)");
			SetConsoleTextAttribute(h, (WORD)(YELLOW << 4 | 0));
		}
		posit.Y += sizeStr;
	}
}

int getMenu() {
	COORD posit;
	int k = 0, n = 0;
	int x = startTableX;
	int y = startTableY + (sizeStr - 1) / 2;
	SetConsoleTextAttribute(h, (WORD)(0 | 2));
	posit.X = x + (sizeCol - strlen(varMenu[k])) / 2 - 1;
	posit.Y = y;
	SetConsoleCursorPosition(h, posit);
	printf("~%s", varMenu[k]);
	while (1) {
		int cp = _getch();
		if (cp == 13)
			return k;
		else if (cp == 27)
			return 7;
		else if (!cp) {
			cp = _getch();
			if (cp > 58 && cp <= 65)
				return (cp - 58) ^ 7;
		}
		if (cp == CODEARROWS) {
			cp = _getch();
			if (cp == UP && posit.Y != startTableY + (sizeStr - 1) / 2) {
				y -= sizeStr;
				k -= SIZEX;
			}
			else if (cp == DOWN && posit.Y != startTableY + (sizeStr - 1) / 2 + sizeStr * (SIZEY - 1)) {
				y += sizeStr;
				k += SIZEX;
			}
			else if (cp == LEFT && posit.X - startTableX > sizeCol) {
				x -= sizeCol;
				k--;
			}
			else if (cp == RIGHT && endTableX - posit.X > sizeCol) {
				x += sizeCol;
				k++;
			}
			if (x != posit.X || y != posit.Y) {
				SetConsoleTextAttribute(h, (WORD)(YELLOW << 4 | 0));
				SetConsoleCursorPosition(h, posit);
				printf(" %s", varMenu[n]);
				posit.X = x + (sizeCol - strlen(varMenu[k])) / 2 - 1;
				posit.Y = y;
				SetConsoleTextAttribute(h, (WORD)(0 | 2));
				SetConsoleCursorPosition(h, posit);
				printf("~%s", varMenu[k]);
				n = k;
			}
		}
	}
}