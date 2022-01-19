#include "Board.h"

Board::Cell::Cell() { x = y = color = borderWidth = 0; }

Board::Cell::Cell(int x, int y, int c) : x(x), y(y), color(c), borderWidth(1)
{}

Board::Cell::~Cell()
{}

void Board::Cell::drawCell()
{
	switch (this->color)
	{
	case 0: glColor3f(0.5, 0.5, 0.5); break; // free
	case 1: glColor3f(1.0, 0.0, 0.0); break; // color_red
	case 2: glColor3f(0.0, 1.0, 0.0); break; // color_green
	case 3: glColor3f(0.0, 0.0, 1.0); break; // color_blue
	case -1: glColor3f(0.0, 0.0, 0.0); break; // blocked
	default: break;
	}

	glRectf(this->x, this->y, this->x + 100, this->y + 100);

	//white border
	glColor3f(1.0, 1.0, 1.0);

	glRectf(this->x, this->y, this->x + 100, this->y + this->borderWidth); // down
	glRectf(this->x, this->y, this->x + this->borderWidth, this->y + 100); // left
	glRectf(this->x + 100 - this->borderWidth, this->y, this->x + 100, this->y + 100); // right
	glRectf(this->x, this->y + 100 - this->borderWidth, this->x  + 100, this->y + 100); // up

	glEnd();
}

bool Board::Cell::selectionÑheck(const int x, const int y)
{
	return ((x >= this->x && x < this->x + 100) && (y >= this->y && y < this->y + 100)) ? true : false;
}

bool Board::Cell::isNearest(Cell* other)
{
	return ((other->x == this->x && (other->y == this->y - 100 || other->y == this->y + 100)) || 
		(other->y == this->y && (other->x == this->x - 100 || other->x == this->x + 100))) ? true : false;
}
