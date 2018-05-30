#include "Box.h"
#include "TypeColor.h"
Box::Box(Point m_pBoxPoint):
	m_iWidth(20),
	m_iHeight(20)
{	
	m_iBoxPoint = m_pBoxPoint;

	m_iColor = SetColor(GREEN);
	Mat tmp_box(m_iWidth, m_iHeight, CV_8UC3, m_iColor);
	m_iBox = tmp_box;
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
	Mat tmp_BackGround = m_pPlayGround(Rect(m_iBoxPoint.x, m_iBoxPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iBox, 1, 0, tmp_BackGround);
	return m_pPlayGround;
}
Mat Box::HideBox(Mat m_pPlayGround)
{
	Mat tmp_BackGround = m_pPlayGround(Rect(m_iBoxPoint.x, m_iBoxPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iBox, 0, 0, tmp_BackGround);
	return m_pPlayGround;
}
Point Box::GetBoxPoint()
{
	return m_iBoxPoint;
}

