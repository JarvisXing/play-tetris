#ifndef PLAY_GROUND_H
#define PLAY_GROUND_H
#include"block.h"
#include"PlayRow.h"
#include"TypeName.h"

#include"TypeColor.h"
#include<array>
#include<opencv2/opencv.hpp>
using namespace cv;

class PlayGround
{
private:
	uint16_t m_iWidth;
	uint16_t m_iHeight;

	Mat m_iPlayGround;
	Scalar m_iColor;//BackColor
	TypeColor m_iTypeColor;//BackColorName
	Point m_iPlayGroundPoint;
	list<PlayRow*> rowlist;
	array<array<bool, 10>, 20> m_iGroundStatus;
public:
	PlayGround(Point m_iPlayGroundPoint);
	virtual ~PlayGround();
	void UpdatePlayGround(Block m_pBlock);
	Mat DisplayPalyGround(Mat m_pBackGround);
	TypeDetect DetectCollision(Block m_pBlock);


};

#endif // !PLAY_GROUND_H
