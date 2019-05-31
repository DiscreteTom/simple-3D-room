#include "gl/glut.h"
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

void buildRoom(){
	glPushMatrix(); // save camera matrix

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