//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <math.h>
//double testQ1(double x)
//{
//	double eps = 0.1;
//	double s, sn;
//	int n;
//		for (s = 0, sn = 1, n = 1; fabs(sn) > eps; n++)
//		{
//			s += sn;
//			sn = -sn * x / n;
//		}
//		return s;
//}
//double testQ6(double x)
//{
//	double eps = 0.1;
//	double s, sn;
//	int n;
//	for (s = 0, sn = x, n = 1; fabs(sn) > eps; n += 2)
//	{
//		s += sn;
//		sn = sn * x *x * n / (n + 1);
//	}
//	return s;
//}
//
//int F7(char c[])
//{
//	int i, s;
//	for (i = 0; c[i] != '\0'; i++)
//		if (c[i] >= '0' && c[i] <= '7') break;
//	for (s = 0; c[i] >= '0' && c[i] <= '7'; i++)
//		s = s * 8 + c[i] - '0';
//	return s;
//}
//
//
//int main()
//{
//	//double x = 0.1;// диапазон значений аргумента от 0,1
//	//do {
//	//	printf(" %.2f testQ1 =  %f |testQ6 = %f\n", x, testQ1(x),testQ6(x));
//	//	x += 0.1; //шаг изменения аргумента
//	//} while (x <= 1.0);  // диапазон значений аргумента до 1
//
//	char str[26] = "11181888888";
//	printf("%d ",F7(str));
//
//	_getch();
//}
#include <stdio.h>

#include <conio.h>

#include <locale.h>

#include <malloc.h>

#include<limits.h>


#define	LENTH 32


int strLen(char *s) {

	int i;

	for (i = 0; *(s + i) != '\0'; i++);

	return i - 1;

}

bool isNumber(char c) {

	return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');

}

void input(char *buf, int *size) {

	printf("Введите произвольный набор данных, до %d символов:\n\n", LENTH - 2);

	fgets(buf, LENTH - 2, stdin);

	int d = strLen(buf);

	*size = strLen(buf);

}

int makeNumber(char *buf, int size, int *sizeNumber) {

	int num = 0;

	for (int i = 0; i<size && isNumber(buf[i]); i++) {

		num *= 10;

		num += (int)(buf[i] - '0');

		(*sizeNumber)++;

		if (num>INT_MAX / 10)break;

	}

	return num;

}

void write(char *buf, int size, char *p) {

	for (int i = 0; i<size; i++) {

		if (isNumber(buf[i])) {

			int sizeNumber = 0;

			*p = '\0';

			p++;

			int *n = (int*)p;

			*n = makeNumber(&buf[i], size - i, &sizeNumber);

			n++;

			p = (char*)n;

			i += sizeNumber - 1;

		}

		else {

			*p = buf[i];

			p++;

		}

	}

	*p++ = '\0';

	*p = '\0';

}

void read(char *p) {

	while ((*p != '\0') || (*(p + 1) != '\0')) {

		if (*p == '\0') {

			p++;

			int *n = (int*)p;

			printf("%d", *n);

			n++;

			p = (char*)n;

		}

		else {

			printf("%c", *p);

			p++;

		}

	}

	printf("\n");

}

void output(char *p) {

	while ((*p != '\0') || (*(p + 1) != '\0')) {


		if (*p == '\0') {

			printf("'\\0', ");

			p++;

			int *n = (int*)p;

			printf("'%d', ", *n);

			n++;

			p = (char*)n;

		}

		else {

			printf("'%c', ", *p);

			p++;

		}

	}

	printf("'\\0', '\\0' \n\n");

}

int main() {

	setlocale(LC_ALL, "rus");

	char *p = (char*)malloc(LENTH * sizeof(int));

	char buf[LENTH];

	int size;


	input(buf, &size);

	write(buf, size, p);

	output(p);

	read(p);


	_getch();

}

