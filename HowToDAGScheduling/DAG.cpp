#include "stdafx.h"
#include "DAG.h"
#include "SchedGrid.h"

NodeBase::NodeBase(int idx, int wcet, Point pos)
{
	_idx = idx;
	_wcet = wcet;
	_chase = false;
	_graph_pos = Point(64, 48) * pos;
	_graph_body = Circle(16);
	_font = Font(16);
	_sched_body = Rect(Point(Random(100), Random(100)), Cell::CELL_SIZE * Point(_wcet, 1));
	_core = -1;
}

void NodeBase::append_pre(NodeBase& pre)
{
	_pre.push_back(pre);
	//前任ノードの右からノードの左に線（エッジ）を追加
	_lines.push_back(Line(pre.graph_pos() + Point(16, 0), _graph_pos - Point(16, 0)));
}

void NodeBase::fit(SchedGrid& grid)
{
	bool fitted = false;

	if (fitted != true)
		// 左上が触れてるグリッドに位置を合わせる
		for (auto& cell : grid.cells())
		{
			Rect body = cell.body();
			if (_sched_body.top().begin.asPoint().intersects(body))
			{
				_sched_body.setPos(body.top().begin.asPoint());
				SEManager::play(SE_name::Fit);
				fitted = true;
				break;
			}
		}

	if (fitted != true)
		// 左下が触れてるグリッドに位置を合わせる
		for (auto& cell : grid.cells())
		{
			Rect body = cell.body();
			if (_sched_body.bottom().end.asPoint().intersects(body))
			{
				_sched_body.setPos(body.top().begin.asPoint());
				SEManager::play(SE_name::Fit);
				fitted = true;
				break;
			}
		}

	if (fitted != true)
		// 右下が触れてるグリッドに位置を合わせる
		for (auto& cell : grid.cells())
		{
			Rect body = cell.body();
			if (_sched_body.bottom().begin.asPoint().intersects(body))
			{
				_sched_body.setPos(body.top().begin.asPoint());
				SEManager::play(SE_name::Fit);
				fitted = true;
				break;
			}
		}

	if(fitted != true)
		// 右上が触れてるグリッドに位置を合わせる
		for (auto& cell : grid.cells())
		{
			Rect body = cell.body();
			if (_sched_body.top().end.asPoint().intersects(body))
			{
				_sched_body.setPos(body.top().begin.asPoint());
				SEManager::play(SE_name::Fit);
				fitted = true;
				break;
			}
		}

	if(fitted == true)
		// 触れてるグリッドのコア、時間をノードにセット
		for (auto& cell : grid.cells())
			if (_sched_body.top().center().intersects(cell.body()))
			{
				_start_time = cell.time();
				_core = cell.core();
			}
}

CompileLog NodeBase::compile()
{
	CompileLog log = CompileLog(true, U"");

	for (auto& p : _pre)
		// 前任者の終了時間より早く開始しようとしたらエラーログを保存
		if (p.get().start_time() + p.get().wcet() > _start_time)
		{
			log.message.append(U"Node " + Format(_idx) + U": Cannot start earlier than Node " + Format(p.get().idx()) + U"\n");
			log.success = false;
		}

	return log;
}

bool NodeBase::update()
{
	// ドラッグされ始めたら追従モードオン
	if (Cursor::Pos().intersects(_sched_body) && MouseL.down())
		_chase = true;
	// 追従モード中は追従
	if (_chase == true)
		_sched_body.moveBy(Cursor::Delta());
	// ドラッグが離されたら追従モードオフ
	if (_chase == true && MouseL.pressed() != true)
		_chase = false;
	return _chase;
}

void NodeBase::draw_sched() const
{
	_sched_body.draw(_color);
	_sched_body.drawFrame(1, Palette::Black);
}

void NodeBase::draw_graph(Point pos) const
{
	for (auto& line : _lines)
		line.movedBy(Point(16, 16) + pos).drawArrow(1.0, Vec2(5, 5), Palette::Black);
	_graph_body.movedBy(_graph_pos + Point(16, 16) + pos).draw(_color);
	_graph_body.movedBy(_graph_pos + Point(16, 16) + pos).drawFrame(1, Palette::Black);
	_font(Format(_wcet)).drawAt(_graph_pos + Point(16, 16) + pos);
}


Node::Node(int idx, int wcet, Point pos) : NodeBase(idx, wcet, pos)
{
	// NodeBase と全く同じ
}


NodeRealTime::NodeRealTime(int idx, int wcet, Point pos) : NodeBase(idx, wcet, pos)
{
	_visible = false;
}

void NodeRealTime::real_time_ready()
{
	if (_visible != true)
	{
		// 全ての前任者が何らかのコアに割り当てられていたら可視化する
		bool tmp = true;
		for (auto& p : _pre)
			if (p.get().core() == -1)
				tmp = false;
		if (tmp == true)
			_visible = true;
	}
}

