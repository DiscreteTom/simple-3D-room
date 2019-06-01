#include "gl/glut.h"
#include <vector>
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

double radians(double degree);
void buildCylinder(double radius, double height, int slices, bool line);

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
	} table;
	struct
	{
		double radius = 0.4;
	} sphere;
	struct
	{
		double radius = 0.4;
		double height = 1;
	} cone;
	struct
	{
		double radius = 0.5;
		double height = 1;
	} cylinder;
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
	glTranslated(room.table.centerX + 1, room.table.centerY + room.table.lenY / 2 + room.sphere.radius, room.table.centerZ);
	glutWireSphere(room.sphere.radius, 25, 25);
	glPopMatrix();

	// build cone
	glPushMatrix();
	glTranslated(room.table.centerX + 2, room.table.centerY + room.table.lenY / 2, room.table.centerZ);
	glRotatef(90, -1, 0, 0);
	glutWireCone(room.cone.radius, room.cone.height, 25, 25);
	glPopMatrix();

	// build cylinder
	glPushMatrix();
	glTranslated(room.table.centerX, room.table.centerY + room.table.lenY / 2 + room.cylinder.height / 2, room.table.centerZ);
	buildCylinder(room.cylinder.radius, room.cylinder.height, 50, true);
	glPopMatrix();

	//
	glPushMatrix();
	glPopMatrix();

	//
	glPushMatrix();
	glPopMatrix();

	//
	glPushMatrix();
	glPopMatrix();

	//
	glPushMatrix();
	glPopMatrix();
}

// build a cylinder, use (0, 0, 0) as center, Y as axis
void buildCylinder(double radius, double height, int slices, bool line = false)
{
	// calculate x and y
	std::vector<double> x;
	std::vector<double> z;
	for (int i = 0; i < slices; ++i)
	{
		x.push_back(radius * cos(radians(360 / slices * i)));
		z.push_back(radius * sin(radians(360 / slices * i)));
	}
	// link head and tail
	x.push_back(x[0]);
	z.push_back(z[0]);

	// build underside
	if (line)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);
	for (int i = 0; i < slices; ++i)
	{
		glVertex3d(x[i], height / 2, z[i]);
	}
	glEnd();
	if (line)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);
	for (int i = 0; i < slices; ++i)
	{
		glVertex3d(x[i], -height / 2, z[i]);
	}
	glEnd();

	//build flank
	for (int i = 0; i < slices; ++i)
	{
		if (line)
			glBegin(GL_LINE_LOOP);
		else
			glBegin(GL_POLYGON);
		glVertex3d(x[i], height / 2, z[i]);
		glVertex3d(x[i + 1], height / 2, z[i + 1]);
		glVertex3d(x[i + 1], -height / 2, z[i + 1]);
		glVertex3d(x[i], -height / 2, z[i]);
		glEnd();
	}
}