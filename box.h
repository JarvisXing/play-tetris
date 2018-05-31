#ifndef BOX_H
#define BOX_H

#include "BaseEntity.h"
#include "TetrisWindow.h"
#include "Block.h"
#include "PlayGround.h"
#include "TypeName.h"
#include<opencv2/opencv.hpp>
using namespace cv;
class TetrisWindow;
class Block;
class PlayGround;
class Box:public BaseEntity
{
private:
	TetrisWindow * m_iWindow;
	Block* m_iBlock;
	PlayGround* m_iPlay;
	Mat m_iMatBox;
	uint8_t m_iField;
public:
	Box(TetrisWindow* window,
		Block* blcok,
		PlayGround* play,
		Point m_pPoint,
		uint16_t m_pWidth,
		uint16_t m_pHeight,
		TypeColor m_pColor);
	virtual ~Box();
	void UpdateEntity(Point m_newPoint);
	Mat DisplayEntity();
	Mat HideEntity();

	TetrisWindow* const GetWindow() { return m_iWindow; }
	Block* const GetBlock() { return m_iBlock; }
	PlayGround* const GetPlay() { return m_iPlay; }

};
#endif
