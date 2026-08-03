#include "pch.h"

Logger* Logger::_instance = nullptr;

Logger::Logger() {
	_instance = this;
}

Logger::~Logger() {
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
		FileHandler::WriteFile_fh(filepath, (const char*)buffer, wcslen(buffer) * sizeof(WCHAR));
	}
}

