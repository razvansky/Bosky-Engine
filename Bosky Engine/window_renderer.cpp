#include "pch.h"
#include "graphics_renderer.h"


WindowRenderer::WindowRenderer(INT width, INT height, HINSTANCE hInstance) {
	this->p_WindowClassName = L"BoskyEngine";
	this->p_WindowTitle = L"Bosky Engine Window";
	this->p_width = width;
	this->p_height = height;

	this->p_hwnd = NULL;
	this->p_hInstance = hInstance;

	this->p_msg = { NULL };

	this->p_hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));


	createWindow();
}

WindowRenderer::~WindowRenderer() {
	if (this->p_hwnd) {
		DestroyWindow(this->p_hwnd);
	}

}

void WindowRenderer::createWindow() {

	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	//  Create a window class

	this->p_wcex = {};
	this->p_wcex.cbSize = sizeof(WNDCLASSEX);
	this->p_wcex.style = CS_HREDRAW | CS_VREDRAW;
	this->p_wcex.cbClsExtra = 0;
	this->p_wcex.cbWndExtra = 0;

	this->p_wcex.lpfnWndProc = WindowRenderer::WindowProc;
	this->p_wcex.lpszClassName = this->p_WindowClassName;

	this->p_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->p_wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	this->p_wcex.hIcon = this->p_hIcon;
	this->p_wcex.hIconSm = this->p_hIcon;

	this->p_wcex.lpszMenuName = NULL;

	// Register the window class

	RegisterClassEx(&this->p_wcex);

	// Create the window

	try {
		this->p_hwnd = CreateWindowEx(
			0,
			this->p_WindowClassName,
			this->p_WindowTitle,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			this->p_width,
			this->p_height,
			NULL,
			NULL,
			this->p_hInstance,
			this
		);

		if (this->p_hwnd == NULL) {
			throw std::exception("Failed to create window");
		}
	}
	catch (const std::exception& e) {
		MessageBoxA(NULL, e.what(), "Failed to create window", MB_OK | MB_ICONERROR);
		return;
	}

	Logger::PrintLog(TRUE, L"[%s] Window created successfully: %s\n", Time::GetDateTimeString(FALSE).c_str(), this->p_WindowTitle);

	if (p_hwnd)
		this->p_GraphicsRendererInstance = std::make_unique<GraphicsRenderer>(FALSE, this->p_width, this->p_height, this->p_hwnd);


	ShowWindow(this->p_hwnd, SW_SHOW);
	UpdateWindow(this->p_hwnd);

}

void WindowRenderer::run() {
	
	while (this->p_msg.message != WM_QUIT) {

		if (PeekMessage(&this->p_msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&this->p_msg);
			DispatchMessage(&this->p_msg);
		}

		else {
			
			Logger::PrintLog(FALSE, L"[%s] Running main loop\n", Time::GetDateTimeString(FALSE).c_str());

			p_GraphicsRendererInstance->FlushPublic();
		}
		
	}
}

LRESULT CALLBACK WindowRenderer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	WindowRenderer* pThis = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<WindowRenderer*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else
	{
		pThis = reinterpret_cast<WindowRenderer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	switch (uMsg)
	{

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		if (pThis && pThis->p_GraphicsRendererInstance)
		{
			pThis->p_GraphicsRendererInstance->Paint();
		}
		break;
	}
	case WM_SYSKEYDOWN:
		break;
	case WM_KEYDOWN:
	{
		bool alt = (::GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

		switch (wParam)
		{
		case 'V':
			if (pThis && pThis->p_GraphicsRendererInstance)
			{
				pThis->p_GraphicsRendererInstance->setVSync();
			}
			break;
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;
		case VK_RETURN:
			if (alt)
			{
		case VK_F11:
				if (pThis && pThis->p_GraphicsRendererInstance)
				{
					pThis->p_GraphicsRendererInstance->setFullScreen();
				}
			}
			break;
		}
	}
	case WM_SIZE:
	{
		RECT clientRect = {};
		::GetClientRect(hwnd, &clientRect);

		int width = clientRect.right - clientRect.left;
		int height = clientRect.bottom - clientRect.top;

		if (pThis && pThis->p_GraphicsRendererInstance)
		{
			pThis->p_GraphicsRendererInstance->Resize(width, height);
		}
		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

