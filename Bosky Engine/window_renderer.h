#pragma once
#include <Windows.h>

class WindowRenderer {
public:
	WindowRenderer(int width, int height);
	~WindowRenderer();
	void run();  // Main message loop

private:	
	int width, height;
	HWND hwnd;
	void createWindow();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};


