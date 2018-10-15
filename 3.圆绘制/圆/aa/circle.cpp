

#include "circle.h"

void CopyPoints(int centerX,int centerY, int x,int y)
{
	glVertex2i(centerX+x,centerY+y);
	glVertex2i(centerX+x,centerY-y);
	glVertex2i(centerX+y,centerY+x);
	glVertex2i(centerX+y,centerY-x);
	glVertex2i(centerX-x,centerY+y);
	glVertex2i(centerX-x,centerY-y);
	glVertex2i(centerX-y,centerY+x);
	glVertex2i(centerX-y,centerY-x);
}

void drawCircleBresenham(int centerX,int centerY,float r)

{
    glColor3f(0.0f,1.0f,0.0f);//���õ����ɫ
	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);//�Ե�ķ�ʽ����	
	
    /*�˴���д����Բ����* �������ص���ɫΪ glVertex2i(x,y)*/
	int x,y,d;
	x=0;
	y=r;
	d=1-r;
	while(x <= y)
	{
		CopyPoints(centerX,centerY,x,y);
		if(d<0)
			d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			y--;
		}
		x++;
	}

    printf("(%d,%d) r=%f\n",centerX,centerY,r);
	
	glEnd();//��������
    glFlush();
	glutSwapBuffers();
	
}
