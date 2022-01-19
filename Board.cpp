#include "Board.h"


Board::Board()
{
	int colorCount[3]{ 6, 6, 6 };
	int colorNumber = rand() % 3;

	srand(time(0));
	//fill control cells
	for (int i = 0, x = 0; i < 3; i++, x += 200)
	{
		do
		{
			colorNumber = rand() % 3;
		} while (colorCount[colorNumber] == 5);
		controlCells[i] = new Cell(x, 550, colorNumber + 1);
		colorCount[colorNumber]--;
	}
	//fill color cells
	for (int i = 0, y = 0; i < 5; i++, y += 100)
	{
		for (int j = 0, x = 0; j < 5; j += 2, x += 200)
		{
			do
			{
				colorNumber = rand() % 3;
			} while (colorCount[colorNumber] == 0);
			cells[i][j] = new Cell(x, y, colorNumber + 1);
			colorCount[colorNumber]--;
		}
	}
	//fill block cells
	for (int i = 0, y = 0; i < 5; i += 2, y += 200)
	{
		for (int j = 1, x = 100; j < 5; j += 2, x += 200)
			cells[i][j] = new Cell(x, y, -1);
	}
	//fill free cells
	for (int i = 1, y = 100; i < 5; i += 2, y += 200)
	{
		for (int j = 1, x = 100; j < 5; j += 2, x += 200)
			cells[i][j] = new Cell(x, y, 0);
	}
	//enterCell
	enterCell = nullptr;
}

Board::~Board()
{
	//cells
	for (size_t i = 0; i < 5; i++)
		delete[] cells[i];
	//control cells
	delete[] controlCells;
}

void Board::show_cell_info()
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			std::cout << cells[i][j]->y << "\t";
			//std::cout << cells[i][j]->color << "|" << cells[i][j]->x << "|" << cells[i][j]->y << "  ";
		}
		std::cout << std::endl;
	}
}

void Board::drawBorad()
{
	//draw color cells
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			cells[i][j]->drawCell();

	//draw control cells
	for (size_t i = 0; i < 3; i++)
		controlCells[i]->drawCell();
}

Board::Cell* Board::findCell(int x, int y)
{
	y = abs(y - 650); // because the mouse coordinates are calculated from the upper left corner
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			if (cells[i][j]->selectionСheck(x, y)) { return cells[i][j]; }
				
		}
	}
	return nullptr;
}

void Board::swap(Cell* other)
{
	int tmp = other->color;
	other->color = enterCell->color;
	enterCell->color = tmp;
}

void Board::enter(int x, int y)
{
	Cell* tmp = findCell(x, y);
	if (tmp) // if click out of 5x5 cells
	{
		if (!enterCell && tmp->color > 0)
		{
			this->enterCell = tmp;
			enterCell->borderWidth = 5;
		}
		if (enterCell && tmp->color == 0 && enterCell->isNearest(findCell(x, y))) // придумать как сделать ограничение на выбор только соседних элементов
		{
			swap(tmp);
			enterCell->borderWidth = 1;
			this->enterCell = nullptr;
		}
	}
}

bool Board::checkWin()
{
	int numControl = 0;
	for (size_t j = 0; j < 5; j += 2)
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (cells[i][j]->color != controlCells[numControl]->color) return false;
		}
		numControl++;
	}
	return true;
}

void Board::cancelEnter() 
{ 
	if (enterCell)
	{
		enterCell->borderWidth = 1;
		this->enterCell = nullptr;
	}
}

