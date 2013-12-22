#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <windows.h>

#define DEBUG 1

/* VARIÁVEIS GLOBAIS */

typedef struct {
	GLboolean   doubleBuffer;
	/*GLint       delay;*/
}Estado;

typedef struct {
	int player;
	int computador;
	int start_game;
	int win;
}Jogo;

typedef struct {
	// variaveis de rato: Win = windows size, mouse = posicao rato
	int mouse_x, mouse_y, Win_x, Win_y, object_select;
}Rato;

// alinhamento das caixas, quando se ganha
// 8 possibilidades, 3 na vertical, 3 na horizontal and 2 na diagonal
//
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
//

static int caixa[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 },
{ 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };

static int mapa_caixa[9];
// centro x,y da localização para cada caixa
static int mapa_objeto[9][2] = { { -6, 6 }, { 0, 6 }, { 6, 6 }, { -6, 0 }, { 0, 0 }, { 6, 0 }, { -6, -6 }, { 0, -6 }, { 6, -6 } };

Jogo jogo;
Rato rato;
Estado estado;

GLUquadricObj *cylinder;
//Modelo modelo;


/* Inicialização do ambiente OPENGL */
void Init(void)
{
	glClearColor(1, 1, 1, 0.0);

	jogo.start_game = 0;
	jogo.win = 0;

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricOrientation(cylinder, GLU_OUTSIDE);

}

void init_game(){
	for (int i = 0; i < 9; i++)
	{
		mapa_caixa[i] = 0;
	}

	jogo.win = 0;
	jogo.start_game = 1;
}

/**************************************
***  callbacks de janela/desenho    ***
**************************************/

// CALLBACK PARA REDIMENSIONAR JANELA

void Reshape(int width, int height)
{
	rato.Win_x = width;
	rato.Win_y = height;
	GLint size;
	GLfloat ratio = (GLfloat)width / height;
	GLfloat ratio1 = (GLfloat)height / width;

	if (width < height)
		size = width;
	else
		size = height;

	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL

	//glViewport(0, 0, (GLint) size, (GLint) size);
	glViewport(0, 0, width, height);


	// Matriz Projecção
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluOrtho2D(left,right,bottom,top); 
	// projeccao ortogonal 2D, com profundidade (Z) entre -1 e 1
	if (width < height)
		gluOrtho2D(-9, 9, -9 * ratio1, 9 * ratio1);
	else
		gluOrtho2D(-9 * ratio, 9 * ratio, -9, 9);

	// Matriz Modelview
	// Matriz onde são realizadas as tranformações dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// verifica se faz linha
// return 1 se houver vencedor
int movimentos(void)
{

	int i, t = 0;

	//verifica se faz linha
	for (i = 0; i < 8; i++)
	{
		t = mapa_caixa[caixa[i][0]] + mapa_caixa[caixa[i][1]] + mapa_caixa[caixa[i][2]];
		if ((t == 3) || (t == -3))
		{
			return(1);
		}
	}
	t = 0;
	// verifica se ha empate
	for (i = 0; i < 8; i++)
	{
		t = t + abs(mapa_caixa[caixa[i][0]]) + abs(mapa_caixa[caixa[i][1]]) + abs(mapa_caixa[caixa[i][2]]);
	}

	if (t == 24) return(2);

	return(0);
}

// verifca se e preciso bloquear
int bloquear(void)
{
	int i, t;
	for (i = 0; i < 8; i++)
	{
		t = mapa_caixa[caixa[i][0]] + mapa_caixa[caixa[i][1]] + mapa_caixa[caixa[i][2]];
		if ((t == 2) || (t == -2))
		{
			if (mapa_caixa[caixa[i][0]] == 0) mapa_caixa[caixa[i][0]] = jogo.computador;
			if (mapa_caixa[caixa[i][1]] == 0) mapa_caixa[caixa[i][1]] = jogo.computador;
			if (mapa_caixa[caixa[i][2]] == 0) mapa_caixa[caixa[i][2]] = jogo.computador;
			return(1);
		}
	}
	return(0);
}

// verifca se pode jogar no canto
int check_cantos(void)
{
	int i;

	if (mapa_caixa[0] == 0)
	{
		mapa_caixa[0] = jogo.computador;
		i = 1;
		return(1);
	}

	if (mapa_caixa[2] == 0)
	{
		mapa_caixa[2] = jogo.computador;
		i = 1;
		return(1);
	}

	if (mapa_caixa[6] == 0)
	{
		mapa_caixa[6] = jogo.computador;
		i = 1;
		return(1);
	}

	if (mapa_caixa[8] == 0)
	{
		mapa_caixa[8] = jogo.computador;
		i = 1;
		return(1);
	}

	return(0);
}

// verifca se ha espaco em linha
int check_linha(void)
{

	if (mapa_caixa[4] == 0)
	{
		mapa_caixa[4] = jogo.computador;
		return(1);
	}

	if (mapa_caixa[1] == 0)
	{
		mapa_caixa[1] = jogo.computador;
		return(1);
	}

	if (mapa_caixa[3] == 0)
	{
		mapa_caixa[3] = jogo.computador;
		return(1);
	}
	if (mapa_caixa[5] == 0)
	{
		mapa_caixa[5] = jogo.computador;
		return(1);
	}
	if (mapa_caixa[7] == 0)
	{
		mapa_caixa[7] = jogo.computador;
		return(1);
	}

	return(0);
}

// movimentos do pc
int computer_move()
{
	if (bloquear() == 1) return(1);
	if (check_cantos() == 1) return(1);
	if (check_linha() == 1) return(1);

	return(0);
}

// é usada para escrever no ecra
void imprimir(int x, int y, char *st)
{
	int tam, i;

	tam = strlen(st); // tamanho da string
	glRasterPos2i(x, y); // coordenadas para começar a escrever
	for (i = 0; i < tam; i++)  // loop para imprimir char
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // imprimir para o ecra
	}

}

