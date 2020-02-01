#pragma once
class Draft
{
private:
	int
		m_x1, m_y1, m_x2, m_y2,
		m_tpFigure, m_tpLine, m_tpBrush,
		m_clPen, m_clBrush;
public:
	Draft(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int tpFigure = 0);
	~Draft();
	void Draft::Draw(HDC, int, int, float);
	void Draft::Set(int, int, int, int, int);
};

