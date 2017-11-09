//#include <stdio.h>
//#include <conio.h>
//#include <locale.h>
//#include <stdlib.h>
//#include <string.h>
#include <iostream>

typedef struct Node//односвязн списка
{
	int value;
	struct Node* next;
};

void push(Node** head, int data)
{
	Node* temp = (Node*) malloc(sizeof(Node));//выделяем память
	temp->value = data;//значение
	temp->next = (*head);//адрес head
	(*head) = temp;//head передаем указатель на новый элемент списка 
}

int del(Node** head)//удаляет элемент, на который указывает head и возвращает значение элемента
{
	Node* Temp = NULL;
	int valTemp;
	if (head == NULL)
	{
		return -1;
	}
	Temp = (*head);
	valTemp = Temp->value;
	(*head) = (*head)->next;
	free(Temp);
	return valTemp;
}

void insert(Node* head, int val, unsigned n)//вставка в указанную позицию списка
{
	unsigned i = 0;
	Node* temp = NULL;
	while (i<n && head->next)
	{
		head = head->next;
		i++;
	}
	temp = (Node*)malloc(sizeof(Node));
	temp->value = val;
	if (head->next)
	{
		temp->next = head->next;
	}
	else
	{
		temp->next = NULL;
	}
	head->next = temp;
}

Node* getNIndex(Node* head, unsigned n)
{
	return head;
}

void main()
{
	struct Node* numb = NULL;
	printf("input numb\n");
	push(&numb, 1);
	
	del(&numb);
}