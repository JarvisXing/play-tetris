#include"PlayGround.h"
class Box;
class Block;
PlayGround::PlayGround(TetrisWindow* window,
	Point m_pPoint, uint16_t m_pWidth, uint16_t m_pHeight, TypeColor m_pColor) :
	BaseEntity(m_pPoint, m_pWidth, m_pHeight, m_pColor),
	m_iWindow(window),m_iDetect(DETECT_NONE)
{
	Mat tmp_play(GetHeight(), GetWidth(), CV_8UC3, SetColor(m_pColor));
	m_iMatPlay = tmp_play;
	m_iMatBoxArr.fill({ true ,true,true,true ,true,true, true ,true,true, true});
	InitPlay();
}
PlayGround::~PlayGround()
{
	
}
void PlayGround::InitPlay()
{
	int tmp_row = 0;//row
	
	for (auto it = m_iMatBoxArr.begin();it!= m_iMatBoxArr.end();it++)
	{		
		int tmp_col = 0;//column

		for (auto ik = it->begin(); ik != it->end(); ik++)
		{	

			if (*ik == true)
			{		
				//cout << "-tmp_row-" << tmp_row << "-tmp_col-" << tmp_col << endl;

				m_iBoxPointSet.insert({ tmp_row, tmp_col});
				Point tmp;
				tmp = Point((20 + 5) * tmp_col+ 5, (20 + 5) * tmp_row + 5);
				Box* box = new Box(NULL, NULL, this, tmp, 20, 20, RED);

				m_iBoxSet.insert(box);
				SetMatPlay(box->DisplayEntity());
			}
			tmp_col++;
		}
		tmp_row++;
		
	}
	
}
void PlayGround::UpdateEntity(Point m_newPoint)
{
	SetPoint(m_newPoint);

}
Mat PlayGround::DisplayEntity()
{
	Mat m_pBackGround = m_iWindow->GetMatWindow();
	Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
	addWeighted(tmp_BackGround, 0, m_iMatPlay, 1, 0, tmp_BackGround);
	return m_pBackGround;
}
Mat PlayGround::HideEntity()
{
	Mat m_pBackGround = m_iWindow->GetMatWindow();
	Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
	addWeighted(tmp_BackGround, 0, m_iMatPlay, 0, 0, tmp_BackGround);
	return m_pBackGround;
}

Mat PlayGround::GetMatPlay()
{
	return m_iMatPlay;
}
void PlayGround::SetMatPlay(Mat m_pNewMat)
{
	m_iMatPlay = m_pNewMat;

}
void PlayGround::DetectCollision(Block m_pBlock)
{

}
/*
void PlayGround::UpdatePlayGround(Block m_pBlock)
{
	note£º deal with edge display
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

}
*/