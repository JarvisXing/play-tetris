#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H
#include<opencv2/opencv.hpp>
using namespace cv;
class BaseEntity
{
private:
	uint16_t m_iWidth;
	uint16_t m_iHeight;
	Point m_iPoint;
	Scalar m_iColor;
public:
	BaseEntity(Point m_pPoint,uint16_t m_pWidth,uint16_t m_pHeight, Scalar m_pColor);
	virtual	~BaseEntity();
	virtual void UpdateEntity() = 0;
	virtual Mat DisplayEntity() = 0;
	virtual Mat HideEntity() = 0;
	void SetPoint(Point m_pPoint);
	void SetRect(uint16_t m_pWidth, uint16_t m_pHeight);
	void SetColor(Scalar m_pColor);
	Point GetPoint();
	uint16_t GetWidth();
	uint16_t GetHeight();
	Scalar GetColor();


};
#endif // !BASE_ENTITY_H
