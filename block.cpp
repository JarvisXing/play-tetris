#include"block.h"

#include<vector>
#include<list>
#include<string>
#include<iostream>
using namespace std;
class Box;

Block::Block(Point m_pBlockPoint) :
	m_iWidth(20 * 4 + (4 + 1) * 5),
	m_iHeight(20 * 4 + (4 + 1) * 5)
{	
	m_iLocation.x = 3;
	m_iLocation.y = 0;

	m_iBoxArr.fill({ 0,0 });

	m_iBlockPoint=m_pBlockPoint;

	m_iColor = SetColor(WHITE);
	
	m_iTypeName = rand() % 7;
	m_iDirection = rand() % 4;
	cout <<"block type "<< m_iTypeName<<"  " << m_iDirection << endl;
	m_iBoxPos = ComputePos();
	m_iBoxPointList = GetPointList();

	Mat tmp_block(m_iHeight,m_iWidth, CV_8UC3, m_iColor);

	for (auto ik = m_iBoxPointList.begin(); ik != m_iBoxPointList.end(); ik++)
	{
		Point tmp;
		tmp = Point(ik->x, ik->y);
		Box* rt = new Box(tmp);
		boxlist.push_back(rt);
		rt->DisplayBox(tmp_block);
	}
	m_iBlock = tmp_block;

}
Block::~Block()
{
 
}
//D3->D2->D1->D0
void Block::RotateBlockCW()
{
	switch (m_iDirection)
	{
	case D0:
		m_iDirection = D3;
		break;
	case D1:
		m_iDirection = D0;
		break;
	case D2:
		m_iDirection = D1;
		break;
	case D3:
		m_iDirection = D2;
		break;
	default:
		break;
	}
	m_iBoxPos = ComputePos();
	m_iBoxPointList = GetPointList();
}
//D0->D1->D2->D3
void Block::RotateBlockCCW()
{
	switch (m_iDirection)
	{
	case D0:
		m_iDirection = D1;
		break;
	case D1:
		m_iDirection = D2;
		break;
	case D2:
		m_iDirection = D3;
		break;
	case D3:
		m_iDirection = D0;
		break;
	default:
		break;
	}
	m_iBoxPos = ComputePos();
	m_iBoxPointList = GetPointList();
}
void Block::UpdateBlock(int x,int y)
{

}
inline int Block::ComputePos()
{
	int tmp_BoxPos=0;
	switch (m_iTypeName)
	{
	case I_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0F00;
			break;
		case D1:
			tmp_BoxPos = 0x2222;
			break;
		case D2:
			tmp_BoxPos = 0x0F00;
			break;
		case D3:
			tmp_BoxPos = 0x4444;
			break;
		default:
			break;
		}
		break;
	case T_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0270;
			break;
		case D1:
			tmp_BoxPos = 0x0262;
			break;
		case D2:
			tmp_BoxPos = 0x0720;
			break;
		case D3:
			tmp_BoxPos = 0x0232;
			break;
		default:
			break;
		}
		break;
	case L_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0170;
			break;
		case D1:
			tmp_BoxPos = 0x0622;
			break;
		case D2:
			tmp_BoxPos = 0x0740;
			break;
		case D3:
			tmp_BoxPos = 0x0223;
			break;
		default:
			break;
		}
		break;
	case J_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0470;
			break;
		case D1:
			tmp_BoxPos = 0x0226;
			break;
		case D2:
			tmp_BoxPos = 0x0710;
			break;
		case D3:
			tmp_BoxPos = 0x0322;
			break;
		default:
			break;
		}
		break;
	case S_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0360;
			break;
		case D1:
			tmp_BoxPos = 0x0231;
			break;
		case D2:
			tmp_BoxPos = 0x0360;
			break;
		case D3:
			tmp_BoxPos = 0x0462;
			break;
		default:
			break;
		}
		break;
	case Z_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0630;
			break;
		case D1:
			tmp_BoxPos = 0x0132;
			break;
		case D2:
			tmp_BoxPos = 0x0630;
			break;
		case D3:
			tmp_BoxPos = 0x0264;
			break;
		default:
			break;
		}
		break;
	case O_BLOCK:
		switch (m_iDirection)
		{
		case D0:
			tmp_BoxPos = 0x0660;
			break;
		case D1:
			tmp_BoxPos = 0x0660;
			break;
		case D2:
			tmp_BoxPos = 0x0660;
			break;
		case D3:
			tmp_BoxPos = 0x0660;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return tmp_BoxPos;
}

inline Point Block::ComputePoint(int x, int y)
{
	return Point((20 + 5) * x + 5, (20 + 5) * y + 5);
}

