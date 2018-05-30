#include "Box.h"
Box::Box(TetrisWindow* window,Point point, uint16_t width, uint16_t height, Scalar color)
{	
	//Mat tmp_box(m_iWidth, m_iHeight, CV_8UC3, m_iColor);
	//m_iBox = tmp_box;
}

Box::~Box()
{
	
}
Mat Box::GetBox()
{
	return m_iBox;
}

Mat Box::DisplayBox(Mat m_pPlayGround)
{
	Mat tmp_BackGround = m_pPlayGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
	addWeighted(tmp_BackGround, 0, m_iBox, 1, 0, tmp_BackGround);
	return m_pPlayGround;
}
Mat Box::HideBox(Mat m_pPlayGround)
{
	Mat tmp_BackGround = m_pPlayGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
	addWeighted(tmp_BackGround, 0, m_iBox, 0, 0, tmp_BackGround);
	return m_pPlayGround;
}


