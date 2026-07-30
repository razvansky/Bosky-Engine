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
	swprintf_s(filepath, L"logs\\log%d-%d-%d-%d%d%d.txt", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);

	FileHandler::WriteFile_fh(filepath, (const char*)buffer, wcslen(buffer) * sizeof(WCHAR));
}

