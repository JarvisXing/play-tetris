#include "Box.h"
Box::Box(TetrisWindow* window, Block* block,PlayGround* play,
	Point m_pPoint,	uint16_t m_pWidth,	uint16_t m_pHeight,	TypeColor m_pColor):
	BaseEntity(m_pPoint,m_pWidth,m_pHeight,	m_pColor),
	m_iWindow(window),m_iMatBlock(block),m_iMatPlay(play)
{	
	Mat tmp_box(GetHeight(),GetWidth(),CV_8UC3, SetColor(m_pColor));
	m_iMatBox = tmp_box;
	if (m_iWindow != NULL)
		m_iField = IN_WINDOW;
	else if (m_iMatBlock != NULL)
		m_iField = IN_BLOCK;
	else if (m_iMatPlay != NULL)
		m_iField = IN_PLAYGROUND;
	else
		m_iField = IN_NONE;
}

Box::~Box()
{
	//delete this;
}
void Box::UpdateEntity(Point m_newPoint)
{
	SetPoint(m_newPoint);

}

Mat Box::DisplayEntity()
{
	if (m_iField == IN_WINDOW)
	{	
		Mat m_pBackGround = m_iWindow->GetMatWindow();
		Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
		addWeighted(tmp_BackGround, 0, m_iMatBox, 1, 0, tmp_BackGround);
		return m_pBackGround;
	}
	if (m_iField == IN_BLOCK)
	{
		Mat m_pBackGround = m_iMatBlock->GetMatBlock();
		Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
		addWeighted(tmp_BackGround, 0, m_iMatBox, 1, 0, tmp_BackGround);
		return m_pBackGround;
	}
	if (m_iField == IN_PLAYGROUND)
	{
		Mat m_pBackGround = m_iMatPlay->GetMatPlay();
		Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
		addWeighted(tmp_BackGround, 0, m_iMatBox, 1, 0, tmp_BackGround);
		return m_pBackGround;
	}
	
}
Mat Box::HideEntity()
{
	if (m_iField == IN_WINDOW)
	{
		Mat m_pBackGround = m_iWindow->GetMatWindow();
		Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
		addWeighted(tmp_BackGround, 0, m_iMatBox, 0, 0, tmp_BackGround);
		return m_pBackGround;
	}
	if (m_iField == IN_BLOCK)
	{
		Mat m_pBackGround = m_iMatBlock->GetMatBlock();
		Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
		addWeighted(tmp_BackGround, 0, m_iMatBox, 0, 0, tmp_BackGround);
		return m_pBackGround;
	}
	if (m_iField == IN_PLAYGROUND)
	{
		Mat m_pBackGround = m_iMatPlay->GetMatPlay();
		Mat tmp_BackGround = m_pBackGround(Rect(GetPoint().x, GetPoint().y, GetWidth(), GetHeight()));
		addWeighted(tmp_BackGround, 0, m_iMatBox, 0, 0, tmp_BackGround);
		return m_pBackGround;
	}
}


