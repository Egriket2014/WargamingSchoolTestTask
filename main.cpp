#include <iostream>
#include <string>
#include "Board.h"
#include <Windows.h>


int w = 500;
int h = 650;

bool winFlag = false;

Board board;

void printText(const std::string& s, const int x, const int y)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x, y);
	for (const char c : s)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)c);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void mousePressed(int button, int press, int x, int y)
{
	if (press == 0 && button == GLUT_LEFT_BUTTON && !winFlag) 
	{
		board.enter(x, y);
	}
	if (press == 0 && button == GLUT_RIGHT_BUTTON && !winFlag)
	{
		board.cancelEnter();
	}

}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	board.drawBorad();
	
	if(winFlag) printText("CONGRATULATIONS!!!", 170, 520);

	glFlush();
	glutSwapBuffers();
}

void timer(int = 0)
{
	display();

	if (board.checkWin())
	{
		winFlag = true;
		//drawRepeatButton();
	}

	glutTimerFunc(50, timer, 0);
}

int main(int argc, char** argv)
{
	//board.show_cell_info();

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutCreateWindow("BoardGame");
	//glClearColor(1.0, 1.0, 0.6, 1.0);  //цвет фона
	//glOrtho(0, w, h, 0, -100.0, 100.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glutDisplayFunc(display);
	glutMouseFunc(mousePressed);
	//glutSpecialUpFunc(KeyboardEventRelease);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
}