void Block::GetBlockArray()
{
	cout << "Pos " << m_iBoxPos << endl;
	switch (m_iBoxPos)
	{
	case 0x0F00:
		m_iBoxArr[0]={3, 2};//3,2
		m_iBoxArr[1]={2, 2};//2,2
		m_iBoxArr[2]={1, 2};//1,2
		m_iBoxArr[3]={0, 2};//0,2
		break;
	case 0x2222:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={1, 1};//1,1
		m_iBoxArr[2]={1, 0};//1,0
		m_iBoxArr[3]={1, 3};//1,3
		break;
	case 0x4444:
		m_iBoxArr[0]={2, 3};//2,3
		m_iBoxArr[1]={2, 2};//2,2
		m_iBoxArr[2]={2, 1};//2,1
		m_iBoxArr[3]={2, 0};//2,0
		break;
	case 0x0270:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={2, 1};//2,1
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={0, 1};//0,1
		break;
	case 0x0262:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={2, 1};//2,1
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0720:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={1, 2};//1,2
		m_iBoxArr[2]={0, 2};//0,2
		m_iBoxArr[3]={1, 1};//1,1
		break;
	case 0x0232:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={1, 1};//1,1
		m_iBoxArr[2]={0, 1};//0,1
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0170:
		m_iBoxArr[0]={0, 2};//0,2
		m_iBoxArr[1]={2, 1};//2,1
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={0, 1};//0,1
		break;
	case 0x0622:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={1, 2};//1,2
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0740:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={1, 2};//1,2
		m_iBoxArr[2]={0, 2};//0,2
		m_iBoxArr[3]={2, 1};//2,1
		break;
	case 0x0223:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={1, 1};//1,1
		m_iBoxArr[2]={1, 0};//1,0
		m_iBoxArr[3]={0, 0};//0,0
		break;
	case 0x0470:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={2, 1};//2,1
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={0, 1};//0,1
		break;
	case 0x0226:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={1, 1};//1,1
		m_iBoxArr[2]={2, 0};//2,0
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0710:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={1, 2};//1,2
		m_iBoxArr[2]={0, 2};//0,2
		m_iBoxArr[3]={0, 1};//0,1
		break;
	case 0x0322:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={0, 2};//0,2
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0360:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={0, 2};//0,2
		m_iBoxArr[2]={2, 1};//2,1
		m_iBoxArr[3]={1, 1};//1,1
		break;
	case 0x0231:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={1, 1};//1,1
		m_iBoxArr[2]={0, 1};//0,1
		m_iBoxArr[3]={0, 0};//0,0
		break;
	case 0x0462:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={2, 1};//2,1
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0630:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={1, 2};//1,2
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={0, 1};//0,1
		break;
	case 0x0132:
		m_iBoxArr[0]={0, 2};//0,2
		m_iBoxArr[1]={1, 1};//1,1
		m_iBoxArr[2]={0, 1};//0,1
		m_iBoxArr[3]={1, 0};//1,0
		break;
	case 0x0264:
		m_iBoxArr[0]={1, 2};//1,2
		m_iBoxArr[1]={2, 1};//2,1
		m_iBoxArr[2]={1, 1};//1,1
		m_iBoxArr[3]={2, 0};//2,0
		break;
	case 0x0660:
		m_iBoxArr[0]={2, 2};//2,2
		m_iBoxArr[1]={1, 2};//1,2
		m_iBoxArr[2]={2, 1};//2,1
		m_iBoxArr[3]={1, 1};//1,1
		break;
	default:
		break;
	}
}

list<Point> Block::GetPointList()
{
	list<Point> tmp_PointList;
	switch (m_iBoxPos)
	{
	case 0x0F00:
		tmp_PointList.push_back(ComputePoint(3,2));//3,2
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		break;
	case 0x2222:
		tmp_PointList.push_back(ComputePoint(1,3));//1,3
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x4444:
		tmp_PointList.push_back(ComputePoint(2,3));//2,3
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(2,0));//2,0
		break;
	case 0x0270:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		break;
	case 0x0262:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0720:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		break;
	case 0x0232:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0170:
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		break;
	case 0x0622:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0740:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		break;
	case 0x0223:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		tmp_PointList.push_back(ComputePoint(0,0));//0,0
		break;
	case 0x0470:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		break;
	case 0x0226:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(2,0));//2,0
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0710:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		break;
	case 0x0322:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0360:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		break;
	case 0x0231:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		tmp_PointList.push_back(ComputePoint(0,0));//0,0
		break;
	case 0x0462:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0630:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		break;
	case 0x0132:
		tmp_PointList.push_back(ComputePoint(0,2));//0,2
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(0,1));//0,1
		tmp_PointList.push_back(ComputePoint(1,0));//1,0
		break;
	case 0x0264:
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		tmp_PointList.push_back(ComputePoint(2,0));//2,0
		break;
	case 0x0660:
		tmp_PointList.push_back(ComputePoint(2,2));//2,2
		tmp_PointList.push_back(ComputePoint(1,2));//1,2
		tmp_PointList.push_back(ComputePoint(2,1));//2,1
		tmp_PointList.push_back(ComputePoint(1,1));//1,1
		break;
	default:
		break;
	}
	return tmp_PointList;
}

Mat Block::DisplayBlock(Mat m_pBackGround)
{
	Mat tmp_BackGround = m_pBackGround(Rect(m_iBlockPoint.x, m_iBlockPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iBlock, 1, 0, tmp_BackGround);
	return m_pBackGround;
}
Mat Block::HideBlock(Mat m_pBackGround)
{
	Mat tmp_BackGround = m_pBackGround(Rect(m_iBlockPoint.x, m_iBlockPoint.y, m_iWidth, m_iHeight));
	addWeighted(tmp_BackGround, 0, m_iBlock, 0, 0, tmp_BackGround);
	return m_pBackGround;
}
void Block::MoveBlock(TypeMoveDir m_pMoveDir)
{
	switch (m_pMoveDir)
	{
	case MOVE_LEFT:
		m_iLocation.x = m_iLocation.x - 1;
		break;
	case MOVE_DOWN:
		m_iLocation.y = m_iLocation.y + 1;
		break;
	case MOVE_RIGHT:
		m_iLocation.x = m_iLocation.x + 1;
		break;
	default:
		break;
	}
}
