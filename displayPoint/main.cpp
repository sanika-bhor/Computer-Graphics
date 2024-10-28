#include <iostream>
#include<GL/glut.h>

using namespace std;
void displayPoint()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2d(100,200);
    glVertex2d(105,200);
    glVertex2d(110,200);
    glVertex2d(115,200);
    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{
    cout << "Hello world!" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640,480);
    glutCreateWindow("creating window");
    glClearColor(1.0,1.0,1.0,0);
    glColor3f(0.0,0.0,0.0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(displayPoint);
    glutMainLoop();

    return 0;
}
