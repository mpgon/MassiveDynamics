#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <SWI-cpp.h>

#ifdef __APPLE__
#include <glut.h>
#else
#include <GL\glut.h>
#endif

#ifdef _WIN32
#include <GL\GLAux.h>
#endif

#include "mathlib.h"
#include "studio.h"
#include "mdlviewer.h"

#pragma comment (lib, "glaux.lib")    /* link with Win32 GLAUX lib usada para ler bitmaps */

using namespace std;

// função para ler jpegs do ficheiro readjpeg.c
extern "C" int read_JPEG_file(const char *, char **, int *, int *, int *);

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define	GAP					        25

#define HEIGHT_20					20
#define HEIGHT_30					30
#define HEIGHT_40					40
#define WIDTH_20					21
#define WIDTH_30					31
#define WIDTH_40					41

#define OBJECTO_FAT			      0.175
#define	OBJECTO_ALTURA		      0.4
#define OBJECTO_VELOCIDADE	      0.05
#define OBJECTO_ROTACAO		        5
#define OBJECTO_RAIO		      0.12
#define SCALE_HOMER               0.005
#define EYE_ROTACAO			        1
#define DIST_CAM					1
#define ALTURA_CAM					0.5

#define ALT_OLHOS					0.4

#ifdef _WIN32
#define NOME_TEXTURA_CUBOS        "Textura.bmp"
#else
#define NOME_TEXTURA_CUBOS        "Textura.jpg"
#endif

#define NOME_TEXTURA_CHAO         "Chao.jpg"


#define NUM_TEXTURAS              2
#define ID_TEXTURA_CUBOS          0
#define ID_TEXTURA_CHAO           1

#define NUM_JANELAS               2
#define JANELA_TOP                0
#define JANELA_NAVIGATE           1

typedef struct teclas_t{
	GLboolean   up, down, left, right,F1;
}teclas_t;

typedef struct pos_t{
	GLfloat    x, y, z;
}pos_t;

typedef struct objecto_t{
	pos_t    pos;
	GLfloat  dir;
	GLfloat  vel;
}objecto_t;

typedef struct camera_t{
	pos_t    eye;
	GLfloat  dir_long;  // longitude olhar (esq-dir)
	GLfloat  dir_lat;   // latitude olhar	(cima-baixo)
	GLfloat  fov;
}camera_t;

typedef struct ESTADO{
	camera_t      camera;
	GLint         timer;
	GLint         mainWindow, topSubwindow, navigateSubwindow;
	teclas_t      teclas;
	GLboolean     localViewer;
	GLuint        vista[NUM_JANELAS];
	GLuint		  contaAnimaCair;
}ESTADO;

typedef struct MODELO{
	GLuint        texID[NUM_JANELAS][NUM_TEXTURAS];
	GLuint        labirinto[NUM_JANELAS];
	GLuint        chao[NUM_JANELAS];
	objecto_t	    objecto;
	GLuint        xMouse;
	GLuint        yMouse;
	StudioModel   homer[NUM_JANELAS];   // Modelo Homer
	GLboolean     andar;
	GLuint        prev;
}MODELO;

/////////////////////////////////////
//variaveis globais

ESTADO estado;
MODELO modelo;

GLuint time1 = 0;
char * tempo = new char[10];
int flagJogo = 0 ; // Usado para determinar vitÛria ou derrota no desafio. 1 - VitÛria; 2 - Derrota.
int vidas = 5; //N˙mero de vidas do boneco
char * vida = new char[1];
int flagDificuldade = 1; //Usado para definir grau de dificuldade do jogo
int chaoConst = 0;

string test[] = {""};

char buffer1[10];
char buffer2[10];

char* file[] = { "libswipl.dll", "-s", "labirinto20.pl", NULL };

char mazedata20[HEIGHT_20][WIDTH_20] = {
	"                    ",
	" ****************** ",
	" *+               * ",
	" *** * *** *      * ",
	" * ** **  * *** *** ",
	" *     *          * ",
	" *          * *   * ",
	" *   ***     *    * ",
	" *     * *** ****** ",
	" * *   *   *      * ",
	" *   * **  *      * ",
	" *** ****  ****   * ",
	" *            *   * ",
	" *     *      *   * ",
	" ** ** *    ***   * ",
	" *   *            * ",
	" ** ** *  * *  *  * ",
	" ***       *  *   * ",
	" ****************** ",
	"                    ",
};

char mazedata30[HEIGHT_30][WIDTH_30] = {
	"                              ",
	" **************************** ",
	" *+     ****       *      * * ",
	" ***** ****** ****** ****** * ",
	" ** **  * ***  **           * ",
	" *  **    **  **   ********** ",
	" *                *         * ",
	" ******** ******  ** ******** ",
	" * *        *               * ",
	" * ***** *    *  **** *  *  * ",
	" *     * ***  * ****** * **** ",
	" * *** *      *             * ",
	" * * * *      **** ****** *** ",
	" *** *   ***   **  **  *    * ",
	" * *    ****          ***   * ",
	" * ********** ******  ***   * ",
	" *       *   *   **    ***  * ",
	" * *** *  ** ** * ****  *   * ",
	" *    *   *   *         * *** ",
	" *   *    * ****   *    *   * ",
	" ** *         * *** *** *** * ",
	" ** * * * *****          ** * ",
	" **  *    * **** ** *  **** * ",
	" *  *     *  **  *  ** ***  * ",
	" *   **      * *    *       * ",
	" *  *     * **   * ******   * ",
	" *  ***   ** * * * ** * *** * ",
	" *    **                *** * ",
	" **************************** ",
	"                              ",
};

