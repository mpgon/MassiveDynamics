#include <math.h>
#include <stdlib.h>
#include "gl\glut.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>
#include "maths.h"
#include "Billboard.h"
#include "tga.h"
//
//
//void iniciaImagemTga(char *imgNome) {
//	
//	tgaInfo *image;
//
//	glEnable(GL_DEPTH_TEST);
//
//	//image = tgaLoad("img/cloud.tga");
//	
//	
//	image = tgaLoad(imgNome);
//	glBindTexture(GL_TEXTURE_2D, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height,
//		0, GL_RGBA, GL_UNSIGNED_BYTE, image->imageData);
//	
//	glEnable(GL_TEXTURE_2D);
//	
//
//	glDisable(GL_DEPTH_TEST);
//	//glDisable(GL_TEXTURE_2D);
//	
//}
//
//void desenhaImagemTga2(void) {
//
//	/*float pos[3], right[3], up[3];
//
//	if (deltaMove)
//		moveMeFlat(deltaMove);
//	if (deltaUp)
//		Lookup(deltaUp);
//	if (deltaAngle) {
//		angle += deltaAngle;
//		orientMe(angle);
//	}
//	float cam[3] = { x, y, z };
//
//	glLoadIdentity();
//	gluLookAt(x, y, z,
//		x + lx, y + ly, z + lz,
//		0.0f, 1.0f, 0.0f);*/
//
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//
//	//desenha chao
//	/*glColor3f(1.0f, 1.0f, 1.0f);
//	glBegin(GL_QUADS);
//	glVertex3f(-50.0f, 0.0f, -50.0f);
//	glVertex3f(-50.0f, 0.0f, 50.0f);
//	glVertex3f(50.0f, 0.0f, 50.0f);
//	glVertex3f(50.0f, 0.0f, -50.0f);
//	glEnd();*/
//
//	/*glDisable(GL_LIGHTING);
//	glEnable(GL_BLEND);
//	glEnable(GL_DEPTH_TEST);
//	
//	//glTranslatef(0,-1.75,0);
//	
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_ALPHA_TEST);
//	//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
//	glAlphaFunc(GL_GREATER, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);*/
//	
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glDisable(GL_LIGHTING);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_ALPHA_TEST);
//	//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
//	glAlphaFunc(GL_GREATER, 0);
//	//glBindTexture(GL_TEXTURE_2D, 0);
//
//
//	for (int i = 0; i < 1; i++)
//	for (int j = 0; j < 1; j++) {
//		glPushMatrix();
//		glTranslatef(25, 20, 25); //posiçao da imagem 
//		BillboardCheatSphericalBegin();
//
//		glBegin(GL_QUADS);
//		glTexCoord2f(0, 0); glVertex3f(-2.0f, 0.0f, 0.0f);  //tamanho imagem
//		glTexCoord2f(1, 0); glVertex3f(2.0f, 0.0f, 0.0f);
//		glTexCoord2f(1, 1); glVertex3f(2.0f, 4.0f, 0.0f);
//		glTexCoord2f(0, 1); glVertex3f(-2.0f, 4.0f, 0.0f);
//		glEnd();
//
//		glPopMatrix();
//	}
//
//	//glBindTexture(GL_TEXTURE_2D, 0);
//	glDisable(GL_BLEND);
//	glDisable(GL_ALPHA_TEST);
//
//	/*glPushMatrix();
//	glLoadIdentity();
//	renderBitmapString(30,15,(void *)font,s);
//	glPopMatrix();
//	resetPerspectiveProjection();*/
//
//
//	//glutSwapBuffers();
//}