#include <gl/glut.h>
#include <gl/GL.h>
#include <iostream>

int width = 640, height = 480;
const char* title = "Window";

//Player
int px = 320, py = 300, sizeX=24, sizeY=8,velX=0;

//Boxes

//Ball

void DrawPlayer()
{
	glColor3f(1, 1, 1);

	glBegin(GL_TRIANGLES);
	glVertex2i(px - sizeX, py - sizeY);
	glVertex2i(px + sizeX, py - sizeY);
	glVertex2i(px - sizeX, py + sizeY);

	glVertex2i(px + sizeX, py + sizeY);
	glVertex2i(px + sizeX, py - sizeY);
	glVertex2i(px - sizeX, py + sizeY);
	glEnd();
}


void render(void)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Render Player
	DrawPlayer();


	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	if (c == 'd')
	{ 
		px += 5; 
	}
	if (c == 'a') 
	{
		px -= 5;
	}

	glutPostRedisplay();
}

void Init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, width, height, 0);
	px = 300; py = 300;
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
	Init();
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}