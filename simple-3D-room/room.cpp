#include "gl/glut.h"
#include <vector>
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

double radians(double degree);
void buildCylinder(double radius, double height, int slices, bool line = false);
void buildPyramid(double bottomLength, double height, bool line = false);
void buildTable();

// size and position data
const struct
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
		double lenY = 1;
		double lenZ = 2;
		double centerX = 3;
		double centerY = 0.5;
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
	struct
	{
		double bottomLength = 0.8;
		double height = 1;
	} pyramid;
} room;

// roof attributes
const struct
{
	double height = 8;
	int xGridNum = 20;
	int zGridNum = 10;
} roof;
// bezier surface control points (for roof)
const int bzPointsNum = 3;
const int bzLinesNum = 3;
const GLdouble ctrlPoints[bzLinesNum][bzPointsNum][3] = {
		{{room.centerX - room.lenX / 2, room.lenY, room.centerZ + room.lenZ / 2},
		 {room.centerX, room.lenY, room.centerZ + room.lenZ / 2},
		 {room.centerX + room.lenX / 2, room.lenY, room.centerZ + room.lenZ / 2}},

		{{room.centerX - room.lenX / 2, room.lenY, room.centerZ},
		 {room.centerX, roof.height + room.lenY, room.centerZ},
		 {room.centerX + room.lenX / 2, room.lenY, room.centerZ}},

		{{room.centerX - room.lenX / 2, room.lenY, room.centerZ - room.lenZ / 2},
		 {room.centerX, room.lenY, room.centerZ - room.lenZ / 2},
		 {room.centerX + room.lenX / 2, room.lenY, room.centerZ - room.lenZ / 2}}};

extern GLuint tex;

void buildRoom()
{
	// build outerline
	glColor3ub(0, 0, 0);
	glPushMatrix(); // save camera matrix
	glTranslated(room.centerX, room.centerY, room.centerZ);
	glScaled(room.lenX, room.lenY, room.lenZ);
	glutWireCube(1);
	glPopMatrix();

	// build table
	buildTable();

	// build sphare
	glColor3ub(255, 0, 0);
	glPushMatrix();
	glTranslated(room.table.centerX + 1, room.table.centerY + room.table.lenY / 2 + room.sphere.radius, room.table.centerZ);
	glutSolidSphere(room.sphere.radius, 25, 25);
	glPopMatrix();

	// build cone
	glColor3ub(0, 255, 0);
	glPushMatrix();
	glTranslated(room.table.centerX + 2, room.table.centerY + room.table.lenY / 2, room.table.centerZ);
	glRotatef(90, -1, 0, 0);
	glutSolidCone(room.cone.radius, room.cone.height, 25, 25);
	glPopMatrix();

	// build cylinder
	glColor3ub(0, 0, 255);
	glPushMatrix();
	glTranslated(room.table.centerX, room.table.centerY + room.table.lenY / 2 + room.cylinder.height / 2, room.table.centerZ);
	buildCylinder(room.cylinder.radius, room.cylinder.height, 50);
	glPopMatrix();

	// build pyramid
	glColor3ub(255, 255, 0);
	glPushMatrix();
	glTranslated(room.table.centerX - 1, room.table.centerY + room.table.lenY / 2, room.table.centerZ);
	buildPyramid(room.pyramid.bottomLength, room.cylinder.height);
	glPopMatrix();

	// build roof (bezier surface)
	glPushMatrix();
	glColor3ub(140, 81, 31);
	glMap2d(													// define a two dimentional evaluator
			GL_MAP2_VERTEX_3,							// target (result)
			room.centerX - room.lenX / 2, // lower bound of x grid
			room.centerX + room.lenX / 2, // upper bound of x grid
			3,														// data invertal in x axis (equals to dimension of points)
			bzPointsNum,									// x axis grid num
			room.centerZ - room.lenZ / 2, // lower bound of z grid
			room.centerZ + room.lenZ / 2, // upper bound of z grid
			3 * bzPointsNum,							// data interval in z axis
			bzLinesNum,										// z axis grid num
			&ctrlPoints[0][0][0]);				// first item of data set
	glEnable(GL_MAP2_VERTEX_3);				// enable evaluator
	glMapGrid2d(roof.xGridNum, room.centerX - room.lenX / 2, room.centerX + room.lenX / 2, roof.zGridNum, room.centerZ - room.lenZ / 2, room.centerZ + room.lenZ / 2);
	// glEvalMesh2(GL_LINE, 0, roof.xGridNum, 0, roof.zGridNum); // calculate grid with line
	glEvalMesh2(GL_FILL, 0, roof.xGridNum, 0, roof.zGridNum); // calculate grid with solid surface
	glPopMatrix();

	// draw bezier control points for debug
	glColor3ub(255, 0, 0);
	glPointSize(10);
	glPushMatrix();
	glBegin(GL_POINTS);
	for (int i = 0; i < bzLinesNum; ++i)
		for (int j = 0; j < bzPointsNum; ++j)
			glVertex3d(ctrlPoints[i][j][0], ctrlPoints[i][j][1], ctrlPoints[i][j][2]);
	glEnd();
	glPopMatrix();

	// build coordinate axis for debug
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
}

