#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define _USE_CRT_SECURE_NO_WARNINES

//Целая переменная - счетчик, затем последовательность вещественных переменных.Функция возвращает сумму переменных.
// вопрос 3

double funk(int N,...)
{
	int i = 0;
	int n = 0;
	double s = 0;
	double* q = (double*)(&N+2);
	
	for ( s = 0 , n = N; n!=0; n--)
	{
		s += *q;
		q++;
	}
	return s;
}

void main()
{
	system("color F0 ");
	printf("%lf\n",funk(3,1.1,2.1,3.3));
}





