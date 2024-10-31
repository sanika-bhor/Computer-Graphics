#include <iostream>
#include<GL/glut.h>
#include<cmath>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int x1,Y1,x2,y2;

int xc,yc,r;

int ROUND(float a)
{
	return (int) (a + 0.5);
}

void DDALine(int xa, int ya, int xb, int yb)
{
	int dx,dy,steps;

	dx = xb - xa;
	dy = yb - ya;

	if(abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	float xinc, yinc;

	xinc = dx / (float)(steps);
	yinc = dy / (float(steps));

	float x = xa, y = ya;


	glBegin(GL_POINTS);
	glVertex2d(xa, ya);

	for(int i = 0; i < steps; i++)
	{
		x = x + xinc;
		y = y + yinc;
		glVertex2d(ROUND(x),ROUND(y));
	}

	glEnd();
	glFlush();

}

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
	//glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_POINTS);
	//glVertex2d(200,200);
	glClear(GL_COLOR_BUFFER_BIT);
	/*DDALine(x1,Y1,x2,Y1);
	DDALine(x2,Y1,x2,y2);
	DDALine(x2,y2,x1,y2);
	DDALine(x1,y2,x1,Y1);
	DDALine((x1+x2)/2,Y1,x2,(Y1+y2)/2);
	DDALine(x2,(Y1+y2)/2,(x1+x2)/2,y2);
	DDALine((x1+x2)/2,y2,x1,(Y1+y2)/2);
	DDALine(x1,(Y1+y2)/2,(x1+x2)/2,Y1);

	int r = (x2 - x1)*(y2 - Y1)/(2*sqrt((x2-x1)*(x2-x1) + (y2-Y1)*(y2-Y1)));
	bresCir((x1+x2)/2,(Y1+y2)/2,r);*/
	int xa=xc;
	int ya=yc+r;
	int xb=xc-(r*sqrt(3)/2);
	int yb= yc-r/2;
	int xcc=xc+(r*sqrt(3)/2);
	int ycc= yc-r/2;
	bresCir(xc,yc,r);
	bresCir(xc,yc,r/2);

	DDALine(xa,ya,xb,yb);
	DDALine(xb,yb,xcc,ycc);
	DDALine(xcc,ycc,xa,ya);

	//glEnd();
	//glFlush();
}

int main(int argc, char** argv) {

    /*cout<<"\nFirst:";
	cin>>x1>>Y1;

	cout<<"\nSecond:";
	cin>>x2>>y2;*/

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

