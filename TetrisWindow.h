#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H
#include "Box.h"
#include "Block.h"
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
class Box;
class Block;
class TetrisWindow
{
private:
	String m_iWindowName;
	//TODO: add a mat as static background,after block solid another as motivation background
	Mat m_iMatWindow;
	uint16_t m_iWidth;
	uint16_t m_iHeight;
	TypeColor m_iColor;
	uint8_t m_iGapPix;
	uint8_t m_iBoxPix;
	uint16_t m_iNumBoxX;
	uint16_t m_iNumBoxY;

	uint16_t m_iNumBlockW;
	uint16_t m_iNumBlockH;
	uint16_t m_iBlockW;
	uint16_t m_iBlockH;
	Box* m_iMatBox;
	Block* m_iMatBlock;

public:
	TetrisWindow();
	virtual ~TetrisWindow();
	void InitWindow();
	void ExitWindow();
	void ShowWindow();
	void UpdateWindow();
	String GetWindowName();
	Mat GetMatWindow();
	void SetMatWindow(Mat m_pNewMat);
	Box* GetBox();
	Block* GetBlock();
};



#endif // !TETRIS_WINDOW_H

