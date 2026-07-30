#include "pch.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	WindowRenderer renderer(1280, 720, hInstance);
	Logger logger;
	FileHandler fileHandler;
	logger.PrintLog(L"Bosky Engine started successfully.\n");
	renderer.run();
	

	return 0;
}