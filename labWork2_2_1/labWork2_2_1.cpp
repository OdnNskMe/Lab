#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#define _USE_CRT_SECURE_NO_WARNINES

/*Определить структурированный тип, определить набор функций для работы с массивом структур.
В  структурированной переменной предусмотреть способ отметки ее как не содержащей данных(т.е. "пустой").
Функции должны работать с массивом структур или с отдельной структурой через указатели, а также при необходимости возвращать указатель на структуру.
В перечень функций входят :
-«очистка» структурированных переменных; сделано
-поиск свободной структурированной переменной; ---обязательно сделано
-ввод элементов(полей) структуры с клавиатуры; ---обязательно сделано
-вывод элементов(полей) структуры на экран; ---обязательно сделано
-поиск в массиве структуры и минимальным значением  заданного поля;
-сортировка массива  структур в порядке возрастания заданного поля
	(при сортировке можно использовать тот факт,что в Си++ разрешается присваивание структурированных переменных); -- обязательно сделано
-поиск в массиве структур элемента с заданным значением поля или с наиболее близким к нему по значению. -- обязательно сделано
-удаление заданного элемента; --обязательно 
-ввод и вывод на с файла --обязательно сделано
-память под структуру динамически --обязательно сделано
-изменение(редактирование) заданного элемента.*/

//----структуры----
struct money
{
	int rub;
	int cent;
};
struct dateTime
{
	int hour;
	int min;
	int day;
	int month;
	int year;
};
struct airBus_type
{
	char numFlight[15];
	char destinationPoint[15];
	dateTime departTime;
	money price;
};
//-----конец структур----
void initCheckList(airBus_type* checkList, int SIZE)//иниц структур  оператором конца
{	
	for (int i = 0; i < SIZE; i++)
	{
		*checkList[i].numFlight = '\0';
	}
}

void reloadCheckList(struct airBus_type** checkList, int* SIZE)
{
	(*SIZE) *=2;
	*checkList = (airBus_type*) realloc(*checkList, (*SIZE) * sizeof(airBus_type));	
	for (int i = (*SIZE)/2; i < (*SIZE); i++)
	{
		*(*checkList)[i].numFlight = '\0';
	}
}

enum Menu
{
	Add = 1,
	Show = 2,
	Search = 3,
	Sort = 4,
	Export = 5,
	Import = 6,
	Delete = 7,
	Edit =8,
	Exite = 0,	
	Default = 9
};

enum StructAir
{
	numFlight = 1,
	destinationPoint = 2,
	departMon = 3,
	nochoice = 0
};

void menu()
{
	printf("----------\n");
	printf("1. Добавить\n");
	printf("2. Показать все рейсы\n");
	printf("3. Найти рейс\n");
	printf("4. Сортировать по номеру рейса\n");
	printf("5. Сохранить в файл\n");
	printf("6. Загрузить из файла\n");
	printf("7. Удалить список\n");
	printf("8. Редактировать рейс\n");
	printf("0. Выход\n");
	printf("----------\n\n");
}

airBus_type createAirBus()//ввод данных в структуру
{
	airBus_type sa;
	printf("Номер рейса\n");	
	scanf("%14s", sa.numFlight);
	printf("Пункт назначения\n");	
	scanf("%14s", sa.destinationPoint);
	printf("Время вылета\nчас мин\n");	
	scanf("%d%d", &sa.departTime.hour, &sa.departTime.min);
	while (sa.departTime.hour > 24 || sa.departTime.hour < 1 || sa.departTime.min > 60 || sa.departTime.min <0)
	{
		printf("некорректный ввод данных\n часы от 1 до 24 минуты от 0 до 59\n");
		printf("Время вылета\nчас мин\n");
		scanf("%d%d", &sa.departTime.hour, &sa.departTime.min);
	} 
	printf("Дата вылета\nдень месяц год\n");	
	scanf("%d%d%d", &sa.departTime.day, &sa.departTime.month, &sa.departTime.year);
	while (sa.departTime.day > 31 ||sa.departTime.day < 1 || sa.departTime.month > 12 || sa.departTime.month < 1)
	{
		printf("некорректный ввод данных\n");
		printf("Дата вылета\nдень месяц год\n");
		scanf("%d%d%d", &sa.departTime.day, &sa.departTime.month, &sa.departTime.year);
	}
	printf("Цена\nруб коп\n");
	scanf("%d%d", &sa.price.rub, &sa.price.cent);
	while (sa.price.rub < 0 || sa.price.cent < 0 || sa.price.cent > 100)
	{
		printf("некорректный ввод данных\n");
		printf("Цена\nруб коп\n");	
		scanf("%d%d", &sa.price.rub, &sa.price.cent);
	}
	
	return sa;
}

