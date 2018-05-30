#include <core/core.hpp>  
#include <highgui/highgui.hpp>  
#include <imgproc/imgproc.hpp>  
#include <iostream>  
#include <time.h>  
#include "box.h"
#include "block.h"
#include "PlayRow.h"
#include "PlayGround.h"
#include <list>
using namespace std;
using namespace cv;
#define BOXPIXEL 20
#define GAPPIXEL 5
//定义每个box大小和窗口大小  
int width = 20;
int hight = 20;
int WinWidth = 10 * (BOXPIXEL + GAPPIXEL) + GAPPIXEL + 4 * (BOXPIXEL + GAPPIXEL) + 3 * BOXPIXEL;
int WinHeight = 20 * (BOXPIXEL + GAPPIXEL) + GAPPIXEL + 2 * BOXPIXEL;

String windowname = "Tetris by Jarvis";
/*
void MoveDirection(int waittime, bool &horizMove, bool &verMove, int &moveDirection);
bool GameOver(const vector<Box> arraryBox);
void MoveAccordingDirecton(const int moveDirection, vector<Box> &arraryBox, Box & boxTarget);
void SnakeMove(vector<Box>&arraryBox1, vector<Box>&arraryBox, Mat &imageBackground);
*/
int main()
{
	time_t t;
	t = time(NULL);
	int newblock = 0;
	TypeDetect typedetect= DETECT_NONE;
	srand((unsigned)t);
	Mat window(WinHeight, WinWidth, CV_8UC3, Scalar(0, 0, 0));
	Block block(Point(10 * (BOXPIXEL + GAPPIXEL) + 2 * BOXPIXEL, BOXPIXEL));
	block.DisplayBlock(window);

	for (int i = 0; i < 30; i++)
	{

		if (i % 9 == 0)
		{
			Block block(Point(10 * (BOXPIXEL + GAPPIXEL) + 2 * BOXPIXEL, BOXPIXEL));
			block.DisplayBlock(window);
		}
		char pointKey = waitKey(1000);
		

		switch (pointKey)
		{
		case 'a':
			if (typedetect != DETECT_LEFT)
			{
				block.MoveBlock(MOVE_LEFT);
			}
			break;
		case 'd':
			if (typedetect != DETECT_RIGHT)
			{
				block.MoveBlock(MOVE_RIGHT);
			}
			break;
		case 's':
			if (typedetect != DETECT_BELOW)
			{
				block.MoveBlock(MOVE_DOWN);
			}
			break;
		case 'w':
			block.RotateBlockCW();
			break;
		default:
			break;
		}
		if (typedetect == DETECT_BELOW)
		{
			block.~block();
			Block block(Point(10 * (BOXPIXEL + GAPPIXEL) + 2 * BOXPIXEL, BOXPIXEL));
			block.DisplayBlock(window);
			typedetect = DETECT_NONE;
			newblock = 0;
		}	
		else {
			block.MoveBlock(MOVE_DOWN);
		}


		PlayGround playground(Point(BOXPIXEL, BOXPIXEL));

		if (newblock == 1)
		{
			typedetect=playground.DetectCollision(block);

		}

		playground.UpdatePlayGround(block);
		playground.DisplayPalyGround(window);
		
		imshow(windowname, window);

	}

	waitKey();
}


