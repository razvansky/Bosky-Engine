#pragma once
#include "pch.h"


class GraphicsRenderer {
public:



private:
	static const UINT8 g_NumFrames = 3;
	BOOL g_UseWarp = FALSE;
	UINT32 g_ClientWidht, g_ClientHeight;
	BOOL g_IsInitialized = FALSE;

	HWND g_hWnd;
	RECT g_WindowRect;

	Microsoft::WRL::ComPtr<ID3D12Device2> g_Device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> g_CommandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> g_SwapChain;
	Microsoft::WRL::ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> g_CommandList;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;

	UINT g_RTVDescriptorSize;
	UINT g_CurrentBackBufferIndex;

	Microsoft::WRL::ComPtr<ID3D12Fence> g_Fence;
	UINT64 g_FenceValue = 0;
	UINT64 g_FrameFenceValues[g_NumFrames] = {};
	HANDLE g_FenceEvent;

	BOOL g_VSync = TRUE;
	BOOL g_TearingSupported = FALSE;
	BOOL g_FullScreen = FALSE;

	VOID EnableDebugLayer();



};
