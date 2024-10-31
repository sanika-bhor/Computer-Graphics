#include <iostream>
#include<GL/glut.h>
using namespace std;

int xc,yc,r;

void bresCir(int xc, int yc, int r)
{
	int x, y, d;
	x = 0;
	y = r;
	d = 3- 2*r;

	do
	{
		glBegin(GL_POINTS);
		glVertex2d(xc+y, yc+x);
		glVertex2d(xc+x, yc+y);
		glVertex2d(xc+x, yc-y);
		glVertex2d(xc+y, yc-x);
		glVertex2d(xc-y, yc-x);
		glVertex2d(xc-x, yc-y);
		glVertex2d(xc-x, yc+y);
		glVertex2d(xc-y, yc+x);
		glEnd();
		glFlush();

		if(d < 0)
		{
			x = x + 1;
			d = d + 4 * x + 6;
		}
		else
		{
			x = x + 1;
			y = y - 1;
			d = d + 4 * x - 4 * y + 10;
		}
	}while( x <= y);
}



void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	bresCir(xc,yc,r);
}


int main(int argc, char** argv) {

	cout<<"\nCenter:";
	cin>>xc>>yc;
	cout<<"\nRadius:";
	cin>>r;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Pattern");
	glClearColor(1.0,1.0,1.0,0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
