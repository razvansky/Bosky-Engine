#include "pch.h"


FileHandler* FileHandler::p_instance = nullptr;
std::unique_ptr<WCHAR[]> FileHandler::p_path;

FileHandler::FileHandler(){
	WCHAR appdata[1024];
	SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appdata);

	WCHAR fullPath[4096];
	swprintf_s(fullPath, L"%s\\BoskyEngine\\", appdata);

	p_path = std::unique_ptr<WCHAR[]>(new WCHAR[wcslen(fullPath) + 1]);
	wcscpy_s(p_path.get(), wcslen(fullPath) + 1, fullPath);

	// Create the directory if it doesn't exist

	WCHAR subtitutePath[1024];
	swprintf_s(subtitutePath, L"%s\\logs\\", p_path.get());

	CreateDirectoryW(p_path.get(), NULL);

	CreateDirectoryW(subtitutePath, NULL);

	swprintf_s(subtitutePath, L"%s\\saves\\", p_path.get());

	CreateDirectoryW(subtitutePath, NULL);


	p_instance = this;
}

FileHandler::~FileHandler(){

}

FileHandler* FileHandler::Instance()
{
	return p_instance;
}

void FileHandler::ReadFile_fh(const WCHAR* filePath, WCHAR** buffer, size_t* size){
	WCHAR fullPath[1024] = { 0 };
	wcscpy_s(fullPath, p_path.get());
	wcscat_s(fullPath, filePath);

	HANDLE hFile = CreateFileW(fullPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD bytesRead = 0;
		// *buffer is typically used here so we read into the memory pointed to, rather than overwriting the pointer itself
		if (ReadFile(hFile, buffer, static_cast<DWORD>(*size), &bytesRead, NULL)) {
			// Read successful
		}

		CloseHandle(hFile);
	}
}

void FileHandler::WriteFile_fh(const WCHAR* filePath, const WCHAR* buffer, size_t size){
	WCHAR fullPath[1024] = { 0 };
	wcscpy_s(fullPath, p_path.get());
	wcscat_s(fullPath, filePath);
	
	HANDLE hFile = CreateFileW(fullPath, FILE_GENERIC_WRITE | FILE_GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE , NULL, OPEN_ALWAYS, FILE_APPEND_DATA, NULL);

	SetFilePointer(hFile, 0, NULL, FILE_END);

	OutputDebugString(L"Writing to file: ");
	OutputDebugString(fullPath);


	if (hFile != INVALID_HANDLE_VALUE) {
		OutputDebugStringW(L"File opened successfully for writing\n");
		DWORD bytesWritten = 0;
		if (WriteFile(hFile, buffer, static_cast<DWORD>(size), &bytesWritten, NULL)) {
			// Write successful
			OutputDebugString(L"Write successful\n");
		}
		
		CloseHandle(hFile);
	}
	else
	{
		OutputDebugString(L"Failed to open file for writing\n");
	}
}
