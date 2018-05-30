#include"PlayGround.h"
#include<vector>
#include<list>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
class PlayRow;

PlayGround::PlayGround(Point m_pPlayGroundPoint) :
	m_iWidth(20 * 10 + (10 + 1) * 5),
	m_iHeight(20 * 20 + (20 + 1) * 5)
{
	m_iPlayGroundPoint = m_pPlayGroundPoint;

	m_iColor = SetColor(GREY);
	Mat tmp_playground(m_iHeight, m_iWidth, CV_8UC3, m_iColor);
	for (size_t i = 0; i<m_iGroundStatus.size(); i++)
	{
		Point tmp;
		tmp = Point(0, int((20+5)*i+0));
		PlayRow* rt = new PlayRow(tmp,int(i));
		rowlist.push_back(rt);
		m_iGroundStatus[i].fill(false);
		rt->UpdatePlayRow(m_iGroundStatus[i]);
		rt->DisplayPlayRow(tmp_playground);
	}
	m_iPlayGround = tmp_playground;
}
PlayGround::~PlayGround()
{

}
void PlayGround::UpdatePlayGround(Block m_pBlock)
{
	/*note£º deal with edge display*/
	m_pBlock.GetBlockArray();
	for (auto it = m_pBlock.m_iBoxArr.begin(); it != m_pBlock.m_iBoxArr.end(); it++)
	{
		cout << "tmp " << (*it)[1] << "  " << (*it)[0] << endl;

		int tmpy = m_pBlock.m_iLocation.y + (*it)[1];
		int tmpx = m_pBlock.m_iLocation.x + (*it)[0];
		cout << "tmpyx " << tmpy << "  " << tmpx << endl;
		m_iGroundStatus[tmpy][tmpx] = true;
	}

	auto ik = rowlist.begin();
	for (size_t i = 0; i < m_iGroundStatus.size(); i++)
	{
		(*ik)->UpdatePlayRow(m_iGroundStatus[i]);
		(*ik)->DisplayPlayRow(m_iPlayGround);
		ik++;
	}
}

Mat PlayGround::DisplayPalyGround(Mat m_pBackGround)
{	
	Mat tmp_BackGround = m_pBackGround(Rect(m_iPlayGroundPoint.x, m_iPlayGroundPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iPlayGround, 1, 0, tmp_BackGround);
	return m_pBackGround;
}
TypeDetect PlayGround::DetectCollision(Block m_pBlock)
{
	//edge detect
	for (auto it = m_pBlock.m_iBoxArr.begin(); it != m_pBlock.m_iBoxArr.end(); it++)
	{
		int tmpy = m_pBlock.m_iLocation.y + (*it)[1];
		int tmpx = m_pBlock.m_iLocation.x + (*it)[0];

		if (tmpy + 1 > 14)
		{
			cout << "detect below" << endl;
			return DETECT_BELOW;
		}
		if (tmpx + 1 > 7)
		{
			cout << "detect right" << endl;
			return DETECT_RIGHT;
		}
		if (tmpx - 1 < 1)
		{
			cout << "detect left" << endl;
			return DETECT_LEFT;
		}

	}

	//block detect
	list<array<int, 2>> tmp_detect;

	for (auto it = m_pBlock.m_iBoxArr.begin(); it != m_pBlock.m_iBoxArr.end(); it++)
	{
		int tmpy = m_pBlock.m_iLocation.y + (*it)[1];
		int tmpx = m_pBlock.m_iLocation.x + (*it)[0];

		if (m_iGroundStatus[tmpy + 1][tmpx] == true)
		{
			tmp_detect.push_back({ tmpx ,tmpy + 1 });
		}
		if (m_iGroundStatus[tmpy][tmpx - 1] == true)
		{
			tmp_detect.push_back({ tmpx - 1,tmpy });
		}
		if (m_iGroundStatus[tmpy][tmpx + 1] == true)
		{
			tmp_detect.push_back({ tmpx + 1,tmpy });
		}
		if (m_iGroundStatus[tmpy - 1][tmpx] == true)
		{
			tmp_detect.push_back({ tmpx,tmpy - 1 });
		}
	}
	set<array<int, 2>> s_detect(tmp_detect.begin(), tmp_detect.end());
	set<array<int, 2>>::iterator iter;

	for (auto ik = m_pBlock.m_iBoxArr.begin(); ik != m_pBlock.m_iBoxArr.end(); ik++)
	{
		int tmpy = m_pBlock.m_iLocation.y + (*ik)[1];
		int tmpx = m_pBlock.m_iLocation.x + (*ik)[0];
		iter = s_detect.find({ tmpx,tmpy });
		if (iter != s_detect.end()) {
			s_detect.erase(iter);
			cout << " find the student!" << endl;
		}
		else {
			cout << "Cannot find the student!" << endl;
		}
	}
	cout << s_detect.size() << endl;
	return DETECT_NONE;
	/*
	for (auto it = s_detect.begin(); it != s_detect.end(); it++)
	{
	if((*it)[1]>16)

	}*/
}
