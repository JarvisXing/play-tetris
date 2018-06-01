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
	TypeName tmpname = TypeName(rand() % 7);
	TypeDir tmpdir = TypeDir(rand() % 4);
	Block* block = new Block(NULL, this, Point(0, 0), 105, 105, GREY,tmpname, tmpdir);

	m_iBlock= block;
	SetMatPlay(block->DisplayEntity());
	m_iNewBlock = false;

}
void PlayGround::UpdateEntity(Point m_newPoint)
{
	SetPoint(m_newPoint);
	Mat tmp_solid(GetHeight(), GetWidth(), CV_8UC3, GetColor());
	m_iMatSolid = tmp_solid;
	SetMatPlay(m_iMatSolid);
	
	m_iBlock->UpdateArr();
	m_iAbsLocArr = m_iBlock->GetBlockArray();
	TypeDetect detectedge = DetectEdge();
	TypeDetect detectblock=DetectCollision();

	char pointKey = waitKey(500);
	cout <<"key.........................."<< pointKey << endl;
	switch (pointKey)
	{
	case 'a':
	{
		if ((detectedge == DETECT_LEFT)||detectblock == DETECT_NOLEFT || detectblock == DETECT_NOSIDE)
		{
			break;
		}
		else
		{			
			m_iBlock->MoveBlock(MOVE_LEFT);
			break;
		}
	}
	case 'd':
	{
		if (detectedge == DETECT_RIGHT || detectblock == DETECT_NORIGHT || detectblock == DETECT_NOSIDE)
		{
			break;
		}
		else
		{		
			m_iBlock->MoveBlock(MOVE_RIGHT);
			break;
		}
	}
	case 's':
	{
		if (detectedge == DETECT_BELOW ||  detectblock == DETECT_NOBELOW)
		{
			break;
		}
		else
		{				
			m_iBlock->MoveBlock(MOVE_DOWN);
			break;
		}
	}

	case 'w'://TODO:rotate problem
		m_iBlock->RotateBlockCW();
		break;
	}

	if (detectedge == DETECT_BELOW || detectblock ==DETECT_NOBELOW)
	{
		//update m_iMatSolidArr
		for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
		{

				m_iMatSolidArr[(*it)[1]][(*it)[0]] = true;

		}

		m_iMatBoxArr.fill({ false ,false,false,false ,false,false, false ,false,false, false });

		cout << "New block" << endl;
		Block* block = new Block(NULL, this, Point(0, 30), 105, 105, GREY, 
			this->GetWindow()->GetBlock()->GetTypeName(), this->GetWindow()->GetBlock()->GetDir());
		m_iBlock = block;
		SetMatPlay(block->DisplayEntity());
		m_iNewBlock = true;
		detectedge = DETECT_NONE;

	}	
	else
	{
		m_iNewBlock = false;

		m_iBlock->MoveBlock(MOVE_DOWN);
		//draw box
		for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
		{
			//cout << "play " << (*it)[0] << "   " << (*it)[1] << endl;
			//if ((*it)[0] < 0 || (*it)[0] > 9|| (*it)[1] >19)
			m_iMatBoxArr[(*it)[1]][(*it)[0]] = true;

			Point tmp;
			tmp = Point((20 + 5) * (*it)[0] + 5, (20 + 5) * (*it)[1] + 5);
			Box* box = new Box(NULL, NULL, this, tmp, 20, 20, WHITE);
			SetMatPlay(box->DisplayEntity());
					
		}

	}
	
	DrawSolid();
	//
	ClearRow();
	DrawSolid();

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
	array<bool, 3> tmp_detectarr = { false,false,false };

	for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
	{
		//cout << "edge "<<(*it)[0] << "   " << (*it)[1] << endl;

		int tmpx = (*it)[0];
		int tmpy = (*it)[1];

		if (tmpx - 1 < 0)
		{
			tmp_detectarr[0] = true;
		}
		if (tmpx + 1 > 9)
		{
			tmp_detectarr[1] = true;
		}
		if (tmpy + 1 > 19)
		{
			tmp_detectarr[2] = true;
		}
	}
	if (tmp_detectarr.at(2) == true)
	{
		cout << "detect below edge" << endl;
		return DETECT_BELOW;
	}
	else if (tmp_detectarr.at(0) == true)
	{
		cout << "detect left edge" << endl;
		return DETECT_LEFT;
	}
	else if (tmp_detectarr.at(1) == true )
	{
		cout << "detect right edge" << endl;
		return DETECT_RIGHT;
	}
	else
	{
		cout << "detect none edge" << endl;
		return DETECT_NONE;
	}
}


