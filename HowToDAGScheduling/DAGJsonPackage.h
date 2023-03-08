#pragma once
#include <Siv3D.hpp>
#include "DAG.h"

namespace DAGJsonReader
{
	DAG generate_dag(FilePath path, bool real_time_mode);
	String get_stage_name(FilePath path);
	int get_core_num(FilePath path);
	int get_response_time(FilePath path);
	String get_result(FilePath path);
};

namespace DAGJsonWriter
{
	void write_result(FilePath path, int core_num, int response_time);
};
