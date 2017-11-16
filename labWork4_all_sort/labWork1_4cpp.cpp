#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

void swap(int* glass1, int* glass2)
{
	int glass3 = *glass1;
	*glass1 = *glass2;
	*glass2 = glass3;
}

void masNumb(int* A, int n, int z)// массив не корректно т.к. размерность идет с нуля а не 
{
	for (int i = 0; i < n; i++)// N задает размер массива, цикл повторяется пока массив не заполнится
	{
		//*(A+i) = rand();//берем текушую ячейку массива и заполняем случайным числом.ограничение случайных чисел до Z
		*(A + i) = n - i;		
	}
}
void masWorkB(int* A, int* B, int n)
{
	for (int i = 0; i < n; i++)
		*(B+i) = *(A+i);
}
//выводим массив на экран
void outPut(int* A, int n, char* title)
{
	printf("--%s--\n", title);
	for (int i = 0; i < n; i++)//берем текушее значение масиива и выводим его на экран, делаем это n раз т.к. n это размер массива
	{
		printf("%d ", *(A+i));//выводим на экран текушее значение массива		
	}
	printf("\n\n");//пустая строчка после массива		
}

void Print(char* title1, _int64 result1, char* title2, _int64 result2, char* title3, _int64 result3)
{
	printf("%s = %" PRId64 "\n%s = %" PRId64 "\n%s = %" PRId64 "\n", title1, result1, title2, result2, title3, result3);
	
}

void menu()
{
	printf("----sort----\n");
	printf("1. Bubble\n");
	printf("2. Shaker\n");
	printf("3. Select\n");
	printf("4. Merge\n");
	printf("5. Quick\n");
	printf("6. Shells\n");
	printf("0. Exit\n");
	printf("----------\n");
}

void sortBubble(int* A, int n, time_t &time, _int64 &countConpare, _int64 &countSwap)
{		
	bool isSwap;
	do 
	{
		isSwap = false;
		int lastSwap = 0;
		for (int i = 0; i < n - 1; i++)
		{
			countConpare = countConpare+1;
			if (*(A + i) > *(A + i + 1))
			{
				countSwap = countSwap+1;
				swap(&(*(A+i)), &(*(A + i + 1)));
				isSwap = true;
				lastSwap = i + 1;
			}			
		}
		n = lastSwap;		
	} while (isSwap);
	time = clock() - time;
}

void sortShaker(int* A, int n, time_t &time, _int64 &countConpare, _int64 &countSwap)
{
	int a = 0, b = n, step = 1;
	while (b - a > 1)
	{
		if (step == 1)
		{
			int last = a;
			for (int i = a; i < b - 1; i++)
			{
				countConpare++;
				if (A[i] > A[i + 1])
				{
					countSwap++;
					swap(&A[i], &A[i + 1]);
					last = i + 1;
				}
			}
			b = last;
		}
		else
		{
			int last = b - 1;
			for (int i = b - 1; i > a; i--)
			{
				countConpare++;
				if (A[i - 1] > A[i])
				{
					countSwap++;
					swap(&A[i - 1], &A[i]);
					last = i - 1;
				}
			}
			a = last;
		}
		step *= -1;
	}
	time = clock() - time;
}

void sortSelect(int* A, int n, time_t &time, _int64 &countConpare, _int64 &countSwap)
{	
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			countConpare++;
			if (A[j] < A[min])
			{
				min = j;
			}				
		}
		countConpare++;
		if (i != min)
		{
			countSwap++;
			swap(&A[i], &A[min]);
		}
			
	}
	time = clock() - time;
}

void sortQuick(int* A, int a, int b, time_t &time, _int64 &countConpare, _int64 &countSwap)
{
	if ((b - a) > 1)
	{
		double sr = 0;
		for (int i = a; i < b; i++)
			sr += A[i];//находим сумму массива
		sr /= (b - a);//рассчет средней арифмет
		//грани сортировки
		int i = a;
		int j = b - 1;
		while (i<j)
		{
			countConpare++;
			if (A[i] <= sr)
			{
				i++;
			}
			else
			{
				countConpare++;
				if (A[j] > sr)
				{
					j--;
				}					
				else
				{
					countSwap++;
					swap(&A[i], &A[j]);
				}
			}
		}
		sortQuick(A, a, i, time, countConpare, countSwap);
		sortQuick(A, i, b, time, countConpare, countSwap);
	}
	time = clock() - time;	
}

