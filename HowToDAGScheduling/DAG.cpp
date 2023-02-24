#include "stdafx.h"
#include "DAG.h"

Node::Node(int idx, int wcet, Point pos)
{
	_idx = idx;
	_wcet = wcet;
	_pos = Point(64, 48) * pos;
	_body = Circle(16);
	_font = Font(16);
}

void Node::append_pre(Node& pre)
{
	_pre.push_back(pre);
	_lines.push_back(Line(pre.pos()+Point(16, 0), _pos - Point(16, 0)));
}

void Node::draw(Point pos)
{
	for (auto& line : _lines)
		line.movedBy(Point(16, 16) + pos).drawArrow(1.0, Vec2(5, 5), Palette::Black);
	_body.movedBy(_pos+Point(16, 16)+pos).draw(Palette::Gray);
	_body.movedBy(_pos+Point(16, 16)+pos).drawFrame(1, Palette::Black);
	_font(Format(_wcet)).drawAt(_pos+Point(16, 16)+pos);
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

void DAG::draw()
{
	for (auto& node : _nodes)
		node.draw(_pos);
}
