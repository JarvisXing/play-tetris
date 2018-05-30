#ifndef _BLOCK_H
#define _BLOCK_H
#include"box.h"
#include"TypeName.h"
#include"TypeColor.h"
#include<opencv2/opencv.hpp>
using namespace cv;
struct Location
{
	uint8_t x;
	uint8_t y;
};
class Block
{
private:
	uint8_t m_iWidth;
	uint8_t m_iHeight;
	int m_iTypeName;
	int m_iDirection;
	int m_iBoxPos;/*current*/
	list<Point> m_iBoxPointList;
	Mat m_iBlock;
	TypeColor m_iTypeColor;
	Scalar m_iColor;
	Point m_iBlockPoint;
	list<Box*> boxlist;

public:
	Location m_iLocation;
	array<array<int, 2>, 4> m_iBoxArr;

	Block(Point m_pBlockPoint);
	virtual ~Block();
	void RotateBlockCW();//D3->D2->D1->D0
	void RotateBlockCCW();//D0->D1->D2->D3
	void UpdateBlock(int x,int y);

	void GetBlockArray();

	inline int ComputePos();
	inline Point ComputePoint(int x, int y);
	list<Point> GetPointList();
	Mat DisplayBlock(Mat m_pBackGround);
	Mat HideBlock(Mat m_pBackGround);
	void MoveBlock(TypeMoveDir m_pMoveDir);
	
};
#endif // !_BLOCK_H

