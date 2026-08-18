#include "pch.h"



void Helpers::ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		auto msg = GetHresultErrorMessage(hr);
		Logger::PrintLog(TRUE, L"Error: HRESULT=0x%08X , %s",(unsigned)hr, msg.c_str());
		throw std::exception();
	}
}

std::wstring Helpers::GetHresultErrorMessage(HRESULT hr)
{
	LPWSTR buffer = nullptr;

	DWORD size = FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&buffer,
		0,
		nullptr);

	std::wstring message = (size && buffer) ? buffer : L"Unknown error";
	if (buffer)
		LocalFree(buffer);

	return message;
}
