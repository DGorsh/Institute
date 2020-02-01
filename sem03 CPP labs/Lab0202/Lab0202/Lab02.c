#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<locale.h>
#include<ctype.h>
#include<stdlib.h>

#define SIZEER 5
#define SIZEBUF 1024
#define SIZEUR 7
#define createTmp char buf[SIZEBUF] = { 0 }, *tmpBuf = buf
#define checkInput isdigit(*b) || *b == '-' || *b == '.'

char arrErrors[SIZEER][SIZEBUF] = { "Ошибка открытия файла" };
char arrUrs[SIZEUR][SIZEBUF] = { "Общее", "Каноническое", "В отрезках", "Нормированное", "Через 2 точки", "Параметрическое", 
"С угловым коэффициентом" };

void openFileUr();
void error(int num);

void usual();
void kanon();
void inOtr();
void norm();
void inTwoPoints();
void param();
void withGrad();
//void differ();

void toUsual();
void toKanon();
void toInOtr();
void toNorm();
void toInTwoPoints();
void toParam();
void toWithGrad();
void toUsualForAll();

void resh();

FILE* fIn;
char bufUr[SIZEBUF] = { 0 }, *b;
int i;

void(*ptr[SIZEUR])() = { usual, kanon, inOtr, norm, inTwoPoints, param, withGrad };

void(*toPtr[SIZEUR])() = { toUsual, toKanon, toInOtr, toNorm, toInTwoPoints, toParam, toWithGrad };

struct usual {
	float a, b, c;
}usStr;

struct kanon {
	float a, b, x0, y0;
}kaStr;

struct inOtr {
	float x1, y1;
}inO;

struct norm {
	float sin, cos, p;
}nor;

struct inTwoPoints {
	float x0, y0, x1, y1;
}inT;

struct param {
	float x0, a, y0, b;
}par;

struct withGrad {
	float k, b;
}wit;

int main() {
	setlocale(LC_ALL, "Russian");
	openFileUr();
	_getch();
	return 0;
}

void openFileUr() {
	char *sIn = "InputUr.in", c, buf[SIZEBUF] = { 0 };
	b = buf;
	if (!(fIn = fopen(sIn, "r"))) {
		error(1);
	}
	while ((c = fgetc(fIn)) != '\n') {
		*b++ = c;
	}
	*b = 0;
	for (i = 0; i < SIZEUR; i++) {
		if (!strcmp(buf, arrUrs[i])) break;
	}
	b = buf;
	while ((c = fgetc(fIn)) != '\n') {
		*b++ = c;
	}
	*b = 0;
	b = buf;
	ptr[i]();
	b = buf;
	while ((c = fgetc(fIn)) != EOF) {
		*b++ = c;
	}
	*b = 0;
	toUsualForAll();
	for (i = 0; i < SIZEUR; i++) {
		if (!strcmp(buf, arrUrs[i])) break;
	}
	toPtr[i]();
	resh();
}

void error(int num) {
	printf("%s\n", arrErrors[num - 1]);
	_getch();
	exit(num);
}

void usual() {
	usStr.a = 0;
	usStr.b = 0;
	usStr.c = 0;
	createTmp;
	while (*b) {
		if (*b == 'x' || *b == 'y' || *b == '=') {
			*tmpBuf = 0;
			switch (*b)
			{
			case 'x':usStr.a = atof(buf);
				break;
			case 'y':usStr.b = atof(buf);
				break;
			case '=':usStr.c = atof(buf);
				break;
			default:
				break;
			}
			tmpBuf = buf;
		}
		if (checkInput)
			*tmpBuf++ = *b;
		*b++;
	}
}

void kanon() {
	kaStr.a = 0;
	kaStr.b = 0;
	kaStr.x0 = 0;
	kaStr.y0 = 0;
	createTmp;
	while (*b) {
		if (*b == '/' || *b == '=' || *(b + 1) == 0) {
			*tmpBuf = 0;
			switch (*b)
			{
			case '=':kaStr.a = atof(buf);
				break;	
			case '/': {
				if (!kaStr.a) {
					kaStr.x0 = -atof(buf);
				}
				else kaStr.y0 = -atof(buf);
				break;
			}
			default:
				kaStr.b = atof(buf);
				break;
			}
			tmpBuf = buf;
		}
		if (checkInput)
			*tmpBuf++ = *b;
		*b++;
	}
}

void inOtr() {
	inO.x1 = 0;
	inO.y1 = 0;
	createTmp;
	while (*b) {
		if (*b == '+' || *b == '=') {
			*tmpBuf = 0;
			switch (*b)
			{
			case '+': inO.x1 = atof(buf);
				break;
			case '=': inO.y1 = atof(buf);
				break;
			default:
				break;
			}
		}
		if (checkInput)
			*tmpBuf++ = *b;
		*b++;
	}
}

void norm() {
	nor.cos = 0;
	nor.sin = 0;
	nor.p = 0;
	createTmp;
	while (*b) {
		if (*b == 'x' || *b == 'y' || *b == '=') {
			*tmpBuf = 0;
			switch (*b)
			{
			case 'x': nor.cos = atof(buf);
				break;
			case 'y': nor.sin = atof(buf);
				break;
			case '=': nor.p = atof(buf);
			default:
				break;
			}
			tmpBuf = buf;
		}
		if (checkInput)
			*tmpBuf++ = *b;
		*b++;
	}
}

