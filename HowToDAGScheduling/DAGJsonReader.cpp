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
    return DAG(nodes, edges);
}

String DAGJsonReader::get_stage_name(FilePath path)
{
	return FileSystem::BaseName(path);
}

int DAGJsonReader::get_core_num(FilePath path)
{
	return JSON::Load(path)[U"core_num"].getOr<int>(2);
}

int DAGJsonReader::get_response_time(FilePath path)
{
	return JSON::Load(path)[U"response_time"].getOr<int>(10);
}
