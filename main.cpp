#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double X1, Y1, X2, Y2;

float round_value(float v)
{
  return floor(v + 0.5);
}

void LineDDA()
{
  double dx=(X2-X1);
  double dy=(Y2-Y1);
  double steps;
  float xInc,yInc,x=X1,y=Y1;
  /* Find out whether to increment x or y */
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2d(x,y);
  int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    /* printf("%0.6lf %0.6lf\n",floor(x), floor(y)); */
    glVertex2d(round_value(x), round_value(y));
  }
  glEnd();

  glFlush();
}
void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}
int DDA()
{

  printf("Entre com os dois pontos da reta:\n");
  printf("\nPonto 1: \n");
  printf("\nX1:  ");
  scanf("%lf",&X1);
  printf("\nY1:  ");
  scanf("%lf",&Y1);

  printf("\nPonto 2: \n");
  printf("\nX2: ");
  scanf("%lf",&X2);
  printf("\nY2: ");
  scanf("%lf",&Y2);

  /* Initialise GLUT library */
  //glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("Reta Gerada Pelo Algoritmo DDA");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(LineDDA);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}

void validaOpcao(int op){

    switch (op){
        case 1:
            DDA();
            break;

        case 0:
            break;
    }
}

int menu(){

    int opcao;

    printf("-----------------------------------------------------\n");
    printf("                       MENU                          \n");
    printf("-----------------------------------------------------\n");
    printf("1 - DDA\n");
    printf("0 - Sair");

    printf("\nEscolha a opcao: \n");
    scanf("%d",&opcao);
}

int main(int argc, char **argv)
{
    int op;

    glutInit(&argc,argv);

    do{
        op = menu();
        validaOpcao(op);
    }while(op != 0);

    return 0;
}
