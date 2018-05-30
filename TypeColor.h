#ifndef TYPE_COLOR_H
#define TYPE_COLOR_H
#include<opencv2/opencv.hpp>
using namespace cv;
//color sequence of opencv is BGR
enum TypeColor
{
	RED = 0,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	GREY,
};
inline Scalar SetColor(TypeColor pColorName)
{
	switch (pColorName)
	{
	case RED:
		return Scalar(0, 0,255);
		break;
	case GREEN:
		return Scalar(0, 255, 0);
		break;
	case BLUE:
		return Scalar(255, 0, 0);
		break;
	case BLACK:
		return Scalar(0, 0, 0);
		break;
	case WHITE:
		return Scalar(255, 255, 255);
		break;
	case GREY:
		return Scalar(127, 127, 127);
		break;
	default:
		return Scalar(0, 0, 0);
		break;
	}
}
#endif // !TYPE_COLOR_H
