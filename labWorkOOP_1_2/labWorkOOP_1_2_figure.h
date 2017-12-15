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
	bool statusBrush;
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
	void setBrush(bool a)
	{
		statusBrush = a;
	}

	virtual void draw(HDC* hdc) = 0;
};