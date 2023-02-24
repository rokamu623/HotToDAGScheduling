#include "stdafx.h"
#include "DAG.h"

Node::Node(int idx, int wcet, Point pos)
{
	_idx = idx;
	_wcet = wcet;
	_chase = false;
	_pos = Point(64, 48) * pos;
	_graph_body = Circle(16);
	_font = Font(16);
	_sched_body = Rect(Random(100), Random(100), 32, 32);
}

void Node::append_pre(Node& pre)
{
	_pre.push_back(pre);
	_lines.push_back(Line(pre.pos() + Point(16, 0), _pos - Point(16, 0)));
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
	_sched_body.draw();
	_sched_body.drawFrame(1, Palette::Black);
}

void Node::draw_graph(Point pos)
{
	for (auto& line : _lines)
		line.movedBy(Point(16, 16) + pos).drawArrow(1.0, Vec2(5, 5), Palette::Black);
	_graph_body.movedBy(_pos + Point(16, 16) + pos).draw(Palette::Gray);
	_graph_body.movedBy(_pos + Point(16, 16) + pos).drawFrame(1, Palette::Black);
	_font(Format(_wcet)).drawAt(_pos + Point(16, 16) + pos);
}

int Node::idx()
{
	return _idx;
}

Point Node::pos()
{
	return _pos;
}

DAG::DAG(Array<Node> nodes, Array<Array<int>> edges, Point pos)
{
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
