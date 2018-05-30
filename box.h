#ifndef _BOX_H
#define _BOX_H
#include<opencv2/opencv.hpp>
#include "TypeColor.h"
using namespace cv;

class Box
{
private:
	int m_iWidth;
	int m_iHeight;
	Scalar m_iColor;
	Mat m_iBox;
	Point m_iBoxPoint;
	TypeColor m_iTypeColor;

public:
	Box(Point m_pBoxPoint);
	virtual ~Box();
	Mat GetBox();
	Mat DisplayBox(Mat m_pPlayGround);
	Mat HideBox(Mat m_pPlayGround);
	Point GetBoxPoint();

};
#endif
