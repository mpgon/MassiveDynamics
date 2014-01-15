#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>     
#include <GL\glut.h>
#include <GL\glaux.h>

#include <iostream>
#include "grafos.h"
#include "rain.h"
#include "ClientWS.h"

#include "Billboard.h"
#include "humor.h"

#include "tga.h"

using namespace std;

#define NOME_TEXTURA_SKYBOX		  "Skybox.jpg"
#define NOME_TEXTURA_CHAO         "Chao2.jpg"
#define NOME_TEXTURA_SUN		  "img/sun.tga"

#define ID_TEXTURA_SKYBOX         3
#define ID_TEXTURA_CHAO           0

#define NUM_TEXTURAS              2

#define JANELA_NAVIGATE 1

#define	xMax 200.0
#define xMin -200.0
#define yMax 200.0
#define yMin -200.0
#define zMax 65.0
#define zMin -65.0 
GLuint texID[1];
GLuint		  textIDSkybox;GLuint		  textIDSun;
extern "C" {
	FILE* _iob = NULL;
}

#define graus(X) (double)((X)*180/M_PI)
#define rad(X)   (double)((X)*M_PI/180)

// função para ler jpegs do ficheiro readjpeg.c
extern "C" int read_JPEG_file(char *, char **, int *, int *, int *);

// luzes e materiais

const GLfloat mat_ambient[][4] = { { 0.33, 0.22, 0.03, 1.0 },	// brass
{ 0.0, 0.0, 0.0 },			// red plastic
{ 0.0215, 0.1745, 0.0215 },	// emerald
{ 0.02, 0.02, 0.02 },		// slate
{ 0.0, 0.0, 0.1745 },		// azul
{ 0.02, 0.02, 0.02 },		// preto
{ 0.1745, 0.1745, 0.1745 } };// cinza

const GLfloat mat_diffuse[][4] = { { 0.78, 0.57, 0.11, 1.0 },		// brass
{ 0.5, 0.0, 0.0 },				// red plastic
{ 0.07568, 0.61424, 0.07568 },	// emerald
{ 0.78, 0.78, 0.78 },			// slate
{ 0.0, 0.0, 0.61424 },			// azul
{ 0.08, 0.08, 0.08 },			// preto
{ 0.61424, 0.61424, 0.61424 } };	// cinza

const GLfloat mat_specular[][4] = { { 0.99, 0.91, 0.81, 1.0 },			// brass
{ 0.7, 0.6, 0.6 },					// red plastic
{ 0.633, 0.727811, 0.633 },		// emerald
{ 0.14, 0.14, 0.14 },				// slate
{ 0.0, 0.0, 0.727811 },			// azul
{ 0.03, 0.03, 0.03 },				// preto
{ 0.727811, 0.727811, 0.727811 } };	// cinza

const GLfloat mat_shininess[] = { 27.8,	// brass
32.0,	// red plastic
76.8,	// emerald
18.78,	// slate
30.0,	// azul
75.0,	// preto
60.0 };	// cinza

enum tipo_material { brass, red_plastic, emerald, slate, azul, preto, cinza };

#ifdef __cplusplus
inline tipo_material operator++(tipo_material &rs, int) {
	return rs = (tipo_material)(rs + 1);
}
#endif

typedef	GLdouble Vertice[3];
typedef	GLdouble Vector[4];


typedef struct Camera{
	GLfloat fov;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice center;
	GLint   pessoa;//1 ou3
	GLfloat dir;
	GLfloat posx;
	GLfloat posy;
	GLfloat posz;
	GLfloat vel;
}Camera;

typedef struct Estado{
	Camera		camera;
	int			xMouse, yMouse;
	GLboolean	light;
	GLboolean	apresentaNormais;
	GLboolean   chuva;
	GLint		lightViewer;
	GLint		eixoTranslaccao;
	GLdouble	eixo[3];
}Estado;

typedef struct Modelo {
#ifdef __cplusplus
	tipo_material cor_cubo;
#else
	enum tipo_material cor_cubo;
#endif

	GLfloat g_pos_luz1[4];
	GLfloat g_pos_luz2[4];

	GLfloat escala;
	GLUquadric *quad;
	GLuint        texID[NUM_TEXTURAS];
}Modelo;

Estado estado;
Modelo modelo;

//Chuva
const int numgotas = 150;
CHUVA rain;

void chuva()
{
	
	glPushMatrix();
	DesenharChuva(rain, numgotas, 0, -75,0);
	glPopMatrix();
}

void humor()
{
	glPushMatrix();
	desenhaImagemTga(textIDSun, 25, 50, 25);
	desenhaImagemTga(textIDSkybox, 10, 10, 25);
	glPopMatrix();
}


