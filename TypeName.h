#ifndef TYPE_NAME_H
#define TYPE_NAME_H
#include <string>
#include <iostream>
using namespace std;
enum TypeField
{
	IN_NONE = 0,
	IN_WINDOW,
	IN_BLOCK,
	IN_PLAYGROUND,
};
enum TypeName
{
	I_BLOCK = 0,
	T_BLOCK,
	L_BLOCK,
	J_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	O_BLOCK,
};
enum TypeDir
{
	D0 = 0,
	D1,
	D2,
	D3,
};
enum TypeMoveDir
{
	MOVE_LEFT = 0,
	MOVE_DOWN,
	MOVE_RIGHT,
};
enum TypeDetect
{
	DETECT_NONE=0,
	DETECT_LEFT,
	DETECT_RIGHT,
	DETECT_BELOW,

	DETECT_BLOCK,

	DETECT_NOBELOW,
	DETECT_NOLEFT,
	DETECT_NORIGHT,
	DETECT_NOSIDE,
	
};
inline int GetIDOfBlock(string name)
{
	if (name == "I_BLOCK")
	{
		return I_BLOCK;		//SixRobot : CL_x
	}
	if (name == "T_BLOCK")
	{
		return T_BLOCK;			//InCharge : IPOS
	}
	if (name == "L_BLOCK")
	{
		return L_BLOCK;		//SldOutCharge : SOPOS
	}
	if (name == "J_BLOCK")
	{
		return J_BLOCK;			//OutCharge : OPOS
	}
	if (name == "S_BLOCK")
	{
		return S_BLOCK;		//SldInCharge : SIPOS
	}
	if (name == "Z_BLOCK")
	{
		return Z_BLOCK;			//CodeScanner : SR_x
	}
	if (name == "O_BLOCK")
	{
		return O_BLOCK;			//VisionCom : VC_x
	}
}
inline string GetNameOfBlock(int n)
{
	switch (n)
	{
	case I_BLOCK:			//SixRobot : CL_x
		return "I_BLOCK";
		break;
	case T_BLOCK:			//InCharge : IPOS
		return "T_BLOCK";
		break;
	case L_BLOCK:		//SldOutCharge : SOPOS
		return "L_BLOCK";
		break;
	case J_BLOCK:			//OutCharge : OPOS
		return "J_BLOCK";
		break;
	case S_BLOCK:		//SldInCharge : SIPOS
		return "S_BLOCK";
		break;
	case Z_BLOCK:			//CodeScanner : SR_x
		return "Z_BLOCK";
		break;
	case O_BLOCK:			//VisionCom : VC_x
		return "O_BLOCK";
		break;
	default:
		return "UNKNOWN BLOCK";
		break;
	}
}
#endif// !TYPE_NAME_H