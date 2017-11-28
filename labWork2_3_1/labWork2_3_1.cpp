///*Разработать две функции, одна из которых вводит с клавиатуры набор данных в произвольной
//последовательности и размещает в памяти в заданном формате. Другая функция читает  эти  данные  
//и выводит на экран. Программа запрашивает и размещает в памяти несколько наборов данных при помощи 
//первой функции, а затем читает их и выводит на экран при помощи второй. Размещение данных производить в 
//выделенном массиве байтов с  контролем  его переполнения.
//Пример:5. Упакованная строка, содержащая символьное представление целых чисел. 
//Все символы строки, кроме цифр, помещаются в последовательность в исходном виде. 
//Последовательность цифр преобразуется в целую переменную, которая записывается в упакованную строку, предваренная символом \0. 
//Конец строки - два подряд идущих символа \0. Пример:
//-исходная строка: "aa2456bbbb6665"
//- упакованная строка : 'a' 'a' '\0' 2456 'b' 'b' 'b' 'b' '\0' 6665 '\0' '\0'


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include<limits.h>



void input(char *buf, int *size,int N) 
{
	printf("Введите  набор данных\n");
	fgets(buf,N, stdin);
	int d = strlen(buf);
	*size = strlen(buf);
}

int makeNumber(char *buf, int size, int *sizeNumber) 
{
	int num = 0;
	for (int i = 0; i<size && isdigit(buf[i]); i++) 
	{
		num *= 10;
		num += (int)(buf[i] - '0');
		(*sizeNumber)++;
		if (num>INT_MAX / 10)break;
	}
	return num;
}

void write(char *buf, int size, char *p) 
{
	for (int i = 0; i<size; i++) 
	{
		if (isdigit(buf[i]))
		{
			int sizeNumber = 0;
			*p = '\0';
			p++;
			int *n = (int*)p;
			*n = makeNumber(&buf[i], size - i, &sizeNumber);
			n++;
			p = (char*)n;
			i += sizeNumber - 1;
		}

		else 
		{
			*p = buf[i];
			p++;
		}

	}

	*p++ = '\0';
	*p = '\0';

}

void read(char *p) 
{
	while ((*p != '\0') || (*(p + 1) != '\0')) 
	{
		if (*p == '\0') 
		{
			p++;
			int *n = (int*)p;
			printf("%d", *n);
			n++;
			p = (char*)n;
		}

		else 
		{
			printf("%c", *p);
			p++;
		}
	}
	printf("\n");
}

void output(char *p) 
{
	while ((*p != '\0') || (*(p + 1) != '\0')) 
	{
		if (*p == '\0') 
		{
			printf("'\\0', ");
			p++;
			int *n = (int*)p;
			printf("'%d', ", *n);
			n++;
			p = (char*)n;
		}
		else 
		{
			printf("'%c', ", *p);
			p++;
		}
	}

	printf("'\\0', '\\0' \n\n");

}

int main() 
{

	setlocale(LC_ALL, "rus");
	const int N = 10;
	char *p = (char*)malloc(N * sizeof(int));
	char buf[N];
	int size = 0;
	input(buf,&size,N);
	write(buf, size, p);
	output(p);
	read(p);
	_getch();

}

//void outputStr(char* str, char tempStr)
//{	
//	int    num = 0;
//
//	while (1)
//	{
//		if (isalpha(*str))
//		{
//			num = 0;
//			sprintf(&tempStr + strlen(&tempStr), "'%c',", *str);			
//		}
//		else if (isdigit(*str))
//		{
//			while (isdigit(*str))
//			{
//				num *= 10;
//				num += *str++ - '0';
//			}
//			sprintf(&tempStr + strlen(&tempStr), "'\\0'%d", num);			
//			str--;
//		}
//		if (!*str++)
//		{
//			sprintf(&tempStr + strlen(&tempStr), "'\\0''\\0'");			
//			break;
//		}
//	}
//	puts(&tempStr);
//}
