#include "stdafx.h"
#include "DAGJsonPackage.h"

DAG DAGJsonReader::generate_dag(FilePath path)
{
	// DAG 情報 json ファイルをロード
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
	// DAG 情報 json ファイルをロード
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
	// ディレクトリ名、拡張子を除いたファイル名を返す
	return FileSystem::BaseName(path);
}

int DAGJsonReader::get_core_num(FilePath path)
{
	// DAG 情報 json ファイルからコア数を返す
	return JSON::Load(path)[U"core_num"].getOr<int>(2);
}

int DAGJsonReader::get_response_time(FilePath path)
{
	// DAG 情報 json ファイルから応答時間を返す
	return JSON::Load(path)[U"response_time"].getOr<int>(10);
}

String DAGJsonReader::get_result(FilePath path)
{
	// DAG 情報 json ファイルをロード
	const JSON json = JSON::Load(path);

	// リザルト形式の文字列を返す
	// Result:
	//
	// Stage: [ファイル名]
	// core n: m processor times
	// core n: m processor times
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
	// DAG 情報 json ファイルをロード
	JSON json = JSON::Load(path);

	// 応答時間の記録がまだないか最高記録より小さければ記録する
	if (json[U"results"][Format(core_num)].getOr<int>(INT_MAX) > response_time)
		json[U"results"][Format(core_num)] = response_time;

	json.save(path);
}