char mazedata40[HEIGHT_40][WIDTH_40] = {
	"                                        ",
	" ************************************** ",
	" *+        *       *    * *           * ",
	" ***  **** *  **** **** * * ********* * ",
	" * ** **  *  ****  ** *      ******* ** ",
	" *  *  *        *  ** ****** **** *   * ",
	" *          * * *   * * * **   ** *** * ",
	" *   ***  *  **                       * ",
	" *  ** * * **** **** ******  *** ****** ",
	" *     *  **           *     *        * ",
	" *   * **  ***  * * * **     ******** * ",
	" *** **** ***** ********     *        * ",
	" **          **          ****** ******* ",
	" *  *  ****   **** ***** **  **       * ",
	" ** ** *    ***  **       *   ******* * ",
	" *   *       *      *******        ** * ",
	" ** ** * ** *  *    **      *** ****  * ",
	" ***   *   ** *      *  ***           * ",
	" *      *  *     *****  *   *****  **** ",
	" * ******  *     *      *   ***    *  * ",
	" *   ***** ***** ********   ****   *  * ",
	" *   ** *  **           ** *** *   ** * ",
	" **     *   *     *****        ***  * * ",
	" *  *****   *     *   *******  **   * * ",
	" *  ** *    *******               *** * ",
	" *  *  *              ******  *****   * ",
	" *     ****** **** ** * *     *       * ",
	" *  *       *   *********   *     *** * ",
	" *  ****    *   **      *  **  **   * * ",
	" *   **  *  *              *  ******  * ",
	" *  *   **       ******   *** **  * * * ",
	" *  *  **  ***** *       **       * *** ",
	" *    ****    *  *  **** ******     * * ",
	" *      ** * **  ** *                 * ",
	" *   *****   *   ****    *** ********** ",
	" *  **   *****      *      *        * * ",
	" * ****      **** **********   **** * * ",
	" *    *                               * ",
	" ************************************** ",
	"                                        ",
};

void insertProlog(int x1, int z1, int x2, int z2){

	PlTermv av(2);

	sprintf_s(buffer1, "(%d,%d)", x1,z1);
	sprintf_s(buffer2, "(%d,%d)", x2, z2);

	av[0] = PlCompound(buffer1);
	av[1] = PlCompound(buffer2);

	PlQuery q("criarBaseConhecimento", av);

	  

}

