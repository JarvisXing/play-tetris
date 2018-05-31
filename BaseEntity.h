#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H
#include "TypeColor.h"
#include<opencv2/opencv.hpp>
using namespace cv;
class BaseEntity
{
private:
	uint16_t m_iWidth;
	uint16_t m_iHeight;
	Point m_iPoint;
	TypeColor m_iColor;
public:
	BaseEntity(Point m_pPoint,uint16_t m_pWidth,uint16_t m_pHeight, TypeColor m_iColor);
	virtual	~BaseEntity();
	virtual void UpdateEntity(Point m_newPoint) = 0;
	virtual Mat DisplayEntity() = 0;
	virtual Mat HideEntity() = 0;
	void SetPoint(Point m_pPoint);
	void SetRect(uint16_t m_pWidth, uint16_t m_pHeight);
	Point GetPoint();
	uint16_t GetWidth();
	uint16_t GetHeight();
	Scalar GetColor();
	//TODO: generate random color£»

};
#endif // !BASE_ENTITY_H
