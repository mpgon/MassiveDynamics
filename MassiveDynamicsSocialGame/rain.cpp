/**************************************
*                                     *
*          Demo Realizada por:        *
*          Javier Barandiaran         *
*   www.geocities.com/opengladiator/  *
*                2002                 *
*                                     *
**************************************/

#include <windows.h>
#include <gl\gl.h>		
#include <math.h>
#include "rain.h"

void InicializarChuva(CHUVA &rain, int numgotas)
{

	//	fade;
	//	x, y, z;       coordenadas do cubo que vai conter a chuva
	//	grosor;        espessura da chuva
	//	longitud;      longitude das gotas
	//	xg, yg, zg;    gravidade em cada eixo
		
	rain.grosor = 0.4f;
	rain.x = 7;
	rain.y = 12;
	rain.z = 7;
	rain.xg = 0.0f;
	rain.yg = -0.002f;
	rain.zg = 0.0f;
	rain.fade = -1;
	rain.longitud = -2;
	rain.gotas = new GOTA[numgotas];

	for (int i = 0; i<numgotas; i++)
	{
		//  xt, yt, zt;    coordenadas extremo superior
		//	xd, yd, zd;    coordenadas extremo inferior
		//	xv, yv, zv;    velocidade em cada eixo
		//	visib;         visibilidade para o canal alpha
		rain.gotas[i].visib = 0.0f;
		rain.gotas[i].xd = float(((rand() % (rain.x * 20)) - rain.x*10.0f) / 10.0f);
		rain.gotas[i].yd = 1.0;
		rain.gotas[i].zd = float(((rand() % (rain.z * 20)) - (rain.z)*10.0f) / 10.0f);
		rain.gotas[i].xt = rain.gotas[i].xd;
		rain.gotas[i].yt = 1.0;
		rain.gotas[i].zt = rain.gotas[i].zd;
		rain.gotas[i].xv = 0.0f;
		rain.gotas[i].yv = (rand() % 1000) / -10000.0f;
		rain.gotas[i].zv = 0.0f;

	}
}

void DesenharChuva(CHUVA &rain, int numgotas, GLfloat x, GLfloat y, GLfloat z)
{
	glDisable(GL_LIGHTING);
	glLineWidth(rain.grosor);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glTranslatef(x,y,z);
	glRotatef(90,1,0,0);

	for (int i = 0; i<numgotas; i++)
	{
		
		glBegin(GL_LINES);
		//glColor4f(0.2f,0.2f,0.2f,rain.gotas[i].visib);
		glVertex3f(rain.gotas[i].xd, rain.gotas[i].yd, rain.gotas[i].zd);
		//glColor4f(0.1f,0.1f,0.2f,rain.gotas[i].visib-0.1f);
		glVertex3f(rain.gotas[i].xt, rain.gotas[i].yt, rain.gotas[i].zt);
		glEnd();
		
		rain.gotas[i].visib += rain.fade;
		rain.gotas[i].xd += rain.gotas[i].xv;
		rain.gotas[i].xt += rain.gotas[i].xv - rain.gotas[i].xv*0.01f;
		rain.gotas[i].xv += rain.xg;
		rain.gotas[i].yd += rain.gotas[i].yv;
		rain.gotas[i].yt += rain.gotas[i].yv;
		rain.gotas[i].yv += rain.yg;
		rain.gotas[i].zd += rain.gotas[i].zv;
		rain.gotas[i].zt += rain.gotas[i].zv - rain.gotas[i].zv*0.01f;
		rain.gotas[i].zv += rain.zg;

		if (rain.gotas[i].yt<-1)
		{
			rain.gotas[i].visib = 0.0f;
			rain.gotas[i].xd = float(((rand() % (rain.x * 20)) - rain.x*10.0f)*0.1f);
			rain.gotas[i].yd = float(rain.y);
			rain.gotas[i].zd = float(((rand() % (rain.z * 20)) - (rain.z)*10.0f)*0.1f);
			rain.gotas[i].xt = rain.gotas[i].xd;
			rain.gotas[i].yt = rain.gotas[i].yd + rain.longitud;
			rain.gotas[i].zt = rain.gotas[i].zd;
			rain.gotas[i].xv = 0.0f;
			rain.gotas[i].yv = (rand() % 1000)*(-0.001f);
			rain.gotas[i].zv = 0.0f;
		}

	}
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
}