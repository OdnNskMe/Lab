#include "labWorkOOP_1_2_geometry.h"

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

	ellipse ob_ellipse;
	circle ob_circle;	
		
	do
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		RECT rt;
		GetClientRect(hwnd, &rt);
		SetBkColor(hdc, RGB(0, 0, 0));
		if (_kbhit()) 
		{
			switch (_getch())
			{
				case f_Ellipse:
				{					
					ob_ellipse.setStart(40, 40);
					ob_ellipse.setEllipse(100, 200);
					ob_ellipse.setColorPen(255, 0, 0);
					ob_ellipse.setBrush(true);
					ob_ellipse.setColorBrush(0, 200, 200);
					ob_ellipse.draw(&hdc);
					break;
				}
				
				case f_circle:
				{
					ob_circle.setStart(200, 200);
					ob_circle.setCirle(50);
					ob_circle.setColorPen(0, 255, 0);
					ob_circle.setBrush(false);
					ob_circle.setColorBrush(0, 200, 200);
					ob_circle.draw(&hdc);
					break;
				}
				case clear:
				{
					system("cls");					
					break;
				}
				case quit:
				{
					gameOver = true;					
					break;
				}
			}
		}
		ReleaseDC(hwnd, hdc);
	} while (gameOver!=true);
	
}
