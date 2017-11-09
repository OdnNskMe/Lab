#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
double testQ1(double x)
{
	double eps = 0.1;
	double s, sn;
	int n;
		for (s = 0, sn = 1, n = 1; fabs(sn) > eps; n++)
		{
			s += sn;
			sn = -sn * x / n;
		}
		return s;
}
double testQ6(double x)
{
	double eps = 0.1;
	double s, sn;
	int n;
	for (s = 0, sn = x, n = 1; fabs(sn) > eps; n += 2)
	{
		s += sn;
		sn = sn * x *x * n / (n + 1);
	}
	return s;
}

int F7(char c[])
{
	int i, s;
	for (i = 0; c[i] != '\0'; i++)
		if (c[i] >= '0' && c[i] <= '7') break;
	for (s = 0; c[i] >= '0' && c[i] <= '7'; i++)
		s = s * 8 + c[i] - '0';
	return s;
}


int main()
{
	//double x = 0.1;// диапазон значений аргумента от 0,1
	//do {
	//	printf(" %.2f testQ1 =  %f |testQ6 = %f\n", x, testQ1(x),testQ6(x));
	//	x += 0.1; //шаг изменения аргумента
	//} while (x <= 1.0);  // диапазон значений аргумента до 1

	char str[26] = "11181888888";
	printf("%d ",F7(str));

	_getch();
}