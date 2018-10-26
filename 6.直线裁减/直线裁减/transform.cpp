#include "transform.h"


/*  ���� ��ƽ��������
    ���� ��(x1,y1) (x2,y2) (x3,y3) ���������ε�����������
	           dx ��x������ƽ����
			   dy ��x������ƽ����
	����ֵ���޸ĺ�ĵ��x,y���꣬���ڲ��á����á��ķ�ʽ���ݲ���������ֱ���޸Ĳ���x,y����ֵ����

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

/*  ���� ��ƽ��������(����)
    ���� ��(x1,y1) (x2,y2) (x3,y3) ���������ε�����������
	           dx ��x������ƽ����
			   dy ��x������ƽ����
	����ֵ���޸ĺ�ĵ��x,y���꣬���ڲ��á����á��ķ�ʽ���ݲ���������ֱ���޸Ĳ���x,y����ֵ����

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

/*  ���� ����������εļ������Ľ�������
    ���� ��(x1,y1) (x2,y2) (x3,y3) ���������ε�����������
	            sx x�������ű���
				sy y�������ű���
	����ֵ���޸ĺ�ĵ��x,y���꣬���ڲ��á����á��ķ�ʽ���ݲ���������ֱ���޸Ĳ���x,y����ֵ����

  */

void scaleTrangle(float &x1,float &y1,float & x2,float &y2,float &x3,float &y3,float sx,float sy)
{
	float center_x = (x1+x2+x3)/3;
	float center_y = (y1+y2+y3)/3;
	translateTrangle(x1,y1,x2,y2,x3,y3,-center_x,-center_y);	//ƽ��
	x1 *= sx;
	x2 *= sx;
	x3 *= sx;
	y1 *= sy;
	y2 *= sy;
	y3 *= sy;
	translateTrangle(x1,y1,x2,y2,x3,y3,center_x,center_y);	//��λ
}

/*  ���� ����������εļ������Ľ�����ת
    ���� ��(x1,y1) (x2,y2) (x3,y3) ���������ε�����������
	            tha ��ת�Ƕȣ�����Ƕ��Զȷ�ʽ�����������ǻ��ȣ����������Һ����ֱ�Ϊsin �� cos
	����ֵ���޸ĺ�ĵ��x,y���꣬���ڲ��á����á��ķ�ʽ���ݲ���������ֱ���޸Ĳ���x,y����ֵ����

  */
void rotateTrangle(float &x1,float &y1,float & x2,float &y2,float &x3,float &y3 ,int tha)
{
	const float PI = acos(-1);
	float center_x = (x1+x2+x3)/3;
	float center_y = (y1+y2+y3)/3;
	float temp;
	translateTrangle(x1,y1,x2,y2,x3,y3,-center_x,-center_y);	//ƽ��

	temp = x1*cos(tha*PI/180) + y1*sin(tha*PI/180);
	y1 = -x1*sin(tha*PI/180) + y1*cos(tha*PI/180);
	x1 = temp;
	temp = x2*cos(tha*PI/180) + y2*sin(tha*PI/180);
	y2 = -x2*sin(tha*PI/180) + y2*cos(tha*PI/180);
	x2 = temp;
	temp = x3*cos(tha*PI/180) + y3*sin(tha*PI/180);
	y3 = -x3*sin(tha*PI/180) + y3*cos(tha*PI/180);
	x3 = temp;

	translateTrangle(x1,y1,x2,y2,x3,y3,center_x,center_y);	//��λ
	printf("%f %f \n",center_x,center_y);
}