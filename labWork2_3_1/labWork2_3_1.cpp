///*����������� ��� �������, ���� �� ������� ������ � ���������� ����� ������ � ������������
//������������������ � ��������� � ������ � �������� �������. ������ ������� ������  ���  ������  
//� ������� �� �����. ��������� ����������� � ��������� � ������ ��������� ������� ������ ��� ������ 
//������ �������, � ����� ������ �� � ������� �� ����� ��� ������ ������. ���������� ������ ����������� � 
//���������� ������� ������ �  ���������  ��� ������������.
//������:5. ����������� ������, ���������� ���������� ������������� ����� �����. 
//��� ������� ������, ����� ����, ���������� � ������������������ � �������� ����. 
//������������������ ���� ������������� � ����� ����������, ������� ������������ � ����������� ������, ������������ �������� \0. 
//����� ������ - ��� ������ ������ ������� \0. ������:
//-�������� ������: "aa2456bbbb6665"
//- ����������� ������ : 'a' 'a' '\0' 2456 'b' 'b' 'b' 'b' '\0' 6665 '\0' '\0'


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <iostream>


void inputStr(char * str, int n)
{
	printf("������� ������\n");
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