void initEstado(){
	estado.camera.pessoa = 3;
	estado.camera.dir_lat = M_PI / 4;
	estado.camera.dir_long = -M_PI / 4;
	estado.camera.fov = 60;
	estado.camera.dist = 100;
	estado.camera.dir = 11;
	estado.camera.vel = 1;
	estado.camera.posx = nos[noInicial].x * 5;
	estado.camera.posy = nos[noInicial].y * 5;
	estado.camera.posz = nos[noInicial].z * 5 + 12;
	estado.eixo[0] = 0;
	estado.eixo[1] = 0;
	estado.eixo[2] = 0;
	estado.camera.center[0] = 0;
	estado.camera.center[1] = 0;
	estado.camera.center[2] = 0;
	estado.light = GL_FALSE;
	estado.apresentaNormais = GL_FALSE;
	estado.chuva = GL_TRUE;
	estado.lightViewer = 1;
}

void initModelo(){
	modelo.escala = 0.2;

	modelo.cor_cubo = brass;
	modelo.g_pos_luz1[0] = -5.0;
	modelo.g_pos_luz1[1] = 5.0;
	modelo.g_pos_luz1[2] = 5.0;
	modelo.g_pos_luz1[3] = 0.0;
	modelo.g_pos_luz2[0] = 5.0;
	modelo.g_pos_luz2[1] = -15.0;
	modelo.g_pos_luz2[2] = 5.0;
	modelo.g_pos_luz2[3] = 0.0;
}


void myInit()
{

	leGrafo();

	GLfloat LuzAmbiente[] = { 0.5, 0.5, 0.5, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	glEnable(GL_NORMALIZE);

	glDepthFunc(GL_LESS);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.lightViewer);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	initModelo();
	initEstado();
	modelo.quad = gluNewQuadric();
	gluQuadricDrawStyle(modelo.quad, GLU_FILL);
	gluQuadricNormals(modelo.quad, GLU_OUTSIDE);

	InicializarChuva(rain, numgotas);

	
}

void imprime_ajuda(void)
{
	printf("\n\nDesenho de um labirinto a partir de um grafo\n");
	printf("h,H - Ajuda \n");
	printf("i,I - Reset dos Valores \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("k,K - Alerna luz de camera com luz global \n");
	printf("s,S - PolygonMode Fill \n");
	printf("w,W - PolygonMode Wireframe \n");
	printf("p,P - PolygonMode Point \n");
	printf("c,C - Liga/Desliga Cull Face \n");
	printf("n,N - Liga/Desliga apresentação das normais \n");
	printf("v,V - Camara: Alernar entre 1a e 3a pessoa \n");
	printf("******* grafos ******* \n");
	printf("F1  - Grava grafo do ficheiro \n");
	printf("F2  - Lê grafo para ficheiro \n");
	printf("F6  - Cria novo grafo\n");
	printf("******* Camera ******* \n");
	printf("Botão esquerdo - Arrastar os eixos (centro da camera)\n");
	printf("Botão direito  - Rodar camera\n");
	printf("Botão direito com CTRL - Zoom-in/out\n");
	printf("PAGE_UP, PAGE_DOWN - Altera distância da camara \n");
	printf("ESC - Sair\n");
}


void material(enum tipo_material mat)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[mat]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[mat]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[mat]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess[mat]);
}

const GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
const GLfloat green_light[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat blue_light[] = { 0.0, 0.0, 1.0, 1.0 };
const GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };


void putLights(GLfloat* diffuse)
{
	const GLfloat white_amb[] = { 0.2, 0.2, 0.2, 1.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_amb);
	glLightfv(GL_LIGHT0, GL_POSITION, modelo.g_pos_luz1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT1, GL_AMBIENT, white_amb);
	glLightfv(GL_LIGHT1, GL_POSITION, modelo.g_pos_luz2);

	/* desenhar luz */
	//material(red_plastic);
	//glPushMatrix();
	//	glTranslatef(modelo.g_pos_luz1[0], modelo.g_pos_luz1[1], modelo.g_pos_luz1[2]);
	//	glDisable(GL_LIGHTING);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glutSolidCube(0.1);
	//	glEnable(GL_LIGHTING);
	//glPopMatrix();
	//glPushMatrix();
	//	glTranslatef(modelo.g_pos_luz2[0], modelo.g_pos_luz2[1], modelo.g_pos_luz2[2]);
	//	glDisable(GL_LIGHTING);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glutSolidCube(0.1);
	//	glEnable(GL_LIGHTING);
	//glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void desenhaImagemTga(GLuint textura, float x, float y, float z) {

	glPushMatrix();

	glPushAttrib(GL_ENABLE_BIT);

	glEnable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	glAlphaFunc(GL_GREATER, 0);

	for (int i = 0; i < 1; i++)
	for (int j = 0; j < 1; j++) {
		glPushMatrix();

		glTranslatef(x, y, z); //posiçao da imagem 
		BillboardCheatSphericalBegin();

		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		//glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);

		glBindTexture(GL_TEXTURE_2D, textura);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-8.0f, 0.0f, 0.0f);  //tamanho imagem
		glTexCoord2f(1, 0); glVertex3f(8.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 1); glVertex3f(8.0f, 16.0f, 0.0f);
		glTexCoord2f(0, 1); glVertex3f(-8.0f, 16.0f, 0.0f);
		glEnd();

		//glBindTexture(GL_TEXTURE_2D, NULL);
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);

		glPopAttrib();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		//glBindTexture(GL_TEXTURE_2D, NULL);
	}

	//glBindTexture(GL_TEXTURE_2D, NULL);

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);

}

