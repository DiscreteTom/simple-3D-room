#include "gl/glut.h"
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

struct
{
	double lenX = 6;
	double lenY = 3;
	double lenZ = 6;
	double centerX = 3;
	double centerY = 1.5;
	double centerZ = 3;
	struct
	{
		double lenX = 5;
		double lenY = 1.2;
		double lenZ = 2;
		double centerX = 3;
		double centerY = 0.6;
		double centerZ = 5;
		struct
		{
			double radius = 0.4;
		} sphere;
		struct
		{
			double radius = 0.4;
			double height = 1;
		} cone;
	} table;
} room;

void buildRoom()
{
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
	glColor3ub(0, 0, 0);
	glPushMatrix(); // save camera matrix
	glTranslated(room.centerX, room.centerY, room.centerZ);
	glScaled(room.lenX, room.lenY, room.lenZ);
	glutWireCube(1);
	glPopMatrix();

	// build table
	glColor3ub(243, 157, 47);
	glPushMatrix();
	glTranslated(room.table.centerX, room.table.centerY, room.table.centerZ);
	glScaled(room.table.lenX, room.table.lenY, room.table.lenZ);
	// glutSolidCube(1);
	glutWireCube(1);
	glPopMatrix();

	// build sphare
	glColor3ub(0, 0, 0);
	glPushMatrix();
	glTranslated(room.table.centerX + 1, room.table.centerY + room.table.lenY / 2 + room.table.sphere.radius, room.table.centerZ);
	glutWireSphere(room.table.sphere.radius, 25, 25);
	glPopMatrix();

	// build cone
	glPushMatrix();
	glTranslated(room.table.centerX + 2, room.table.centerY + room.table.lenY / 2, room.table.centerZ);
	glRotatef(90, -1, 0, 0);
	glutWireCone(room.table.cone.radius, room.table.cone.height, 25, 25);
	glPopMatrix();
}