void swapStruct(struct airBus_type* A, struct airBus_type* B)
{
	struct airBus_type temp;
	temp = *A;
	*A = *B;
	*B = temp;
}

int inputAircraft(airBus_type* checkList, int* SIZE)//поиск первой незаполненной строки
{
	int i;
	for (i = 0; i < *SIZE; i++)
	{
		if (!*checkList[i].numFlight)// идем до первого нуля
			break;
	}
	if (i == (*SIZE))
	{			
		return -1;
	}
	else
	{
		checkList[i] = createAirBus();
	}
	return i;
}

void show(airBus_type sa)//вывод структуры
{
	if (sa.numFlight!=NULL)
	{
		printf("номер рейса %s\n", sa.numFlight);
		printf("Пункт назначения %s\n", sa.destinationPoint);
		printf("Время вылета %d:%d\n", sa.departTime.hour, sa.departTime.min);
		printf("Дата вылета %d-%d-%d\n", sa.departTime.day, sa.departTime.month, sa.departTime.year);
		printf("Цена %d,%d\n\n", sa.price.rub, sa.price.cent);		
	}
}
//---- реализация поиска -----
int airbuscmpByNumFlyght(airBus_type a, airBus_type b)
{
	return strcmp(a.numFlight, b.numFlight) == 0;
}

int airbuscmpByDestination(airBus_type a, airBus_type b)
{
	return strcmp(a.destinationPoint, b.destinationPoint) == 0;
}

int airbuscmpByDepartMonth(airBus_type a, airBus_type b)
{
	return a.departTime.month - b.departTime.month == 0;
}

int searchAircraft(airBus_type *arr, int SIZE, airBus_type searchPat, int cmp(airBus_type,airBus_type))
{
	int index;
	int cost = 0;
	for (index = 0; index < SIZE; index++)
	{
		if (cmp(searchPat, arr[index]))
		{
			show(arr[index]);
			cost++;
		}
	}
	return cost;
}

//----поиск по всем полям-----
bool seachWords(char str, char subStr)
{
	return(subStr != '\0'&&str != '\0'&&str == subStr);
}

int findstr(char* str, char* subStr)
{
	int len = strlen(str);
	int lenSub = strlen(subStr);
	if (len > lenSub)
	{
		for (int i = 0, j = 0; i < len && j < lenSub; i++)
		{
			if (seachWords(*(str + i), *(subStr + j)))
			{
				j++;
			}
			else
			{
				i = i - j;
				j = 0;
			}
			if (j == lenSub)
			{				
				return 1;
			}
		}
	}
	return -1;
}

int searchAllAircraft(char* searchPart, airBus_type* checkList, int SIZE)
{
	int index = 0;
	int cost = 0;
	char temp[15];
	for (index = 0; index < SIZE; index++)
	{		
		(findstr(checkList[index].numFlight, searchPart)) == 1 ? show(checkList[index]), cost++ :
			(findstr(checkList[index].destinationPoint, searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].departTime.hour, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].departTime.min, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].departTime.day, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].departTime.month, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].departTime.year, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].price.rub, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ :
			(findstr(_itoa(checkList[index].price.cent, temp, 10), searchPart) == 1 ? show(checkList[index]), cost++ : 
			false))))))));

	}
	return cost;
}
//------------

void searchAircraft(airBus_type* checkList, int SIZE)//поиск по пункту назначения
{
	printf("-- Выбрать критерий---\n");
	printf("1. Номер рейса\n");
	printf("2. Пункт назначения\n");
	printf("3. Месяц отправления\n");
	printf("4. Поиск по всем полям\n");
	printf("0. Отмена\n");
	printf("----------\n\n");
	int count = 0;
	int ch = nochoice;
	scanf_s("%d", &ch);
	airBus_type searchPat;//искомая часть	
	char searchAllPat[15];
	switch (ch)
	{
	case (numFlight):
	{
		printf("Введите искомый номер рейса\n");
		scanf("%15s", searchPat.numFlight);
		count=searchAircraft(checkList, SIZE, searchPat, airbuscmpByNumFlyght);
	}
	break;
	case (destinationPoint):
	{
		printf("Введите искомый пункт назначения\n");
		scanf("%15s", searchPat.destinationPoint);
		count=searchAircraft(checkList, SIZE, searchPat, airbuscmpByDestination);
	}
	break;
	case (departMon):
	{
		printf("Введите искомый месяц отправления\n");
		scanf("%d", searchPat.departTime.month);
		count=searchAircraft(checkList, SIZE, searchPat, airbuscmpByDepartMonth);
	}
	case (4):
	{
		printf("Введите искомое значение\n");
		scanf("%15s", searchAllPat);
		count=searchAllAircraft(searchAllPat, checkList, SIZE);
	}
	break;
	case (nochoice):
		printf("Поиск Не выбран\n");
		break;
	default:
		break;
	}
	if (count == 0)
	{
		printf("Совпадений не найдено");
	}
}
//----- конец поиска -----
void showAll(airBus_type* checkList, int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (*(checkList+i)->numFlight != '\0')
		{
			show(checkList[i]);
		}		
	}
}