void mensagem_inicio(){
	glPushMatrix();
	glColor3f(1, 0.0, 0.0);
	imprimir(-4, 4, "Jogo do Galo");
	imprimir(-4, -1, "Para começar: ");
	imprimir(-4, -2, "botao direito: X's");
	imprimir(-4, -3, "botao esquerdo: O's");
	glPopMatrix();
}

void mensagem_final(int win){
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	if (win == 1) imprimir(-2, 1, "Ganhou!!!");
	if (win == -1) imprimir(-2, 1, "Perdeu...");
	if (win == 2) imprimir(-2, 1, "Empate...");
	glPopMatrix();
}


// ... definição das rotinas auxiliares de desenho ...

void desenhagrelha(void){
	for (int ix = 0; ix < 4; ix++)
	{
		glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2i(-9, -9 + ix * 6);
		glVertex2i(9, -9 + ix * 6);
		glEnd();
		glPopMatrix();
	}

	for (int iy = 0; iy < 4; iy++)
	{
		glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2i(-9 + iy * 6, 9);
		glVertex2i(-9 + iy * 6, -9);
		glEnd();
		glPopMatrix();
	}
}

void desenhaO(int x, int y, int z){
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(x, y, z);
	glutSolidTorus(0.5, 2.0, 8, 16);
	glPopMatrix();
}

void desenhaX(int x, int y, int z){
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glTranslatef(0, 0, -3);
	gluCylinder(cylinder, 0.5, 0.5, 6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(90, 0, 1, 0);
	glRotatef(315, 1, 0, 0);
	glTranslatef(0, 0, -3);
	gluCylinder(cylinder, 0.5, 0.5, 6, 16, 16);
	glPopMatrix();

	glPopMatrix();
}

// Callback de desenho

void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// ... chamada das rotinas auxiliares de desenho ...

	desenhagrelha();

	if (jogo.start_game == 0 && jogo.win == 0)
	{
		mensagem_inicio();
	}

	for (int i = 0; i < 9; i++)
	{
		if (mapa_caixa[i] == 1)
		{
			desenhaX(mapa_objeto[i][0], mapa_objeto[i][1], -1);
		}
		if (mapa_caixa[i] == -1)
		{
			desenhaO(mapa_objeto[i][0], mapa_objeto[i][1], -1);
		}
	}

	if (jogo.win != 0)
	{
		mensagem_final(jogo.win);
	}

	glFlush();
	if (estado.doubleBuffer)
		glutSwapBuffers();

	if (jogo.win != 0)
	{
		Sleep(5000);
		exit(1);
	}
}

/*******************************
***   callbacks timer/idle   ***
*******************************/

// Callback de temporizador (não colocar instruções de desenho aqui...)

void Timer(int value)
{
	// redesenhar o ecrã (invoca o callback de desenho)
	glutPostRedisplay();
	
	glutTimerFunc(10, Timer, 1);
}

/*******************************
*** callbacks de teclado/rato***
*******************************/

void mouse(int button, int state, int x, int y){
	rato.mouse_x = (18 * (float)((float)x / (float)rato.Win_x)) / 6;
	rato.mouse_y = (18 * (float)((float)y / (float)rato.Win_y)) / 6;

	rato.object_select = rato.mouse_x + rato.mouse_y * 3;

	if (jogo.start_game == 0)
	{
		if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		{
			jogo.player = 1;
			jogo.computador = -1;
			init_game();//da se inicio ao jogo
			return;
		}

		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			jogo.player = -1;
			jogo.computador = 1;
			init_game();
			//da se inicio ao jogo
			return;
		}

	}

	if (jogo.start_game == 1)
	{
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			if (jogo.win == 0) //verifica se ainda nao ha vencedores
			{
				if (mapa_caixa[rato.object_select] == 0)//verifica se a caixa ainda nao foi jogada antes
				{
					mapa_caixa[rato.object_select] = jogo.player; //modificar o valor da caixa para o jogador
					jogo.win = movimentos();//verificar se alguem ganhou
					if (jogo.win == 1)//se ganhou acabou
					{
						jogo.start_game = 0;
						return;
					}
					computer_move();//chamar o prolog para o pc jogar
					jogo.win = movimentos();//verificar se ganhou
					if (jogo.win == 1)//se ganhou acabou o jogo
					{
						jogo.win = -1;
						jogo.start_game = 0;
					}
				}
			}
		}
	}

	if (jogo.win == 2)jogo.start_game = 0; //acabou
}

void main(int argc, char **argv)
{
	estado.doubleBuffer = GL_TRUE;  // colocar a GL_TRUE para ligar o Double Buffer

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(300, 300);
	glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
	if (glutCreateWindow("Exemplo") == GL_FALSE)
		exit(1);

	glutSetWindowTitle("Jogo do Galo");

	Init();
	// Registar callbacks do GLUT

	// callbacks de janelas/desenho
	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	// Callbacks de rato
	glutMouseFunc(mouse);

	// callbacks timer
	glutTimerFunc(10, Timer, 1);

	// COMEÇAR...
	glutMainLoop();
}