TypeDetect PlayGround::DetectCollision()
{
	array<bool, 3> tmp_detectarr = {false,false,false};//left right below

	for (auto it = m_iAbsLocArr.begin(); it != m_iAbsLocArr.end(); it++)
	{
		int tmpx = (*it)[0];
		int tmpy = (*it)[1];
		cout << "colli " << tmpx << "  " << tmpy << endl;

		//if ((*it)[0] < 0 || (*it)[0] > 9|| (*it)[1] >19)
		if (tmpx == 0 && tmpy == 19)		//below ->
		{
			if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
			{
				tmp_detectarr[1] = true;
			}

		}
		else if (tmpx == 9 && tmpy == 19)//below <-
		{
			if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
			{
				tmp_detectarr[0] = true;
			}
			
		}
		else if (tmpx == 0 && tmpy < 19)//сроб
		{
			if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
			{
				tmp_detectarr[1] = true;
			}
			if (m_iMatSolidArr[tmpy + 1][tmpx] == true)
			{
				tmp_detectarr[2] = true;
			}

		}
		else if (tmpx == 9 && tmpy < 19)//zuoxia
		{
			if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
			{
				tmp_detectarr[0] = true;
			}
			if (m_iMatSolidArr[tmpy + 1][tmpx] == true)
			{
				tmp_detectarr[2] = true;
			}

		}
		else if (tmpx > 0 && tmpy == 19)
		{
			if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
			{
				tmp_detectarr[0] = true;
			}
			if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
			{
				tmp_detectarr[1] = true;
			}
		}
		else if (tmpx < 9 && tmpy == 19)
		{
			if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
			{
				tmp_detectarr[0] = true;
			}
			if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
			{
				tmp_detectarr[1] = true;
			}
		}
		else if(tmpx < 0 && tmpy < 19) //ср
		{

			if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
			{
				tmp_detectarr[1] = true;
			}
		}
		else if (tmpx > 9 && tmpy < 19)			// zuo
		{
			if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
			{
				tmp_detectarr[0] = true;
			}
			
		}
		else if (tmpx < 0 && tmpy > 19)	//left corner none
		{ 
		}
		else if (tmpx > 9 && tmpy > 19)	//right corner none
		{

		}
		else		//mid
		{
			
			if (m_iMatSolidArr[tmpy][tmpx - 1] == true)
			{
				tmp_detectarr[0] = true;
			}
			if (m_iMatSolidArr[tmpy][tmpx + 1] == true)
			{
				tmp_detectarr[1] = true;
			}
			if (m_iMatSolidArr[tmpy + 1][tmpx] == true)
			{
				tmp_detectarr[2] = true;
			}

		}
		cout << "array " << tmp_detectarr[0] << "---" << tmp_detectarr[1] << "---" << tmp_detectarr[2] << endl;

	}

	if (tmp_detectarr.at(2)==true)
	{
		cout << "detect below block" << endl;
		return DETECT_NOBELOW;
	}
	else if (tmp_detectarr.at(0) == true && tmp_detectarr.at(1) == false)
	{
		cout << "detect left block" << endl;
		return DETECT_NOLEFT;
	}
	else if (tmp_detectarr.at(0) == false && tmp_detectarr.at(1) == true)
	{
		cout << "detect right block" << endl;
		return DETECT_NORIGHT;
	}
	else if (tmp_detectarr.at(0) == true && tmp_detectarr.at(1) == true)
	{
		cout << "detect side block" << endl;
		return DETECT_NOSIDE;
	}
	else
	{
		cout << "detect none block" << endl;
		return DETECT_NONE;
	}
}

void PlayGround::DrawSolid()
{
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
				Box* box = new Box(NULL, NULL, this, tmp, 20, 20, WHITE);
				SetMatPlay(box->DisplayEntity());
			}
			tmp_col++;
		}
		tmp_row++;
	}
}

void PlayGround::ClearRow()
{
	int tmp_row = 0;
	int tmp_num = 0;
	set<int> full_set;
	set<int>::iterator iter;

	for (auto it = m_iMatSolidArr.begin(); it != m_iMatSolidArr.end(); it++)
	{	
		int tmp_sum = 0;
		for (auto ik = it->begin(); ik != it->end(); ik++)
		{
			tmp_sum = tmp_sum + (*ik);
		}	
		if (tmp_sum == 10)
		{	
			cout<<"Sum ......"<< tmp_row <<endl;
			full_set.insert(tmp_row);
		}
		tmp_row++;	
	}
	tmp_num = 0;
	
	if (full_set.size() > 0)
	{
		for (auto it = full_set.rbegin(); it != full_set.rend(); it++)
		{
			cout << "*it ------" << (*it) << endl;
			
			for (int i = (*it); i > 0; i--)
			{
				cout << "i------" << i << endl;
				if (i == 0)
				{
					m_iMatSolidArr[i].fill(false);
				}
				else
				{
					m_iMatSolidArr[i] = m_iMatSolidArr[i-1];
				}
			}
			
		}
		m_iMatSolidArr;

	}
	else
	{

	}
	
	

}
bool PlayGround::GetBlockState()
{
	return m_iNewBlock;
}