void assertInProlog(int height, int width){

	int coordzTemp = 0;
	int coordxTemp = 0;
	int valorKeep = 0;

	int coordx1 = 0;
	int coordz1 = 0;
	int coordx2 = 0;
	int coordz2 = 0;

	PlEngine e(3, file);

	switch (flagDificuldade){
	case 1:
		coordzTemp = -9;
		valorKeep = -8;
		break;
	case 2:
		coordzTemp = -14;
		valorKeep = -14;
		break;
	case 3:
		break;
	}

	for (int i = 2; i < height - 3; i++)
	{
		coordzTemp += 1;
		coordxTemp = valorKeep;
		for (int j = 2; j < width - 3; j++)
		{
			coordxTemp += 1;
			if (flagDificuldade == 1){
				if (mazedata20[i][j - 1] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp - 1;
					coordz2 = coordzTemp;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata20[i][j + 1] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp + 1;
					coordz2 = coordzTemp;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata20[i - 1][j] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp;
					coordz2 = coordzTemp - 1;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata20[i + 1][j] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp;
					coordz2 = coordzTemp + 1;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
			}
			else if (flagDificuldade == 2){
				if (mazedata30[i][j - 1] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp - 1;
					coordz2 = coordzTemp;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata30[i][j + 1] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp + 1;
					coordz2 = coordzTemp;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata30[i - 1][j] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp;
					coordz2 = coordzTemp - 1;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata30[i + 1][j] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp;
					coordz2 = coordzTemp + 1;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
			}
			else{
				if (mazedata40[i][j - 1] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp - 1;
					coordz2 = coordzTemp;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata40[i][j + 1] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp + 1;
					coordz2 = coordzTemp;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata40[i - 1][j] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp;
					coordz2 = coordzTemp - 1;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
				if (mazedata40[i + 1][j] != '*'){
					coordx1 = coordxTemp;
					coordz1 = coordzTemp;
					coordx2 = coordxTemp;
					coordz2 = coordzTemp + 1;
					insertProlog(coordx1, coordz1, coordx2, coordz2);
				}
			}
		}
	}

}

int criaBaseConhecimento(){

	switch (flagDificuldade){
		case 1:
			assertInProlog(HEIGHT_20, WIDTH_20);
			break;
		case 2:
			assertInProlog(HEIGHT_30, WIDTH_30);
			break;
		case 3:
			assertInProlog(HEIGHT_40, WIDTH_40);
			break;
	}

	/*sprintf_s(buffer, "caminho(%d,%d,%d,%d)", coordx1, coordz1, coordx2, coordz2);
	av[0] = PlCompound(buffer);
	
	PlQuery q("criarBaseConhecimento", av);*/

	return (1);
}

////////////////////////////////////
/// IluminaÁ„o e materiais


void setLight()
{
	GLfloat light_pos[4] = { -5.0, 20.0, -8.0, 0.0 };
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	// ligar iluminaÁ„o

	glEnable(GL_LIGHTING);

	// ligar e definir fonte de luz 0
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.localViewer);
}

void setMaterial()
{
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_shininess = 104;

	// criaÁ„o autom·tica das componentes Ambiente e Difusa do material a partir das cores
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// definir de outros par‚metros dos materiais est·ticamente
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}


///////////////////////////////////
//// Redisplays

void redisplayTopSubwindow(int width, int height)
{

	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL
	glViewport(0, 0, (GLint)width, (GLint)height);
	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / height, .5, 100);
	// Matriz Modelview
	// Matriz onde s„o realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	
}


void reshapeNavigateSubwindow(int width, int height)
{
	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL
	glViewport(0, 0, (GLint)width, (GLint)height);
	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(estado.camera.fov, (GLfloat)width / height, 0.1, 50);
	// Matriz Modelview
	// Matriz onde s„o realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
}

void reshapeMainWindow(int width, int height)
{
	GLint w, h;
	w = (width - GAP * 3)*.5;
	h = (height - GAP * 2);
	glutSetWindow(estado.topSubwindow);
	glutPositionWindow(GAP, GAP);
	glutReshapeWindow(w, h);
	glutSetWindow(estado.navigateSubwindow);
	glutPositionWindow(GAP + w + GAP, GAP);
	glutReshapeWindow(w, h);

}

void strokeCenterString(char *str, double x, double y, double z, double s)
{
	int i, n;

	n = strlen(str);
	glPushMatrix();
	glTranslated(x - glutStrokeLength(GLUT_STROKE_ROMAN, (const unsigned char*)str)*0.5*s, y - 119.05*0.5*s, z);
	glScaled(s, s, s);
	for (i = 0; i < n; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)str[i]);
	glPopMatrix();

}

/////////////////////////////////////
//Modelo


