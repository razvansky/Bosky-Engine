#pragma once

class Logger {
public:
	~Logger();
	Logger();
	static Logger* Instance();
	static void PrintLog(const WCHAR* message, ...);;

private:
	static Logger* instance;


};