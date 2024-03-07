#include "stdafx.h"
#include "DAG.h"


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
