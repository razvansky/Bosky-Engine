#include "pch.h"

std::wstring Time::GetTime(BOOL stripped) {
	if (stripped) {
		SYSTEMTIME st;
		GetLocalTime(&st);
		wchar_t buffer[100];
		swprintf_s(buffer, 100, L"%02d%02d%02d", st.wHour, st.wMinute, st.wSecond);
		return std::wstring(buffer);
	}
	else {
		SYSTEMTIME st;
		GetLocalTime(&st);
		wchar_t buffer[100];
		swprintf_s(buffer, 100, L"%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
		return std::wstring(buffer);
	}
}

std::wstring Time::GetDate(BOOL stripped) {

	if (stripped) {
		SYSTEMTIME st;
		GetLocalTime(&st);
		wchar_t buffer[100];
		swprintf_s(buffer, 100, L"%04d%02d%02d", st.wYear, st.wMonth, st.wDay);
		return std::wstring(buffer);
	}
	else {
		SYSTEMTIME st;
		GetLocalTime(&st);
		wchar_t buffer[100];
		swprintf_s(buffer, 100, L"%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
		return std::wstring(buffer);
	}

}

std::wstring Time::GetDateTimeString(BOOL stripped) {
	return Time::GetDate(stripped) + Time::GetTime(stripped);
}