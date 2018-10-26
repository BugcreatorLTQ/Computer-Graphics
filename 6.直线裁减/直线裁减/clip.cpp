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

/// ���ƣ���ȡ��������
/// ������������
/// ����ֵ����������
int GetCode(const Point2D point)
{
	int code=0;
	code |= (int)point.x < Window::Left ? 1: 0;		//Left
	code |= (int)point.x > Window::Right ? 2: 0;	//Right
	code |= (int)point.y < Window::Bottom ? 4: 0;	//Bottom
	code |= (int)point.y > Window::Top ? 8: 0;		//Top
	return code;
}

/// ���ƣ��ü�������
/// ������������ б��
/// ����ֵ�����ü���ɷ���true ���򷵻�false
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

/// ���ƣ�ֱ�߲ü�
/// ������ֱ�ߵ�����������
/// ����ֵ������ȡ����true ��������false
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

/*  ���� ���ü�ֱ��
    ���� ��(x1,y1) (x2,y2) (x3,y3) ����ֱ�ߵ�����������
         
  
	       left right top bottom �ֱ�Ϊ���βü������������4���߽�



          left
		   |----------------|top ����:����ͼ �ü������Ͻ�����Ϊ(right, top);
		   |                |
		   |                |
		   |                |
   bottom  |----------------|
	                      right
	   
	  
		����ֵ���޸ĺ�ĵ��x,y���꣬���ڲ��á����á��ķ�ʽ���ݲ���������ֱ���޸Ĳ���x,y����ֵ����
                ����Ϊ�ü�֮��ֱ����������
  
        return�ķ���ֵ  0:ֱ���ڲü����⣬������
		                1:ֱ����ȫ�ڲü����ڣ�������ü����н���,����

*/



int clipLine(int left ,int right,int top ,int bottom,float &x1,float &y1,float &x2,float &y2)
{
	Point2D A,B;
	A.x = x1;
	A.y = y1;
	B.x = x2;
	B.y = y2;
	printf("�ü�ǰ %f %f %f %f\n",x1,y1,x2,y2);
	Window::Set(left,right,top,bottom);
    if(LineCut(A,B))
	{
		x1 = A.x;
		x2 = B.x;
		y1 = A.y;
		y2 = B.y;
		printf("�ü��� %f %f %f %f\n",x1,y1,x2,y2);
		return 1;
	}
	else
	{
		printf("����\n");
		return 0;
	}
}
