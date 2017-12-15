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
	printf("Введите строку букв и цифр\n");
	fgets(buf,N, stdin);
	*size = strlen(buf);
}

int stringToDigit(char *buf, int size, int *sizeNumber) 
{
	int digit = 0;
	for (int i = 0; i<size && isdigit(buf[i]); i++) 
	{
		digit *= 10;
		digit += (int)(buf[i] - '0');
		(*sizeNumber)++;
		if (digit>INT_MAX / 10)break;
	}
	return digit;
}

void convert(char *buf, int size, char *str)
{
	for (int i = 0; i<size; i++) 
	{
		if (isdigit(buf[i]))
		{
			int sizeNumber = 0;
			*str = '\0';
			str++;
			int *n = (int*)str;
			*n = stringToDigit(&buf[i], size - i, &sizeNumber);
			n++;
			str = (char*)n;
			i += sizeNumber - 1;
		}
		else 
		{
			*str = buf[i];
			str++;
		}
	}
	*str++ = '\0';
	*str = '\0';

}

void readConvert(char *str)
{
	while ((*str != '\0') || (*(str + 1) != '\0'))
	{
		if (*str == '\0')
		{
			str++;
			int *n = (int*)str;
			printf("%d", *n);
			n++;
			str = (char*)n;
		}
		else 
		{
			printf("%c", *str);
			str++;
		}
	}
	printf("\n");
}

void outputConvert(char *str)
{
	while ((*str != '\0') || (*(str + 1) != '\0'))
	{
		if (*str == '\0')
		{
			printf("'\\0'");
			str++;
			int *digit = (int*)str;
			printf("'%d'", *digit);
			digit++;
			str = (char*)digit;
		}
		else 
		{
			printf("'%c'", *str);
			str++;
		}
	}
	printf("'\\0''\\0'\n");
}

int main() 
{
	system("color F0 ");
	setlocale(LC_ALL, "rus");
	const int N = 20;
	char *str = (char*)malloc(sizeof(int) * N);
	char strBuf[N];
	int size = 0;
	input(strBuf,&size,N);
	convert(strBuf, size, str);
	outputConvert(str);
	readConvert(str);
	_getch();
	free(str);
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
