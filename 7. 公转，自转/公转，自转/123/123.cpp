



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





//






float angle_sun_self=0.0; //太阳自传
float angle_earth=0.0; //地球公转
float angle_earth_self=0.0; //地球自转
float angle_moon=0.0; //月球公转







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
gluLookAt(20,10,0, 0.0,0.0,0.0,0.0f,1.0f,0.0f);




glPushMatrix();

glRotatef(angle_sun_self,0.0,1.0,0.0);

glutWireSphere(1.5,25,25);//太阳自转，绘制实心球体，半径1.5,横向分割20份,纵向分割20份

//or 
//glutSolidSphere(1.5,50,50);//太阳自转，绘制实心球体，半径1.5,横向分割20份,纵向分割20份



glPopMatrix();

glTranslatef(0.0,0.0,4);

glRotatef(angle_sun_self,0.0,1.0,0.0);

glutWireSphere(1.5,25,25);//太阳自转，绘制实心球体，半径1.5,横向分割20份,纵向分割20份




// 交换缓冲区 
glutSwapBuffers(); 
// 让angle自动增加。 
//改变转动角度
angle_sun_self+=0.1;
angle_earth+=0.3;
angle_earth_self+=0.5;
angle_moon+=0.3;

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
gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0,0.0f,1.0f,0.0f);
}







//光照初始化
void light_init()
{
	float mat_specular[]={1.0,1.0,1.0,1.0};//镜面反射系数
	float mat_shininess[]={128.0};//镜面反射高亮程序

		float mat_diffuse[]={0.9,0.9,0.9,1.0}; //材质漫反射系数

	float light_position[]={1.0,1.0,1.0,1.0};//光源位置
    float white_light[]={0.3,0.6,0.7,1.0};//定义白光

	float lmodel_light[]={0.4,0.8,0.9,1.0};//整体光照

	glShadeModel(GL_SMOOTH); //着色模式

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);  //设置材质镜面反射系数
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);//设置材质镜面反射高亮区域
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);//设置光照漫反射系数

	glLightfv(GL_LIGHT0,GL_POSITION,light_position); //设置光源位置

	glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light); //设置光源漫反射

	glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);//设置光源镜面反射
  
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_light);//设全局光照

	glEnable(GL_LIGHTING);//开启光照

	glEnable(GL_LIGHT0); //开启(GL_LIGHT0灯)

	glEnable(GL_DEPTH_TEST);//开启深度测试




}




void main(int argc, char **argv) { 

	


glutInit(&argc, argv); 
// 在这里设置双缓冲区。 
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
glutInitWindowPosition(100,100); 
glutInitWindowSize(320,320); 
glutCreateWindow("3D Tech- GLUT Tutorial"); 

//灯光初始化
light_init();


glutDisplayFunc(renderScene); 
// 这里让程序空闲时调用renderScene， 
glutIdleFunc(renderScene); 

//glutKeyboardFunc(processNormalKeys);


//glutReshapeFunc(changeSize); 
//开启深度测试。 
glEnable(GL_DEPTH_TEST); 
glutMainLoop();


}