void strokeCenterString(char *str, double x, double y, double z, double s)
{
	int i, n;

	n = strlen(str);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslated(x - glutStrokeLength(GLUT_STROKE_ROMAN, (const unsigned char*)str)*0.5*s, y - 119.05*0.5*s, z);
	glScaled(s, s, s);
	for (i = 0; i < n; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)str[i]);
	glPopMatrix();

}

void desenhaSkyBox(){

	
		glPushMatrix();
		glRotatef(90, 1, 0, 0); // rotate on z-axis
		glTranslated(estado.eixo[0], estado.eixo[1]-60, estado.eixo[2]);
		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		//glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);

		// Just in case we set all vertices to white.
		glColor4f(1, 1, 1, 1);

		// frente
		glBindTexture(GL_TEXTURE_2D, textIDSkybox);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.75, 0.25); glVertex3f(xMin, zMin, yMin);
		glTexCoord2f(0.5, 0.25); glVertex3f(xMax, zMin, yMin);
		glTexCoord2f(0.5, 0.5); glVertex3f(xMax, zMax * 2, yMin);
		glTexCoord2f(0.75, 0.5); glVertex3f(xMin, zMax * 2, yMin);
		glEnd();

		// esquerda
		glBindTexture(GL_TEXTURE_2D, textIDSkybox);
		glBegin(GL_POLYGON);
		glTexCoord2f(1, 0.25); glVertex3f(xMin + 0.1, zMin, yMax);
		glTexCoord2f(0.75, 0.25);   glVertex3f(xMin + 0.1, zMin, yMin);
		glTexCoord2f(0.75, 0.5);    glVertex3f(xMin + 0.1, zMax * 2, yMin);
		glTexCoord2f(1, 0.5); glVertex3f(xMin + 0.1, zMax * 2, yMax);
		glEnd();

		// tras
		glBegin(GL_POLYGON);
		glTexCoord2f(0.5, 1.0); glVertex3f(xMax, zMin, yMax);
		glTexCoord2f(0.75, 1.0);   glVertex3f(xMin, zMin, yMax);
		glTexCoord2f(0.75, 0.75);    glVertex3f(xMin, zMax * 2, yMax);
		glTexCoord2f(0.5, 0.75); glVertex3f(xMax, zMax * 2, yMax);
		glEnd();

		// direita
		glBegin(GL_POLYGON);
		glTexCoord2f(0.5, 0.25); glVertex3f(xMax - 0.1, zMin, yMin);
		glTexCoord2f(0.25, 0.25);   glVertex3f(xMax - 0.1, zMin, yMax);
		glTexCoord2f(0.25, 0.5);    glVertex3f(xMax - 0.1, zMax * 2, yMax);
		glTexCoord2f(0.5, 0.5); glVertex3f(xMax - 0.1, zMax * 2, yMin);
		glEnd();

		// topo
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glBegin(GL_POLYGON);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0.75, 0.5); glVertex3f(xMin, zMax * 2, yMin);
		glTexCoord2f(0.5, 0.5);   glVertex3f(xMax, zMax * 2, yMin);
		glTexCoord2f(0.5, 0.75);    glVertex3f(xMax, zMax * 2, yMax);
		glTexCoord2f(0.75, 0.75); glVertex3f(xMin, zMax * 2, yMax);
		glEnd();
		glDisable(GL_CULL_FACE);

		// chao
		glBegin(GL_POLYGON);
		glTexCoord2f(0.75, 0.25); glVertex3f(xMin, zMin, yMin);
		glTexCoord2f(0.5, 0.25);   glVertex3f(xMax, zMin, yMin);
		glTexCoord2f(0.5, 0.0);    glVertex3f(xMax, zMin, yMax);
		glTexCoord2f(0.75, 0.0); glVertex3f(xMin, zMin, yMax);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, NULL);
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glPopAttrib();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);
	
}

