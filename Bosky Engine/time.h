#pragma once
#include <string>

namespace Time {

	std::wstring GetTime(BOOL stripped);

	std::wstring GetDate(BOOL stripped);

	std::wstring GetDateTimeString(BOOL stripped);

}