void sortStruct(struct airBus_type* A, int n)//сортировка по номеру рейса
{	
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (strcmp(A[j].numFlight, A[min].numFlight)<0)
			{				
				min = j;
			}
		}
		if (i != min)
		{			
			swapStruct(&A[i], &A[min]);
		}
	}
}

void exportFile(struct airBus_type* checkList, char* filename, int SIZE)
{
	FILE* fd;
	char* startImport;
	int len = SIZE * sizeof(struct airBus_type);// определяем количество записываемых байтов
	
	if ((fd = fopen(filename, "wb")) == NULL)
	{
		perror("Error file");
	}	
	startImport = (char*)&SIZE; //записываем кол-во структур
	for (int i = 0; i < sizeof(int); i++)
	{
		putc(*startImport++, fd);
	}
	startImport = (char*)checkList;//записываем в файл посимвольно весь массив
	for (int i = 0; i < len; i++)
	{
		putc(*startImport, fd);
		startImport++;
	} 	
	fclose(fd);
}

void importFile(char* filename, airBus_type** checkList, int* SIZE)
{
	FILE* fd;
	char* startExport;
	int len = sizeof(int);
	int n, i;
	int* countStruct = (int*)malloc(len);//выделяем память под кол-во данных
	
	if ((fd = fopen(filename, "r")) == NULL)
	{
		perror("Error file");
	}
	//считываем кол-во структур
	startExport = (char*)countStruct;	

	while (len>0)
	{
		i = getc(fd);
		if (i == EOF) break;
		*startExport = i;
		startExport++;
		len--;
	}

	n = *countStruct;
	if (*SIZE < n)
	{
		*SIZE = n;
		reloadCheckList(checkList, &n);		
	}

	startExport = (char*)(*checkList);
	while ((i=getc(fd))!=EOF) //посимвольно читаем из файла
	{
		*startExport = i;
		startExport++;
	}
	free(countStruct);
	fclose(fd);
}

void editStruct(struct airBus_type* checkList, int SIZE)//редактируем данные по номеру рейса
{
	airBus_type editFlight;
	printf("Введите номер редактируемого рейса\n");
	scanf("%15s", editFlight.numFlight);
	int index;	
	for (index = 0; index < SIZE; index++)
	{
		if (strcmp(editFlight.numFlight, (checkList[index]).numFlight)==0)
		{
			show(checkList[index]);
			printf("Новые данные рейса\n--------\n");
			checkList[index] = createAirBus();
		}
	}
}


int main()
{
	system("color F0 ");
	setlocale(LC_ALL, "Russian");
	int SIZE2 = 2; //начальное значение массива	
	airBus_type* checkList = (airBus_type*)malloc(sizeof(airBus_type)*SIZE2);
	initCheckList(checkList, SIZE2);
	char * filename = "checkList.dat";	
	Menu choice = Default;
	int ch = choice;	
	do 
	{		
		menu();
		scanf_s("%d", &ch);
		system("cls");
		choice = (Menu)ch;
		switch (choice)
		{
			case (Add):				
				(inputAircraft(checkList, &SIZE2) == -1) ? reloadCheckList(&checkList, &SIZE2) : false;
				break;
			case (Show):				
				showAll(checkList,SIZE2);
				break;
			case (Search):				
				searchAircraft(checkList, SIZE2);
				break;
			case (Sort):
				sortStruct(checkList,SIZE2);
				break;
			case (Export):
				exportFile(checkList,filename,SIZE2);
				break;
			case (Import):
				importFile(filename,&checkList,&SIZE2);
				break;
			case (Edit):
				editStruct(checkList, SIZE2);
				break;
			case (Delete):
				initCheckList(checkList, SIZE2);
				break;
			default:
				break;
		}	
	} while (choice!=Exite);	
}




struct tree3
{
	int vv;
	struct tree3 *l, *r;
}
A3 = { 1,NULL,NULL },
B3 = { 2,NULL,NULL },
C3 = { 3, &A3, &B3 },
D3 = { 4, &C3, NULL },
*p3 = &D3;
void F3() 
{
	int	i1, i2, i3, i4;
	i1 = A3.vv;		
	i2 = D3.l->vv;
	i3 = p3->l->r->vv; 
	i4 = p3->vv;
}
