#ifndef PLAY_ROW_H
#define PLAY_ROW_H

#include"box.h"
#include"TypeName.h"

#include"TypeColor.h"
#include<array>
#include<opencv2/opencv.hpp>
using namespace cv;

class PlayRow
{
private:
	int m_iID;
	uint16_t m_iWidth;
	uint16_t m_iHeight;

	Mat m_iPlayRow;
	Scalar m_iColor;//BackColor
	TypeColor m_iTypeColor;//BackColorName
	Point m_iPlayRowPoint;
	list<Box*> boxlist;
	//bool m_iRowStatus[10];
	array<bool, 10> m_iRowStatus;
public:
	PlayRow(Point m_pPlayRowPoint,int m_pID);
	virtual ~PlayRow();
	void UpdatePlayRow(array<bool,10> m_pRowStatus);
	Mat DisplayPlayRow(Mat m_pBackGround);
	Mat HidePlayRow(Mat m_pBackGround);

};



#endif // !PLAY_ROW_H
