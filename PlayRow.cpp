#include "PlayRow.h"
#include<vector>
#include<list>
#include<string>
#include<iostream>
using namespace std;
class Box;

PlayRow::PlayRow(Point m_pPlayRowPoint, int m_pID) :
	m_iWidth(20 * 10 + (10 + 1) * 5),
	m_iHeight(20 * 1 + (1 + 1) * 5)
{
	m_iID = m_pID;
	m_iPlayRowPoint = m_pPlayRowPoint;
	m_iColor = SetColor(GREY);

	Mat tmp_playrow(m_iHeight, m_iWidth, CV_8UC3, m_iColor);
	for (size_t i=0;i<m_iRowStatus.size();i++)
	{
		Point tmp;
		tmp = Point((20+5)*i+5, 5);
		Box* rt = new Box(tmp);
		boxlist.push_back(rt);
		m_iRowStatus[i]=true;
		rt->DisplayBox(tmp_playrow);
	}
	m_iPlayRow= tmp_playrow;

}
PlayRow::~PlayRow()
{

}
void PlayRow::UpdatePlayRow(array<bool,10> m_pRowStatus)
{
	auto ik=boxlist.begin();
	for (int i=0;i<10;i++)
	{
		m_iRowStatus[i] = m_pRowStatus[i];
		if (m_iRowStatus[i])
		{
			
			(*ik)->DisplayBox(m_iPlayRow);
		}
		else
		{
			(*ik)->HideBox(m_iPlayRow);

		}
		ik++;
	}
}
Mat PlayRow::DisplayPlayRow(Mat m_pBackGround)
{
	Mat tmp_BackGround = m_pBackGround(Rect(m_iPlayRowPoint.x, m_iPlayRowPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iPlayRow, 1, 0, tmp_BackGround);
	return m_pBackGround;

}
Mat PlayRow::HidePlayRow(Mat m_pBackGround)
{
	Mat tmp_BackGround = m_pBackGround(Rect(m_iPlayRowPoint.x, m_iPlayRowPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iPlayRow, 0, 0, tmp_BackGround);
	return m_pBackGround;
}
