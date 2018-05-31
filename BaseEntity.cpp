#include"BaseEntity.h"

BaseEntity::BaseEntity(Point m_pPoint, 
	uint16_t m_pWidth,
	uint16_t m_pHeight,
	TypeColor m_pColor)
{
	SetPoint(m_pPoint);
	SetRect(m_pWidth,m_pHeight);
	m_iColor = m_pColor;
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
	return SetColor(m_iColor);
}
BaseEntity::~BaseEntity()
{

}
