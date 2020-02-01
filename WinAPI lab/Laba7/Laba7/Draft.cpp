#include "stdafx.h"
#include "Draft.h"


Draft::Draft(int x1, int y1, int x2 , int y2, int tpFigure)
{
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
	m_tpFigure = tpFigure;
	/*m_tpLine = tpLine;
	m_tpBrush = tpBrush;
	m_clPen = clPen;
	m_clBrush = clBrush;*/
}


Draft::~Draft()
{
}

void Draft::Draw(HDC hdc, int kx, int ky, float k)
{
	HPEN pen = CreatePen(PS_DASHDOT, 10, RGB(255, 100, 255));
	HBRUSH brush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 255));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	switch (m_tpFigure)
	{
		case 1:
			MoveToEx(hdc, m_x1, m_y1, NULL);
			LineTo(hdc, m_x2, m_y2);
			break;
		case 2:
			Rectangle(hdc, (m_x1 - kx)*k, (m_y1 - ky)*k, (m_x2 - kx)*k, (m_y2 - ky)*k);
			break;
		case 3:
			Ellipse(hdc, m_x1, m_y1, m_x2, m_y2);
			break;
	}
	m_x1 = (m_x1 - kx);
	m_y1 = (m_y1 - ky);
	m_x2 = (m_x2 - kx);
	m_y2 = (m_y2 - ky);
	DeleteObject(pen);
	DeleteObject(brush);
}
