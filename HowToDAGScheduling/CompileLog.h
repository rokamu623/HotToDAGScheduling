#pragma once
class CompileLog
{
public:
	bool _success;
	String _message;

	CompileLog() {};
	CompileLog(bool success, String message);
};

