#ifndef CIRCLE_H
#define CIRCLE_H
#include<GL/glut.h>
#include"Point.h"

typedef GLint Type;
struct Circle {
    point<Type> Center;
    Type R;
    void Foreach(void(*fun)(GLint x, GLint y));
    void Display();
    void CopyPoint(void(*fun)(GLint x, GLint y), const point<Type> & now_point);
    void MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y);
    void MouseButtonMove(GLint mouse_x, GLint mouse_y);
};

void Circle::Foreach(void(*fun)(GLint x, GLint y))
{
    point<Type> now_point(0, R);
    Type e = (Type)1 - R;
    do {
        Circle::CopyPoint(fun, now_point);
        now_point.x++;
        if (e >= 0) {
            now_point.y -= 1;
            e += 2 * (now_point.x - now_point.y) + 1;
        }
        else {
            e += 2 * now_point.x + 1;
        }
    } while (now_point.x <= now_point.y);
    Circle::CopyPoint(fun, now_point);
}

void Circle::Display()
{
    glBegin(GL_POINTS);
    Circle::Foreach(_glVertex2i);
    glEnd();
    glFlush();
}

void Circle::CopyPoint(void(*fun)(GLint x, GLint y), const point<Type> & now_point)
{
    Type x = now_point.x, y = now_point.y;
    fun(Center.x + x, Center.y + y);
    fun(Center.x + y, Center.y + x);
    fun(Center.x + x, Center.y - y);
    fun(Center.x - y, Center.y + x);
    fun(Center.x - x, Center.y + y);
    fun(Center.x + y, Center.y - x);
    fun(Center.x - x, Center.y - y);
    fun(Center.x - y, Center.y - x);
}

void Circle::MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y)
{
    point<Type> mouse_posi(mouse_x, -mouse_y);
    mouse_posi += point<Type>(-Window::size.x / 2, Window::size.y / 2);
    if (button == GLUT_LEFT_BUTTON) {
        if (action == GLUT_UP) {
            this->R = (mouse_posi - Center).abs();
        }
        else {
            this->Center = mouse_posi;
        }
    }
}

void Circle::MouseButtonMove(GLint mouse_x, GLint mouse_y)
{
    point<Type> now_point(mouse_x, -mouse_y);
    now_point += point<Type>(-Window::size.x / 2, Window::size.y / 2);
    this->R = (now_point - Center).abs();
    Circle::Display();
    glutPostRedisplay();
    glutSwapBuffers();
}

#endif // !CIRCLE_H
