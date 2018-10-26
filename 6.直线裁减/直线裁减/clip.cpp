#include "clip.h"


typedef struct _point2D
{
	float x;
	float y;
}Point2D;

namespace Window
{
    int Left;
    int Right;
    int Top;
    int Bottom;
    void Set(const int left, const int right, const int top, const int bottom);
}


void Window::Set(const int left, const int right, const int top, const int bottom)
{
    Window::Left = left;
    Window::Right = right;
    Window::Top = top;
    Window::Bottom = bottom;
}

/// 名称：获取特征代码
/// 参数：点坐标
/// 返回值：特征代码
int GetCode(const Point2D point)
{
	int code=0;
	code |= (int)point.x < Window::Left ? 1: 0;		//Left
	code |= (int)point.x > Window::Right ? 2: 0;	//Right
	code |= (int)point.y < Window::Bottom ? 4: 0;	//Bottom
	code |= (int)point.y > Window::Top ? 8: 0;		//Top
	return code;
}

/// 名称：裁剪单个点
/// 参数：点坐标 斜率
/// 返回值：若裁剪完成返回true 否则返回false
bool CutPoint(Point2D &point, const float k)
{
	enum MOD{LEFT = 0, RIGHT, BOTTOM, TOP};
	int code = GetCode(point), mod;
	float b = point.y - k*point.x;
	if(code == 0)
	{
		return false;
	}
	for(mod = 0; code != 0; mod++)
	{
		if(((code>>mod) & 1) == 1)
			break;
	}
	MOD Mod = (MOD)mod;
	switch(Mod)
	{
	case LEFT:
		point.x = Window::Left;
		point.y = k*Window::Left + b;
		break;
	case RIGHT:
		point.x = Window::Right;
		point.y = k*Window::Right + b;
		break;
	case BOTTOM:
		point.y = Window::Bottom;
		point.x = (Window::Bottom - b)/k;
		break;
	case TOP:
		point.y = Window::Top;	
		point.x = (Window::Top - b)/k;
		break;
	default:
		break;
	}
	return true;
}	

/// 名称：直线裁剪
/// 参数：直线的两个点坐标
/// 返回值：若简取返回true 简弃返回false
bool LineCut(Point2D &A, Point2D &B)
{
	int codeA, codeB;
	float k = (A.y - B.y)/(A.x - B.x);
	codeA = GetCode(A);
	codeB = GetCode(B);
	if((codeA | codeB) == 0)
	{
		return true;
	}
	else if((codeA & codeB) != 0)
	{
		return false;
	}
	else
	{
		if(CutPoint(A, k) || CutPoint(B,k))
			LineCut(A, B);
	}
}

/*  名称 ：裁减直线
    参数 ：(x1,y1) (x2,y2) (x3,y3) 构成直线的两个点坐标
         
  
	       left right top bottom 分别为矩形裁减框的上下左右4个边界



          left
		   |----------------|top 补充:如左图 裁减框右上角坐标为(right, top);
		   |                |
		   |                |
		   |                |
   bottom  |----------------|
	                      right
	   
	  
		返回值：修改后的点的x,y坐标，由于采用“引用”的方式传递参数，所以直接修改参数x,y的数值即可
                返回为裁减之后直线两点坐标
  
        return的返回值  0:直线在裁减框外，被舍弃
		                1:直线完全在裁减框内，或者与裁减框有交点,保留

*/



int clipLine(int left ,int right,int top ,int bottom,float &x1,float &y1,float &x2,float &y2)
{
	Point2D A,B;
	A.x = x1;
	A.y = y1;
	B.x = x2;
	B.y = y2;
	printf("裁剪前 %f %f %f %f\n",x1,y1,x2,y2);
	Window::Set(left,right,top,bottom);
    if(LineCut(A,B))
	{
		x1 = A.x;
		x2 = B.x;
		y1 = A.y;
		y2 = B.y;
		printf("裁剪后 %f %f %f %f\n",x1,y1,x2,y2);
		return 1;
	}
	else
	{
		printf("舍弃\n");
		return 0;
	}
}
