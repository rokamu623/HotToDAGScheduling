#pragma once
#include <Siv3D.hpp>
#include "DAG.h"

namespace DAGJsonReader
{
	DAG generate_dag(FilePath path);
	String get_stage_name(FilePath path);
	int get_core_num(FilePath path);
	int get_response_time(FilePath path);
};

