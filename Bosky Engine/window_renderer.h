#pragma once
#include <Windows.h>
#include <exception>

class WindowRenderer {
public:
	WindowRenderer(int width, int height, HINSTANCE hInstance);
	~WindowRenderer();
	void run();  // Main message loop

private:	
	int _width, _height;
	HWND _hwnd;
	WNDCLASSEX _wcex;
	LPCWSTR _WindowClassName, _WindowTitle;
	HINSTANCE _hInstance;
	void createWindow();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};


