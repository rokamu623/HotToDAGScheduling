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
	// DAG 表示の基準の値
	_pos = LAYOUT::MERGIN + Point(0, LAYOUT::STAZE_SPACE_HEIGHT);

	_graph_field = Rect(_pos, LAYOUT::DAG_SPACE_SIZE);
	_sched_field = Rect(LAYOUT::MERGIN * 2 + Point(LAYOUT::SCHED_SPACE_SIZE.x, LAYOUT::DAG_SPACE_SIZE.y) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::SPACE_SPACE_SIZE);

	for (int i = 0; i < _nodes.size(); i++)
	{
		// 適当な色を割り当て
		_nodes[i].set_color(HSV(i * (360 / _nodes.size()), 20, 50));
		// スケジューリング長方形を一定の範囲内にランダム配置
		_nodes[i].set_sched_pos(RandomPoint(Rect(_sched_field.top().begin.asPoint() + Point(_sched_field.size) / 4, Point(_sched_field.size) / 2)));
	}

	// エッジをノードに反映させる
	for (auto& edge : edges)
	{
		if (edge.size() == 2)
			for (auto& pre : _nodes)
				if (edge[0] == pre.idx())
					for (auto& suc : _nodes)
						if (edge[1] == suc.idx())
							suc.append_pre(pre);

	}
}

void DAG::fit(SchedGrid& grid)
{
	if (MouseL.up())
	{
		// ドラッグが終了したら掴んでいるスケジューリング長方形の位置をグリッドに合わせる
		for (auto& node : _nodes)
		{
			if (node.sched_body().mouseOver())
				node.fit(grid);
		}
	}
}

CompileLog DAG::compile(SchedGrid& grid)
{
	CompileLog log = CompileLog(true, U"");

	// 各ノードのエラーチェック
	for (auto& node : _nodes)
	{
		CompileLog node_log = node.compile();
		// ひとつでもノードにエラーが合ったらエラー判定
		// エラーログは全て結合する
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
	// 全てのノードの処理を実行
	for (auto& node : _nodes)
	{
		// あるノードが動いたら以降は動かない
		// そうしないと、重なったノードが全部ドラッグで動いてしまう
		if (node.update())
			break;
	}
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
	// DAG 表示の基準の値
	_pos = LAYOUT::MERGIN + Point(0, LAYOUT::STAZE_SPACE_HEIGHT);

	_graph_field = Rect(_pos, LAYOUT::DAG_SPACE_SIZE);
	_sched_field = Rect(LAYOUT::MERGIN * 2 + Point(LAYOUT::SCHED_SPACE_SIZE.x, LAYOUT::DAG_SPACE_SIZE.y) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::SPACE_SPACE_SIZE);

	for (int i = 0; i < _nodes.size(); i++)
	{
		// 適当な色を割り当て
		_nodes[i].set_color(HSV(i * (360 / _nodes.size()), 20, 50));
		// スケジューリング長方形を一定の範囲内にランダム配置
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

	// 最初のノードを可視化する（前任がないのでnode.real_time_ready()を呼び出すと可視化される）
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
		}

		// 全ての前任者が何らかのコアに割り当てられていたら可視化する
		for (auto& node : _nodes)
			node.real_time_ready();
	}
}

CompileLog DAGRealTime::compile(SchedGrid& grid)
{
	CompileLog log = CompileLog(true, U"");

	// 各ノードのエラーチェック
	for (auto& node : _nodes)
	{
		CompileLog node_log = node.compile();
		if (node_log.success != true)
		{
			// ひとつでもノードにエラーが合ったらエラー判定
			// エラーログは全て結合する
			log.message.append(node_log.message);
			log.success = false;
		}
	}

	return log;
}

void DAGRealTime::update()
{
	for (auto& node : _nodes)
	{
		// あるノードが動いたら以降は動かない
		// そうしないと、重なったノードが全部ドラッグで動いてしまう
		if (node.update())
			break;
	}
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
