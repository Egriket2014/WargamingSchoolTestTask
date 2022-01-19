#pragma once

#include <time.h>
#include <vector>
#include <GL/freeglut.h>
#include <iostream>

class Board
{
private:

	class Cell
	{
	public:

		Cell();

		Cell(int x, int y, int c);

		//Cell(const Cell& other);

		~Cell();

		//Cell& operator=(const Cell& other);

		void drawCell();

		bool selection—heck(int x, int y);

		bool isNearest(Cell* other);

		//private:
		int x;
		int y;
		int color;
		size_t borderWidth;
	};

	Cell* cells[5][5];
	Cell* controlCells[3];
	Cell* enterCell;

public:

	Board();

	~Board();

	void show_cell_info();

	void drawBorad();

	void enter(int x, int y);

	bool checkWin();

	void cancelEnter();

private:

	Cell* findCell(int x, int y);

	void swap(Cell* other);

};
