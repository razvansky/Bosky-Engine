#include "pch.h"



WindowRenderer::WindowRenderer(INT width, INT height, HINSTANCE hInstance) {
	this->_WindowClassName = L"BoskyEngine";
	this->_WindowTitle = L"Bosky Engine Window";
	this->_width = width;
	this->_height = height;

	this->_hwnd = NULL;
	this->_hInstance = hInstance;

	this->_msg = { NULL };

	_hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));

	createWindow();
}

WindowRenderer::~WindowRenderer() {
	if (this->_hwnd) {
		DestroyWindow(this->_hwnd);
	}
}

void WindowRenderer::createWindow() {

	//  Create a window class

	_wcex = {};
	_wcex.cbSize = sizeof(WNDCLASSEX);
	_wcex.style = CS_HREDRAW | CS_VREDRAW;
	_wcex.cbClsExtra = 0;
	_wcex.cbWndExtra = 0;

	_wcex.lpfnWndProc = WindowRenderer::WindowProc;
	_wcex.lpszClassName = this->_WindowClassName;

	_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	_wcex.hIcon = this->_hIcon;
	_wcex.hIconSm = this->_hIcon;

	_wcex.lpszMenuName = NULL;
	_wcex.lpfnWndProc = WindowRenderer::WindowProc;

	// Register the window class

	RegisterClassEx(&_wcex);

	// Create the window

	try {
		this->_hwnd = CreateWindowEx(
			0,
			this->_WindowClassName,
			this->_WindowTitle,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			this->_width,
			this->_height,
			NULL,
			NULL,
			this->_hInstance,
			NULL 
		);

		if (this->_hwnd == NULL) {
			throw std::exception("Failed to create window");
		}
	}
	catch (const std::exception& e) {
		MessageBoxA(NULL, e.what(), "Failed to create window", MB_OK | MB_ICONERROR);
		return;
	}

	ShowWindow(this->_hwnd, SW_SHOW);
	UpdateWindow(this->_hwnd);

}

void WindowRenderer::run() {
	
	while (_msg.message != WM_QUIT) {

		if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}

		else {
			
		}
		
	}
}

LRESULT CALLBACK WindowRenderer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg)
	{

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

