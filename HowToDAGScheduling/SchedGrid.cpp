#include "stdafx.h"
#include "SchedGrid.h"

Cell::Cell(Point pos)
{
	_body = Rect(Point(400, 400) + Point(16, 32) * pos, Point(16, 32));
}

void Cell::draw()
{
	_body.draw();
	_body.drawFrame(1, Palette::Black);
}

SchedGrid::SchedGrid()
{
	_grid = Grid<Cell>(10, 2, Cell(Point()));
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 10; j++)
			_grid[i][j] = Cell(Point(j, i));
}

void SchedGrid::draw()
{
	for (auto& cell : _grid)
		cell.draw();
}

Grid<Rect> SchedGrid::grid()
{
	Grid<Rect> tmp_grid = Grid<Rect>(10, 2, Rect());

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 10; j++)
			tmp_grid[i][j] = _grid[i][j].body();
	return tmp_grid;
}