bool NodeRealTime::update()
{
	// 可視時のみ処理
	if (_visible)
		return NodeBase::update();
	else
		return false;
}

void NodeRealTime::draw_sched() const
{
	// 可視時のみ処理
	if (_visible)
		NodeBase::draw_sched();
}


void DAGBase::draw_field() const
{
	_graph_field.draw(LAYOUT::FIELD_COLOR);
	_sched_field.draw(LAYOUT::FIELD_COLOR);
}


DAG::DAG(Array<Node> nodes, Array<Array<int>> edges)
{
	_nodes = nodes;
	_pos = LAYOUT::MERGIN + Point(0, LAYOUT::STAZE_SPACE_HEIGHT);

	_graph_field = Rect(_pos, LAYOUT::DAG_SPACE_SIZE);
	_sched_field = Rect(LAYOUT::MERGIN * 2 + Point(LAYOUT::SCHED_SPACE_SIZE.x, LAYOUT::DAG_SPACE_SIZE.y) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::SPACE_SPACE_SIZE);

	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i].set_color(HSV(i * (360 / _nodes.size()), 20, 50));
		_nodes[i].set_sched_pos(RandomPoint(Rect(_sched_field.top().begin.asPoint() + Point(_sched_field.size) / 4, Point(_sched_field.size) / 2)));
	}

	for (auto& edge : edges)
	{
		if (edge.size() == 2)
		{
			for (auto& suc : _nodes)
				if (edge[1] == suc.idx())
					for (auto& pre : _nodes)
						if (edge[0] == pre.idx())
							suc.append_pre(pre);
		}

	}
}

void DAG::fit(SchedGrid& grid)
{
	if (MouseL.up())
	{
		for (auto& node : _nodes)
		{
			if (node.sched_body().mouseOver())
				node.fit(grid);
			node.real_time_ready();
		}
	}
}

CompileLog DAG::compile(SchedGrid& grid)
{
	CompileLog log = CompileLog(true, U"");

	for (auto& node : _nodes)
	{
		CompileLog node_log = node.compile();
		if (node_log.success != true)
		{
			log.message.append(node_log.message);
			log.success = false;
		}
	}

	return log;
}

void DAG::update()
{
	for (auto& node : _nodes)
		if (node.update())
			break;
}

void DAG::draw() const
{
	for (auto& node : _nodes)
	{
		node.draw_graph(_pos + LAYOUT::MERGIN);
		node.draw_sched();
	}
}


DAGRealTime::DAGRealTime(Array<NodeRealTime> nodes, Array<Array<int>> edges)
{
	_nodes = nodes;
	_pos = LAYOUT::MERGIN + Point(0, LAYOUT::STAZE_SPACE_HEIGHT);

	_graph_field = Rect(_pos, LAYOUT::DAG_SPACE_SIZE);
	_sched_field = Rect(LAYOUT::MERGIN * 2 + Point(LAYOUT::SCHED_SPACE_SIZE.x, LAYOUT::DAG_SPACE_SIZE.y) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::SPACE_SPACE_SIZE);

	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i].set_color(HSV(i * (360 / _nodes.size()), 20, 50));
		_nodes[i].set_sched_pos(RandomPoint(Rect(_sched_field.top().begin.asPoint() + Point(_sched_field.size) / 4, Point(_sched_field.size) / 2)));
	}

	for (auto& edge : edges)
	{
		if (edge.size() == 2)
		{
			for (auto& suc : _nodes)
				if (edge[1] == suc.idx())
					for (auto& pre : _nodes)
						if (edge[0] == pre.idx())
							suc.append_pre(pre);
		}

	}

	for (auto& node : _nodes)
		node.real_time_ready();
}

void DAGRealTime::fit(SchedGrid& grid)
{
	if (MouseL.up())
	{
		for (auto& node : _nodes)
		{
			if (node.sched_body().mouseOver())
				node.fit(grid);
			node.real_time_ready();
		}
	}
}

CompileLog DAGRealTime::compile(SchedGrid& grid)
{
	CompileLog log = CompileLog(true, U"");

	for (auto& node : _nodes)
	{
		CompileLog node_log = node.compile();
		if (node_log.success != true)
		{
			log.message.append(node_log.message);
			log.success = false;
		}
	}

	return log;
}

void DAGRealTime::update()
{
	for (auto& node : _nodes)
		if (node.update())
			break;
}

void DAGRealTime::draw() const
{
	for (auto& node : _nodes)
	{
		ClearPrint();
		node.draw_graph(_pos + LAYOUT::MERGIN);
		node.draw_sched();
	}
}
