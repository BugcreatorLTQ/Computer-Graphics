



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

float angle=0;


AUX_RGBImageRec *LoadBMP(CHAR *Filename)				// ����λͼͼ��
{
	FILE *File=NULL;									// �ļ����
	if (!Filename)										// ȷ���ļ������ṩ
	{
		return NULL;									// ���û�ṩ������ NULL
	}
	File=fopen(Filename,"r");							// ���Դ��ļ�
	if (File)											// �ļ�����ô?
	{
		fclose(File);									// �رվ��
		return auxDIBImageLoadA(Filename);				// ����λͼ������ָ��
	}
	return NULL;										// �������ʧ�ܣ����� NULL
}

int LoadGLTexture()									// ����λͼ(��������Ĵ���)��ת��������
{
	int Status=FALSE;									// ״ָ̬ʾ��
	AUX_RGBImageRec *TextureImage[1];					// ��������Ĵ洢�ռ�
	memset(TextureImage,0,sizeof(void *)*1);			// ��ָ����Ϊ NULL
	// ����λͼ��������޴������λͼû�ҵ����˳�
	if (TextureImage[0]=LoadBMP("Data/123.bmp"))
	{
		Status=TRUE;									// �� Status ��Ϊ TRUE
		glGenTextures(1, &texture[0]);					// ��������

		// ʹ������λͼ�������� �ĵ�������
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// �����˲�
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// �����˲�
	}

	if (TextureImage[0])								// �����Ƿ����
	{
		if (TextureImage[0]->data)						// ����ͼ���Ƿ����
		{
			free(TextureImage[0]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
		}

		free(TextureImage[0]);							// �ͷ�ͼ��ṹ
	}
	return Status;										// ���� Status
}

void drawDemo()
{
	double base = 5, top = 5, height = 10;
	float params[]={
		1.0,0.0,0.0,1.0
	};
	float paramt[]={
		0.0,1.0,0.0,1.0
	};
	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);

	gluCylinder(obj, base, top, height, 20, 20);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T); 
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, params);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, paramt);

	gluDeleteQuadric(obj);
}

// ����Բ��
void drawCylinder()
{
}

// ��������
void drawBall()
{
}

// ���Ʒ���
void drawCube()
{
	
	glBegin(GL_QUADS);
		// ǰ��
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		// ����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		// ����
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		// ����
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		// ����
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		// ����
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ı��ε�����
	glEnd();
}

void texture_init()
{
   LoadGLTexture();
   glEnable(GL_TEXTURE_2D);
}


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
gluLookAt(15,15,15, 0.0,0.0,0.0,0.0f,1.0f,0.0f);




glPushMatrix();
glRotatef(angle,0.0,1.0,0.0);

//drawCube();
drawDemo();



// ���������� 
glutSwapBuffers(); 
// ��angle�Զ����ӡ� 
//�ı�ת���Ƕ�
angle+=0.05;
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
gluLookAt(0.0,0.0,7.0, 0.0,0.0,-1.0,0.0f,1.0f,0.0f);
}





void main(int argc, char **argv) { 




glutInit(&argc, argv); 
// ����������˫�������� 
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
glutInitWindowPosition(100,100); 
glutInitWindowSize(320,320); 
glutCreateWindow("3D Tech- GLUT Tutorial"); 

texture_init();


glutDisplayFunc(renderScene); 
// �����ó������ʱ����renderScene�� 
glutIdleFunc(renderScene); 

//glutKeyboardFunc(processNormalKeys);


//glutReshapeFunc(changeSize); 
//������Ȳ��ԡ� 
glEnable(GL_DEPTH_TEST); 
glutMainLoop();


}
