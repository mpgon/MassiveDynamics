#include "JogoEnforcado.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <vector>
#include <GL/glut.h>
using namespace std;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEBUG 1



//-------------------------------------------------------------------------
//  Variaveis Globais
//-------------------------------------------------------------------------
typedef struct {
	GLboolean   doubleBuffer;
	GLint       delay;
}Estado;

typedef struct {
	GLfloat   cabecaX;
	GLfloat   cabecaY;
	GLfloat	  cabecaRaio;
	///////////////////////////
	GLfloat   corpoComprimento;
	GLfloat   corpoIniX;
	GLfloat   corpoIniY;
	GLfloat   corpoFimX;
	GLfloat   corpoFimY;
	///////////////////////////
	GLfloat   cordaIniX;
	GLfloat   cordaIniY;
	GLfloat   cordaFimX;
	GLfloat   cordaFimY;
	///////////////////////////
	GLfloat   bracoComprimento;
	GLfloat   bracoIniX;
	GLfloat   bracoIniY;
	GLfloat   bracoFimX;
	GLfloat   bracoFimY;
	///////////////////////////
	GLfloat   pernaComprimento;
	GLfloat   pernaIniX;
	GLfloat   pernaIniY;
	///////////////////////////
	GLfloat   barraHorizontalIniX;
	GLfloat   barraHorizontalIniY;
	GLfloat   barraHorizontalFimX;
	GLfloat   barraHorizontalFimY;
	///////////////////////////
	GLfloat   barraVerticalIniX;
	GLfloat   barraVerticalIniY;
	GLfloat   barraVerticalFimX;
	GLfloat   barraVerticalFimY;
	///////////////////////////
	GLfloat   baseIniX;
	GLfloat   baseIniY;
	GLfloat   baseFimX;
	GLfloat   baseFimY;
}Enforcado;

Estado estado;
Enforcado enforcado;
char* palavras[] = { "amalia rodrigues", "castelo branco", "eca de queiros", "institucionalizacao", "rosa dos ventos" };
//char* abc[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
char* abc = "abcdefghijklmnopqrstuvwxyz";
int NUMTOTALPALAVRAS; // Inicializado no main de forma a ser dinamico conforme actualizacao do array
char* PALAVRA;
vector<char> vecLetrasErradas;
vector<char> vecLetrasCorrectas;
int TENTATIVAS;
float ang;

//-------------------------------------------------------------------------
//  Inicialização das variaveis
//-------------------------------------------------------------------------
void Init(void)
{
	TENTATIVAS = 0;
	ang = 0;

	enforcado.baseIniX = -0.6;
	enforcado.baseIniY = -0.7;
	enforcado.baseFimX = 0.5;
	enforcado.baseFimY = -0.7;
	/////////////////////////////////////
	enforcado.barraVerticalIniX = -0.5;
	enforcado.barraVerticalIniY = -0.7;
	enforcado.barraVerticalFimX = -0.5;
	enforcado.barraVerticalFimY = 0.2;
	//////////////////////////////////////
	enforcado.barraHorizontalIniX = -0.5;
	enforcado.barraHorizontalIniY = 0.2;
	enforcado.barraHorizontalFimX = 0;
	enforcado.barraHorizontalFimY = 0.2;
	/////////////////////////////////
	enforcado.cordaIniX = 0;
	enforcado.cordaIniY = 0.1;
	enforcado.cordaFimX = 0;
	enforcado.cordaFimY = 0.2;
	///////////////////////////////
	enforcado.cabecaX = 0;
	enforcado.cabecaY = 0;
	enforcado.cabecaRaio = 0.1;
	///////////////////////////////
	enforcado.corpoComprimento = 0.3;
	enforcado.corpoIniX = 0;
	enforcado.corpoIniY = -enforcado.cabecaRaio;
	enforcado.corpoFimX = 0;
	enforcado.corpoFimY = -(enforcado.cabecaRaio + enforcado.corpoComprimento);
	///////////////////////////////
	enforcado.bracoComprimento = 0.1 + enforcado.corpoComprimento / 2;
	enforcado.bracoIniX = 0;
	enforcado.bracoIniY = -(enforcado.corpoComprimento / 2);
	enforcado.bracoFimX = enforcado.bracoComprimento;
	enforcado.bracoFimY = -(enforcado.bracoComprimento);
	///////////////////////////////
	enforcado.pernaComprimento = 0.1 + enforcado.corpoComprimento / 2;
	enforcado.pernaIniX = 0;
	enforcado.pernaIniY = -(enforcado.corpoComprimento + enforcado.cabecaRaio);

	

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

}

