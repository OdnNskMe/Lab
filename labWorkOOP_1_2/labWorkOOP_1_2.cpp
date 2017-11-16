#include <Windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

struct point
{
	int x;
	int y;
};
struct RGB
{
	int r;
	int g;
	int b;
};

class figure
{
protected:
	struct point point1;
	struct point point2;
	struct RGB colorPen;
	struct RGB colorBrush;
public:
	void setX1y1(int a, int b)
	{
		point1.x = a;
		point1.y = b;
	}
	void setX2y2(int a, int b)
	{
		point2.x = a;
		point2.y = b;
	}
	void setColorPen(int a, int b, int c)
	{
		colorPen.r = a;
		colorPen.g = b;
		colorPen.b = c;
	}
	void setColorBrush(int a, int b, int c)
	{
		colorBrush.r = a;
		colorBrush.g = b;
		colorBrush.b = c;
	}
	virtual void draw(HWND* hwnd) = 0;
};


class ellipse: public figure
{
public:	
	void draw(HWND* hwnd)
	{	
		POINT pt;
		HDC hdc = GetDC(*hwnd);
		Ellipse(hdc, point1.x, point1.y, point2.x, point2.y);		
	}	
};

void main()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;
	char buf[2];
	ellipse ob_ellipse;
	ellipse* ell = &ob_ellipse;
		
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 0, 0));
	HPEN hRedPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	HPEN hOldPen = SelectPen(hdc, hRedPen);	
	HBRUSH hGreenBrush = CreateSolidBrush(RGB(0,255,0));
	HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);
	do
	{
		GetClientRect(hwnd, &rt);
		std::cout << "Window " << rt.right <<" x " << rt.bottom;
		TextOutA(hdc, 10, 20, buf, strlen(buf));
		ell->setX1y1(40, 40);
		ell->setX2y2(100, 100);
		ell->draw(&hwnd);		

	} while (_getch() != 27);
	SelectPen(hdc, hOldPen);
	SelectBrush(hdc, hOldBrush);
	DeletePen(hRedPen);
	DeleteBrush(hGreenBrush);
	ReleaseDC(hwnd, hdc);
}
