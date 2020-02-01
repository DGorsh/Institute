#include "stdafx.h"
#include "Draft.h"


Draft::Draft(int x1, int y1, int x2 , int y2, int tpFigure)
{
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
	m_tpFigure = tpFigure;
}


Draft::~Draft()
{
}

void Draft::Draw(HDC hdc, int kx, int ky, float k)
{
	HPEN pen = CreatePen(PS_DASHDOT, 10, RGB(255, 100, 255));
	HBRUSH brush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 255));
	switch (m_tpFigure)
	{
		case 1:
			MoveToEx(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, NULL);
			LineTo(hdc, (m_x2 - kx)*k, (m_y2 - ky)*k);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, ((m_y1 - ky)*k + (m_y2 - ky)*k) / 2, "Line", 5);
			break;
		case 2:
			Rectangle(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, (m_y1 - ky)*k - 20, "Rectangle", 10);
			break;
		case 3:
			Ellipse(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, (m_y1 - ky)*k - 20, "Ellipse", 10);
			break;
		case 4:
			RoundRect(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k, 10, 10);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, (m_y1 - ky)*k - 20, "RoundRect", 10);
			break;
		case 5:
			Arc(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, (m_y1 - ky)*k - 20, "Arc", 4);
			break;
		case 6:
			Chord(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, (m_y1 - ky)*k - 20, "Chord", 5);
			break;
		case 7:
			Pie(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k);
			TextOut(hdc, ((m_x1 - kx)*k + (m_x2 - kx)*k) / 2, (m_y1 - ky)*k - 20, "Pie", 4);
			break;
	}
	m_x1 = (m_x1 - kx);
	m_y1 = (m_y1 - ky);
	m_x2 = (m_x2 - kx);
	m_y2 = (m_y2 - ky);
}

void Draft::Set(int x1, int y1, int x2, int y2, int tpFigure)
{
	m_x1 = x1;
	m_x2 = x2;
	m_y1 = y1;
	m_y2 = y2;
	m_tpFigure = tpFigure;
}
