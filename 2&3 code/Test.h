#ifndef TEST_H
#define TEST_H
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<queue>
#include"point.h"
#include"Line.h"
#include"Circle.h"

enum PlotMod { T_LINE, T_CIRCLE, T_FULL };

///Display
namespace Test {
  std::vector<Line> lines;
  std::vector<Circle> circles;
  std::vector<std::vector<GLint>> pixel;
  GLint left_min, right_max, up_min, down_max;
  Line now_line;
  Circle now_circle;
  PlotMod plot_mod = T_LINE;
  bool Flag = true;
	void Display(void);
  void MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y);
  void MouseButtonMove(GLint mouse_x, GLint mouse_y);
  void Show();
  void ProcessMenu(int value);
  void CreateMenu();
  void ReadPixel(GLint x,GLint y);
  void InitPixelArray();
  void WirtePixel();
  void Full(GLint x, GLint y);
  void Debug();
}

void Test::Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (pixel.empty() == false)
        Test::WirtePixel();
    for (auto line : lines) {
        line.Display();
    }
    for (auto circle : circles) {
        circle.Display();
    }
    Test::Show();
}

void Test::MouseButton(GLint button, GLint action, GLint mouse_x, GLint mouse_y)
{
    static bool Flag = true;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && Flag == true)
        Flag = false;
    else if (button == GLUT_LEFT_BUTTON && action == GLUT_UP && Flag == false)
        Flag = true;
    else
        return;
    if (plot_mod == T_LINE) {
        now_line.MouseButton(button, action, mouse_x, mouse_y);
        if (button == GLUT_LEFT_BUTTON && action == GLUT_UP) {
            if (now_line.start == now_line.end)
                return;
            lines.push_back(now_line);
        }
    }
    else if (plot_mod == T_CIRCLE) {
        now_circle.MouseButton(button, action, mouse_x, mouse_y);
        if (button == GLUT_LEFT_BUTTON && action == GLUT_UP) {
            if (now_circle.R == 0)
                return;
        circles.push_back(now_circle);
        }
    }
    else if(plot_mod == T_FULL){
        Full(mouse_x, mouse_y);
        glutSwapBuffers();
        Test::Display();
    }
    glutPostRedisplay();
}

void Test::MouseButtonMove(GLint mouse_x, GLint mouse_y)
{
    if (Test::Flag == false)
    {
        Test::Flag = true;
        return;
    }
    if (plot_mod == T_LINE)
        now_line.MouseButtonMove(mouse_x, mouse_y);
    else if (plot_mod == T_CIRCLE)
        now_circle.MouseButtonMove(mouse_x, mouse_y);
}

void Test::Show()
{
    system("cls");
    int count = 0;
    for (auto line : Test::lines) {
        std::cout << "Lines: " << ++count << "\t";
        std::cout.width(10);
        std::cout << "start: " << line.start.x << "," << line.start.y << "\t";
        std::cout << "end: " << line.end.x << "," << line.end.y << std::endl;
    }
    count = 0;
    for (auto circle : circles) {
        std::cout << "Circles: " << ++count << "\t";
        std::cout.width(10);
        std::cout << "center: " << circle.Center.x << "," << circle.Center.y << "\t";
        std::cout << "R: " << circle.R << std::endl;
    }
}

void Test::ProcessMenu(int value)
{
    Test::Flag = false;
    switch (value)
    {
    case 1:
        plot_mod = T_LINE;
        break;
    case 2:
        plot_mod = T_CIRCLE;
        break;
    case 3:
        lines.clear();
        circles.clear();
        pixel.clear();
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
        Test::Display();
        break;
    case 4:
        plot_mod = T_FULL;
        break;
    default:
        break;
    }
}

void Test::CreateMenu()
{
  glutCreateMenu(Test::ProcessMenu);
  glutAddMenuEntry("Line", 1);
  glutAddMenuEntry("Circle", 2);
  glutAddMenuEntry("Clear", 3);
  glutAddMenuEntry("Full", 4);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Test::ReadPixel(GLint x, GLint y)
{
    x = Window::size.x / 2 + x;
    y = Window::size.y / 2 - y;
    pixel[x][y] = 1;
}

void Test::InitPixelArray()
{
    pixel.clear();
    //set size
    pixel.resize(Window::size.x);
    for (auto &x : pixel)
    {
        x.resize(Window::size.y);
        for (auto &y : x)
            y = 0;
    }
    for (auto &x : lines)
    {
        x.Foreace(ReadPixel);
    }
    for (auto &x : circles)
    {
        x.Foreach(ReadPixel);
    }
}

void Test::WirtePixel()
{
    glColor3d(0.4, 0.2, 0.8);
    glBegin(GL_POINTS);
    for (int i = left_min; i < right_max; i++) {
        for (int j = up_min; j < down_max; j++) {
            if (pixel[i][j] == 2)
                glVertex2i(i - Window::size.x / 2, Window::size.y / 2 - j);
        }
    }
    glEnd();
    glFlush();
    glColor3i(0, 0, 0);
}

void Test::Full(GLint x,GLint y)
{
    InitPixelArray();
    std::queue<point<GLint>> roots;
    point<GLint> temp(x, y);
    roots.push(temp);
    right_max = down_max = 0;
    left_min = Window::size.x;
    up_min = Window::size.y;
    while (roots.empty() == false)
    {
        temp = roots.front();
        roots.pop();
        int x = temp.x, y = temp.y;
        bool flag_left, flag_right;
        flag_left = flag_right = true;
        //move to top
        while ((y >= 0) && (pixel[x][y] == 0))
            y--;
        y++;
        if (y < up_min)
            up_min = y;
        //foreach
        while ((y < Window::size.y) && (pixel[x][y] == 0))
        {
            pixel[x][y] = 2;
            //left
            if ((x > 0) && (flag_left ^ (pixel[x - 1][y] >= 1)))
            {
                if (flag_left == true)
                {
                    temp.set(x - 1, y);
                    roots.push(temp);
                }
                flag_left = !flag_left;
                if (x - 1 < left_min)
                    left_min = x - 1;
            }
            //right
            if ((x < Window::size.x - 1) && (flag_right ^ (pixel[x + 1][y] >= 1)))
            {
                if (flag_right == true)
                {
                    temp.set(x + 1, y);
                    roots.push(temp);
                }
                flag_right = !flag_right;
                if (x + 1 > right_max)
                    right_max = x + 1;
            }
            y++;
        }
        if (y > down_max)
            down_max = y;
    }
}

void Test::Debug()
{
    for (int j = 0; j < Window::size.y; j++)
    {
        for (int i = 0; i < Window::size.x; i++)
            std::cout << (GLint)pixel[i][j];
        std::cout << std::endl;
    }
}

#endif // TEST_H
