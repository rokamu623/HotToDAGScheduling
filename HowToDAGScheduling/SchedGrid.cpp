#include "stdafx.h"
#include "SchedGrid.h"
#include "DAG.h"

Point Cell::CELL_SIZE = Point(16, 32);

Cell::Cell(Point pos, Point offset)
{
	_core = pos.y;
	_time = pos.x;
	_body = Rect(Cell::CELL_SIZE * Point(pos.x, -pos.y-1) + offset, Cell::CELL_SIZE);
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

void Cell::draw() const
{
	if(_invalid)
		_body.draw(Palette::Red);
	_body.drawFrame(0.25, Color(0, 0, 0, 64));
}

SchedGrid::SchedGrid()
{
	int core_num = 3;
	int time_limit = ceil(8 * 1.5);

	_field = Rect(LAYOUT::MERGIN * Point(1, 2) + LAYOUT::DAG_SPACE_SIZE * Point(0, 1) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::SCHED_SPACE_SIZE);
	_grid_rect = Rect(_field.top().begin.asPoint() + Point(LAYOUT::MERGIN.x * 2, _field.h / 4), Point(_field.w - LAYOUT::MERGIN.x * 4, _field.h / 2));

	int x = (floor(_grid_rect.w / time_limit) > Cell::CELL_SIZE.x) ? floor(_grid_rect.w / time_limit) : Cell::CELL_SIZE.x;
	int y = (floor(_grid_rect.h / time_limit) > Cell::CELL_SIZE.y) ? floor(_grid_rect.h / time_limit) : Cell::CELL_SIZE.y;
	Cell::CELL_SIZE = Point(x, y);

	_x_axis = Line(_grid_rect.bottom().end.asPoint() + LAYOUT::MERGIN * Point(-1, 0), _grid_rect.bottom().begin.asPoint());
	_y_axis = Line(_grid_rect.bottom().end.asPoint() + LAYOUT::MERGIN * Point(0, 1), _grid_rect.top().begin.asPoint());

	for (int i = 0; i < time_limit; i += 5)
		_y_sub_axises.push_back(_y_axis.movedBy(Cell::CELL_SIZE * Point(i, 0)));

	_cells = Grid<Cell>(time_limit, core_num, Cell());
	for (int i = 0; i < core_num; i++)
		for (int j = 0; j < time_limit; j++)
			_cells[i][j] = Cell(Point(j, i), _grid_rect.bottom().end.asPoint());

	_font = Font(16);
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

void SchedGrid::draw() const
{
	//_grid_rect.draw();
	_x_axis.drawArrow(1, SizeF(5, 5), Palette::Black);
	_y_axis.drawArrow(1, SizeF(5, 5), Palette::Black);

	for (auto& y_sub_axis : _y_sub_axises)
		y_sub_axis.draw(LineStyle::SquareDot, 1, Palette::Black);

	for (auto& cell : _cells)
		cell.draw();

	for (int i = 0; i < _cells.height(); i++)
		_font(Format(i)).draw(_grid_rect.bottom().end.asPoint() + Point(-int(LAYOUT::MERGIN.x * 1.5), -Cell::CELL_SIZE.y * (1 + i)), Palette::Black);
}

Grid<Cell> SchedGrid::cells()
{
	return _cells;
}
