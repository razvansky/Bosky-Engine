#include "pch.h"

Logger* Logger::instance;

Logger::Logger() {
	instance = this;
}

Logger::~Logger() {
}

void Logger::PrintLog(const WCHAR* message, ...) {
	va_list args;
	va_start(args, message);

	WCHAR buffer[4096];

	vswprintf_s(buffer, message, args);
	va_end(args);

	OutputDebugStringW(buffer);

	SYSTEMTIME st;

	GetLocalTime(&st);

	WCHAR filepath[1024];
	swprintf_s(filepath, L"logs\\log%s.txt", Time::GetDateTimeString(TRUE).c_str());

	FileHandler::WriteFile_fh(filepath, (const char*)buffer, wcslen(buffer) * sizeof(WCHAR));
}

