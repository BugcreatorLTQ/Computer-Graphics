



#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	

#include <windows.h>		// Windows的头文件
#include "glew.h"	

#include "glut.h"

#include	<stdio.h>		// 标准输入/输出库的头文件
#include	"glaux.h"		// GLaux库的头文件
#include <math.h>

GLuint		texture[1];		// 存储一个纹理

float angle=0;


AUX_RGBImageRec *LoadBMP(CHAR *Filename)				// 载入位图图象
{
	FILE *File=NULL;									// 文件句柄
	if (!Filename)										// 确保文件名已提供
	{
		return NULL;									// 如果没提供，返回 NULL
	}
	File=fopen(Filename,"r");							// 尝试打开文件
	if (File)											// 文件存在么?
	{
		fclose(File);									// 关闭句柄
		return auxDIBImageLoadA(Filename);				// 载入位图并返回指针
	}
	return NULL;										// 如果载入失败，返回 NULL
}

int LoadGLTexture()									// 载入位图(调用上面的代码)并转换成纹理
{
	int Status=FALSE;									// 状态指示器
	AUX_RGBImageRec *TextureImage[1];					// 创建纹理的存储空间
	memset(TextureImage,0,sizeof(void *)*1);			// 将指针设为 NULL
	// 载入位图，检查有无错误，如果位图没找到则退出
	if (TextureImage[0]=LoadBMP("Data/123.bmp"))
	{
		Status=TRUE;									// 将 Status 设为 TRUE
		glGenTextures(1, &texture[0]);					// 创建纹理

		// 使用来自位图数据生成 的典型纹理
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// 线形滤波
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// 线形滤波
	}

	if (TextureImage[0])								// 纹理是否存在
	{
		if (TextureImage[0]->data)						// 纹理图像是否存在
		{
			free(TextureImage[0]->data);				// 释放纹理图像占用的内存
		}

		free(TextureImage[0]);							// 释放图像结构
	}
	return Status;										// 返回 Status
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

// 绘制圆柱
void drawCylinder()
{
}

// 绘制球体
void drawBall()
{
}

// 绘制方块
void drawCube()
{
	
	glBegin(GL_QUADS);
		// 前面
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的左上
		// 后面
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下
		// 顶面
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		// 底面
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		// 右面
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		// 左面
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
	glEnd();
}

void texture_init()
{
   LoadGLTexture();
   glEnable(GL_TEXTURE_2D);
}


void renderScene(void) { 



//注意我们这里清除了深度缓冲区。 
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

//设置当前矩阵为投影矩阵
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); //单位化当前矩阵
gluPerspective(45,1.0,1,1000); //设置投影矩阵


glViewport(0, 0, 320, 320); //设置视区

glMatrixMode(GL_MODELVIEW); //设置当前矩阵为模型视图矩阵
glLoadIdentity(); 
//设置模型视图矩阵，看向原点
gluLookAt(15,15,15, 0.0,0.0,0.0,0.0f,1.0f,0.0f);




glPushMatrix();
glRotatef(angle,0.0,1.0,0.0);

//drawCube();
drawDemo();



// 交换缓冲区 
glutSwapBuffers(); 
// 让angle自动增加。 
//改变转动角度
angle+=0.05;
}









void changeSize(int w, int h) { 
// 防止除数即高度为0 
// (你可以设置窗口宽度为0). 
if(h == 0) 
h = 1; 
float ratio = 1.0* w / h; 
// 单位化投影矩阵。 
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); 
// 设置视口大小为增个窗口大小 
//glViewport(160, 160, 160, 160); 
// 设置正确的投影矩阵 
gluPerspective(45,ratio,1,1000); 
//下面是设置模型视图矩阵 
glMatrixMode(GL_MODELVIEW); 
glLoadIdentity(); 
gluLookAt(0.0,0.0,7.0, 0.0,0.0,-1.0,0.0f,1.0f,0.0f);
}





void main(int argc, char **argv) { 




glutInit(&argc, argv); 
// 在这里设置双缓冲区。 
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
glutInitWindowPosition(100,100); 
glutInitWindowSize(320,320); 
glutCreateWindow("3D Tech- GLUT Tutorial"); 

texture_init();


glutDisplayFunc(renderScene); 
// 这里让程序空闲时调用renderScene， 
glutIdleFunc(renderScene); 

//glutKeyboardFunc(processNormalKeys);


//glutReshapeFunc(changeSize); 
//开启深度测试。 
glEnable(GL_DEPTH_TEST); 
glutMainLoop();


}