//-------------------------------------------------------------------------
//  Callback para redimensionar janela
//-------------------------------------------------------------------------
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
	for (int i = 0; i < strlength; i++){
		glutBitmapCharacter(font_style, text[i]);
	}
}

//-------------------------------------------------------------------------
//  Desenhar letra em coordenadas especificadas
//-------------------------------------------------------------------------
void printLetra(float x, float y, float z, char* text, int pos)
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

	glRasterPos3f(x, y, z); // Posicionamento

	// Imprimir caracter
	glutBitmapCharacter(font_style, text[pos]);
	
}

//-------------------------------------------------------------------------
//  Desenhar base
//-------------------------------------------------------------------------
void desenhaBase()
{
	glLineWidth(2);

	glBegin(GL_LINES);
	glVertex2f(enforcado.baseIniX, enforcado.baseIniY);
	glVertex2f(enforcado.baseFimX, enforcado.baseFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar barra vertical
//-------------------------------------------------------------------------
void desenhaBarraVertical()
{
	glLineWidth(2);

	glBegin(GL_LINES);
	glVertex2f(enforcado.barraVerticalIniX, enforcado.barraVerticalIniY);
	glVertex2f(enforcado.barraVerticalFimX, enforcado.barraVerticalFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar barra horizontal
//-------------------------------------------------------------------------
void desenhaBarraHorizontal()
{
	glLineWidth(2);

	glBegin(GL_LINES);
	glVertex2f(enforcado.barraHorizontalIniX, enforcado.barraHorizontalIniY);
	glVertex2f(enforcado.barraHorizontalFimX, enforcado.barraHorizontalFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar corda
//-------------------------------------------------------------------------
void desenhaCorda()
{
	glLineWidth(2);

	glBegin(GL_LINES);
	glVertex2f(enforcado.cordaIniX, enforcado.cordaIniY);
	glVertex2f(enforcado.cordaFimX, enforcado.cordaFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar cabeca
//-------------------------------------------------------------------------
void desenhaCabeca()
{
	GLint numLados = 60;
	GLfloat ang = 2 * M_PI / numLados;
	GLint i;

	glLineWidth(3);

	//ang = 2 * M_PI / 60;
	glBegin(GL_LINES);
	for (i = 0; i<60; i++)
	{
		glVertex2f(enforcado.cabecaX + enforcado.cabecaRaio*cos(ang*i), enforcado.cabecaY + enforcado.cabecaRaio*sin(ang*i));
		glVertex2f(enforcado.cabecaX + enforcado.cabecaRaio*cos(ang*i + 0.1), enforcado.cabecaY + enforcado.cabecaRaio*sin(ang*i + 0.1));
	}
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar corpo
//-------------------------------------------------------------------------
void desenhaCorpo()
{
	glLineWidth(3);

	glBegin(GL_LINES);
	glVertex2f(enforcado.corpoIniX, enforcado.corpoIniY);
	glVertex2f(enforcado.corpoFimX, enforcado.corpoFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar braco direito
//-------------------------------------------------------------------------
void desenhaBracoD()
{
	glLineWidth(3);

	glBegin(GL_LINES);
	glVertex2f(enforcado.bracoIniX, enforcado.bracoIniY);
	glVertex2f(enforcado.bracoFimX, enforcado.bracoFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar braco esquerdo
//-------------------------------------------------------------------------
void desenhaBracoE()
{
	glLineWidth(3);

	glBegin(GL_LINES);
	glVertex2f(enforcado.bracoIniX, enforcado.bracoIniY);
	glVertex2f(-enforcado.bracoFimX, enforcado.bracoFimY);
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar perna direita
//-------------------------------------------------------------------------
void desenhaPernaD()
{
	GLint numLados = 10;
	GLfloat ang = 2 * M_PI / numLados;

	glLineWidth(3);

	//ang = 2 * M_PI / 60;
	glBegin(GL_LINES);
	glVertex2f(enforcado.pernaIniX, enforcado.pernaIniY);
	glVertex2f(enforcado.pernaIniX + enforcado.pernaComprimento*cos(ang), enforcado.pernaIniY + -enforcado.pernaComprimento*sin(ang));
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar perna esquerda
//-------------------------------------------------------------------------
void desenhaPernaE()
{
	GLint numLados = 10;
	GLfloat ang = 2 * M_PI / numLados;

	glLineWidth(3);

	//ang = 2 * M_PI / 60;
	glBegin(GL_LINES);
	glVertex2f(enforcado.pernaIniX, enforcado.pernaIniY);
	glVertex2f(enforcado.pernaIniX + -enforcado.pernaComprimento*cos(ang), enforcado.pernaIniY + -enforcado.pernaComprimento*sin(ang));
	glEnd();
}

//-------------------------------------------------------------------------
//  Desenhar palavra														AJUSTAR POSICAO
//-------------------------------------------------------------------------
void desenharPalavra(){
	int numChar;
	numChar = strlen(PALAVRA); // Tamanho do texto
	float mid = (numChar / 2);
	printWord(-mid, -0.9, 0, PALAVRA);
}

//-------------------------------------------------------------------------
//  Verificar se letra foi usada
//-------------------------------------------------------------------------
int vecsContem(char letra)
{
	if (std::find(vecLetrasErradas.begin(), vecLetrasErradas.end(), letra) != vecLetrasErradas.end()) {
		return 1;
	}
	else if (std::find(vecLetrasCorrectas.begin(), vecLetrasCorrectas.end(), letra) != vecLetrasCorrectas.end()) {
		return 1;
	}
	else{
		return 0;
	}
}

//-------------------------------------------------------------------------
//  Verificar se pertence a palavra											SUBSTITUIR POR PROLOG
//-------------------------------------------------------------------------
int letraPertence(char letra)
{
	int strlength;
	strlength = strlen(PALAVRA);

	for (int i = 0; i < strlength; i++){
		if (PALAVRA[i] == letra){
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------------
//  Imprime corectas selecionadas
//-------------------------------------------------------------------------
void printLetrasPalavra()
{
	int length;
	length = strlen(PALAVRA);
	
		for (int i = 0; i < length; i++){
			if (vecsContem(PALAVRA[i]) == 1){
				printLetra((-1 + i*0.1), -0.9, 0, PALAVRA, i);
			}
			else if (PALAVRA[i] == ' '){
				printLetra((-1 + i*0.1), -0.9, 0, " ", 0);
			}
			else{
				printLetra((-1 + i*0.1), -0.9, 0, "_", 0);
			}
		}
}

//-------------------------------------------------------------------------
//  Imprime letras usadas
//-------------------------------------------------------------------------
void printLetrasUsadas()
{
	int length;
	int k = 0;
	length = strlen(abc);

	printWord(-1,0.9,0,"Letras Usadas:");

	for (int i = 0; i < length; i++){
		if (vecsContem(abc[i]) == 1){
			k = i;
			if (i<20){				
				printLetra((-1 + k*0.1), 0.8, 0, abc, i);
			}
			else if (i<26){
				printLetra((-1 + (k-20)*0.1), 0.7, 0, abc, i);
			}
			else{
				printLetra((-1 + (k - 20)*0.1), 0.6, 0, abc, i);
			}
			
		}
	}
}

//-------------------------------------------------------------------------
//  Construir enforcado
//-------------------------------------------------------------------------
void desenhaBoneco(){

	switch (TENTATIVAS){
	case 10:
		desenhaPernaD();
	case 9:
		desenhaPernaE();
	case 8:
		desenhaBracoD();
	case 7:
		desenhaBracoE();
	case 6:
		desenhaCorpo();
	case 5:
		desenhaCabeca();
	case 4:
		desenhaCorda();
	case 3:
		desenhaBarraHorizontal();
	case 2:
		desenhaBarraVertical();
	case 1:
		desenhaBase();
		break;

	}

	glutPostRedisplay();

}

//-------------------------------------------------------------------------
//  Tratar evento: letra carregada
//-------------------------------------------------------------------------
void letraCarregada(char letra)
{
	
	if (vecsContem(letra) == 0){ // Se nao foi usada
		// Verificar se letra esta contido na palavra
		if (letraPertence(letra) == 0){ // Se nao conter letra
			TENTATIVAS++;
			desenhaBoneco();
			vecLetrasErradas.push_back(letra);
		}
		else{
			vecLetrasCorrectas.push_back(letra);
		}
	}
	else{
		//REPETIDA
	}
	

}

//-------------------------------------------------------------------------
//  Callback de desenho
//-------------------------------------------------------------------------
void Draw(void)
{

	glClear(GL_COLOR_BUFFER_BIT);


	if (TENTATIVAS < 10){
		printLetrasPalavra();
		desenhaBoneco();
		printLetrasUsadas();
	}
	else{
		printLetrasUsadas();
		printWord(-1, -0.9, 0, "PERDEU");

		//											Animacao baloucar do boneco
		desenhaBase();
		desenhaBarraVertical();
		desenhaBarraHorizontal();
		glRotated(ang,0,0,1);
		desenhaCorda();
		desenhaCabeca();
		desenhaCorpo();
		desenhaBracoE();
		desenhaBracoD();
		desenhaPernaE();
		desenhaPernaD();
		glRotated(-ang, 0, 0, 1);
		ang++;
	}

	glFlush();
	if (estado.doubleBuffer)
		glutSwapBuffers();

}

//-------------------------------------------------------------------------
//  Callback de temporizador
//-------------------------------------------------------------------------
void Timer(int value)
{
}

//-------------------------------------------------------------------------
//  Callback de teclado
//-------------------------------------------------------------------------
void Key(unsigned char key, int x, int y)
{

	switch (key) {
	case 27:
		exit(1);
	case 'a':
	case 'A':
		letraCarregada('a');
		break;
	case 'b':
	case 'B':
		letraCarregada('b');
		break;
	case 'c':
	case 'C':
		letraCarregada('c');
		break;
	case 'd':
	case 'D':
		letraCarregada('d');
		break;
	case 'e':
	case 'E':
		letraCarregada('e');
		break;
	case 'f':
	case 'F':
		letraCarregada('f');
		break;
	case 'g':
	case 'G':
		letraCarregada('g');
		break;
	case 'h':
	case 'H':
		letraCarregada('h');
		break;
	case 'i':
	case 'I':
		letraCarregada('i');
		break;
	case 'j':
	case 'J':
		letraCarregada('j');
		break;
	case 'k':
	case 'K':
		letraCarregada('k');
		break;
	case 'l':
	case 'L':
		letraCarregada('l');
		break;
	case 'm':
	case 'M':
		letraCarregada('m');
		break;
	case 'n':
	case 'N':
		letraCarregada('n');
		break;
	case 'o':
	case 'O':
		letraCarregada('o');
		break;
	case 'p':
	case 'P':
		letraCarregada('p');
		break;
	case 'q':
	case 'Q':
		letraCarregada('q');
		break;
	case 'r':
	case 'R':
		letraCarregada('r');
		break;
	case 's':
	case 'S':
		letraCarregada('s');
		break;
	case 't':
	case 'T':
		letraCarregada('t');
		break;
	case 'u':
	case 'U':
		letraCarregada('u');
		break;
	case 'v':
	case 'V':
		letraCarregada('v');
		break;
	case 'w':
	case 'W':
		letraCarregada('w');
		break;
	case 'x':
	case 'X':
		letraCarregada('x');
		break;
	case 'y':
	case 'Y':
		letraCarregada('y');
		break;
	case 'z':
	case 'Z':
		letraCarregada('z');
		break;
	}

	glutPostRedisplay();

	//if (DEBUG)
	//	printf("Carregou na tecla %c\n", key);

}

//-------------------------------------------------------------------------
//  Selecionar palavra aleatorio
//-------------------------------------------------------------------------
void gerarPalavra(){
	srand(time(0)); // Garantir numero gerado é aleatorio
	int numRand = (rand() % NUMTOTALPALAVRAS);
	PALAVRA = palavras[numRand];
}

int main(int argc, char **argv)
{
	// Defenir variavel conforme numero de palavras no array
	NUMTOTALPALAVRAS = sizeof(palavras)/sizeof(char*);

	estado.doubleBuffer = GL_TRUE;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);

	glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
	if (glutCreateWindow("Jogo Do Enforcado") == GL_FALSE)
		exit(1);


	// Selecionar palavra
	gerarPalavra();

	Init();





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
