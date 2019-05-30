#include <iostream>
#include "gl/glut.h"
#ifdef _DEBUG
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif

// display callback function
void render()
{
	// clear window with glClearColor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// finish drawing
	glFlush();
	glFinish();
}

// setup rendering context
void setupRC()
{
	glClearColor(255, 255, 255, 1); // white background
}

// keyboard callback function(for ascii chars)
// x and y are the coordinates of mouse when key is pressed
void keyPressedEvent(char key, int x, int y)
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
	glutCreateWindow("simple-3D-room by DiscreteTom"); // window title

	glutDisplayFunc(render);					 // set display callback function
	glutKeyboardFunc(keyPressedEvent); // set keyboard callback function(for ascii chars)

	setupRC();
	glutMainLoop(); // start event loop
}