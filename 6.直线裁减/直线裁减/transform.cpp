#include "transform.h"


/*  名称 ：平移三角形
    参数 ：(x1,y1) (x2,y2) (x3,y3) 构成三角形的三个点坐标
	           dx 沿x轴正向平移量
			   dy 沿x轴纵向平移量
	返回值：修改后的点的x,y坐标，由于采用“引用”的方式传递参数，所以直接修改参数x,y的数值即可

  */

void translateTrangle(float &x1,float &y1,float & x2,float &y2,float &x3,float &y3,int dx,int dy)
{
	x1 += dx;
	x2 += dx;
	x3 += dx;
	y1 += dy;
	y2 += dy;
	y3 += dy;
	
}

/*  名称 ：平移三角形(浮点)
    参数 ：(x1,y1) (x2,y2) (x3,y3) 构成三角形的三个点坐标
	           dx 沿x轴正向平移量
			   dy 沿x轴纵向平移量
	返回值：修改后的点的x,y坐标，由于采用“引用”的方式传递参数，所以直接修改参数x,y的数值即可

  */

void translateTrangle(float &x1,float &y1,float & x2,float &y2,float &x3,float &y3,float dx,float dy)
{
	x1 += dx;
	x2 += dx;
	x3 += dx;
	y1 += dy;
	y2 += dy;
	y3 += dy;
	
}

/*  名称 ：针对三角形的几何中心进行缩放
    参数 ：(x1,y1) (x2,y2) (x3,y3) 构成三角形的三个点坐标
	            sx x方向缩放比例
				sy y方向缩放比例
	返回值：修改后的点的x,y坐标，由于采用“引用”的方式传递参数，所以直接修改参数x,y的数值即可

  */

void scaleTrangle(float &x1,float &y1,float & x2,float &y2,float &x3,float &y3,float sx,float sy)
{
	float center_x = (x1+x2+x3)/3;
	float center_y = (y1+y2+y3)/3;
	translateTrangle(x1,y1,x2,y2,x3,y3,-center_x,-center_y);	//平移
	x1 *= sx;
	x2 *= sx;
	x3 *= sx;
	y1 *= sy;
	y2 *= sy;
	y3 *= sy;
	translateTrangle(x1,y1,x2,y2,x3,y3,center_x,center_y);	//复位
}

/*  名称 ：针对三角形的几何中心进行旋转
    参数 ：(x1,y1) (x2,y2) (x3,y3) 构成三角形的三个点坐标
	            tha 旋转角度，这里角度以度方式给出，而不是弧度，求正、余弦函数分别为sin 和 cos
	返回值：修改后的点的x,y坐标，由于采用“引用”的方式传递参数，所以直接修改参数x,y的数值即可

  */
void rotateTrangle(float &x1,float &y1,float & x2,float &y2,float &x3,float &y3 ,int tha)
{
	const float PI = acos(-1);
	float center_x = (x1+x2+x3)/3;
	float center_y = (y1+y2+y3)/3;
	float temp;
	translateTrangle(x1,y1,x2,y2,x3,y3,-center_x,-center_y);	//平移

	temp = x1*cos(tha*PI/180) + y1*sin(tha*PI/180);
	y1 = -x1*sin(tha*PI/180) + y1*cos(tha*PI/180);
	x1 = temp;
	temp = x2*cos(tha*PI/180) + y2*sin(tha*PI/180);
	y2 = -x2*sin(tha*PI/180) + y2*cos(tha*PI/180);
	x2 = temp;
	temp = x3*cos(tha*PI/180) + y3*sin(tha*PI/180);
	y3 = -x3*sin(tha*PI/180) + y3*cos(tha*PI/180);
	x3 = temp;

	translateTrangle(x1,y1,x2,y2,x3,y3,center_x,center_y);	//复位
	printf("%f %f \n",center_x,center_y);
}