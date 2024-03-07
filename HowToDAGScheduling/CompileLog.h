#pragma once
class CompileLog
{
public:
	bool success;
	String message;

	CompileLog() {};
	CompileLog(bool success, String message);
};

