#include"BaseEntity.h"

BaseEntity::BaseEntity(Point m_pPoint, 
	uint16_t m_pWidth,
	uint16_t m_pHeight,
	Scalar m_pColor)
{
	SetPoint(m_pPoint);
	SetRect(m_pWidth,m_pHeight);
	SetColor(m_pColor);
}
void BaseEntity::SetPoint(Point point)
{
	m_iPoint = point;

}
void BaseEntity::SetRect(uint16_t m_pWidth, uint16_t m_pHeight)
{
	m_iWidth = m_pWidth;
	m_iHeight = m_pHeight;
}
void BaseEntity::SetColor(Scalar m_pColor)
{
	m_iColor = m_pColor;
}

Point BaseEntity::GetPoint()
{
	return m_iPoint;
}
uint16_t BaseEntity::GetWidth() 
{
	return m_iWidth;
}
uint16_t BaseEntity::GetHeight()
{
	return m_iHeight;
}
Scalar BaseEntity::GetColor()
{
	return m_iColor;
}
BaseEntity::~BaseEntity()
{

}
