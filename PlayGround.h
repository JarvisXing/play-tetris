#ifndef PLAY_GROUND_H
#define PLAY_GROUND_H
#include "BaseEntity.h"
#include "Box.h"
#include "Block.h"
#include "TetrisWindow.h"
#include <array>
#include "TypeName.h"
#include<opencv2/opencv.hpp>
using namespace cv;
class TetrisWindow;
class Box;
class Block;
class PlayGround:public BaseEntity
{
private:
	TetrisWindow * m_iWindow;
	Mat m_iMatPlay;
	Mat m_iMatSolid;
	Block* m_iBlock;
	array<array<bool, 10>,  20> m_iMatBoxArr;
	array<array<bool, 10>, 20> m_iMatSolidArr;
	bool m_iNewBlock;
	set<array<int, 2>> m_iBoxPointSet;
	set<Box*> m_iBoxSet;
	TypeDetect m_iDetect;
	list<Box*> m_iMatBoxList;
	array<array<int, 2>, 4> m_iAbsLocArr;//block的绝对位置坐标
	//TODO: Box* array
public:
	PlayGround(TetrisWindow* window,
		Point m_pPoint,
		uint16_t m_pWidth,
		uint16_t m_pHeight,
		TypeColor m_pColor);

	virtual ~PlayGround();
	void InitPlay();

	void UpdateEntity(Point m_newPoint);
	Mat DisplayEntity();
	Mat HideEntity();

	Mat GetMatPlay();
	void SetMatPlay(Mat m_pNewMat);
	TypeDetect DetectEdge();
	TypeDetect DetectCollision();
	void DrawSolid();
	void ClearRow();
	bool GetBlockState();

	TetrisWindow* const GetWindow() { return m_iWindow; }
	Block* const GetBlock() { return m_iBlock; }

};

#endif // !PLAY_GROUND_H
