#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

struct Point_Pt
{
	int x;
	int y;
};

struct RGB_Color
{
	int r;
	int g;
	int b;
};

class figure
{
protected:
	struct Point_Pt pointStart;
	
	struct RGB_Color colorPen;
	struct RGB_Color colorBrush;
public:
	void setStart(int a, int b)
	{
		pointStart.x = a;
		pointStart.y = b;
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
		
	virtual void draw(HDC* hdc) = 0;
};


class ellipse : public figure
{
	int heigth;
	int width;
public:
	void setEllipse(int a, int b)
	{
		heigth = a;
		width = b;
	}
	
	void draw(HDC* hdc)
	{	
		SetBkColor(*hdc, RGB(0, 0, 0));		
		HPEN hColorPen = CreatePen(PS_SOLID, 5, RGB(colorPen.r, colorPen.g, colorPen.b));
		HPEN hOldPen = SelectPen(*hdc, hColorPen);
		Ellipse(*hdc, pointStart.x, pointStart.y, pointStart.x + heigth, pointStart.y + width);
		DeletePen(hColorPen);		
	}
};

class circle : public figure
{
	int radius;
	int diameter;
public:	
	void setCirle(int a)
	{
		radius = a;
		diameter = radius * 2;
	}
	void draw(HDC* hdc)
	{		
		SetBkColor(*hdc, RGB(0, 0, 0));
		HPEN hColorPen = CreatePen(PS_SOLID, 5, RGB(colorPen.r, colorPen.g, colorPen.b));
		HPEN hOldPen = SelectPen(*hdc, hColorPen);
		Ellipse(*hdc, pointStart.x, pointStart.y, pointStart.x + diameter, pointStart.y + diameter);
		DeletePen(hColorPen);
	}	
};