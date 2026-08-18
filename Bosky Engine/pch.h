#pragma once


#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <exception>
#include <shlobj.h>
#include <fstream>
#include <filesystem>
#include <memory>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")


#include "Helpers.h"
#include "logger.h"
#include "filehandler.h"
#include "window_renderer.h"
#include "resource.h"
#include "time.h"
#include "graphics_renderer.h"

