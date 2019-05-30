#include <iostream>
#include "gl/glut.h"
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

// Light values and coordinates
GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
// display callback function
void render()
{
	// clear window with glClearColor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// finish drawing
	glFlush();
	glFinish();
	glutSwapBuffers(); // for double buffering
}

// setup rendering context
void setupRC()
{
	glClearColor(1, 1, 1, 1); // white background

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Set drawing color to blue
	glColor3ub(0, 0, 255);
}

// keyboard callback function(for ascii chars)
// x and y are the coordinates of mouse when key is pressed
void keyPressedEvent(unsigned char key, int x, int y)
{
	// key to lower case
	if (key >= 'A' && key <= 'Z')
		key = key - 'A' + 'a';

	switch (key)
	{
	case 'w':
		break;
	case 'a':
		break;
	case 's':
		break;
	case 'd':
		break;
	default:
		break;
	}

	// refresh the window
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // use double buffer, rgb color mode, depth buffer
	glutCreateWindow("simple-3D-room by DiscreteTom"); // window title

	glutDisplayFunc(render);					 // set display callback function
	glutKeyboardFunc(keyPressedEvent); // set keyboard callback function(for ascii chars)

	setupRC();
	glutMainLoop(); // start event loop
}