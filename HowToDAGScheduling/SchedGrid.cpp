#include "stdafx.h"
#include "SchedGrid.h"
#include "DAG.h"

Cell::Cell(Point pos)
{
	_core = pos.y;
	_time = pos.x;
	_body = Rect(Point(400, 400) + Point(16, 32) * pos, Point(16, 32));
	_assigned = false;
	_invalid = false;
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
	_cells = Grid<Cell>(10, 2, Cell(Point()));
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 10; j++)
			_cells[i][j] = Cell(Point(j, i));
}

CompileLog SchedGrid::compile(DAG dag)
{
	for (auto& cell : _cells)
		cell.assign(false);

	for (auto& node : dag.nodes())
		for (auto& cell : _cells)
			if (node.sched_body().intersects(cell.body()))
				cell.assign(true);

	CompileLog log = CompileLog(true, U"");

	for (auto& cell : _cells)
		if (cell.invalid())
		{
			log._success = false;
			log._message.append(U"Core " + Format(cell.core()) + U", time " + Format(cell.time()) + U": Each core has one job at same time\n");
		}

	return log;
}

void SchedGrid::draw()
{
	for (auto& cell : _cells)
		cell.draw();
}

Grid<Cell> SchedGrid::cells()
{
	return _cells;
}
