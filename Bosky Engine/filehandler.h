#pragma once

class FileHandler {
public:
	FileHandler();
	~FileHandler();
	static FileHandler* Instance();
	static void ReadFile_fh(const WCHAR* filePath, char** buffer, size_t* size);
	static void WriteFile_fh(const WCHAR* filePath, const char* buffer, size_t size);
	WCHAR* GetPath() { return (WCHAR*)_path; }
	
private:
	static FileHandler* _instance;
	static const WCHAR* _path;
};