GLboolean detectaColisao(GLfloat nx, GLfloat nz)
{
	if (flagDificuldade == 1){
		int l = nz + HEIGHT_20 / 2.0 + 0.5;
		int c = nx + WIDTH_20 / 2.0 + 0.5;

		if (mazedata20[l][c] == '*'){
			return GL_TRUE;
		}
	}
	else if (flagDificuldade == 2){
		int l = nz + HEIGHT_30 / 2.0 + 0.5;
		int c = nx + WIDTH_30 / 2.0 + 0.5;

		if (mazedata30[l][c] == '*'){
			return GL_TRUE;
		}
	}
	else{
		int l = nz + HEIGHT_40 / 2.0 + 0.5;
		int c = nx + WIDTH_40 / 2.0 + 0.5;

		if (mazedata40[l][c] == '*'){
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}

GLboolean detectaColisaoEstrela(GLfloat nx, GLfloat nz)
{
	if (flagDificuldade == 1){
		int l = nz + HEIGHT_20 / 2.0 + 0.5;
		int c = nx + WIDTH_20 / 2.0 + 0.5;

		if (mazedata20[l][c] == '+'){
			return GL_TRUE;
		}
	}
	else if (flagDificuldade == 2){
		int l = nz + HEIGHT_30 / 2.0 + 0.5;
		int c = nx + WIDTH_30 / 2.0 + 0.5;

		if (mazedata30[l][c] == '+'){
			return GL_TRUE;
		}
	}
	else{
		int l = nz + HEIGHT_40 / 2.0 + 0.5;
		int c = nx + WIDTH_40 / 2.0 + 0.5;

		if (mazedata40[l][c] == '+'){
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}

void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], float s, float t)
{
	glBegin(GL_POLYGON);
	glNormal3fv(normal);
	glTexCoord2f(s, t);
	glVertex3fv(a);
	glTexCoord2f(s, t + 0.25);
	glVertex3fv(b);
	glTexCoord2f(s + 0.25, t + 0.25);
	glVertex3fv(c);
	glTexCoord2f(s + 0.25, t);
	glVertex3fv(d);
	glEnd();
}


void desenhaCubo(GLuint texID)
{
	GLfloat vertices[][3] = { { -0.5, -0.5, -0.5 },
	{ 0.5, -0.5, -0.5 },
	{ 0.5, 0.5, -0.5 },
	{ -0.5, 0.5, -0.5 },
	{ -0.5, -0.5, 0.5 },
	{ 0.5, -0.5, 0.5 },
	{ 0.5, 0.5, 0.5 },
	{ -0.5, 0.5, 0.5 } };
	GLfloat normais[][3] = { { 0, 0, -1 }, //
	{ 0, 0, 1 }, //
	{ -1, 0, 0 }, //
	{ 1, 0, 0 }, //
	{ 0, -1, 0 }, //
	{ 0, 1, 0 } //
	};


	glBindTexture(GL_TEXTURE_2D, texID);

	float s = rand() % 4 * 0.25;
	float t = rand() % 4 * 0.25;

	desenhaPoligono(vertices[1], vertices[0], vertices[3], vertices[2], normais[1], s, t);
	desenhaPoligono(vertices[2], vertices[3], vertices[7], vertices[6], normais[4], s, t);
	desenhaPoligono(vertices[3], vertices[0], vertices[4], vertices[7], normais[2], s, t);
	desenhaPoligono(vertices[6], vertices[5], vertices[1], vertices[2], normais[3], s, t);
	desenhaPoligono(vertices[4], vertices[5], vertices[6], vertices[7], normais[0], s, t);
	desenhaPoligono(vertices[5], vertices[4], vertices[0], vertices[1], normais[5], s, t);
	 
	glBindTexture(GL_TEXTURE_2D, NULL);
}


void desenhaInfoJogo(int width, int height)  // largura e altura da janela
{

	// Altera viewport e projecÁ„o para 2D (copia de um reshape de um projecto 2D)

	//....
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Blending (transparencias)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);


	//desenha bussola 2D
	glColor4f(1, 1, 1, 0.5);

	/*glBegin(GL_TRIANGLES);
	glVertex3f(8, -7.5, 0);
	glVertex3f(7.5, -8.5, 0);
	glVertex3f(8.5, -8.5, 0);
	glEnd();*/

	switch(flagJogo){
	case 0:
		strokeCenterString(vida, 8, 9, 0, 0.01);
		strokeCenterString("", 8, -6.7, 0, 0.01); // string, x ,y ,z ,scale
		strokeCenterString(tempo, 8, -9.2, 0, 0.01);
		break;
	case 1:
		glColor3f(0,1,0);
		strokeCenterString("Congratulations!! You just", 0, 1, 0, 0.01);
		strokeCenterString(" made a new friend!!", 0, 0, 0, 0.01);
		glColor3f(0, 0, 0);
		strokeCenterString("Press ESC to exit!!", 0, -2, 0, 0.01);
		break;
	case 2:
		glColor3f(1,0,0);
		strokeCenterString("Game Over!! You Lost", 0, 1, 0, 0.01);
		strokeCenterString(" the challenge", 0, 0, 0, 0.01);
		glColor3f(0, 0, 0);
		strokeCenterString("Press ESC to exit!!", 0, -2, 0, 0.01);
		break;
	default:
		break;
	}

	//latitude da camara, para mudar angulo de vis„o
	//em qualquer momento sabemos  a posiÁ„o 
	//sÛ faz mudanca de 60 graus

	// ropıe estado
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);


	//repıe projecÁ„o chamando redisplay
	reshapeNavigateSubwindow(width, height);

}

void desenhaModeloDir(objecto_t obj, int width, int height)
{
	// Altera viewport e projecÁ„o
	//....

	// Blending (transparencias)
	/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	*/

	//desenha Seta

	// ropıe estado
	/*  glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	*/
	//repıe projecÁ„o chamando redisplay
	redisplayTopSubwindow(width, height);
}

void desenhaAngVisao(camera_t *cam)
{
	GLfloat ratio;
	ratio = (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT); // proporÁ„o 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glPushMatrix();
	glTranslatef(cam->eye.x, OBJECTO_ALTURA, cam->eye.z);
	glColor4f(0, 0, 1, 0.2);
	glRotatef(GRAUS(cam->dir_long), 0, 1, 0);

	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(5 * cos(RAD(cam->fov*ratio*0.5)), 0, -5 * sin(RAD(cam->fov*ratio*0.5)));
	glVertex3f(5 * cos(RAD(cam->fov*ratio*0.5)), 0, 5 * sin(RAD(cam->fov*ratio*0.5)));
	glEnd();
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void desenhaModelo()
{
	glColor3f(0, 1, 0);
	glutSolidCube(OBJECTO_ALTURA);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, OBJECTO_ALTURA*0.75, 0);
	glRotatef(GRAUS(estado.camera.dir_long - modelo.objecto.dir), 0, 1, 0);
	glutSolidCube(OBJECTO_ALTURA*0.5);
	glPopMatrix();
}

