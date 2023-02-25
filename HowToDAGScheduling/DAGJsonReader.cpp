#include "stdafx.h"
#include "DAGJsonReader.h"

DAG DAGJsonReader::generate_dag(FilePath path)
{
	JSON json = JSON::Load(path);

	Array<Node> nodes;
	for (const auto& node : json[U"nodes"].arrayView())
		nodes.push_back(Node(node[U"idx"].get<int>(), node[U"wcet"].get<int>(), Point(node[U"x"].get<int>(), node[U"y"].get<int>())));

	Array<Array<int>> edges;
	for (const auto& edge : json[U"edges"].arrayView())
		edges.push_back({ edge[U"src"].get<int>(), edge[U"dst"].get<int>() });
    return DAG(nodes, edges, Point(64, 64));
}