void desenhaSolo(GLuint texID){
#define STEP 10
	glBindTexture(GL_TEXTURE_2D, texID);
	//glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	for (int i = -300; i < 300; i += STEP)
	for (int j = -300; j < 300; j += STEP){
		glVertex2f(i, j);
		glVertex2f(i + STEP, j);
		glVertex2f(i + STEP, j + STEP);
		glVertex2f(i, j + STEP);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void CrossProduct(GLdouble v1[], GLdouble v2[], GLdouble cross[])
{
	cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
	cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
	cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

GLdouble VectorNormalize(GLdouble v[])
{
	int		i;
	GLdouble	length;

	if (fabs(v[1] - 0.000215956) < 0.0001)
		i = 1;

	length = 0;
	for (i = 0; i < 3; i++)
		length += v[i] * v[i];
	length = sqrt(length);
	if (length == 0)
		return 0;

	for (i = 0; i < 3; i++)
		v[i] /= length;

	return length;
}

void desenhaNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat){

	switch (mat){
	case red_plastic:
		glColor3f(1, 0, 0);
		break;
	case azul:
		glColor3f(0, 0, 1);
		break;
	case emerald:
		glColor3f(0, 1, 0);
		break;
	default:
		glColor3f(1, 1, 0);
	}
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.4, 0.4, 0.4);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3dv(normal);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void desenhaParede(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf){
	GLdouble v1[3], v2[3], cross[3];
	GLdouble length;
	v1[0] = xf - xi;
	v1[1] = yf - yi;
	v1[2] = 0;
	v2[0] = 0;
	v2[1] = 0;
	v2[2] = 1;
	CrossProduct(v1, v2, cross);
	//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
	length = VectorNormalize(cross);
	//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);

	material(emerald);
	glBegin(GL_QUADS);
	glNormal3dv(cross);
	glVertex3f(xi, yi, zi);
	glVertex3f(xf, yf, zf + 0);
	glVertex3f(xf, yf, zf + 1);
	glVertex3f(xi, yi, zi + 1);
	glEnd();

	if (estado.apresentaNormais) {
		desenhaNormal(xi, yi, zi, cross, emerald);
		desenhaNormal(xf, yf, zf, cross, emerald);
		desenhaNormal(xf, yf, zf + 1, cross, emerald);
		desenhaNormal(xi, yi, zi + 1, cross, emerald);
	}
}

void desenhaChao(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf, int orient){
	GLdouble v1[3], v2[3], cross[3];
	GLdouble length;
	
	

	v1[0] = xf - xi;
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = yf - yi;

	switch (orient) {
	case NORTE_SUL:
		v1[2] = 0;
		v2[2] = zf - zi;
		CrossProduct(v1, v2, cross);
		//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
		length = VectorNormalize(cross);
		//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);

		material(red_plastic);
		glBegin(GL_QUADS);
		glNormal3dv(cross);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zi);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zf);
		glEnd();
		if (estado.apresentaNormais) {
			desenhaNormal(xi, yi, zi, cross, red_plastic);
			desenhaNormal(xf, yi, zi, cross, red_plastic);
			desenhaNormal(xf, yf, zf, cross, red_plastic);
			desenhaNormal(xi, yi, zf, cross, red_plastic);
		}
		break;
	case ESTE_OESTE:
		v1[2] = zf - zi;
		v2[2] = 0;
		CrossProduct(v1, v2, cross);
		//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
		length = VectorNormalize(cross);
		//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);
		material(red_plastic);
		glBegin(GL_QUADS);
		glNormal3dv(cross);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zf);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zi);
		glEnd();
		if (estado.apresentaNormais) {
			desenhaNormal(xi, yi, zi, cross, red_plastic);
			desenhaNormal(xf, yi, zf, cross, red_plastic);
			desenhaNormal(xf, yf, zf, cross, red_plastic);
			desenhaNormal(xi, yi, zi, cross, red_plastic);
		}
		break;
	default:
		cross[0] = 0;
		cross[1] = 0;
		cross[2] = 1;
		material(azul);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zf);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zi);
		glEnd();
		if (estado.apresentaNormais) {
			desenhaNormal(xi, yi, zi, cross, azul);
			desenhaNormal(xf, yi, zf, cross, azul);
			desenhaNormal(xf, yf, zf, cross, azul);
			desenhaNormal(xi, yi, zi, cross, azul);
		}
		break;
	}

	glBindTexture(GL_TEXTURE_2D, NULL);

}

void desenhaNo(int no){
	//GLboolean norte, sul, este, oeste;
	//GLfloat larguraNorte, larguraSul, larguraEste, larguraOeste;
	Arco arco = arcos[0];
	No *noi = &nos[no];// *nof;

	glPushMatrix();

	//mudar a cor da esfera

	glTranslatef(nos[no].x, nos[no].y, nos[no].z + 1);

	
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	int radius = nos[no].getLargura()*.2;//tem que ser variavel...
	if (radius == 0)
		radius = 1;


	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, radius, 36, 18);
	gluDeleteQuadric(quadric);
	

	glPopMatrix();
}


void desenhaArco(Arco arco){
	No *noi, *nof;
	noi = &nos[arco.noi];
	nof = &nos[arco.nof];
	glPushMatrix();
	glTranslatef(noi->x, noi->y, noi->z + 1);
	double ang = atan2(nof->y - noi->y, nof->x - noi->x);
	glRotatef(graus(ang), 0, 0, 1);
	double p = sqrt(0 + pow(nof->x - noi->x, 2) + pow(nof->y - noi->y, 2));
	double desnivel = nof->z - noi->z;
	double beta = atan(desnivel/ p);
	double ang2 = M_PI * .5 - beta;
	glRotatef(graus(ang2), 0, 1, 0);

	double comprimento = sqrt(pow(p, 2) + pow(desnivel, 2));

	GLfloat radius = arco.getLargura()*.5;
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, radius, radius, comprimento, 30, 3);
	gluDeleteQuadric(quadric);

	glPopMatrix();
	
}

