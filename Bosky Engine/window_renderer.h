#pragma once

class WindowRenderer {
public:
	WindowRenderer(INT width, INT height, HINSTANCE hInstance);
	~WindowRenderer();
	void run();  // Main message loop

private:	
	int _width, _height;
	HWND _hwnd;
	WNDCLASSEX _wcex;
	LPCWSTR _WindowClassName, _WindowTitle;
	MSG _msg;
	HICON _hIcon;
	HINSTANCE _hInstance;
	void createWindow();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};


