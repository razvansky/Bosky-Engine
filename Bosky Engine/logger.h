#pragma once

class Logger {
public:
	~Logger();
	Logger();
	static Logger* Instance();
	static void PrintLog(BOOL writeToFile, const WCHAR* message, ...);;

private:
	static Logger* _instance;


};