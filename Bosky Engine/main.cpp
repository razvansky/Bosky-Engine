#include "pch.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_	int nCmdShow) {
	Logger logger;
	FileHandler fileHandler;
	
	WindowRenderer renderer(1280, 720, hInstance);
	
	
	renderer.run();
	
	
	return 0;
}