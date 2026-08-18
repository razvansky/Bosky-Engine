#pragma once

class GraphicsRenderer;

class WindowRenderer {
public:
	WindowRenderer(INT width, INT height, HINSTANCE hInstance);
	~WindowRenderer();
	void run();  // Main message loop

private:	
	int p_width, p_height;
	HWND p_hwnd;
	WNDCLASSEX p_wcex;
	LPCWSTR p_WindowClassName, p_WindowTitle;
	MSG p_msg;
	HICON p_hIcon;
	HINSTANCE p_hInstance;
	
	std::unique_ptr<GraphicsRenderer> p_GraphicsRendererInstance;

	void createWindow();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};


