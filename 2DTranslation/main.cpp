#include <iostream>
#include<GL/glut.h>
#include<cmath>

using namespace std;


int x1,Y1,x2,y2;
int v, tx, ty;

int input[3][10], output[3][10], t[3][3];

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

void mul(int input[3][10], int t[3][3], int output[3][10])
{
	int i,j,k;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < v; j++)
		{
			output[i][j] = 0;
			for(k = 0; k < 3; k++)
			{
				output[i][j] = output[i][j] + t[i][k] * input[k][j];
			}
		}
	}

	output[0][i] = output[0][0];
	output[1][i] = output[1][0];
}



void Draw()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	for(int m = 0; m < 3; m++)
	{
		for(int n = 0; n < 3; n++)
		{
			if(m == n)
			{
				t[m][n] = 1;
			}
			else
			{
				t[m][n] = 0;
			}
			t[0][2] = tx;
			t[1][2] = ty;
		}
	}


	mul(input, t, output);

	for(i = 0; i < v; i++)
    {
		DDALine(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
	}

	glColor3f(1.0,0.0,0.0);


	for(i = 0; i < v; i++)
	{
		DDALine(output[0][i],output[1][i],output[0][i+1],output[1][i+1]);
	}

}

int main(int argc, char** argv) {


	cout<<"\nVerices:";
	cin>>v;

	int i,j;

	for(i = 0; i < v; i++)
	{
			cout<<"\nx:";
			cin>>input[0][i];
			cout<<"\ny:";
			cin>>input[1][i];
			input[2][i] = 1;
	}

	input[0][i] = input[0][0];
	input[1][i] = input[1][0];

    cout<<"\ntx:";
    cin>>tx;
    cout<<"\nty:";
    cin>>ty;


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
