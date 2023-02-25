#pragma once
class Cell
{
private:
	Rect _body;
	bool _fill;

public:
	Cell() {};
	Cell(Point pos);

	void draw();

	Rect body() { return _body; };
};

class SchedGrid
{
private:
	Grid<Cell> _grid;

public:
	SchedGrid();

	void draw();

	Grid<Rect> grid();
};

