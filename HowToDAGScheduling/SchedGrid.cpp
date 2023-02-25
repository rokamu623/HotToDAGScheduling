#include "stdafx.h"
#include "SchedGrid.h"
#include "DAG.h"

Cell::Cell(Point pos)
{
	_core = pos.y;
	_time = pos.x;
	_body = Rect(Point(400, 400) + Point(16, 32) * pos, Point(16, 32));
}

bool Cell::invalid()
{
	return _invalid;
}

void Cell::assign(bool input)
{
	if (_assigned == true && input == true)
		_invalid = true;
	_assigned = input;
}

void Cell::draw()
{
	if(_invalid)
		_body.draw(Palette::Red);
	_body.drawFrame(1, Palette::Black);
}

SchedGrid::SchedGrid()
{
	_grid = Grid<Cell>(10, 2, Cell(Point()));
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 10; j++)
			_grid[i][j] = Cell(Point(j, i));
}

void SchedGrid::compile(DAG dag)
{
	for (auto& cell : _grid)
		cell.assign(false);

	for (auto& node : dag.nodes())
		for (auto& cell : _grid)
			if (node.sched_body().intersects(cell.body()))
				cell.assign(true);

	ClearPrint();
	Print << U"Compile Error";
	for (auto& cell : _grid)
		if (cell.invalid())
			Print << U"Core " + Format(cell.core()) + U", time " + Format(cell.time()) + U": Each core has one job at same time";
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
