#pragma once
#include "labWorkOOP_1_2_figure.h"

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

		if (statusBrush == true)
		{
			HBRUSH hColorBrush = CreateSolidBrush(RGB(colorBrush.r, colorBrush.g, colorBrush.b));
			HBRUSH hOldBrush = SelectBrush(*hdc, hColorBrush);
			Ellipse(*hdc, pointStart.x, pointStart.y, pointStart.x + heigth, pointStart.y + width);
			FloodFill(*hdc, pointStart.x + (heigth / 2), pointStart.y + (width / 2), RGB(colorBrush.r, colorBrush.g, colorBrush.b));
			DeleteBrush(hColorBrush);
		}		
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
		
		if (statusBrush == true)
		{
			HBRUSH hColorBrush = CreateSolidBrush(RGB(colorBrush.r, colorBrush.g, colorBrush.b));
			HBRUSH hOldBrush = SelectBrush(*hdc, hColorBrush);
			Ellipse(*hdc, pointStart.x, pointStart.y, pointStart.x + diameter, pointStart.y + diameter);
			FloodFill(*hdc, pointStart.x + radius, pointStart.y + radius, RGB(colorPen.r, colorPen.g, colorPen.b));
			DeleteBrush(hColorBrush);
		}		
		DeletePen(hColorPen);		
	}
};