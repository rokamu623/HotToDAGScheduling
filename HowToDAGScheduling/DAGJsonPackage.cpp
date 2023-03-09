#include "stdafx.h"
#include "DAGJsonPackage.h"

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

DAGRealTime DAGJsonReader::generate_dag_realtime(FilePath path)
{
	JSON json = JSON::Load(path);

	Array<NodeRealTime> nodes;
	for (const auto& node : json[U"nodes"].arrayView())
		nodes.push_back(NodeRealTime(node[U"idx"].get<int>(), node[U"wcet"].get<int>(), Point(node[U"x"].get<int>(), node[U"y"].get<int>())));

	Array<Array<int>> edges;
	for (const auto& edge : json[U"edges"].arrayView())
		edges.push_back({ edge[U"src"].get<int>(), edge[U"dst"].get<int>() });
	return DAGRealTime(nodes, edges);
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

String DAGJsonReader::get_result(FilePath path)
{
	const JSON json = JSON::Load(path);

	String text;
	text.append(U"Result:\n");
	text.append(U"\n");
	text.append(U"Stage: " + DAGJsonReader::get_stage_name(path) + U"\n");

	for (auto& stage : json[U"results"])
		text.append(U"core " + stage.key + U" : " + Format(stage.value.get<int>()) + U" processor times\n");

	return text;
}

void DAGJsonWriter::write_result(FilePath path, int core_num, int response_time)
{
	JSON json = JSON::Load(path);

	if (json[U"results"][Format(core_num)].getOr<int>(999) > response_time)
		json[U"results"][Format(core_num)] = response_time;

	json.save(path);
}
