#ifndef LINE_H
#define LINE_H
#include<GL/glut.h>
#include<cmath>
#include"point.h"
#include"Window.h"

typedef GLint Type;

struct Line {
    point<Type> start = point<Type>(0, 0);
    point<Type> end = point<Type>(0, 0);
    point<Type> step = point<Type>(0, 0);
    void Set(const point<Type> &start, const point<Type> &end);
    Type Length();
    void Foreace(void(*fun)(GLint x, GLint y));
    void Display();
    void MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y);
    void MouseButtonMove(GLint mouse_x, GLint mouse_y);
};


inline void _glVertex2i(GLint x, GLint y)
{
    glVertex2i(x, y);
}

void Line::Set(const point<Type> &_start, const point<Type> &_end)
{
    start = _start;
    end = _end;
    step = end - start;
}

Type Line::Length()
{
    return (start - end).abs();
}

void Line::Foreace(void(*fun)(GLint x, GLint y))
{
    point<Type> now_point = start;
    point<Type> e_step, point_step;
    e_step.x = abs(step.x);
    e_step.y = abs(step.y);
    if (step.x == 0 && step.y == 0) //No Step
        return;
    point_step.x = (step.x == 0) ? 1 : step.x / e_step.x;
    point_step.y = (step.y == 0) ? 1 : step.y / e_step.y;
    if (step.x == 0) {   // k is endless
        do {
            fun(now_point.x, now_point.y);
            now_point.y += point_step.y;
        } while (now_point.y != end.y);
    }
    else if (step.y == 0) {   //k is zero
        do {
            fun(now_point.x, now_point.y);
            now_point.x += point_step.x;
        } while (now_point.x != end.x);
    }
    else if (abs(step.y / step.x) == 0) {   // |k| < 1
        Type e = -e_step.x;
        do {
            fun(now_point.x, now_point.y);
            e += 2 * e_step.y;
            now_point.x += point_step.x;
            if (e > 0) {
                now_point.y += point_step.y;
                e -= 2 * e_step.x;
            }
        } while (now_point.x != end.x);
    }
    else {    // |k| >= 1
        Type e = -e_step.y;
        do {
            fun(now_point.x, now_point.y);
            e += 2 * e_step.x;
            now_point.y += point_step.y;
            if (e > 0) {
                now_point.x += point_step.x;
                e -= 2 * e_step.y;
            }
        } while (now_point.y != end.y);
    }
}

void Line::Display()
{
    glBegin(GL_POINTS);
    Line::Foreace(_glVertex2i);
    glEnd();
    glFlush();
}

void Line::MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y)
{
  if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
    point<Type> start(mouse_x, -mouse_y);
    start += point<Type>(-Window::size.x / 2, Window::size.y / 2);
    Set(start, start);
  }
}

void Line::MouseButtonMove(GLint mouse_x, GLint mouse_y)
{
  point<GLint> temp(mouse_x, -mouse_y);
  end = temp + point<Type>(-Window::size.x / 2, Window::size.y / 2);
  step = end - start;
  Line::Display();
  glutPostRedisplay();
  glutSwapBuffers();
}

#endif // !LINE_H
