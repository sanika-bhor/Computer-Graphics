
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

int input[10][2],no;
int x,y;
float bCol[3],fCol[3];

void LineDDA(int xa,int ya,int xb,int yb)
{
  int dx=(xb-xa);
  int dy=(yb-ya);
  int steps;
  float xInc,yInc,x=xa,y=ya;
  /* Find out whether to increment x or y */
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2i(x,y);
  int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    /* printf("%0.6lf %0.6lf\n",floor(x), floor(y)); */
    glVertex2i(floor(x+0.5),floor(y+0.5));
  }
  glEnd();

  glFlush();
}


void Draw_Poly()
{

  int i,j;

  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0,j=1;i<no-1;i++,j++)
  {
   LineDDA(input[i][0],input[i][1],input[j][0],input[j][1]);
  }

   LineDDA(input[i][0],input[i][1],input[0][0],input[0][1]);
}

void boundary_fill(int x, int y, float* fillColor, float* bc)
{
 float color[3];

 glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);

 if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
 color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
 {


  glColor3f(fillColor[0],fillColor[1],fillColor[2]);

  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
  glFlush();

  boundary_fill(x+1,y,fillColor,bc);
  boundary_fill(x-1,y,fillColor,bc);
  boundary_fill(x,y+1,fillColor,bc);
  boundary_fill(x,y-1,fillColor,bc);
 }
}


void P_Fill()
{
  Draw_Poly();
  boundary_fill(x,y,fCol,bCol);
}


void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to Red */
  glColor3f(bCol[0],bCol[1],bCol[2]);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}


int main(int argc, char **argv)
{

  int i;
  printf("\nEnter the number of vertices:");
  scanf("%d",&no);
  int j;
  for(j=0;j<no;j++)
  {
    printf("\nEnter the x coordinate of vertex:");
    scanf("%d",&input[j][0]);
    printf("\nEnter the y cordinate of vertex:");
    scanf("%d",&input[j][1]);
  }

   printf("\nEnter the value of x and y:");
   scanf("%d%d", &x,&y);


   printf("\nAccept Boundary Color:");
   for(i=0;i<3;i++)
   scanf("%f",&bCol[i]);
   printf("\nAccept Fill Color:");
   for(i=0;i<3;i++)
   scanf("%f",&fCol[i]);

/* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("Polygon Filling");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(P_Fill);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
