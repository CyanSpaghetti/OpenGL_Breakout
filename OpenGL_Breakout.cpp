#include <gl/glut.h>
#include <gl/GL.h>
#include <iostream>
#include <chrono>

int width = 640, height = 480;
const char* title = "Window";

//Player
int px = 320, py = 300, sizeX=24, sizeY=8, pspeed=4;

//Boxes

//Ball
float bx, by; int bsize;
float bspeed = 0.2f, bxvel, byvel;


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

void DrawBall()
{
	glColor3f(1, 0, 0);
	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex2i(bx, by);
	glEnd();
}

void ChangeBallVel(int x, int y)
{
	bxvel = bxvel*x;
	byvel = byvel*y;
}

void BallMove()
{
	if (bxvel > 1) bxvel = 1;
	if (bxvel < -1) bxvel = -1;
	if (byvel > 1) byvel = 1;
	if (byvel < -1) byvel = -1;
	if (bx + bxvel < px + sizeX && bx + bxvel > px - sizeX && by + byvel < py + sizeY && by + byvel > py - sizeY)
	{
		ChangeBallVel(1,-1);
	}
	else if (bx + bxvel <= 0 || bx + bxvel >= width) ChangeBallVel(-1,1);
	else if(by + byvel <= 0 || by + byvel >= height) ChangeBallVel(1,-1);
	else 
	{ 
		bx = ((float)bx + bxvel);
		by = ((float)by + byvel); 
	}
	glutPostRedisplay();
}

void render(void)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Render Ball
	DrawBall();
	//Render Player
	DrawPlayer();
	BallMove();
	std::cout << "B: " << bx << " " << by << std::endl;
	std::cout << "P: " << px << std::endl;
	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	if (c == 'd')
	{ 
		px += pspeed; 
	}
	if (c == 'a') 
	{
		px -= pspeed;
	}
}

void Init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, width, height, 0);
	px = 300; py = 400;
	bx = width / 2; by = height / 2; 
	bxvel = bspeed; byvel = bspeed;
	glutPostRedisplay();
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
	//glutIdleFunc(BallMove);
	glutMainLoop();
	return 0;
}