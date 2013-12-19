#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
using namespace std;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEBUG 1


//-------------------------------------------------------------------------
//  Variaveis Globais
//------------------------------------------------------------------------
typedef struct {
	GLboolean   doubleBuffer;
	GLint       delay;
}Estado;

typedef struct {
	GLfloat   cabecaX;
	GLfloat   cabecaY;
	GLfloat	  cabecaRaio;
}Enforcado;

Estado estado;
Enforcado enforcado;

//-------------------------------------------------------------------------
//  Inicialização das variaveis
//-------------------------------------------------------------------------
void Init(void)
{
	enforcado.cabecaX = 0;
	enforcado.cabecaY = 0;
	enforcado.cabecaRaio = 0.1;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

}

//-------------------------------------------------------------------------
//  Callback para redimensionar janela
//------------------------------------------------------------------------
void Reshape(int width, int height)
{
	GLint size;

	if (width < height)
		size = width;
	else
		size = height;

	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL

	glViewport(0, 0, (GLint)size, (GLint)size);


	// Matriz Projecção
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluOrtho2D(left,right,bottom,top); 
	// projecção ortogonal 2D, com profundidade (Z) entre -1 e 1
	gluOrtho2D(-1, 1, -1, 1);

	// Matriz Modelview
	// Matriz onde são realizadas as tranformacões dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//-------------------------------------------------------------------------
//  Desenhar string em coordenadas especificadas
//-------------------------------------------------------------------------
void printWord(float x, float y, float z, char* text)
{
	//  Difrentes fonts:
	//  GLUT_BITMAP_8_BY_13, 
	//  GLUT_BITMAP_9_BY_15,
	//	GLUT_BITMAP_TIMES_ROMAN_10, 
	//  GLUT_BITMAP_TIMES_ROMAN_24,
	//	GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12,
	//	GLUT_BITMAP_HELVETICA_18.
	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	int strlength;
	strlength = strlen(text); // Tamanho do texto

	glRasterPos3f(x, y, z); // Posicionamento

	// Imprimir caracteres um a um
	for (int i = 0; i <= strlength; i++){
		glutBitmapCharacter(font_style, text[i]);
	}
}

//-------------------------------------------------------------------------
//  Desenhar cabeca
//-------------------------------------------------------------------------
void desenhaCabeca()
{
	GLfloat x = enforcado.cabecaX;
	GLfloat y = enforcado.cabecaY;
	GLfloat raio = enforcado.cabecaRaio;
	GLint numLados = 30;
	GLfloat ang = 2 * M_PI / numLados;
	GLint i;

	glLineWidth(1 * raio);

	ang = 2 * M_PI / 60;
	glBegin(GL_LINES);
	for (i = 0; i<60; i++)
	{
		glVertex2f(x + raio*cos(ang*i), y + raio*sin(ang*i));
		glVertex2f(x + raio*cos(ang*i + 0.1), y + raio*sin(ang*i + 0.1));
	}
	glEnd();
}

//-------------------------------------------------------------------------
//  Callback de desenho
//-------------------------------------------------------------------------
void Draw(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	desenhaCabeca();

	printWord(-1, -1, 0, "Hello World");

	glFlush();
	if (estado.doubleBuffer)
		glutSwapBuffers();

}

//-------------------------------------------------------------------------
//  Callback de temporizador
//-------------------------------------------------------------------------
void Timer(int value)
{

	// redesenhar o ecra 
	glutPostRedisplay();
}

//-------------------------------------------------------------------------
//  Consola ajuda
//-------------------------------------------------------------------------
void imprime_ajuda(void)
{
	printf("\n\nTexto de ajuda...\n");
	printf("\n\nH -> Help\n");

}

//-------------------------------------------------------------------------
//  Callback de teclado
//-------------------------------------------------------------------------
void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
	case 'h':
	case 'H':
		imprime_ajuda();
		break;
	}

	if (DEBUG)
		printf("Carregou na tecla %c\n", key);

}


int main(int argc, char **argv)
{
	estado.doubleBuffer = GL_TRUE;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);



	glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
	if (glutCreateWindow("Jogo Do Enforcado") == GL_FALSE)
		exit(1);

	Init();
	imprime_ajuda();

	// Registar callbacks do GLUT
	// callbacks de janelas/desenho
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);

	// Callbacks de teclado
	glutKeyboardFunc(Key);
	//glutKeyboardUpFunc(KeyUp);
	//glutSpecialFunc(SpecialKey);
	//glutSpecialFunc(SpecialKeyUp);

	// callbacks timer/idle
	glutTimerFunc(estado.delay, Timer, 0);
	//glutIdleFunc(Idle);


	// COMECAR...
	glutMainLoop();

	return 0;
}