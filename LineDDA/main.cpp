#include <GL/glut.h>
#include <iostream>
using namespace std;

int x1, y1, x2, y2;

int ROUND_Num(float a)
{
    return (int)(a + 0.5);
}

void draw_objects(int xa, int ya, int xb, int yb)
{

    int dx, dy, steps;
    dx = xb - xa;
    dy = yb - ya;

    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float xinc, yinc;

    xinc = dx / (float)(steps);
    yinc = dy / (float)(steps);

    int i;
    float x = xa, y = ya;
    glVertex2d(xa, ya);
    for (i = 0; i < steps; i++)
    {
        x = x + xinc;
        y = y + yinc;
        glVertex2d(ROUND_Num(x), ROUND_Num(y));
    }
}

void LineDDA()
{
    glClear(GL_COLOR_BUFFER_BIT); // clear buffers to create values
    glBegin(GL_POINTS);
    draw_objects(x1, y1, x2, y1);
    draw_objects(x2, y1, x2, y2);
    draw_objects(x2, y2, x1, y2);
    draw_objects(x1, y2, x1, y1);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{

    cout << "\nFirst:";
    cin >> x1 >> y1;
    cout << "\nSecond:";
    cin >> x2 >> y2;

    glutInit(&argc, argv);                        // Initialise the GLUT Library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set the initial display mode
    glutInitWindowSize(640, 480);                 // Set initial position and size
    glutInitWindowPosition(0, 0);                 // Set initial position from point
    glutCreateWindow("My First OpenGL Program!"); // Name of the window
    glClearColor(1.0, 1.0, 1.0, 0.0);             // Set clear colour to white
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // set fill color black
    glutDisplayFunc(LineDDA);           // call the display function
    glutMainLoop();                     // keep displaying until the progrsm is closed
    return 0;
}