void desenhaLabirinto(){
	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glScalef(5, 5, 5);
	material(red_plastic);
	for (int i = 0; i < numNos; i++){
		glPushMatrix();
		material(preto);
		//glTranslatef(nos[i].x, nos[i].y, nos[i].z + 0.25);
		//glutSolidCube(0.5);
		glPopMatrix();
		desenhaNo(i);
	}
	material(emerald);
	for (int i = 0; i < numArcos; i++)
		desenhaArco(arcos[i]);
	glPopMatrix();
}

void desenhaEixo(){
	gluCylinder(modelo.quad, 0.5, 0.5, 20, 16, 15);
	glPushMatrix();
	glTranslatef(0, 0, 20);
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	gluDisk(modelo.quad, 0.5, 2, 16, 6);
	glPopMatrix();
	gluCylinder(modelo.quad, 2, 0, 5, 16, 15);
	glPopMatrix();
}

#define EIXO_X		1
#define EIXO_Y		2
#define EIXO_Z		3

void desenhaPlanoDrag(int eixo){
	glPushMatrix();
	glTranslated(estado.eixo[0], estado.eixo[1], estado.eixo[2]);
	switch (eixo) {
	case EIXO_Y:
		if (abs(estado.camera.dir_lat)<M_PI / 4)
			glRotatef(-90, 0, 0, 1);
		else
			glRotatef(90, 1, 0, 0);
		material(red_plastic);
		break;
	case EIXO_X:
		if (abs(estado.camera.dir_lat)>M_PI / 6)
			glRotatef(90, 1, 0, 0);
		material(azul);
		break;
	case EIXO_Z:
		if (abs(cos(estado.camera.dir_long)) > 0.5)
			glRotatef(90, 0, 0, 1);

		material(emerald);
		break;
	}
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-100, 0, -100);
	glVertex3f(100, 0, -100);
	glVertex3f(100, 0, 100);
	glVertex3f(-100, 0, 100);
	glEnd();
	glPopMatrix();
}

void desenhaEixos(){

	glPushMatrix();
	glTranslated(estado.eixo[0], estado.eixo[1], estado.eixo[2]);
	material(emerald);
	glPushName(EIXO_Z);
	desenhaEixo();
	glPopName();
	glPushName(EIXO_Y);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	material(red_plastic);
	desenhaEixo();
	glPopMatrix();
	glPopName();
	glPushName(EIXO_X);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	material(azul);
	desenhaEixo();
	glPopMatrix();
	glPopName();
	glPopMatrix();
}

void setCamera(){
	Vertice eye;
	if (estado.camera.pessoa == 3){
		eye[0] = estado.camera.center[0] + estado.camera.dist*cos(estado.camera.dir_long)*cos(estado.camera.dir_lat);
		eye[1] = estado.camera.center[1] + estado.camera.dist*sin(estado.camera.dir_long)*cos(estado.camera.dir_lat);
		eye[2] = estado.camera.center[2] + estado.camera.dist*sin(estado.camera.dir_lat);


	}
	else {//1ªpessoa

		eye[0] = estado.camera.posx;
		eye[1] = estado.camera.posy;
		eye[2] = estado.camera.posz;
		
		if (estado.camera.dir == 0){
			estado.camera.center[0] = eye[0];
			estado.camera.center[1] = eye[1];
			estado.camera.center[2] = eye[2];
		}
		else {
			estado.camera.center[0] = eye[0] + cos(estado.camera.dir);
			estado.camera.center[1] = eye[1] - sin(estado.camera.dir);
			estado.camera.center[2] = eye[2];
		}
		
	}

	if (estado.light){
		gluLookAt(eye[0], eye[1], eye[2], estado.camera.center[0], estado.camera.center[1], estado.camera.center[2], 0, 0, 1);
		putLights((GLfloat*)white_light);
	}
	else{
		putLights((GLfloat*)white_light);
		gluLookAt(eye[0], eye[1], eye[2], estado.camera.center[0], estado.camera.center[1], estado.camera.center[2], 0, 0, 1);
	}
	//cout << "gluLookat(" << eye[0] << " - " << eye[1] << " - " << eye[2] << " - " << estado.camera.center[0] << " - " << estado.camera.center[1] << " - " << estado.camera.center[2] << endl;
}

void setCameraMiniMapa(){
	Vertice eye;

	GLfloat dist = (100) -20;
	GLfloat longit = (-M_PI / 4) - 4;
	GLfloat latit = (M_PI / 4) + 6;

	eye[0] = 0 + dist*cos(longit)*cos(latit);
	eye[1] = 0 + dist*sin(longit)*cos(latit);
	eye[2] = 0 + dist*sin(latit);

	putLights((GLfloat*)white_light);
	//gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 0, 1);
	gluLookAt(46.33, 60.06, -46.55, 0, 0, 0, 0, 0, 1);

}

