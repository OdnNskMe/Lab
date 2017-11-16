#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

/*� ������ ����� ��� ����� � ���������� ������� ���������, 
������������ ����� ������, � ������� �������� �� ��������������� �������������� � ����������������� �������.*/

bool isDigit(char dig)// �������� ������� �� �����
{
	return (dig >= '0' && dig <= '9');
}

void revers(char *s) // ������ ������ �������
{
	int j;
	for (j = 0; s[j] != '\0'; j++);
	j--;
	for (int i = 0; i < j; i++, j--)
	{
		char swap = s[i];
		s[i] = s[j];
		s[j] = swap;
	}
}

int stringToDigit(char* c) //������� ������� � �����
{
	int digit = 0;
	for (int i = 0; c[i] != '\0'; i++)
	{
		if (isDigit(c[i]))
		{
			digit *= 10;
			digit += c[i] - '0';
		}				
	}
	return digit;
}

void digitToHex(char* s)// ������� ����������� ����� � ������ HEX ������� ���������
{
	int a = 0;
	int j = 0;
	int digit = stringToDigit(s);
	while (digit!=0)
	{		
		a = digit % 16;
		if (a > 9)
			s[j] = a + '7';
		else s[j] = a + '0';
		digit = digit / 16;
		j++;
	}
	s[j++] = 'x';
	s[j++] = '0';
	s[j] = '\0';
	revers(s);
}

void len(char* str, int* digit, int* index, int* maxIndex)// ������ ���������� ��� ��������� ������
{
	*index = strlen(str);//���-�� ����	
	int lenOfDigit = 0;
	for (int i = 0; i<*index; i++)
	{
		if (isDigit(*(str + i)))
		{
			if (i == 0 || !isDigit(*(str + i - 1)))
			{
				*digit += 2;
				lenOfDigit = 0;
			}
			lenOfDigit++;
			if (lenOfDigit > *maxIndex)
				*maxIndex = lenOfDigit;
		}
	}
	*maxIndex += 1;
	*digit += 1;
}

void secondArray(char** strD, char* strS, int index)//��������� ������
{
	for (int i = 0, currentWord = 0, currentLetter = 0; i < index; i++)
	{
		if (isDigit(*(strS + i)))
		{
			if (!isDigit(*(strS + i + 1)))
			{				
				strD[currentWord][currentLetter++] = *(strS + i);
				strD[currentWord][currentLetter] = '\0';
				currentWord++;
				currentLetter = 0;
			}
			else
			{
				strD[currentWord][currentLetter++] = *(strS + i);
			}			
		}
		else
		{
			if (isDigit(*(strS + i + 1)))
			{
				strD[currentWord][currentLetter++] = *(strS + i);
				strD[currentWord][currentLetter] = '\0';
				currentWord++;
				currentLetter = 0;
			}
			else
			{
				strD[currentWord][currentLetter++] = *(strS + i);
			}
		}
	}
}

void merger(char** str1, char* str2, int digit, int maxIndex)
{
	int z = 0;
	for (int i = 0; i < digit; i++)
	{
		for (int j = 0; j < maxIndex && str1[i][j] != '\0'; j++)
		{
			*(str2 + z) = str1[i][j];
			z++;
		}
		*(str2 + z) = ' ';
		z++;
	}
	*(str2 + z) = '\0';//��� ��������
}


void work(char* str)
{
	int digit = 0;
	int maxIndex = 0;
	int index = 0;
	len(str, &digit, &index, &maxIndex);
	// �������� ������
	char** arrayDigit = (char**) malloc(sizeof(char*)* digit);
	for (int i = 0; i < digit; i++)
	{
		*(arrayDigit + i) = (char*)malloc(sizeof(char*)*maxIndex);
	}
	//---------------		
	secondArray(arrayDigit, str, index);//������� �� ��������� ������

	if (!isDigit(*(str)))// �������� � 16�� ����������� �����
	{
		for (int i=1; i<digit;i+=2)
			{		
				digitToHex(*(arrayDigit + i));				
			}
	}
	else
	{
		for (int i = 0; i<digit; i += 2)
		{
			digitToHex(*(arrayDigit + i));			
		}
	}
	merger(arrayDigit,str,digit,maxIndex);//������� ��������� ������ � ����������
	
	//����������� ������
	for (int i = 0; i<digit; i++)
	{
		free(*(arrayDigit + i));
	}
	free(arrayDigit);
}

void main()
{
	system("color F0 ");
	char str[26] = "A11d23t111i";
	printf("origin array - %s\n", str);
	work(str);
	printf("work array - %s\n", str);
}