void buildTable()
{
	glColor3ub(243, 157, 47);
	glPushMatrix();
	glTranslated(room.table.centerX, room.table.centerY, room.table.centerZ);
	glScaled(room.table.lenX, room.table.lenY, room.table.lenZ);
	// glutSolidCube(1);
	// draw 4 faces is enough
	glBegin(GL_POLYGON);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(0.5, -0.5, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, -0.5, 0.5);
	glVertex3d(0.5, -0.5, -0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glEnd();
	glPopMatrix();

	// draw the front face with texture
	glBindTexture(GL_TEXTURE_2D, tex); // enable texture
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0);
	glVertex3d(room.table.centerX + room.table.lenX / 2,
						 room.table.centerY + room.table.lenY / 2,
						 room.table.centerZ - room.table.lenZ / 2); // left top
	glTexCoord2d(room.table.lenX, 0);
	glVertex3d(room.table.centerX - room.table.lenX / 2,
						 room.table.centerY + room.table.lenY / 2,
						 room.table.centerZ - room.table.lenZ / 2); // right top
	glTexCoord2d(room.table.lenX, room.table.lenY);
	glVertex3d(room.table.centerX - room.table.lenX / 2,
						 room.table.centerY - room.table.lenY / 2,
						 room.table.centerZ - room.table.lenZ / 2); // right bottom
	glTexCoord2d(0, room.table.lenY);
	glVertex3d(room.table.centerX + room.table.lenX / 2,
						 room.table.centerY - room.table.lenY / 2,
						 room.table.centerZ - room.table.lenZ / 2); // left bottom
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0); // disable texture
}

// build a pyramid, use (0, 0, 0) as center of bottom, Y as axis
void buildPyramid(double bottomLength, double height, bool line)
{
	double t = bottomLength / 2;
	if (line)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);
	glVertex3d(t, 0, -t);
	glVertex3d(t, 0, t);
	glVertex3d(0, height, 0);
	glEnd();

	if (line)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);
	glVertex3d(-t, 0, -t);
	glVertex3d(t, 0, -t);
	glVertex3d(0, height, 0);
	glEnd();

	if (line)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);
	glVertex3d(-t, 0, t);
	glVertex3d(-t, 0, -t);
	glVertex3d(0, height, 0);
	glEnd();

	if (line)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);
	glVertex3d(0, height, 0);
	glVertex3d(-t, 0, t);
	glVertex3d(t, 0, t);
	glEnd();
}

// build a cylinder, use (0, 0, 0) as center, Y as axis
void buildCylinder(double radius, double height, int slices, bool line)
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
	for (int i = slices - 1; i >= 0; --i)
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
		glVertex3d(x[i], -height / 2, z[i]);
		glVertex3d(x[i + 1], -height / 2, z[i + 1]);
		glVertex3d(x[i + 1], height / 2, z[i + 1]);
		glVertex3d(x[i], height / 2, z[i]);
		glEnd();
	}
}