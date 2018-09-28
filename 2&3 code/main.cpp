#include"Namespaces.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    Window::DisplayMode = GLUT_DOUBLE;
    Window::Init();
    Window::InitWin();
    glPointSize(2.0);
    glutMouseFunc(Test::MouseButton);
    glutMotionFunc(Test::MouseButtonMove);
    Test::CreateMenu();
    glutDisplayFunc(Test::Display);
    Window::InitColor();
    glutMainLoop();
    return 0;
}
