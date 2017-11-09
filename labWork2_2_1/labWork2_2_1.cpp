#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#define _USE_CRT_SECURE_NO_WARNINES

/*���������� ����������������� ���, ���������� ����� ������� ��� ������ � �������� ��������.
�  ����������������� ���������� ������������� ������ ������� �� ��� �� ���������� ������(�.�. "������").
������� ������ �������� � �������� �������� ��� � ��������� ���������� ����� ���������, � ����� ��� ������������� ���������� ��������� �� ���������.
� �������� ������� ������ :
-�������� ����������������� ����������; �������
-����� ��������� ����������������� ����������; ---����������� �������
-���� ���������(�����) ��������� � ����������; ---����������� �������
-����� ���������(�����) ��������� �� �����; ---����������� �������
-����� � ������� ��������� � ����������� ���������  ��������� ����;
-���������� �������  �������� � ������� ����������� ��������� ����
	(��� ���������� ����� ������������ ��� ����,��� � ��++ ����������� ������������ ����������������� ����������); -- ����������� �������
-����� � ������� �������� �������� � �������� ��������� ���� ��� � �������� ������� � ���� �� ��������. -- ����������� �������
-�������� ��������� ��������; --����������� 
-���� � ����� �� � ����� --����������� �������
-������ ��� ��������� ����������� --����������� �������
-���������(��������������) ��������� ��������.*/

//----���������----
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
//-----����� ��������----
void initCheckList(airBus_type* checkList, int SIZE)//���� ��������  ���������� �����
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
	printf("1. ��������\n");
	printf("2. �������� ��� �����\n");
	printf("3. ����� ����\n");
	printf("4. ����������� �� ������ �����\n");
	printf("5. ��������� � ����\n");
	printf("6. ��������� �� �����\n");
	printf("7. ������� ������\n");
	printf("8. ������������� ����\n");
	printf("0. �����\n");
	printf("----------\n\n");
}

airBus_type createAirBus()//���� ������ � ���������
{
	airBus_type sa;
	printf("����� �����\n");	
	scanf("%14s", sa.numFlight);
	printf("����� ����������\n");	
	scanf("%14s", sa.destinationPoint);
	printf("����� ������\n��� ���\n");	
	scanf("%d%d", &sa.departTime.hour, &sa.departTime.min);
	while (sa.departTime.hour > 24 || sa.departTime.hour < 1 || sa.departTime.min > 60 || sa.departTime.min <0)
	{
		printf("������������ ���� ������\n ���� �� 1 �� 24 ������ �� 0 �� 59\n");
		printf("����� ������\n��� ���\n");
		scanf("%d%d", &sa.departTime.hour, &sa.departTime.min);
	} 
	printf("���� ������\n���� ����� ���\n");	
	scanf("%d%d%d", &sa.departTime.day, &sa.departTime.month, &sa.departTime.year);
	while (sa.departTime.day > 31 ||sa.departTime.day < 1 || sa.departTime.month > 12 || sa.departTime.month < 1)
	{
		printf("������������ ���� ������\n");
		printf("���� ������\n���� ����� ���\n");
		scanf("%d%d%d", &sa.departTime.day, &sa.departTime.month, &sa.departTime.year);
	}
	printf("����\n��� ���\n");
	scanf("%d%d", &sa.price.rub, &sa.price.cent);
	while (sa.price.rub < 0 || sa.price.cent < 0 || sa.price.cent > 100)
	{
		printf("������������ ���� ������\n");
		printf("����\n��� ���\n");	
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

int inputAircraft(airBus_type* checkList, int* SIZE)//����� ������ ������������� ������
{
	int i;
	for (i = 0; i < *SIZE; i++)
	{
		if (!*checkList[i].numFlight)// ���� �� ������� ����
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

void show(airBus_type sa)//����� ���������
{
	if (sa.numFlight!=NULL)
	{
		printf("����� ����� %s\n", sa.numFlight);
		printf("����� ���������� %s\n", sa.destinationPoint);
		printf("����� ������ %d:%d\n", sa.departTime.hour, sa.departTime.min);
		printf("���� ������ %d-%d-%d\n", sa.departTime.day, sa.departTime.month, sa.departTime.year);
		printf("���� %d,%d\n\n", sa.price.rub, sa.price.cent);		
	}
}
//---- ���������� ������ -----
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

//----����� �� ���� �����-----
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

void searchAircraft(airBus_type* checkList, int SIZE)//����� �� ������ ����������
{
	printf("-- ������� ��������---\n");
	printf("1. ����� �����\n");
	printf("2. ����� ����������\n");
	printf("3. ����� �����������\n");
	printf("4. ����� �� ���� �����\n");
	printf("0. ������\n");
	printf("----------\n\n");
	int count = 0;
	int ch = nochoice;
	scanf_s("%d", &ch);
	airBus_type searchPat;//������� �����	
	char searchAllPat[15];
	switch (ch)
	{
	case (numFlight):
	{
		printf("������� ������� ����� �����\n");
		scanf("%15s", searchPat.numFlight);
		count=searchAircraft(checkList, SIZE, searchPat, airbuscmpByNumFlyght);
	}
	break;
	case (destinationPoint):
	{
		printf("������� ������� ����� ����������\n");
		scanf("%15s", searchPat.destinationPoint);
		count=searchAircraft(checkList, SIZE, searchPat, airbuscmpByDestination);
	}
	break;
	case (departMon):
	{
		printf("������� ������� ����� �����������\n");
		scanf("%d", searchPat.departTime.month);
		count=searchAircraft(checkList, SIZE, searchPat, airbuscmpByDepartMonth);
	}
	case (4):
	{
		printf("������� ������� ��������\n");
		scanf("%15s", searchAllPat);
		count=searchAllAircraft(searchAllPat, checkList, SIZE);
	}
	break;
	case (nochoice):
		printf("����� �� ������\n");
		break;
	default:
		break;
	}
	if (count == 0)
	{
		printf("���������� �� �������");
	}
}
//----- ����� ������ -----
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

void sortStruct(struct airBus_type* A, int n)//���������� �� ������ �����
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
	int len = SIZE * sizeof(struct airBus_type);// ���������� ���������� ������������ ������
	
	if ((fd = fopen(filename, "wb")) == NULL)
	{
		perror("Error file");
	}	
	startImport = (char*)&SIZE; //���������� ���-�� ��������
	for (int i = 0; i < sizeof(int); i++)
	{
		putc(*startImport++, fd);
	}
	startImport = (char*)checkList;//���������� � ���� ����������� ���� ������
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
	int* countStruct = (int*)malloc(len);//�������� ������ ��� ���-�� ������
	
	if ((fd = fopen(filename, "r")) == NULL)
	{
		perror("Error file");
	}
	//��������� ���-�� ��������
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
	while ((i=getc(fd))!=EOF) //����������� ������ �� �����
	{
		*startExport = i;
		startExport++;
	}
	free(countStruct);
	fclose(fd);
}

void editStruct(struct airBus_type* checkList, int SIZE)//����������� ������ �� ������ �����
{
	airBus_type editFlight;
	printf("������� ����� �������������� �����\n");
	scanf("%15s", editFlight.numFlight);
	int index;	
	for (index = 0; index < SIZE; index++)
	{
		if (strcmp(editFlight.numFlight, (checkList[index]).numFlight)==0)
		{
			show(checkList[index]);
			printf("����� ������ �����\n--------\n");
			checkList[index] = createAirBus();
		}
	}
}


int main()
{
	system("color F0 ");
	setlocale(LC_ALL, "Russian");
	int SIZE2 = 2; //��������� �������� �������	
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
