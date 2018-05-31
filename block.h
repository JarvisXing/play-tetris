#ifndef _BLOCK_H
#define _BLOCK_H
#include "BaseEntity.h"
#include "Box.h"
#include "TetrisWindow.h"

#include "TypeName.h"
#include<opencv2/opencv.hpp>
using namespace cv;
class TetrisWindow;
class Box;
struct Location
{
	uint8_t x;
	uint8_t y;
};
 
class Block:public BaseEntity
{
private:
	TetrisWindow * m_iWindow;
	Mat m_iMatBlock;
	Mat m_iMatSolid;
	list<Box*> m_iMatBoxList;	
	//array<array<bool, 4>, 4> m_iMatBlockArr;//表示显示block形状方向的数组

	Location m_iLocation;

	int m_iTypeName;
	int m_iDirection;
	int m_iBoxPos;//middle varient
	list<Point> m_iBoxPointList;
	array<array<int,2>, 4> m_iMatBoxArr;//表示box的形状及方向{1,2}{2,1}
	//array<array<uint16_t, 2>, 4> m_iMatBoxPointArr;//表示box绘图点在block中的位置
public:
	Block(TetrisWindow* window,
		Point m_pPoint,
		uint16_t m_pWidth,
		uint16_t m_pHeight,
		TypeColor m_pColor);
	virtual ~Block();

	void InitBlock();	
	void UpdateEntity(Point m_newPoint);

	Mat DisplayEntity();
	Mat HideEntity();
	
	Mat GetMatBlock();
	void SetMatBlock(Mat m_pNewMat);
	void RotateBlockCW();//D3->D2->D1->D0
	void RotateBlockCCW();//D0->D1->D2->D3
	void MoveBlock(TypeMoveDir m_pMoveDir);//

	void GetBlockArray();

	inline int ComputePos();
	inline Point ComputePoint(int x, int y);
	list<Point> GetPointList();

	void UpdateBlock();

	TetrisWindow* const GetWindow() { return m_iWindow; }

};
#endif // !_BLOCK_H