void display(void)
{

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	glLoadIdentity();
	setCamera();

	material(slate);

	//---
	//if(gameIsOver)
	//glColor3f(0, 1, 0);
	//strokeCenterString("Congratulations!! You just", estado.camera.posx, estado.camera.posy+75, estado.camera.posz*5, 0.05);
	//strokeCenterString("Congratulations!! You just", estado.camera.center[0], estado.camera.center[2], estado.camera.center[1], 0.05);
	//strokeCenterString(" made a new friend!!", 0, 0, 0, 0.05);
	//glColor3f(0, 0, 0);
	//strokeCenterString("Press ESC to exit!!", 0, 0, -2, 0.051);
	//---

	desenhaSkyBox();
	//desenhaSolo(texID[ID_TEXTURA_CHAO]);


	desenhaEixos();

	desenhaLabirinto();
	humor();

	//desenha chuva
	if (estado.chuva){
		glPushMatrix();
		chuva();
		glutPostRedisplay();
		glPopMatrix();
	}

	if (estado.eixoTranslaccao) {
		// desenha plano de translacção
		cout << "Translate... " << estado.eixoTranslaccao << endl;
		desenhaPlanoDrag(estado.eixoTranslaccao);

	}


	//--------------DRAW MINIMAP

	glClear(GL_DEPTH_BUFFER_BIT);
	glScissor(0, 0, 100, 100);
	glViewport(0, 0, 100, 100);

	glLoadIdentity();
	setCameraMiniMapa();

	material(slate);

	desenhaSkyBox();
	//desenhaSolo();

	desenhaEixos();

	desenhaLabirinto();

	//desenha chuva
	if (estado.chuva){
		glPushMatrix();
		chuva();
		glutPostRedisplay();
		glPopMatrix();
	}

	if (estado.eixoTranslaccao) {
		// desenha plano de translacção
		cout << "Translate... " << estado.eixoTranslaccao << endl;
		desenhaPlanoDrag(estado.eixoTranslaccao);

	}
	
	glClear(GL_DEPTH_BUFFER_BIT);
	glScissor(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	glFlush();
	glutSwapBuffers();

}



void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'h':
	case 'H':
		imprime_ajuda();
		break;
	case 'l':
	case 'L':
		if (estado.lightViewer)
			estado.lightViewer = 0;
		else
			estado.lightViewer = 1;
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.lightViewer);
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		estado.light = !estado.light;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		glutPostRedisplay();
		break;
	case 'n':
	case 'N':
		estado.apresentaNormais = !estado.apresentaNormais;
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		initEstado();
		initModelo();
		glutPostRedisplay();
		break;
	case 'v':
	case 'V':
		if (estado.camera.pessoa == 3)
			estado.camera.pessoa = 1;
		else
			estado.camera.pessoa = 3;
		glutPostRedisplay();
		break;
	}
}

void colisaoArcoVertical(No *noi, No *nof, int i, GLfloat x, GLfloat y){
	GLfloat ang = atan2((nof->y - noi->y), (nof->x - noi->x));
	GLfloat x2 = (x - noi->x) * cos(ang) + (y - noi->y) * sin(ang);
	GLfloat y2 = (y - noi->y) * cos(ang) - (x - noi->x) * sin(ang);
	double dist = sqrt(0 + pow(nof->y - noi->y, 2) + pow(nof->z - noi->z, 2));
	if (0 < x2 && x2 < dist && -1 * .5 <= y2 && y2 <= 1 * .5){
		cout << "ARCO[" << i << "]" << endl;
		estado.camera.posx = x * 5;
		estado.camera.posy = y * 5;
		estado.camera.posz = (noi->z) * 5 + (x2 / dist) * 1 + 12;
	}
}
void colisaoArcoHorizontal(No *noi, No *nof, int i, GLfloat x, GLfloat y){
	GLfloat ang = atan2((nof->x - noi->x), (nof->y - noi->y));
	//double ang2 = 90 + atan2(nof->z - noi->z, nof->y - noi->y) * 180 / M_PI + 180;
	GLfloat x2 = (y - noi->y) * cos(ang) + (x - noi->x) * sin(ang);
	GLfloat y2 = (x - noi->x) * cos(ang) - (y - noi->y) * sin(ang);
	double dist = sqrt(0 + pow(nof->x - noi->x, 2) + pow(nof->z - noi->z, 2));
	if (0 < x2 && x2 < dist && -1 * .5 <= y2 && y2 <= 1 * .5){
		cout << "ARCO[" << i << "]" << endl;
		estado.camera.posx = x * 5;
		estado.camera.posy = y * 5;
		estado.camera.posz = (noi->z) * 5 + (x2 / dist) * 1 + 12;
	}
}

void colisaoArcos(GLfloat x, GLfloat y, GLfloat z){
	for (int i = 0; i < numArcos; i++){
		No *noi, *nof;

		noi = &nos[arcos[i].noi];
		nof = &nos[arcos[i].nof];

		colisaoArcoVertical(noi, nof, i, x, y);
		colisaoArcoHorizontal(noi, nof, i, x, y);

	}
}

