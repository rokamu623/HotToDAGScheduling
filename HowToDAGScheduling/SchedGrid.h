#pragma once
#include "CompileLog.h"
#include "Layout.h"

class DAG;

class Cell
{
private:
	int _core;
	int _time;

	Rect _body;
	bool _invalid;
	bool _assigned;

public:
	static Point CELL_SIZE;

	Cell() {};
	Cell(Point pos, Point offset);

	bool invalid();
	void assign(bool input);

	void draw() const;

	int core() { return _core; };
	int time() { return _time; };
	Rect body() { return _body; };
};

class SchedGrid
{
private:
	Grid<Cell> _cells;
	Rect _field;
	Rect _grid_rect;
	int _core_num;

	Line _x_axis, _y_axis;
	Array<Line> _y_sub_axises;

	Font _font;

public:
	SchedGrid();
	SchedGrid(int core_num, int time_limit);

	CompileLog compile(DAG dag);

	void draw() const;
	void draw_field() const { _field.draw(LAYOUT::FIELD_COLOR); };

	Grid<Cell> cells();
	int core_num() { return _core_num; };
};

