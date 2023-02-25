#include "stdafx.h"
#include "DAG.h"
#include "SchedGrid.h"

Node::Node(int idx, int wcet, Point pos)
{
	_idx = idx;
	_wcet = wcet;
	_chase = false;
	_graph_pos = Point(64, 48) * pos;
	_graph_body = Circle(16);
	_font = Font(16);
	_sched_body = Rect(Point(Random(100), Random(100)), Point(16 * _wcet, 32));
}

void Node::append_pre(Node& pre)
{
	_pre.push_back(pre);
	_lines.push_back(Line(pre.graph_pos() + Point(16, 0), _graph_pos - Point(16, 0)));
}

void Node::fit(Point pos)
{
	_sched_body.setPos(pos);
}

CompileLog Node::compile()
{
	CompileLog log = CompileLog(true, U"");

	for (auto& p : _pre)
		if (p.get().time() + p.get().wcet() > _time)
		{
			log._message.append(U"Node " + Format(_idx) + U": Cannot start earlier than Node " + Format(p.get().idx()) + U"\n");
			log._success = false;
		}

	return log;
}

void Node::assign(int time, int core)
{
	_time = time;
	_core = core;
}

bool Node::update()
{
	if (Cursor::Pos().intersects(_sched_body) && MouseL.down())
		_chase = true;
	if (_chase == true)
		_sched_body.moveBy(Cursor::Delta());
	if (_chase == true && MouseL.pressed() != true)
		_chase = false;
	return _chase;
}

void Node::draw_sched()
{
	_sched_body.draw(_color);
	_sched_body.drawFrame(1, Palette::Black);
}

void Node::draw_graph(Point pos)
{
	for (auto& line : _lines)
		line.movedBy(Point(16, 16) + pos).drawArrow(1.0, Vec2(5, 5), Palette::Black);
	_graph_body.movedBy(_graph_pos + Point(16, 16) + pos).draw(_color);
	_graph_body.movedBy(_graph_pos + Point(16, 16) + pos).drawFrame(1, Palette::Black);
	_font(Format(_wcet)).drawAt(_graph_pos + Point(16, 16) + pos);
}

int Node::idx()
{
	return _idx;
}

Point Node::graph_pos()
{
	return _graph_pos;
}

DAG::DAG(Array<Node> nodes, Array<Array<int>> edges, Point pos)
{
	for (int i = 0; i < nodes.size(); i++)
		nodes[i].set_color(HSV(i * (360 / nodes.size()), 20, 50));

	_nodes = nodes;
	_pos = pos;

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

	for (auto& node : _nodes)
		for (auto& cell : grid.cells())
		{
			Rect body = cell.body();
			if (node.sched_body().top().begin.intersects(body))
			{
				node.fit(body.top().begin.asPoint());
				break;
			}
			else if (node.sched_body().bottom().end.intersects(body))
			{
				node.fit(body.top().begin.asPoint());
				break;
			}
			else if (node.sched_body().bottom().begin.intersects(body))
			{
				node.fit(body.top().begin.asPoint());
				break;
			}
			else if (node.sched_body().top().end.intersects(body))
			{
				node.fit(body.top().begin.asPoint());
				break;
			}
		}
}

CompileLog DAG::compile(SchedGrid& grid)
{
	CompileLog log = CompileLog(true, U"");

	for (auto& node : _nodes)
		for (auto& cell : grid.cells())
			if (node.sched_body().top().begin.intersects(cell.body()))
				node.assign(cell.time(), cell.core());

	for (auto& node : _nodes)
	{
		CompileLog node_log = node.compile();
		if (node_log._success != true)
		{
			log._message.append(node_log._message);
			log._success = false;
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

void DAG::draw()
{
	for (auto& node : _nodes)
	{
		node.draw_graph(_pos);
		node.draw_sched();
	}
}
