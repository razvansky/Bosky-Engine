#include "pch.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_	int nCmdShow) {
	WindowRenderer renderer(1280, 720, hInstance);
	Logger logger;
	FileHandler fileHandler;
	logger.PrintLog(L"Bosky Engine started successfully.\n");
	renderer.run();
	

	return 0;
}