#include "window_renderer.h"



WindowRenderer::WindowRenderer(int width, int height) {
	this->width = width;
	this->height = height;
	this->hwnd = NULL;
	createWindow();
}

WindowRenderer::~WindowRenderer() {
	if (hwnd) {
		DestroyWindow(hwnd);
	}
}

void WindowRenderer::createWindow() {
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowRenderer::WindowProc;  // Connect your custom message handler
	wc.lpszClassName = L"BoskyEngineWindow";
	RegisterClass(&wc);

	hwnd = CreateWindowEx(
		0,
		L"BoskyEngineWindow",
		L"Bosky Engine",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (!hwnd) {
		return;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
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

