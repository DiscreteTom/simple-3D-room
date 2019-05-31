#include "gl/glut.h"
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

void buildRoom(){
	// build coordinate axis
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 0);
	glEnd();
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 0);
	glEnd();
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 100);
	glEnd();
	glFlush();
	glPopMatrix();

	// build outerline
	glTranslatef(0, 1.5, 0);
	glScalef(2, 1, 2);
	glutWireCube(3);


	glPopMatrix();
	glPushMatrix();

	// build sphare
	glTranslatef(0, 1, 0);
	glutWireSphere(1, 25, 25);

	glPopMatrix();
}