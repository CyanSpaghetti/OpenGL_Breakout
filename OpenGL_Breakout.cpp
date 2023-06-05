/*
	CyanSpaghetti 2023
*/

#include <gl/glut.h>
#include <gl/GL.h>
#include <iostream>
#include <chrono>

//Constants
const int width = 640, height = 480;
const char* title = "Breakout";

//Player
int px = 320, py = 400, sizeX=24, sizeY=8, pspeed=16;

//Ball
float bx, by; int bsize;
float bspeed = 0.1f, bxvel, byvel;

//Boxes
int _bsizeX = 24, _bsizeY = 12, bq = 13, tb = 0;
int _bx[18] = {}, _by[18] = {};

void DrawPlayer() // Draw Player rect using triangles
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

void DrawBall() // Draw ball point
{
	glColor3f(1, 0, 0);
	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex2i(bx, by);
	glEnd();
}

void ChangeBallVel(int x, int y) // Change Velocity of the ball using a direction and magnitude
{
	bxvel = bxvel*x;
	byvel = byvel*y;
}

void BallMove()
{
	//Clamp the speed of the ball
	if (bxvel > 1) bxvel = 1;
	if (bxvel < -1) bxvel = -1;
	if (byvel > 1) byvel = 1;
	if (byvel < -1) byvel = -1;

	// Collision detection - i have no idea why this works
	if (bx + bxvel < px + sizeX && bx + bxvel > px - sizeX && by + byvel < py + sizeY && by + byvel > py - sizeY)
	{
		ChangeBallVel(1,-1);
	}
	else if (bx + bxvel <= 0 || bx + bxvel >= width) ChangeBallVel(-1,1); // go other direction of out of bounds
	else if(by + byvel <= 0 || by + byvel >= height) ChangeBallVel(1,-1);
	else 
	{ 
		bx = ((float)bx + bxvel); // move ball on x axis
		by = ((float)by + byvel); // move ball on y axis
	}
}

void InitBoxes()
{
	for (int i = 1; i < bq; i++)
	{
		_bx[i-1] = width - _bsizeX*i*2;
		_by[i-1] = 100;
	}
}

void DrawBoxes()
{
	for (int i = 0; i < bq; i++)
	{
		if (_bx[i] == NULL) continue;
		glColor3f(0, 1, 1);

		glBegin(GL_TRIANGLES);
		glVertex2i(_bx[i] - _bsizeX+1, _by[i] - _bsizeY+1);
		glVertex2i(_bx[i] + _bsizeX-1, _by[i] - _bsizeY+1);
		glVertex2i(_bx[i] - _bsizeX+1, _by[i] + _bsizeY-1);

		glVertex2i(_bx[i] + _bsizeX-1, _by[i] + _bsizeY-1);
		glVertex2i(_bx[i] + _bsizeX-1, _by[i] - _bsizeY+1);
		glVertex2i(_bx[i] - _bsizeX+1, _by[i] + _bsizeY-1);
		glEnd();
	}
}

void RemoveBoxes()
{
	for (int i = 0; i < bq; i++)
	{
		if (_bx[i] == NULL) continue;
		if (bx + bxvel < _bx[i] + _bsizeX && bx + bxvel > _bx[i] - _bsizeX && by + byvel < _by[i] + _bsizeY && by + byvel > _by[i] - _bsizeY)
		{
			_bx[i] = NULL; _by[i] = NULL;
			tb++;
			ChangeBallVel(1, -1);
		}
	}
}

void WinCheck()
{
	if (tb == bq-1)
	{
		std::cout << " You Won! " << std::endl;
		exit(0);
	}
}

void physics()
{
	WinCheck();
	BallMove();
	RemoveBoxes();
	glutPostRedisplay(); // since i don't understand the timer or idle functions of glut, i use recursion!!
}

void render(void)
{
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// -- Drawing -- //
	//Render Ball
	DrawBall();
	//Render Player
	DrawPlayer();
	// Render all Boxes
	DrawBoxes();
	// -- End of Drawing -- //	
	physics();
	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	// input
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
	glClearColor(0, 0, 0, 0); // bgcolor
	gluOrtho2D(0, width, height, 0); // create 2d camera
	px = 300; py = 400; // fixes y position of player
	bx = width / 2; by = height / 2; // sets ball to center
	bxvel = bspeed; byvel = bspeed; // changes the velocity of the ball to move in a NW direction
	InitBoxes(); // create array and stuff
	glutPostRedisplay(); // render game
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
	Init(); // initalize game
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}