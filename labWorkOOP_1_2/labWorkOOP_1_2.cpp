//#include <Windows.h>
//#include <windowsx.h>
//#include <stdio.h>
//#include <conio.h>
//#include <iostream>

#include "labWorkOOP_1_2.h"

void main()
{
	enum choise
	{
		f_Ellipse = 'e',
		f_circle = 'c',
		clear = 'z',
		quit ='q'
	};

	bool gameOver = false;

	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;	

	ellipse ob_ellipse;
	ellipse* ell = &ob_ellipse;

	circle ob_circle;
	circle* cir = &ob_circle;
	
	
	SetBkColor(hdc, RGB(0, 0, 0));

	
	do
	{
		GetClientRect(hwnd, &rt);
		if (_kbhit()) 
		{
			switch (_getch())
			{
				case f_Ellipse:
				{
					ell->setStart(40, 40);
					ell->setEllipse(100, 200);
					ell->setColorPen(255, 0, 0);
					ell->draw(&hdc);
					break;
				}
				
				case f_circle:
				{
					cir->setStart(200, 200);
					cir->setCirle(50);
					cir->setColorPen(0, 255, 0);
					cir->draw(&hdc);
					break;
				}
				case quit:
				{
					gameOver = true;
					break;
				}
			}
		}
	} while (gameOver!=true);
	
	ReleaseDC(hwnd, hdc);
}
