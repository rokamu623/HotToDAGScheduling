#include "stdafx.h"
#include "SchedGrid.h"
#include "DAG.h"

Point Cell::CELL_SIZE = Point(16, 32);

Cell::Cell(Point pos, Point offset)
{
	//x軸要素を時間、y軸要素をコアIDとして保存
	_time = pos.x;
	_core = pos.y;
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
	_invalid = false;
	// 配置済みのグリッドに配置したら不正とする
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
}

SchedGrid::SchedGrid(int core_num, int time_limit)
{
	_core_num = core_num;

	// 下地
	_field = Rect(LAYOUT::MERGIN * Point(1, 2) + LAYOUT::DAG_SPACE_SIZE * Point(0, 1) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::SCHED_SPACE_SIZE);
	// グリッドの範囲
	_grid_rect = Rect(_field.top().begin.asPoint() + Point(LAYOUT::MERGIN.x * 2, _field.h / 4), Point(_field.w - LAYOUT::MERGIN.x * 4, _field.h / 2));

	// Cellのサイズ定義（グリッドを個数で割る）
	// 大きくとも (16, 32) で収める
	int x = Min(int(ceil(_grid_rect.w / time_limit)), int(Cell::CELL_SIZE.x));
	int y = Min(int(ceil(_grid_rect.h / _core_num)), int(Cell::CELL_SIZE.y));
	Cell::CELL_SIZE = Point(x, y);

	// x、y軸
	_x_axis = Line(_grid_rect.bottom().end.asPoint() + LAYOUT::MERGIN * Point(-1, 0), _grid_rect.bottom().begin.asPoint() + LAYOUT::MERGIN * Point(1, 0));
	_y_axis = Line(_grid_rect.bottom().end.asPoint() + LAYOUT::MERGIN * Point(0, 1), _grid_rect.top().begin.asPoint() + LAYOUT::MERGIN * Point(0, -1));

	// x軸サブ（x軸をCellのx大きさごとにコピー）
	for (int i = 0; i < time_limit; i += 5)
		_y_sub_axises.push_back(_y_axis.movedBy(Cell::CELL_SIZE * Point(i, 0)));

	// Cell 追加
	_cells = Grid<Cell>(time_limit, core_num, Cell());
	for (int i = 0; i < core_num; i++)
		for (int j = 0; j < time_limit; j++)
			_cells[i][j] = Cell(Point(j, i), _grid_rect.bottom().end.asPoint());

	_font = Font(16);
}

CompileLog SchedGrid::compile(DAG dag)
{
	// 各Cell の割り当て情報をfalseに
	for (auto& cell : _cells)
		cell.assign(false);

	//ノードと触れているCell には割り当て情報をtrue に
	for (auto& node : dag.nodes())
		for (auto& cell : _cells)
			if (cell.body().center().intersects(node.sched_body()))
				cell.assign(true);

	CompileLog log = CompileLog(true, U"");

	// 不正な配置をされている（2タスク以上配置されている）ときその旨をエラーログに保存
	for (auto& cell : _cells)
		if (cell.invalid())
		{
			log.success = false;
			log.message.append(U"Core " + Format(cell.core()) + U", time " + Format(cell.time()) + U": Each core has one job at same time\n");
		}

	return log;
}

CompileLog SchedGrid::compile(DAGRealTime dag)
{
	// 各Cell の割り当て情報をfalseに
	for (auto& cell : _cells)
		cell.assign(false);

	//ノードと触れているCell には割り当て情報をtrue に
	for (auto& node : dag.nodes())
		for (auto& cell : _cells)
			if (node.sched_body().intersects(cell.body()))
				cell.assign(true);

	CompileLog log = CompileLog(true, U"");

	// 不正な配置をされている（2タスク以上配置されている）ときその旨をエラーログに保存
	for (auto& cell : _cells)
		if (cell.invalid())
		{
			log.success = false;
			log.message.append(U"Core " + Format(cell.core()) + U", time " + Format(cell.time()) + U": Each core has one job at same time\n");
		}

	return log;
}

void SchedGrid::draw() const
{
	_x_axis.drawArrow(1, SizeF(5, 5), Palette::Black);
	_y_axis.drawArrow(1, SizeF(5, 5), Palette::Black);

	for (auto& y_sub_axis : _y_sub_axises)
		y_sub_axis.draw(LineStyle::SquareDot, 1, Palette::Black);

	for (auto& cell : _cells)
		cell.draw();

	for (int i = 0; i < _core_num; i++)
		_font(Format(i)).draw(_grid_rect.bottom().end.asPoint() + Point(-int(LAYOUT::MERGIN.x * 1.5), -Cell::CELL_SIZE.y * (1 + i)), Palette::Black);
}

Grid<Cell> SchedGrid::cells()
{
	return _cells;
}
