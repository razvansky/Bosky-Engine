#pragma once

class FileHandler {
public:
	FileHandler();
	~FileHandler();
	static FileHandler* Instance();
	static void ReadFile_fh(const WCHAR* filePath, WCHAR** buffer, size_t* size);
	static void WriteFile_fh(const WCHAR* filePath, const WCHAR* buffer, size_t size);
	WCHAR* GetPath() { return this->p_path.get(); }
	
private:
	static FileHandler* p_instance;
	static std::unique_ptr<WCHAR[]> p_path;
};
