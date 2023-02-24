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

void Node::draw(Point pos)
{
	_body.movedBy(_pos+Point(16, 16)+pos).draw(Palette::Gray);
	_body.movedBy(_pos+Point(16, 16)+pos).drawFrame(1, Palette::Black);
	_font(Format(_wcet)).drawAt(_pos+Point(16, 16)+pos);
}

DAG::DAG(Array<Node> nodes, Array<Array<int>> edges, Point pos)
{
	_nodes = nodes;
	_pos = pos;
}

void DAG::draw()
{
	for (auto& node : _nodes)
		node.draw(_pos);
}
