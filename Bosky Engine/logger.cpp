#include "pch.h"

Logger*	Logger::p_instance = nullptr;

Logger::Logger() {
	p_instance = this;
}

Logger::~Logger() {
}

Logger* Logger::Instance() {
	return p_instance;
}

void Logger::PrintLog(BOOL writeToFile, const WCHAR* message, ...) {
	va_list args;
	va_start(args, message);

	WCHAR buffer[4096];

	vswprintf_s(buffer, message, args);
	va_end(args);

	OutputDebugStringW(buffer);
	
	if (writeToFile) {
		WCHAR filepath[1024];
		swprintf_s(filepath, L"logs\\log%s.txt", Time::GetDate(TRUE).c_str());
		FileHandler::WriteFile_fh(filepath, buffer, wcslen(buffer) * sizeof(WCHAR));
	}
}