void desenhaEstrela(){

	glPushMatrix();
		glTranslatef(2,.3,2);
		glColor3f(1,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0.0, 0.2, 0.0);
			glVertex3f(0.1, 0.1, 0.0);
			glVertex3f(0.2, 0.05, 0.0);
			glVertex3f(0.1, 0.0, 0.0);
			glVertex3f(0.2, -0.1, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(-0.2, -0.1, 0.0);
			glVertex3f(-0.1, 0.0, 0.0);
			glVertex3f(-0.2, 0.05, 0.0);
			glVertex3f(-0.1, 0.1, 0.0);
			glEnd();
		glFlush();
	glPopMatrix();
}

void desenhaLabirinto(GLuint texID)
{

	// cÛdigo para desenhar o labirinto
	glPushMatrix();
	criaBaseConhecimento();

	//PlTermv av2(2);

	//av2[0] = PlCompound("1");

	//PlQuery q("listarValores", av2);
		
	//cout << (char*)av2[1] << endl;

	/*while (q.next_solution())
	{
		cout << (char*)av2[1] << endl;
	}*/

	if (flagDificuldade == 1){
		glTranslatef(-WIDTH_20 / 2.0, 0, -HEIGHT_20 / 2.0);
		desenhaEstrela();
		for (int mz = 0; mz < HEIGHT_20; mz++){
			for (int mx = 0; mx < WIDTH_20; mx++){
				if (mazedata20[mz][mx] == '*'){
					glPushMatrix();
					glTranslatef(mx, 0.5, mz);
					desenhaCubo(texID);
					glPopMatrix();
				}
			}
		}
	}
	else if (flagDificuldade == 2){
		glTranslatef(-WIDTH_30 / 2.0, 0, -HEIGHT_30 / 2.0);
		desenhaEstrela();
		for (int mz = 0; mz < HEIGHT_30; mz++){
			for (int mx = 0; mx < WIDTH_30; mx++){
				if (mazedata30[mz][mx] == '*'){
					glPushMatrix();
					glTranslatef(mx, 0.5, mz);
					desenhaCubo(texID);
					glPopMatrix();
				}
			}
		}
	}
	else{
		glTranslatef(-WIDTH_40 / 2.0, 0, -HEIGHT_40 / 2.0);
		desenhaEstrela();
		for (int mz = 0; mz < HEIGHT_40; mz++){
			for (int mx = 0; mx < WIDTH_40; mx++){
				if (mazedata40[mz][mx] == '*'){
					glPushMatrix();
					glTranslatef(mx, 0.5, mz);
					desenhaCubo(texID);
					glPopMatrix();
				}
			}
		}
	}

	glPopMatrix();

}
	

#define STEP    1

void desenhaChao(GLfloat dimensao, GLuint texID)
{
	// cÛdigo para desenhar o ch„o
	GLfloat i, j;
	glBindTexture(GL_TEXTURE_2D, texID);

	glColor3f(0.5f, 0.5f, 0.5f);
	for (i = -dimensao; i <= dimensao; i += STEP)
	for (j = -dimensao; j <= dimensao; j += STEP)
	{
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(i + STEP, 0, j + STEP);
		glTexCoord2f(0, 1);
		glVertex3f(i, 0, j + STEP);
		glTexCoord2f(0, 0);
		glVertex3f(i, 0, j);
		glTexCoord2f(1, 0);
		glVertex3f(i + STEP, 0, j);
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, NULL);
}

/////////////////////////////////////
//navigateSubwindow

void motionNavigateSubwindow(int x, int y)
{

}


void mouseNavigateSubwindow(int button, int state, int x, int y)
{

}

void setNavigateSubwindowCamera(camera_t *cam, objecto_t obj)
{

	pos_t center;
	pos_t up;

	if (!estado.vista[JANELA_NAVIGATE])
	{//3™ PESSOA

		cam->eye.x = obj.pos.x - DIST_CAM * cos(obj.dir);
		cam->eye.y = 1;
		cam->eye.z = obj.pos.z + DIST_CAM * sin(obj.dir);

		center.x = obj.pos.x;
		center.y = ALTURA_CAM;
		center.z = obj.pos.z;

		up.x = 0;
		up.y = 1;
		up.z = 0;


	}
	else
	{//1™ PESSOA
		cam->eye.x = obj.pos.x;
		cam->eye.y = ALT_OLHOS;
		cam->eye.z = obj.pos.z;

		center.x = obj.pos.x + cos(obj.dir);
		center.y = ALT_OLHOS;
		center.z = obj.pos.z - sin(obj.dir);

		up.x = 0;
		up.y = 1;
		up.z = 0;
	}

	gluLookAt(cam->eye.x, cam->eye.y, cam->eye.z, center.x, center.y, center.z, 0, 1, 0);
}


void displayNavigateSubwindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setNavigateSubwindowCamera(&estado.camera, modelo.objecto);
	setLight();

	glCallList(modelo.labirinto[JANELA_NAVIGATE]);
	glCallList(modelo.chao[JANELA_NAVIGATE]);

	if (!estado.vista[JANELA_NAVIGATE])
	{
		glPushMatrix();
		glTranslatef(modelo.objecto.pos.x, modelo.objecto.pos.y, modelo.objecto.pos.z);
		glRotatef(GRAUS(modelo.objecto.dir), 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
		mdlviewer_display(modelo.homer[JANELA_NAVIGATE]);
		glPopMatrix();
	}

	desenhaInfoJogo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	glutSwapBuffers();
}

/////////////////////////////////////
//topSubwindow
void setTopSubwindowCamera(camera_t *cam, objecto_t obj)
{
	cam->eye.x = obj.pos.x;
	cam->eye.z = obj.pos.z;
	if (flagDificuldade == 1){
		if (estado.vista[JANELA_TOP])
			gluLookAt(obj.pos.x, chaoConst * 5, obj.pos.z, obj.pos.x, obj.pos.y, obj.pos.z, 0, 0, -1);
		else
			gluLookAt(obj.pos.x, chaoConst *.5, obj.pos.z, obj.pos.x, obj.pos.y, obj.pos.z, 0, 0, -1);
	}
	else if (flagDificuldade == 2){
		if (estado.vista[JANELA_TOP])
			gluLookAt(obj.pos.x, chaoConst * 3, obj.pos.z, obj.pos.x, obj.pos.y, obj.pos.z, 0, 0, -1);
		else
			gluLookAt(obj.pos.x, chaoConst *.3, obj.pos.z, obj.pos.x, obj.pos.y, obj.pos.z, 0, 0, -1);
	}
	else{
		if (estado.vista[JANELA_TOP])
			gluLookAt(obj.pos.x, chaoConst * 2, obj.pos.z, obj.pos.x, obj.pos.y, obj.pos.z, 0, 0, -1);
		else
			gluLookAt(obj.pos.x, chaoConst *.2, obj.pos.z, obj.pos.x, obj.pos.y, obj.pos.z, 0, 0, -1);
	}
}

void displayTopSubwindow()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	setTopSubwindowCamera(&estado.camera, modelo.objecto);
	setLight();

	glCallList(modelo.labirinto[JANELA_TOP]);
	glCallList(modelo.chao[JANELA_TOP]);

	glPushMatrix();
	glTranslatef(modelo.objecto.pos.x, modelo.objecto.pos.y, modelo.objecto.pos.z);
	glRotatef(GRAUS(modelo.objecto.dir), 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
	mdlviewer_display(modelo.homer[JANELA_TOP]);
	glPopMatrix();

	desenhaAngVisao(&estado.camera);
	desenhaModeloDir(modelo.objecto, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	desenhaInfoJogo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glutSwapBuffers();
	
}


/////////////////////////////////////
//mainWindow

void redisplayAll(void)
{
	glutSetWindow(estado.mainWindow);
	glutPostRedisplay();
	glutSetWindow(estado.topSubwindow);
	glutPostRedisplay();
	glutSetWindow(estado.navigateSubwindow);
	glutPostRedisplay();
}

void displayMainWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void Timer(int value)
{
			
	if (flagJogo != 2){
		if (flagJogo != 1){
			if (vidas == 0){
				flagJogo = 2;
				desenhaInfoJogo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			}
			else{

				if (modelo.homer[JANELA_NAVIGATE].GetSequence() == 20){
					if (value < 10){
						glutTimerFunc(estado.timer, Timer, value + 1);
						redisplayAll();
						return;
					}
					else
					{
						modelo.homer[JANELA_NAVIGATE].SetSequence(0);
						modelo.homer[JANELA_TOP].SetSequence(0);
					}
				}


				GLfloat nx = 0, nz = 0;
				GLboolean andar = GL_FALSE;

				GLuint curr = glutGet(GLUT_ELAPSED_TIME);
				int minutos = (curr % (1000 * 60 * 60)) / (1000 * 60);
				int segundos = ((curr % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
				string temp = to_string(minutos) + ":" + to_string(segundos);
				strcpy(tempo, temp.c_str());

				string tmp = to_string(vidas);
				strcpy(vida, tmp.c_str());

				desenhaInfoJogo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
				// calcula velocidade baseado no tempo passado
				float velocidade = modelo.objecto.vel*(curr - modelo.prev)*0.001;

				glutTimerFunc(estado.timer, Timer, 0);
				modelo.prev = curr;

				if (estado.teclas.up){

					// calcula nova posiÁ„o nx,nz
					nx = modelo.objecto.pos.x + modelo.objecto.vel * cos(modelo.objecto.dir);
					nz = modelo.objecto.pos.z - modelo.objecto.vel * sin(modelo.objecto.dir);

					if (!detectaColisaoEstrela(nx, nz)){
						if (!detectaColisao(nx, nz)){
							modelo.objecto.pos.x = nx;
							modelo.objecto.pos.z = nz;
							if (modelo.homer[JANELA_NAVIGATE].GetSequence() != 3){
								modelo.homer[JANELA_NAVIGATE].SetSequence(3);
								modelo.homer[JANELA_TOP].SetSequence(3);
							}
						}
						else
						{
							modelo.homer[JANELA_NAVIGATE].SetSequence(20);
							modelo.homer[JANELA_TOP].SetSequence(20);
							vidas -= 1;
						}
					}
					else
					{
						//printf("%d minutes and %d seconds\n", (Milliseconds % (1000 * 60 * 60)) / (1000 * 60), ((Milliseconds % (1000 * 60 * 60)) % (1000 * 60)) / 1000);
						modelo.homer[JANELA_NAVIGATE].SetSequence(5);
						modelo.homer[JANELA_TOP].SetSequence(5);
						flagJogo = 1;
						desenhaInfoJogo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
					}

					andar = GL_TRUE;
				}


				if (estado.teclas.down){
					// calcula nova posiÁ„o nx,nz
					nx = modelo.objecto.pos.x - modelo.objecto.vel * cos(modelo.objecto.dir);
					nz = modelo.objecto.pos.z + modelo.objecto.vel * sin(modelo.objecto.dir);

					if (!detectaColisaoEstrela(nx, nz)){
						if (!detectaColisao(nx, nz)){
							modelo.objecto.pos.x = nx;
							modelo.objecto.pos.z = nz;
							if (modelo.homer[JANELA_NAVIGATE].GetSequence() != 3){
								modelo.homer[JANELA_NAVIGATE].SetSequence(3);
								modelo.homer[JANELA_TOP].SetSequence(3);
							}
						}
						else
						{
							modelo.homer[JANELA_NAVIGATE].SetSequence(20);
							modelo.homer[JANELA_TOP].SetSequence(20);
							vidas -= 1;
						}
					}
					else
					{
						flagJogo = 1;
						desenhaInfoJogo(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
						modelo.homer[JANELA_NAVIGATE].SetSequence(5);
						modelo.homer[JANELA_TOP].SetSequence(5);

					}

					andar = GL_TRUE;
				}

				if (estado.teclas.left){
					// rodar camara e objecto
					modelo.objecto.dir += .12;
					estado.camera.dir_long += .12;
				}
				if (estado.teclas.right){
					// rodar camara e objecto
					modelo.objecto.dir -= .12;
					estado.camera.dir_long -= .12;
				}
				/*/*
				if (modelo.homer[JANELA_NAVIGATE].GetSequence() == 0){
				if (estado.contaAnimaCair>0){
				estado.contaAnimaCair--;
				}
				}
				*/

				if (!andar)
				{
					modelo.homer[JANELA_NAVIGATE].SetSequence(0);
					modelo.homer[JANELA_TOP].SetSequence(0);
				}

				if (estado.teclas.F1){
					//chamada ao prolog da sugest„o de caminho possÌvel
				}

				// Sequencias - 0(parado) 3(andar) 20(choque)
				//  modelo.homer[JANELA_NAVIGATE].GetSequence()  le Sequencia usada pelo homer
				//  modelo.homer[JANELA_NAVIGATE].SetSequence()  muda Sequencia usada pelo homer
			}
		}
	}
	else{
		modelo.homer[JANELA_NAVIGATE].SetSequence(75);
		modelo.homer[JANELA_TOP].SetSequence(75);
	}
	
	redisplayAll();

}


void imprime_ajuda(void)
{
	printf("h,H - Ajuda \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("w,W - Wireframe \n");
	printf("f,F - Fill \n");
	printf("F1 - Sugerir Caminho a seguir");
	printf("******* Camara ******* \n");
	printf("F2 - Alterna camara da janela da Direita \n");
	printf("PAGE_UP, PAGE_DOWN - Altera abertura da camara \n");
	printf("ESC - Sair\n");
}


void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
		break;
	case 'h':
	case 'H':
		imprime_ajuda();
		break;
	case 'l':
	case 'L':
		estado.localViewer = !estado.localViewer;
		break;
	case 'w':
	case 'W':
		glutSetWindow(estado.navigateSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		glutSetWindow(estado.topSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
		break;
	case 's':
	case 'S':
		glutSetWindow(estado.navigateSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		glutSetWindow(estado.topSubwindow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_TEXTURE_2D);
		break;
	case 'a':
	case 'A':

		break;
	}

}
void SpecialKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: estado.teclas.up = GL_TRUE;
		break;
	case GLUT_KEY_DOWN: estado.teclas.down = GL_TRUE;
		break;
	case GLUT_KEY_LEFT: estado.teclas.left = GL_TRUE;
		break;
	case GLUT_KEY_RIGHT: estado.teclas.right = GL_TRUE;
		break;
	case GLUT_KEY_F1: estado.teclas.F1 = GL_TRUE;
		break;
	case GLUT_KEY_F2: estado.vista[JANELA_NAVIGATE] = !estado.vista[JANELA_NAVIGATE];
		break;
	case GLUT_KEY_PAGE_UP:
		if (estado.camera.fov > 20)
		{
			estado.camera.fov--;
			glutSetWindow(estado.navigateSubwindow);
			reshapeNavigateSubwindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			redisplayAll();
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (estado.camera.fov < 130)
		{
			estado.camera.fov++;
			glutSetWindow(estado.navigateSubwindow);
			reshapeNavigateSubwindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			redisplayAll();
		}
		break;
	}

}
// Callback para interaccao via teclas especiais (largar na tecla)
void SpecialKeyUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: estado.teclas.up = GL_FALSE;
		break;
	case GLUT_KEY_DOWN: estado.teclas.down = GL_FALSE;
		break;
	case GLUT_KEY_LEFT: estado.teclas.left = GL_FALSE;
		break;
	case GLUT_KEY_RIGHT: estado.teclas.right = GL_FALSE;
		break;
	case GLUT_KEY_F1: estado.teclas.F1 = GL_FALSE;
		break;
	}
}

////////////////////////////////////
// InicializaÁıes



void createDisplayLists(int janelaID)
{
	modelo.labirinto[janelaID] = glGenLists(2);
	glNewList(modelo.labirinto[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
	desenhaLabirinto(modelo.texID[janelaID][ID_TEXTURA_CUBOS]);
	glPopAttrib();
	glEndList();

	modelo.chao[janelaID] = modelo.labirinto[janelaID] + 1;
	glNewList(modelo.chao[janelaID], GL_COMPILE);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
	if (flagDificuldade == 1){
		chaoConst = 10;
	}
	else if (flagDificuldade == 2){
		chaoConst = 20;
	}
	else{
		chaoConst = 30;
	}
	desenhaChao(chaoConst, modelo.texID[janelaID][ID_TEXTURA_CHAO]);
	glPopAttrib();
	glEndList();
}


///////////////////////////////////
/// Texturas


// Só para windows (usa biblioteca glaux)
#ifdef _WIN32

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File = NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File = fopen(Filename, "r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}
#endif

void createTextures(GLuint texID[])
{
	char *image;
	int w, h, bpp;

#ifdef _WIN32
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage, 0, sizeof(void *)* 1);           	// Set The Pointer To NULL
#endif

	glGenTextures(NUM_TEXTURAS, texID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef _WIN32
	if (TextureImage[0] = LoadBMP(NOME_TEXTURA_CUBOS))
	{
		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CUBOS]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
#else
	if (read_JPEG_file(NOME_TEXTURA_CUBOS, &image, &w, &h, &bpp))
	{
		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CUBOS]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
#endif
	else
	{
		printf("Textura %s not Found\n", NOME_TEXTURA_CUBOS);
		exit(0);
	}

	if (read_JPEG_file(NOME_TEXTURA_CHAO, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CHAO]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else{
		printf("Textura %s not Found\n", NOME_TEXTURA_CHAO);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, NULL);
}


void init()
{

	time1 = glutGet(GLUT_ELAPSED_TIME);

	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };

	estado.timer = 100;

	estado.camera.eye.x = 0;
	estado.camera.eye.y = OBJECTO_ALTURA * 2;
	estado.camera.eye.z = 0;
	estado.camera.dir_long = 0;
	estado.camera.dir_lat = 0;
	estado.camera.fov = 60;

	estado.localViewer = 1;
	//estado.vista[JANELA_TOP] = 0;
	estado.vista[JANELA_NAVIGATE] = 0;


	modelo.objecto.pos.x = 6;
	modelo.objecto.pos.y = OBJECTO_ALTURA*.5;
	modelo.objecto.pos.z = 7;
	modelo.objecto.dir = 0;
	modelo.objecto.vel = OBJECTO_VELOCIDADE;
	modelo.xMouse = modelo.yMouse = -1;
	modelo.andar = GL_FALSE;

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);  // por causa do Scale ao Homer

	if (glutGetWindow() == estado.mainWindow)
		glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	else
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

/////////////////////////////////////
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800 + GAP * 3, 600 + GAP * 2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if ((estado.mainWindow = glutCreateWindow("Labirinto")) == GL_FALSE)
		exit(1);

	//passar valor para flagDificuldade

	imprime_ajuda();

	// Registar callbacks do GLUT da janela principal
	init();
	glutReshapeFunc(reshapeMainWindow);
	glutDisplayFunc(displayMainWindow);

	glutTimerFunc(estado.timer, Timer, 0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);

	// criar a sub window topSubwindow
	estado.topSubwindow = glutCreateSubWindow(estado.mainWindow, GAP, GAP, 400, 400);

	init();
	setLight();
	setMaterial();
	createTextures(modelo.texID[JANELA_TOP]);
	createDisplayLists(JANELA_TOP);

    mdlviewer_init("homer.mdl", modelo.homer[JANELA_TOP]);

	glutReshapeFunc(redisplayTopSubwindow);
	glutDisplayFunc(displayTopSubwindow);

	glutTimerFunc(estado.timer, Timer, 0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);

	// criar a sub window navigateSubwindow
	estado.navigateSubwindow = glutCreateSubWindow(estado.mainWindow, 800 + GAP, GAP, 300, 300);
	init();
	setLight();
	setMaterial();

	createTextures(modelo.texID[JANELA_NAVIGATE]);
	createDisplayLists(JANELA_NAVIGATE);
	mdlviewer_init("homer.mdl", modelo.homer[JANELA_NAVIGATE]);
	glutReshapeFunc(reshapeNavigateSubwindow);
	glutDisplayFunc(displayNavigateSubwindow);
	glutMouseFunc(mouseNavigateSubwindow);

	glutTimerFunc(estado.timer, Timer, 0);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);


	glutMainLoop();
	return 0;

}