void inTwoPoints() {
	inT.y1 = 0;
	inT.y0 = 0;
	inT.x1 = 0;
	inT.x0 = 0;
	createTmp;
	char k = ' ';
	int n = 0;
	while (*b) {
		if (*b == '/' || *b == '=' || *b == '-') {
			*tmpBuf = 0;
			switch (*b)
			{
			case '/': { 
				if (*(b - 1) != 'x' && *(b - 1) != 'y') {
					if (k == 'x') {
						inT.x0 = -atof(buf);
					}
					else
						inT.y0 = -atof(buf);
				}
				break;
			}
			case '-': {
				if (*(b - 1) != 'x' && *(b - 1) != 'y') {
					if (k == 'x') {
						inT.x1 = atof(buf);
					}
					else
						inT.y1 = atof(buf);
				}
				break;
			}
			default:
				break;
			}
			tmpBuf = buf;
		}
		if (checkInput)
			*tmpBuf++ = *b;
		else if (isalpha(*b)) k = *b;
		*b++;
	}
}

void param() {
	par.a = 0;
	par.b = 0;
	par.x0 = 0;
	par.y0 = 0;
	createTmp;
	char k = ' ';
	while (*b) {
		if (*b == '+' || *b == 't') {
			*tmpBuf = 0;
			switch (*b)
			{
			case '-':
			case '+': {
				if (k == 'x')
					par.x0 = atof(buf);
				else par.y0 = atof(buf);
				break;
			}
			case 't': {
				if (k == 'x')
					par.a = atof(buf);
				else par.b = atof(buf);
				break;
			}
			default:
				break;
			}
			tmpBuf = buf;
		}
		if (checkInput)
			*tmpBuf++ = *b;
		if (*b == 'x' || *b == 'y')
			k = *b;
		*b++;
	}
}

void withGrad() {
	wit.b = 0;
	wit.k = 0;
	createTmp;
	while (*b) {
		if (*b == 'x' || *(b + 1) == 0) {
			*tmpBuf = 0;
			switch (*b)
			{
			case 'x':
				wit.k = atof(buf);
				break;
			default:
				wit.b = atof(buf);
				break;
			}
			tmpBuf = buf;
		}
		if (checkInput)
			*tmpBuf++ = *b;
		*b++;
	}
}

/*void differ() {
	float k = 0;
}*/

void toUsualForAll() {
	switch (i)
	{
	case 0: break;
	case 1: {
		usStr.a = kaStr.b;
		usStr.b = -kaStr.a;
		usStr.c = -kaStr.x0 * kaStr.b + kaStr.y0 * kaStr.a;
		break;
	}
	case 2: {
		usStr.a = inO.y1;
		usStr.b = inO.x1;
		usStr.c = -inO.x1 + inO.y1;
		break;
	}
	case 3: {
		usStr.a = -nor.cos * 5;
		usStr.b = -nor.sin * 5;
		usStr.c = -nor.p * 5;
		break;
	}
	case 4: {
		usStr.a = inT.y1 - inT.y0;
		usStr.b = inT.x1 - inT.x0;
		usStr.c = -(inT.y1 - inT.y0)*inT.x0 + (inT.x1 - inT.x0) * inT.y0;
		break;
	}
	case 5: {
		usStr.a = par.b;
		usStr.b = par.a;
		usStr.c = -(par.x0 * par.b) + par.y0 * par.a;
		break;
	}
	case 6: {
		usStr.a = wit.k;
		usStr.b = -1;
		usStr.c = wit.b;
		break;
	}
	default:
		break;
	}
}

void toUsual() {
	printf("%g*x+%g*y+%g=0", usStr.a, usStr.b, usStr.c);
}

void toKanon() {
	kaStr.a = -usStr.b;
	kaStr.b = usStr.a;
	kaStr.x0 = 0;
	kaStr.y0 = usStr.c / usStr.b;
	printf("x-%g/%g=y-%g/%g", kaStr.x0, kaStr.a, kaStr.y0, kaStr.b);
}

void toInOtr() {
	inO.x1 = (1 / usStr.a) * -usStr.c;
	inO.y1 = (1 / usStr.b) * -usStr.c;
	printf("x/%g+y/%g=1", inO.x1, inO.y1);
}

void toNorm() {
	nor.cos = usStr.a / sqrt(usStr.a * usStr.a + usStr.b * usStr.b);
	nor.sin = usStr.b / sqrt(usStr.a * usStr.a + usStr.b * usStr.b);
	nor.p = usStr.c / sqrt(usStr.a * usStr.a + usStr.b * usStr.b);
	printf("%gx+%gy-%g=0", nor.cos, nor.sin, nor.p);
}

void toInTwoPoints() {
	inT.x0 = 0;
	inT.y0 = usStr.c / usStr.b;
	inT.x1 = -usStr.b;
	inT.y1 = usStr.a - inT.y0;
	printf("x-%g/%g-%g=y-%g/%g-%g", inT.x0, inT.x1, inT.x0, inT.y0, inT.y1, inT.y0);
}

void toParam() {
	par.a = usStr.b;
	par.b = usStr.a;
	par.x0 = 0;
	par.y0 = usStr.c / usStr.b;
	printf("t=%g+%gx\nt=%g+%gy", par.x0, par.a, par.y0, par.b);
}

void toWithGrad() {
	wit.k = -usStr.a / usStr.b;
	wit.b = -usStr.c / usStr.b;
	printf("y=%gx+%g", wit.k, wit.b);
}

void resh() {
	printf("\nРасстояние p от прямой до начала координат O равно\np=%g", usStr.c / sqrt(usStr.a * usStr.a + usStr.b * usStr.b));
}