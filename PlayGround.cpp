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
	//TODO:draw back line
	InitPlay();
}
PlayGround::~PlayGround()
{
	
}
void PlayGround::InitPlay()
{
	m_iMatBoxArr.fill({ false ,false,false,false ,false,false, false ,false,false, false });
	m_iMatSolidArr.fill({ false ,false,false,false ,false,false, false ,false,false, false });

	//int tmp_row = 0;//row
	//for (auto it = m_iMatBoxArr.begin();it!= m_iMatBoxArr.end();it++)
	//{		
	//	int tmp_col = 0;//column

	//	for (auto ik = it->begin(); ik != it->end(); ik++)
	//	{	
	//		if (*ik == true)
	//		{		
	//			//cout << "-tmp_row-" << tmp_row << "-tmp_col-" << tmp_col << endl;
	//			m_iBoxPointSet.insert({ tmp_row, tmp_col});
	//			Point tmp;
	//			tmp = Point((20 + 5) * tmp_col+ 5, (20 + 5) * tmp_row + 5);
	//			Box* box = new Box(NULL, NULL, this, tmp, 20, 20, RED);

	//			m_iBoxSet.insert(box);
	//			SetMatPlay(box->DisplayEntity());
	//		}
	//		tmp_col++;
	//	}
	//	tmp_row++;
	//}


	Block* block = new Block(NULL, this, Point(0, 30), 105, 135, BLUE);
	m_iBlock= block;
	SetMatPlay(block->DisplayEntity());

}
void PlayGround::UpdateEntity(Point m_newPoint)
{
	SetPoint(m_newPoint);
	Mat tmp_solid(GetHeight(), GetWidth(), CV_8UC3, GetColor());
	m_iMatSolid = tmp_solid;
	SetMatPlay(m_iMatSolid);
	
	//Point tmp_Point;
	//tmp_Point = m_iBlock->LocToPoint();
	//m_iBlock->UpdateEntity(tmp_Point);
	//SetMatPlay(m_iBlock->DisplayEntity());

	m_iBlock->UpdateArr();
	m_iAbsLocArr=m_iBlock->GetBlockArray();
	TypeDetect typedetect = DetectEdge();
	char pointKey = waitKey(1000);

	switch (pointKey)
	{
	case 'a':
		if (typedetect != DETECT_LEFT)
		{
			m_iBlock->MoveBlock(MOVE_LEFT);
		}
		break;
	case 'd':
		if (typedetect != DETECT_RIGHT)
		{
			m_iBlock->MoveBlock(MOVE_RIGHT);
		}
		break;
	case 's':
		if (typedetect != DETECT_BELOW)
		{
			m_iBlock->MoveBlock(MOVE_DOWN);
		}
		break;
	case 'w':
		m_iBlock->RotateBlockCW();
		break;
	default:
		break;
	}

	if (typedetect != DETECT_BELOW)
	{	
		typedetect=DetectCollision();
		m_iBlock->MoveBlock(MOVE_DOWN);
	}

	//draw box
	for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
	{
		//cout << "play " << (*it)[0] << "   " << (*it)[1] << endl;

		m_iMatBoxArr[(*it)[1]][(*it)[0]] = true;
		
		Point tmp;
		tmp = Point((20 + 5) * (*it)[0] + 5, (20 + 5) * (*it)[1] + 5);
		Box* box = new Box(NULL, NULL, this, tmp, 20, 20, RED);
		SetMatPlay(box->DisplayEntity());
	}
	int tmp_row = 0;//row
	for (auto it = m_iMatSolidArr.begin(); it != m_iMatSolidArr.end(); it++)
	{
		int tmp_col = 0;//column

		for (auto ik = it->begin(); ik != it->end(); ik++)
		{
			if (*ik == true)
			{
				Point tmp;
				tmp = Point((20 + 5) * tmp_col + 5, (20 + 5) * tmp_row + 5);
				Box* box = new Box(NULL, NULL, this, tmp, 20, 20, RED);
				SetMatPlay(box->DisplayEntity());
			}
			tmp_col++;
		}
		tmp_row++;
	}
	if (typedetect == DETECT_BELOW || typedetect==DETECT_BLOCK)
	{
		//update m_iMatSolidArr
		for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
		{
			m_iMatSolidArr[(*it)[1]][(*it)[0]] = true;
		}
		m_iMatBoxArr.fill({ false ,false,false,false ,false,false, false ,false,false, false });

		cout << "New block" << endl;
		Block* block = new Block(NULL, this, Point(0, 30), 105, 135, BLUE);
		m_iBlock = block;
		SetMatPlay(block->DisplayEntity());
		typedetect = DETECT_NONE;
	}
	tmp_row = 0;//row
	for (auto it = m_iMatSolidArr.begin(); it != m_iMatSolidArr.end(); it++)
	{
		int tmp_col = 0;//column

		for (auto ik = it->begin(); ik != it->end(); ik++)
		{
			if (*ik == true)
			{
				Point tmp;
				tmp = Point((20 + 5) * tmp_col + 5, (20 + 5) * tmp_row + 5);
				Box* box = new Box(NULL, NULL, this, tmp, 20, 20, RED);
				SetMatPlay(box->DisplayEntity());
			}
			tmp_col++;
		}
		tmp_row++;
	}

	
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
void PlayGround::SetMatPlay(Mat m_pNewMat)
{
	m_iMatPlay = m_pNewMat;

}
Mat PlayGround::GetMatPlay()
{
	return m_iMatPlay;
}

TypeDetect PlayGround::DetectEdge()
{
	for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
	{
		cout << "edge "<<(*it)[0] << "   " << (*it)[1] << endl;

		int tmpx = (*it)[0];
		int tmpy = (*it)[1];

		if (tmpy + 1 > 19)
		{
			cout << "detect below" << endl;
			return DETECT_BELOW;
		}
		if (tmpx + 1 > 9)
		{
			cout << "detect right" << endl;
			return DETECT_RIGHT;
		}
		if (tmpx - 1 < 0)
		{
			cout << "detect left" << endl;
			return DETECT_LEFT;
		}

	}
	return DETECT_NONE;
}


TypeDetect PlayGround::DetectCollision()
{
	list<array<int, 2>> tmp_detect;

	for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
	{
		int tmpx = (*it)[0];
		int tmpy = (*it)[1];
		cout << "colli " << tmpx <<"  "<< tmpy << endl;
		if (m_iMatSolidArr[tmpy + 1][tmpx] == true)
		{
			tmp_detect.push_back({ tmpx ,tmpy + 1 });
		}
		//TODO: x<0,y<0
		if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
		{
			tmp_detect.push_back({ tmpx - 1,tmpy });
		}
		if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
		{
			tmp_detect.push_back({ tmpx + 1,tmpy });
		}
		//if (m_iMatSolidArr[tmpy - 1][tmpx] == true)
		//{
		//	tmp_detect.push_back({ tmpx,tmpy - 1 });
		//}
	}
	set<array<int, 2>> s_detect(tmp_detect.begin(), tmp_detect.end());
	set<array<int, 2>>::iterator iter;

	for (auto ik = m_iAbsLocArr.begin(); ik != m_iAbsLocArr.end(); ik++)
	{
		int tmpx = (*ik)[0];
		int tmpy = (*ik)[1];
		iter = s_detect.find({ tmpx,tmpy });
		if (iter != s_detect.end()) {
			s_detect.erase(iter);
			cout << " find the student!" << endl;
			return DETECT_BLOCK;

		}
		else {
			cout << "Cannot find the student!" << endl;
			return DETECT_NONE;

		}
	}
	//cout << s_detect.size() << endl;
}