void colisaoNos(GLfloat x, GLfloat y, GLfloat z){
	for (int i = 0; i < numNos; i++){
		if (pow(x - nos[i].x, 2) + pow(y - nos[i].y, 2) <= pow(1, 2)){
			cout << "NO[" << i << "]" << endl;
			if (nos[i].getTipo()=='F'){
				cout << "GANHOU!" << endl;
				glColor3f(0,1,0);
		strokeCenterString("Congratulations!! You just", 0, 1, 0, 0.01);
		strokeCenterString(" made a new friend!!", 0, 0, 0, 0.01);
		glColor3f(0, 0, 0);
		strokeCenterString("Press ESC to exit!!", 0, -2, 0, 0.01);
			}
			estado.camera.posx = x * 5;
			estado.camera.posy = y * 5;
			estado.camera.posz = nos[i].z * 5 + 12;
		}
	}
}

void Special(int key, int x, int y){

	switch (key){
	case GLUT_KEY_F1:
		gravaGrafo();
		break;
	case GLUT_KEY_F2:
		leGrafo();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F6:
		numNos = numArcos = 0;
		/*addNo(No(0, 10, 0));  // 0
		addNo(criaNo(0, 5, 0));  // 1
		addNo(criaNo(-5, 5, 0));  // 2
		addNo(criaNo(5, 5, 0));  // 3
		addNo(criaNo(-5, 0, 0));  // 4
		addNo(criaNo(5, 0, 0));  // 5
		addNo(criaNo(-5, -5, 0));  // 6
		addArco(criaArco(0, 1, 1, 1));  // 0 - 1
		addArco(criaArco(1, 2, 1, 1));  // 1 - 2
		addArco(criaArco(1, 3, 1, 1));  // 1 - 3
		addArco(criaArco(2, 4, 1, 1));  // 2 - 4
		addArco(criaArco(3, 5, 1, 1));  // 3 - 5
		addArco(criaArco(4, 5, 1, 1));  // 4 - 5
		addArco(criaArco(4, 6, 1, 1));  // 4 - 6*/
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		if (estado.camera.pessoa == 3)
			estado.camera.dist -= 1;
		else
		{
			GLfloat x = (estado.camera.posx + estado.camera.vel * cos(estado.camera.dir))*.2;
			GLfloat y = (estado.camera.posy - estado.camera.vel * sin(estado.camera.dir))*.2;
			GLfloat z = (estado.camera.posz)*.2;
			colisaoArcos(x, y, z);
			colisaoNos(x, y, z);
		}						 
		glutPostRedisplay();
	break;
	case GLUT_KEY_DOWN:
		if (estado.camera.pessoa == 3)
			estado.camera.dist += 1;
		else
		{
			GLfloat x = (estado.camera.posx - estado.camera.vel * cos(estado.camera.dir))*.2;
			GLfloat y = (estado.camera.posy + estado.camera.vel * sin(estado.camera.dir))*.2;
			GLfloat z = (estado.camera.posz)*.2;
			colisaoArcos(x, y, z);
			colisaoNos(x, y, z);
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:

		estado.camera.dir -= .2;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:

		estado.camera.dir += .2;
		glutPostRedisplay();
		break;
	}
}



void setProjection(int x, int y, GLboolean picking){
	glLoadIdentity();
	if (picking) { // se está no modo picking, lê viewport e define zona de picking
		GLint vport[4];
		glGetIntegerv(GL_VIEWPORT, vport);
		gluPickMatrix(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 4, 4, vport); // Inverte o y do rato para corresponder à jana
	}

	gluPerspective(estado.camera.fov, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1, 500);

}

void myReshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	setProjection(0, 0, GL_FALSE);
	glMatrixMode(GL_MODELVIEW);
}

void motionRotate(int x, int y){
#define DRAG_SCALE	0.01
	double lim = M_PI / 2 - 0.1;
	estado.camera.dir_long += (estado.xMouse - x)*DRAG_SCALE;
	estado.camera.dir_lat -= (estado.yMouse - y)*DRAG_SCALE*0.5;
	if (estado.camera.dir_lat > lim)
		estado.camera.dir_lat = lim;
	else
	if (estado.camera.dir_lat < -lim)
		estado.camera.dir_lat = -lim;
	estado.xMouse = x;
	estado.yMouse = y;
	glutPostRedisplay();
}

void motionZoom(int x, int y){
#define ZOOM_SCALE	0.5
	estado.camera.dist -= (estado.yMouse - y)*ZOOM_SCALE;
	if (estado.camera.dist<5)
		estado.camera.dist = 5;
	else
	if (estado.camera.dist>200)
		estado.camera.dist = 200;
	estado.yMouse = y;
	glutPostRedisplay();
}

