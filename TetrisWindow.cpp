#include "TetrisWindow.h"

TetrisWindow::TetrisWindow() :m_iWindowName("Tetris"),
m_iColor(BLACK),m_iBoxPix(20),m_iGapPix(5),
m_iNumBoxX(17),m_iNumBoxY(22),
m_iNumBlockW(4), m_iNumBlockH(4)
{
	m_iWidth = m_iNumBoxX * (m_iBoxPix + m_iGapPix) + m_iGapPix;
	m_iHeight = m_iNumBoxY * (m_iBoxPix + m_iGapPix) + m_iGapPix;
	Mat tmp_Window(m_iHeight, m_iWidth, CV_8UC3, SetColor(m_iColor));
	m_iMatWindow = tmp_Window;
	m_iBlockW =(m_iNumBlockW) * (m_iBoxPix + m_iGapPix) +  m_iGapPix;
	m_iBlockH =(m_iNumBlockH )* (m_iBoxPix + m_iGapPix) + m_iGapPix;
}


TetrisWindow::~TetrisWindow()
{
}
void TetrisWindow::InitWindow()
{
	Box* box = new Box(this, NULL,Point(10,10), m_iBoxPix, m_iBoxPix, GREY);
	m_iMatBox = box;
	Block* block = new Block(this, Point(30, 30), m_iBlockW, m_iBlockH, WHITE);
	m_iMatBlock = block;
}
void TetrisWindow::ExitWindow()
{

}
void TetrisWindow::ShowWindow()
{
	imshow(GetWindowName(),GetMatWindow());
	//move action
	Mat tmp_Window(m_iHeight, m_iWidth, CV_8UC3, SetColor(m_iColor));
	m_iMatWindow = tmp_Window;
}
void TetrisWindow::UpdateWindow()
{
	SetMatWindow(m_iMatBox->DisplayEntity());
	SetMatWindow(m_iMatBlock->DisplayEntity());
}
String TetrisWindow::GetWindowName()
{
	return m_iWindowName;
}
Mat TetrisWindow::GetMatWindow()
{
	return m_iMatWindow;
}
void TetrisWindow::SetMatWindow(Mat m_pNewMat)
{
	m_iMatWindow = m_pNewMat;
}
Box* TetrisWindow::GetBox()
{
	return m_iMatBox;
}
Block* TetrisWindow::GetBlock()
{
	return m_iMatBlock;
}