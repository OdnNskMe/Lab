#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

const int height = 20;
const int width = 40;
bool gameOver = false;

enum MoveSnake
{
	LEFT ='a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 's',
	STOP = 0
}go;

struct bodySnake
{
	int snakeX;
	int snakeY;
	struct bodySnake* next;
};

struct fruit
{
	int fruitX;
	int fruitY;
}apple;

void seting()
{
	
}

void move(bodySnake** headSnake)
{	
	if (_kbhit())
	{
		switch (_getch())
		{
		case UP:
			(*headSnake)->snakeX--;
			break;
		case LEFT:
			(*headSnake)->snakeY--;
			break;
		case DOWN:
			(*headSnake)->snakeX++;
			break;
		case RIGHT:
			(*headSnake)->snakeY++;
			break;
		case 'q':
			gameOver = true;
			break;
		}		
	}	
}

void setBodySnake(bodySnake** head, int x, int y)//добавляем тело змейки
{
	struct bodySnake* tempSnake = (struct bodySnake*) malloc(sizeof(bodySnake));
	 tempSnake->snakeX = x;
	 tempSnake->snakeY = y;
	 tempSnake->next = (*head);
	 (*head) = tempSnake;
}

void printSnake(bodySnake** headSnake)
{
	while((*headSnake)->next!=NULL)
	{
		printf("x= %d , y = %d", (*headSnake)->snakeX, (*headSnake)->snakeY);
		(*headSnake) = (*headSnake)->next;
	}
}

void draw(bodySnake** headSnake, int* score)
{	
	system("cls");
	for (int x = 0; x <= height; x++)
	{
		for (int y = 0; y <= width; y++)
		{
			if (x == 0 || x == height || y == 0 || y == width)
			{
				printf("*");
			}
			else if (x == apple.fruitX && y == apple.fruitY)
			{
				printf("$");
				if (apple.fruitX == (*headSnake)->snakeX && apple.fruitY == (*headSnake)->snakeY)//новая позиция для фрукта
				{
					apple.fruitX = rand() % (height - 1);
					apple.fruitY = rand() % (width - 1);					
					//setBodySnake(&(*headSnake), (x-3), (y-3));
					(*score) += 10;
				}
			}			
			else if (x == (*headSnake)->snakeX && y == (*headSnake)->snakeY)
			{				
				printf("+");				
			}
			else if ((*headSnake)->snakeX < 0 || (*headSnake)->snakeY < 0 || (*headSnake)->snakeX > height || (*headSnake)->snakeY > width)
			{
				gameOver = true;
			}
			else
			{	
				while ((*headSnake)->next!=NULL)
				{
					if ((*headSnake)->snakeX == x && (*headSnake)->snakeY == y)
					{
						printf("=");
					}
					(*headSnake) = (*headSnake)->next;
				}
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("Score: %d \n",*score);	
}

void deleteSnake(bodySnake** headSnake) 
{
	bodySnake* prev = NULL;
	while ((*headSnake)->next) 
	{
		prev = *headSnake;
		*headSnake = (*headSnake)->next;
		free(prev);
	}
	free(*headSnake);
}


int main()
{	
	int score = 0;
	struct bodySnake* headSnake = NULL;
	setBodySnake(&headSnake, height / 2, width / 2);
	apple.fruitX = rand() % (height - 1);
	apple.fruitY = rand() % (width - 1);
	while (gameOver != true)
	{
		draw(&headSnake,&score);
		move(&headSnake);
	}
	
	deleteSnake(&headSnake);	
	return 0;
}