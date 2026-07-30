#include "window_renderer.h"



WindowRenderer::WindowRenderer(int width, int height, HINSTANCE hInstance) {
	this->_WindowClassName = L"BoskyEngineWindow";
	this->_WindowTitle = L"Bosky Engine";

	this->_width = width;
	this->_height = height;

	this->_hwnd = NULL;
	this->_hInstance = hInstance;

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

	_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	_wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	_wcex.lpszMenuName = nullptr;
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
	}
	catch (const std::exception& e) {
		MessageBoxA(NULL, e.what(), "Failed to create window", MB_OK | MB_ICONERROR);
		return;
	}


	ShowWindow(this->_hwnd, SW_SHOW);
	UpdateWindow(this->_hwnd);
}

void WindowRenderer::run() {
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);	
	}
}

LRESULT CALLBACK WindowRenderer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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