void sortMerge(int A[], int a, int b, time_t &time, _int64 &countConpare, _int64 &countSwap)
{	
	if (b - a > 1)
	{
		int center = (a + b) / 2;
		sortMerge(A, a, center, time, countConpare, countSwap);
		sortMerge(A, center, b, time, countConpare, countSwap);
		int *Temp = new int[b - a];
		int i = 0;
		int j = 0;
		while (a + i < center&&center + j < b)
		{
			countConpare++;
			if (A[a + i] < A[center + j])
			{
				Temp[i + j] = A[a + i];
				i++;
			}
			else
			{
				Temp[i + j] = A[center + j];
				j++;
			}
		}
		while (a + i < center)
		{
			Temp[i + j] = A[a + i];
			i++;
		}
		while (center + j < b)
		{
			Temp[i + j] = A[center + j];
			j++;
		}
		for (int i = 0; i < b-a; i++)
		{
			A[a + i] = Temp[i];
		}
		delete[]Temp;
	}
	time = clock() - time;
	
}

void ShellsSort(int A[], int n, time_t &time, _int64 &countConpare, _int64 &countSwap)
{
	int i;
	int j;
	int step= n/2; //задаем параметр шага
	int delt = 0; //параметр для сдвига обаласти сортировки 
	int temp;

	for (step; step > 0; step /= 2)
		for (i = step+delt; i < n; i++)
		{
			countSwap++;
			temp = A[i];
			for (j = i; j >= step; j -= step)
			{
				countConpare++;
				if (temp < A[j - step])
				{
					countSwap++;
					A[j] = A[j - step];
				}
				else
					break;
			}
			countSwap++;
			A[j] = temp;
		}
	countSwap /= 3;
	time = clock() - time;
}

void main()
{
	system("color F0 ");
	const int N = 500000;
	int Z = 5;

	int *A = (int*)malloc(N * sizeof(int));
	int *B = (int*)malloc(N * sizeof(int));
	
	int action;
	time_t time;
	_int64 countConpare = 0;
	_int64 countSwap = 0;

	masNumb(A, N, Z);
	//outPut(A, N, "massiv");
	do {
		//outPut(A, N,"massiv");
		menu();		
		scanf_s("%d", &action);
		switch (action)
		{
		case(1):
		{	
			countConpare = 0;
			countSwap = 0;
			masWorkB(A,B,N);
			time = clock();
			sortBubble(B, N, time, countConpare, countSwap);
			//time = clock() - time;
			//outPut(B, N,"Bubble");
			Print("time_Bubble", time, "conpare_Bubble", countConpare, "swap_Bubble", countSwap);
		}
			break;
		case(2):
		{
			time = clock();
			countConpare = 0;
			countSwap = 0;
			masWorkB(A, B, N);
			sortShaker(B, N, time, countConpare, countSwap);
			//outPut(B, N,"Sheker");
			Print("time_Shaker", time, "conpare_Shaker", countConpare, "swap_Shaker", countSwap);
		}
			break;
		case(3):
		{
			time = clock();
			countConpare = 0;
			countSwap = 0;
			masWorkB(A, B, N);
			sortSelect(B, N, time, countConpare, countSwap);
			//outPut(B, N,"Select");
			Print("time_Select", time, "conpare_Select", countConpare, "swap_Select", countSwap);
		}
			break;
		case(4):
		{
			time = clock();
			countConpare = 0;
			countSwap = 0;
			masWorkB(A, B, N);
			sortMerge(B,0, N, time, countConpare, countSwap);
			//outPut(B, N, "Merge");
			Print("time_Merge", time, "conpare_Merge", countConpare, "swap_Merge", countSwap);
		}
		break;
		case(5):
		{
			time = clock();
			countConpare = 0;
			countSwap = 0;
			masWorkB(A, B, N);
			sortQuick(B,0, N, time, countConpare, countSwap);
			//outPut(B, N, "Quick");
			Print("time_Quick", time, "conpare_Quick", countConpare, "swap_Quick", countSwap);
		}
		break;
		case(6):
		{
			time = clock();
			countConpare = 0;
			countSwap = 0;
			masWorkB(A, B, N);
			ShellsSort(B, N, time, countConpare, countSwap);
			//outPut(B, N, "Shells");
			Print("time_Shells", time,"conpare_Shells", countConpare,"swap_Shells", countSwap);
		}
		break;

		default:
			break;
		}
		
	} while (action != 0);

	free(A);
	free(B);	
}