/*
int main()
{
	Box box01;
	arraryBox.push_back(box01);
	srand(time(0));
	moveDirection = rand() % 4;  //初始化移动方向  0:向左   1：向右   2 向上  3 乡下     
	while (true)
	{
		//判断是否越界，越界则游戏结束  
		if (!GameOver(arraryBox))
		{
			break;
		}
		//初始化显示界面  
		Mat imageBackground(Width, Hight, CV_8UC3, Scalar(0, 0, 0));
		Mat ROIBackground = imageBackground(Rect(boxTarget.boxPoint.x, boxTarget.boxPoint.y, width, hight));
		addWeighted(ROIBackground, 0, boxTarget.boxMat, 1, 0, ROIBackground);

		Mat ROICenterPoint = imageBackground(Rect(arraryBox[0].boxPoint.x, arraryBox[0].boxPoint.y, width, hight));
		addWeighted(ROICenterPoint, 0, arraryBox[0].boxMat, 1, 0, ROICenterPoint);

		if (arraryBox.size()>1)
		{
			Mat imageBackground01(Width, Hight, CV_8UC3, Scalar(0, 0, 0));
			imageBackground = imageBackground01;
			Mat ROIBackground = imageBackground(Rect(boxTarget.boxPoint.x, boxTarget.boxPoint.y, width, hight));
			addWeighted(ROIBackground, 0, boxTarget.boxMat, 1, 0, ROIBackground);
		}

		if (meetTargetBox)
		{
			boxTarget.boxPoint.x = (rand() % (Width / width))*width;
			boxTarget.boxPoint.y = (rand() % (Hight / hight))*hight;
			Mat ROIBackground = imageBackground(Rect(boxTarget.boxPoint.x, boxTarget.boxPoint.y, width, hight));
			addWeighted(ROIBackground, 0, boxTarget.boxMat, 1, 0, ROIBackground);
			meetTargetBox = false;
		}

		//通过键盘a s d w四个键控制上下左右移动方向；  
		MoveDirection(1000, horizMove, verMove, moveDirection);

		//定义蛇身box移动  
		SnakeMove(arraryBox1, arraryBox, imageBackground);

		//根据移动方向改变第一个box的增长方向  
		MoveAccordingDirecton(moveDirection, arraryBox, boxTarget);

		backGroundImage = imageBackground;
		imshow(windowname, imageBackground);
	}
	waitKey();
}

void MoveDirection(int waittime, bool &horizMove, bool &verMove, int &moveDirection)
{
	char pointKey = waitKey(waittime);
	switch (pointKey)
	{
	case 'a':
		if (horizMove)
		{
			moveDirection = 0;
			horizMove = false;
			verMove = true;
		}
		break;
	case 'd':
		if (horizMove)
		{
			moveDirection = 1;
			horizMove = false;
			verMove = true;
		}
		break;
	case 's':
		if (verMove)
		{
			moveDirection = 3;
			horizMove = true;
			verMove = false;
		}
		break;

	case 'w':
		if (verMove)
		{
			moveDirection = 2;
			horizMove = true;
			verMove = false;
		}
		break;
	default:
		break;
	}
}

bool GameOver(const vector<Box> arraryBox)
{
	if (arraryBox[0].boxPoint.x<0)
	{

		putText(backGroundImage, "Game Over!", Point(50, 200), 1, 3, Scalar(0, 0, 255), 2, 8, false);
		imshow(windowname, backGroundImage);
		return false;
	}
	if ((arraryBox[0].boxPoint.x) >= Width)
	{
		putText(backGroundImage, "Game Over!", Point(50, 200), 1, 3, Scalar(0, 0, 255), 2, 8, false);
		imshow(windowname, backGroundImage);
		return false;
	}
	if (arraryBox[0].boxPoint.y<0)
	{
		putText(backGroundImage, "Game Over!", Point(50, 200), 1, 3, Scalar(0, 0, 255), 2, 8, false);
		imshow(windowname, backGroundImage);
		return false;
	}
	if ((arraryBox[0].boxPoint.y) >= Hight)
	{
		putText(backGroundImage, "Game Over!", Point(50, 200), 1, 3, Scalar(0, 0, 255), 2, 8, false);
		imshow(windowname, backGroundImage);
		return false;
	}
	return true;
}

void MoveAccordingDirecton(const int moveDirection, vector<Box> &arraryBox, Box & boxTarget)
{
	switch (moveDirection)
	{
	case 0:
		arraryBox[0].boxPoint.x -= width;

		if (arraryBox[0].boxPoint == boxTarget.boxPoint)
		{
			arraryBox.insert(arraryBox.begin(), boxTarget);
			meetTargetBox = true;
		}
		break;
	case 1:
		arraryBox[0].boxPoint.x += width;
		if (arraryBox[0].boxPoint == boxTarget.boxPoint)
		{
			arraryBox.insert(arraryBox.begin(), boxTarget);
			meetTargetBox = true;
		}
		break;
	case 2:
		arraryBox[0].boxPoint.y -= hight;
		if (arraryBox[0].boxPoint == boxTarget.boxPoint)
		{
			arraryBox.insert(arraryBox.begin(), boxTarget);
			meetTargetBox = true;
		}
		break;
	case 3:
		arraryBox[0].boxPoint.y += hight;
		if (arraryBox[0].boxPoint == boxTarget.boxPoint)
		{
			arraryBox.insert(arraryBox.begin(), boxTarget);
			meetTargetBox = true;
		}
		break;
	default:
		break;
	}
}

void SnakeMove(vector<Box>&arraryBox1, vector<Box>&arraryBox, Mat &imageBackground)
{
	Box bb;
	arraryBox1.push_back(bb);
	arraryBox1[0] = arraryBox[0];
	for (int i = 0; i<arraryBox.size(); i++)
	{
		if (i != 0)
		{
			arraryBox1[1] = arraryBox[i];
			arraryBox[i] = arraryBox1[0];
			arraryBox1[0] = arraryBox1[1];
		}
		for (int i = 0; i<arraryBox.size(); i++)
		{
			Mat ROICenterPoint = imageBackground(Rect(arraryBox[i].boxPoint.x, arraryBox[i].boxPoint.y, width, hight));
			addWeighted(ROICenterPoint, 0, arraryBox[i].boxMat, 1, 0, ROICenterPoint);
		}
	}
	imshow(windowname, imageBackground);
}
*/