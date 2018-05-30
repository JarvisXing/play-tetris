#ifndef SCORE_H
#define SCORE_H
#include"TypeColor.h"

#include<string>
#include<opencv2/opencv.hpp>


putText(backGroundImage, 
	"Game Over!", 
	Point(50, 200), 
	1, 3, Scalar(0, 0, 255), 2, 8, false);
imshow(windowname, backGroundImage);

#endif // !SCORE_H
