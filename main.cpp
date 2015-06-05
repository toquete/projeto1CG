#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define LINHA_DDA 1
#define LINHA_BRES 2
#define CIRC_BRES 3
#define REPEAT 100000000

int X1, Y1, X2, Y2, raio;
clock_t tempo;

float arredonda(float valor)
{
  return floor(valor + 0.5);
}

void definePontosReta()
{
  printf("Entre com os dois pontos da reta:\n");
  printf("\nPonto 1: \n");
  printf("\nX1:  ");
  scanf("%d", &X1);
  printf("\nY1:  ");
  scanf("%d", &Y1);

  printf("\nPonto 2: \n");
  printf("\nX2: ");
  scanf("%d", &X2);
  printf("\nY2: ");
  scanf("%d", &Y2);
}

void definePontosCirc()
{
  printf("Entre com as coordenadas do centro o tamanho do raio da circunferência:\n");
  printf("\nX:  ");
  scanf("%d", &X1);
  printf("\nY:  ");
  scanf("%d", &Y1);
  printf("\nRaio:  ");
  scanf("%d", &raio);
}

void linhaDDA()
{
  int dx, dy, iter, k;
  float x_inc, y_inc, x, y;

  dx = X2 - X1;
  dy = Y2 - Y1;
  if (abs(dx) > abs(dy))
    iter = abs(dx);
  else
    iter = abs(dy);
  x_inc = dx/iter;
  y_inc = dy/iter;
  x = X1;
  y = Y1;

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  glVertex2i(arredonda(x), arredonda(y));
  for(k = 0; k < iter; k++)
  {
    x += x_inc;
    y += y_inc;
    glVertex2i(arredonda(x), arredonda(y));
  }
  glEnd();
  glFlush();
}

void inicializaCores()
{
  glClearColor(1.0,1.0,1.0,0);// define a cor de fundo da janela (no caso, branco)
  glColor3f(1.0,0.0,0.0);// define cor do traço (no caso, vermelho)
  glPointSize(4.0);// define espessura do traço
  gluOrtho2D(0 , 640 , 0 , 480);
}

void inicializaOpenGL()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Define o modo inicial de apresentação
  glutInitWindowPosition(0,0); // Define a posição inicial da tela a ser apresentada
  glutInitWindowSize(640,480); // Define o tamanho da tela a ser apresentada
}

void dda()
{
  definePontosReta();
  inicializaOpenGL();
  glutCreateWindow("Reta Gerada Pelo Algoritmo DDA"); //Cria a janela com o nome indicado por parâmetro
  inicializaCores();
  tempo = clock();
  for(int i = 0; i < REPEAT; i++)
    glutDisplayFunc(linhaDDA);//chamada do algoritmo
  tempo = clock() - tempo;
  printf("O tempo de execucao do algoritmo foi de %fs\n", ((float)tempo)/CLOCKS_PER_SEC);
  glutMainLoop();//mantém a linha sendo mostrada enquanto o programa estiver rodando
}

void linhaBresenham()
{
  int dx, dy, d, const1, const2, x, y, xFinal;

  dx = abs(X2 - X1);
  dy = abs(Y2 - Y1);
  d = 2 * dy - dx;
  const1 = 2 * dy;
  const2 = 2 * (dy - dx);

  if (X1 > X2)
  {
    x = X2;
    y = Y2;
    xFinal = X1;
  }
  else
  {
    x = X1;
    y = Y2;
    xFinal = X2;
  }

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  while(x < xFinal)
  {
    x++;
    if(d < 0)
      d += const1;
    else
    {
      y++;
      d += const2;
    }
   glVertex2i(x, y);
  }
  glEnd();
  glFlush();
}

void desenhaPontosCirc(int x, int y)
{
  glVertex2i(X1 + x, Y1 + y);
  glVertex2i(X1 + y, Y1 + x);
  glVertex2i(X1 + y, Y1 - x);
  glVertex2i(X1 + x, Y1 - y);
  glVertex2i(X1 - x, Y1 - y);
  glVertex2i(X1 - y, Y1 - x);
  glVertex2i(X1 - y, Y1 + x);
  glVertex2i(X1 - x, Y1 + y);
}

void circBresenham()
{
  int x, y, d;

  x = 0;
  y = raio;
  d = 1 - raio;

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  desenhaPontosCirc(x, y);
  while(x < y)
  {
    if (d < 0)
      d = d + 2 * x + 3;
    else
    {
      d = d + 2 * (x - y) + 5;
      y--;
    }
    x++;
    desenhaPontosCirc(x, y);
  }
  glEnd();
  glFlush();
}

void bresenhamLinha()
{
  definePontosReta();
  inicializaOpenGL();
  glutCreateWindow("Reta Gerada Pelo Algoritmo Bresenham"); //Cria a janela com o nome indicado por parâmetro
  inicializaCores();
  tempo = clock();
  for(int i = 0; i < REPEAT; i++)
    glutDisplayFunc(linhaBresenham);//chamada do algoritmo
  tempo = clock() - tempo;
  printf("O tempo de execucao do algoritmo foi de %fs\n", ((float)tempo)/CLOCKS_PER_SEC);
  glutMainLoop();//mantém a linha sendo mostrada enquanto o programa estiver rodando
}

void bresenhamCirc()
{
  definePontosCirc();
  inicializaOpenGL();
  glutCreateWindow("Circunferência Gerada pelo Algoritmo Bresenham");
  inicializaCores();
  tempo = clock();
  for(int i = 0; i < REPEAT; i++)
    glutDisplayFunc(circBresenham);
  tempo = clock() - tempo;
  printf("O tempo de execucao do algoritmo foi de %fs\n", ((float)tempo)/CLOCKS_PER_SEC);
  glutMainLoop();
}

void validaOpcao(int op)
{
  switch (op){
    case LINHA_DDA:
      dda();
      break;
    case LINHA_BRES:
      bresenhamLinha();
      break;
    case CIRC_BRES:
      bresenhamCirc();
      break;
    case 0:
      break;
  }
}

int menu()
{
  int opcao;

  printf("-----------------------------------------------------\n");
  printf("                       MENU                          \n");
  printf("-----------------------------------------------------\n");
  printf("1 - DDA\n");
  printf("2 - Bresenham para Retas\n");
  printf("3 - Bresenham para Circunferencias\n");
  printf("0 - Sair");

  printf("\nEscolha a opcao: \n");
  scanf("%d",&opcao);
  return opcao;
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
