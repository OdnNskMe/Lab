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


void inputStr(char * str, int n)
{
	printf("Введите данные\n");
	fgets(str, n, stdin);
}

void outputStr(char * str)
{
	char   tempStr[256] = "";
	int    num = 0;

	while (1)
	{
		if (isalpha(*str))
		{
			num = 0;
			sprintf(tempStr + strlen(tempStr), "'%c'", *str);
		}
		else if (isdigit(*str))
		{
			while (isdigit(*str))
			{
				num *= 10;
				num += *str++ - '0';
			}
			sprintf(tempStr + strlen(tempStr), "'\\0'%d", num);
			str--;
		}
		if (!*str++)
		{
			sprintf(tempStr + strlen(tempStr), "'\\0''\\0'");
			break;
		}
	}
	puts(tempStr);

	char   tempStr2[256] = "";
	char temp[256] = "";
	while (1)
	{
		if (isalpha(*tempStr))
		{
			sprintf(tempStr2 + strlen(tempStr2), "'%c'", *tempStr);
		}

		else if (*tempStr=='\0')
		{
			(*tempStr)++;
			while (isdigit(*tempStr))
			{
				_itoa(*tempStr, temp, 10);
			}
			sprintf(tempStr + strlen(tempStr), "'\\0'%d", temp);
			(*tempStr)--;
		}
		if (!(*tempStr)++)
		{
			sprintf(tempStr + strlen(tempStr), "'\\0''\\0'");
			break;
		}
	}
}

int main()
{
	system("color F0 ");
	setlocale(LC_ALL, "Russian");
	const int N = 81;
	char strstr[N];
	inputStr(strstr,N);
	outputStr(strstr);

	return 0;
}