void motionDrag(int x, int y){
	GLuint buffer[100];
	GLint vp[4];
	GLdouble proj[16], mv[16];
	int n;
	GLdouble newx, newy, newz;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projecção
	glLoadIdentity();
	setProjection(x, y, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCamera();
	desenhaPlanoDrag(estado.eixoTranslaccao);

	n = glRenderMode(GL_RENDER);
	if (n > 0) {
		glGetIntegerv(GL_VIEWPORT, vp);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		glGetDoublev(GL_MODELVIEW_MATRIX, mv);
		gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, (double)buffer[2] / UINT_MAX, mv, proj, vp, &newx, &newy, &newz);
		printf("Novo x:%lf, y:%lf, z:%lf\n\n", newx, newy, newz);
		switch (estado.eixoTranslaccao) {
		case EIXO_X:
			estado.eixo[0] = newx;
			//estado.eixo[1]=newy;
			break;
		case EIXO_Y:
			estado.eixo[1] = newy;
			//estado.eixo[2]=newz;
			break;
		case EIXO_Z:
			//estado.eixo[0]=newx;
			estado.eixo[2] = newz;
			break;
		}
		glutPostRedisplay();
	}


	glMatrixMode(GL_PROJECTION); //repõe matriz projecção
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int picking(int x, int y){
	int i, n, objid = 0;
	double zmin = 10.0;
	GLuint buffer[100], *ptr;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projecção
	glLoadIdentity();
	setProjection(x, y, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCamera();
	desenhaEixos();

	n = glRenderMode(GL_RENDER);
	if (n > 0)
	{
		ptr = buffer;
		for (i = 0; i < n; i++)
		{
			if (zmin >(double) ptr[1] / UINT_MAX) {
				zmin = (double)ptr[1] / UINT_MAX;
				objid = ptr[3];
			}
			ptr += 3 + ptr[0]; // ptr[0] contem o número de nomes (normalmente 1); 3 corresponde a numnomes, zmin e zmax
		}
	}


	glMatrixMode(GL_PROJECTION); //repõe matriz projecção
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	return objid;
}
void mouse(int btn, int state, int x,  int y){
	switch (btn) {
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN){
			estado.xMouse = x;
			estado.yMouse = y;
			if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
				glutMotionFunc(motionZoom);
			else
				glutMotionFunc(motionRotate);
			cout << "Left down\n";
		}
		else{
			glutMotionFunc(NULL);
			cout << "Left up\n";
		}
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			estado.eixoTranslaccao = picking(x, y);
			if (estado.eixoTranslaccao)
				glutMotionFunc(motionDrag);
			cout << "Right down - objecto:" << estado.eixoTranslaccao << endl;
		}
		else{
			if (estado.eixoTranslaccao != 0) {
				estado.camera.center[0] = estado.eixo[0];
				estado.camera.center[1] = estado.eixo[1];
				estado.camera.center[2] = estado.eixo[2];
				glutMotionFunc(NULL);
				estado.eixoTranslaccao = 0;
				glutPostRedisplay();
			}
			cout << "Right up\n";
		}
		break;
	}
}

void createTextures(GLuint texID[])
{
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture
	char *image;
	int w, h, bpp;

//	glGenTextures(1, texID);
	

	memset(TextureImage, 0, sizeof(void *)* 1);           	// Set The Pointer To NULL
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	
	

	//Para criar a textura do chao em jpeg-----------------------------------------
	/*if (read_JPEG_file(NOME_TEXTURA_CHAO, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, texID[ID_TEXTURA_CHAO]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else{
		printf("Textura %s not Found\n", NOME_TEXTURA_CHAO);
		exit(0);
	}*/

	//Para criar a textura da skybox em jpeg-----------------------------------------
	if (read_JPEG_file(NOME_TEXTURA_SKYBOX, &image, &w, &h, &bpp)){
		glBindTexture(GL_TEXTURE_2D, textIDSkybox);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
		free(image);
	}
	else{
		printf("Textura %s not Found\n", NOME_TEXTURA_SKYBOX);
		exit(0);
	}

	if (tgaLoad(NOME_TEXTURA_SUN))
	{
		tgaInfo *img;
		glEnable(GL_DEPTH_TEST);

		img = tgaLoad("img/sun.tga");
		glGenTextures(1, &textIDSun);
		glBindTexture(GL_TEXTURE_2D, textIDSun);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, img->imageData);

		glDisable(GL_DEPTH_TEST);
	}
	else{
		printf("Textura %s not Found\n", NOME_TEXTURA_SUN);
		exit(0);
	}


	glBindTexture(GL_TEXTURE_2D, NULL);
}

void main(int argc, char **argv)
{


	if (/*login()*/true){
		glutInit(&argc, argv);
		/*need both double buffering and z buffer*/
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(640, 480);
		glutCreateWindow("OpenGL");
		glutReshapeFunc(myReshape);
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(Special);
		glutMouseFunc(mouse);

		texID[0] = textIDSkybox;
		texID[1] = textIDSun;

		createTextures(texID);

		myInit();

		imprime_ajuda();

		glutMainLoop();
	}
	else{

	}



}
