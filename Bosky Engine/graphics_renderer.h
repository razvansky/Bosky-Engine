#pragma once
#include "pch.h"


class GraphicsRenderer {
public:
	GraphicsRenderer(BOOL useWarp, UINT32 clientWidth, UINT32 clientHeight, HWND hWnd);
	~GraphicsRenderer();

	GraphicsRenderer();

	VOID Paint();
	VOID setVSync();
	VOID setFullScreen();
	VOID Update();
	VOID Render();
	VOID Resize(UINT32 width, UINT32 height);
	VOID FlushPublic();

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
	Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter(BOOL useWarp);
	Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter);
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	BOOL CheckTearingSupport();
	Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain(Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, HWND hWnd, UINT32 width, UINT32 height, UINT32 bufferCount);
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT32 numDescriptors);
	VOID UpdateRenderTargetViews(Microsoft::WRL::ComPtr<ID3D12Device2> device, Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap);
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateCommandList(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type, Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator);
	Microsoft::WRL::ComPtr<ID3D12Fence> CreateFence(Microsoft::WRL::ComPtr<ID3D12Device2> device);
	HANDLE CreateEventHandle();
	UINT64 Signal(Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, Microsoft::WRL::ComPtr<ID3D12Fence> fence, UINT64& fenceValue);
	VOID WaitForFenceValue(Microsoft::WRL::ComPtr<ID3D12Fence> fence, UINT64 fenceValue, HANDLE fenceEvent, std::chrono::milliseconds duration = std::chrono::milliseconds::max());
	VOID Flush(Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, Microsoft::WRL::ComPtr<ID3D12Fence> fence, UINT64& fenceValue, HANDLE fenceEvent);
	VOID SetFullScreen(BOOL fullscreen);
};
