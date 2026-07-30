#include "main.h"
#include "window_renderer.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	WindowRenderer renderer(1280, 720);
	renderer.run();

	return 0;
}