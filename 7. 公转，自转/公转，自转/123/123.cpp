



#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	

#include <windows.h>		// Windows��ͷ�ļ�
#include "glew.h"	

#include "glut.h"

#include	<stdio.h>		// ��׼����/������ͷ�ļ�
#include	"glaux.h"		// GLaux���ͷ�ļ�
#include <math.h>

GLuint		texture[1];		// �洢һ������





//






float angle_sun_self=0.0; //̫���Դ�
float angle_earth=0.0; //����ת
float angle_earth_self=0.0; //������ת
float angle_moon=0.0; //����ת







void renderScene(void) { 



//ע�����������������Ȼ������� 
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

//���õ�ǰ����ΪͶӰ����
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); //��λ����ǰ����
gluPerspective(45,1.0,1,1000); //����ͶӰ����


glViewport(0, 0, 320, 320); //��������

glMatrixMode(GL_MODELVIEW); //���õ�ǰ����Ϊģ����ͼ����
glLoadIdentity(); 
//����ģ����ͼ���󣬿���ԭ��
gluLookAt(20,10,0, 0.0,0.0,0.0,0.0f,1.0f,0.0f);




glPushMatrix();

glRotatef(angle_sun_self,0.0,1.0,0.0);

glutWireSphere(1.5,25,25);//̫����ת������ʵ�����壬�뾶1.5,����ָ�20��,����ָ�20��

//or 
//glutSolidSphere(1.5,50,50);//̫����ת������ʵ�����壬�뾶1.5,����ָ�20��,����ָ�20��



glPopMatrix();

glTranslatef(0.0,0.0,4);

glRotatef(angle_sun_self,0.0,1.0,0.0);

glutWireSphere(1.5,25,25);//̫����ת������ʵ�����壬�뾶1.5,����ָ�20��,����ָ�20��




// ���������� 
glutSwapBuffers(); 
// ��angle�Զ����ӡ� 
//�ı�ת���Ƕ�
angle_sun_self+=0.1;
angle_earth+=0.3;
angle_earth_self+=0.5;
angle_moon+=0.3;

}









void changeSize(int w, int h) { 
// ��ֹ�������߶�Ϊ0 
// (��������ô��ڿ��Ϊ0). 
if(h == 0) 
h = 1; 
float ratio = 1.0* w / h; 
// ��λ��ͶӰ���� 
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); 
// �����ӿڴ�СΪ�������ڴ�С 
//glViewport(160, 160, 160, 160); 
// ������ȷ��ͶӰ���� 
gluPerspective(45,ratio,1,1000); 
//����������ģ����ͼ���� 
glMatrixMode(GL_MODELVIEW); 
glLoadIdentity(); 
gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0,0.0f,1.0f,0.0f);
}







//���ճ�ʼ��
void light_init()
{
	float mat_specular[]={1.0,1.0,1.0,1.0};//���淴��ϵ��
	float mat_shininess[]={128.0};//���淴���������

		float mat_diffuse[]={0.9,0.9,0.9,1.0}; //����������ϵ��

	float light_position[]={1.0,1.0,1.0,1.0};//��Դλ��
    float white_light[]={0.3,0.6,0.7,1.0};//����׹�

	float lmodel_light[]={0.4,0.8,0.9,1.0};//�������

	glShadeModel(GL_SMOOTH); //��ɫģʽ

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);  //���ò��ʾ��淴��ϵ��
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);//���ò��ʾ��淴���������
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);//���ù���������ϵ��

	glLightfv(GL_LIGHT0,GL_POSITION,light_position); //���ù�Դλ��

	glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light); //���ù�Դ������

	glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);//���ù�Դ���淴��
  
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_light);//��ȫ�ֹ���

	glEnable(GL_LIGHTING);//��������

	glEnable(GL_LIGHT0); //����(GL_LIGHT0��)

	glEnable(GL_DEPTH_TEST);//������Ȳ���




}




void main(int argc, char **argv) { 

	


glutInit(&argc, argv); 
// ����������˫�������� 
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
glutInitWindowPosition(100,100); 
glutInitWindowSize(320,320); 
glutCreateWindow("3D Tech- GLUT Tutorial"); 

//�ƹ��ʼ��
light_init();


glutDisplayFunc(renderScene); 
// �����ó������ʱ����renderScene�� 
glutIdleFunc(renderScene); 

//glutKeyboardFunc(processNormalKeys);


//glutReshapeFunc(changeSize); 
//������Ȳ��ԡ� 
glEnable(GL_DEPTH_TEST); 
glutMainLoop();


}
