#pragma once
#include <Siv3D.hpp>
#include "DAG.h"

namespace DAGJsonReader
{
	// ファイルパスから DAG を構成
	DAG generate_dag(FilePath path);
	// ファイルパスから リアルタイムモードの DAG を校正
	DAGRealTime generate_dag_realtime(FilePath path);
	// ファイルパスからステージ名（DAG名）を取得
	String get_stage_name(FilePath path);
	// ファイルパスからコア数を取得
	int get_core_num(FilePath path);
	// ファイルパスから設定された（目標）応答時間を取得
	int get_response_time(FilePath path);
	// ファイルパスからリザルトデータを取得
	String get_result(FilePath path);
};

namespace DAGJsonWriter
{
	// DAG のデータを json 形式で書き出す
	void write_result(FilePath path, int core_num, int response_time);
};
