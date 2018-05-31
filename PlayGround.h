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
	array<array<bool, 10>,  20> m_iMatBoxArr;
	set<array<int, 2>> m_iBoxPointSet;
	set<Box*> m_iBoxSet;
	TypeDetect m_iDetect;
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
	void DetectCollision(Block m_pBlock);

	TetrisWindow* const GetWindow() { return m_iWindow; }

};

#endif // !PLAY_GROUND_H
