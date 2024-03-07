#pragma once

// 結果計算（コンパイル評価）のデータ
class CompileLog
{
public:
	bool success;
	String message;

	CompileLog() {};
	CompileLog(bool success, String message);
};

