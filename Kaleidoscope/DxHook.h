#pragma once
#include "framework.h"
#include <d3d11.h>
#include <polyhook2/Virtuals/VFuncSwapHook.hpp>

#define PresentIndex        8
#define ResizeBufferIndex  13

using tDxPresent      = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
using tDxResizeBuffer = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

namespace DxHook
{
	inline PLH::VFuncMap directx_vtable;
	inline std::unique_ptr<PLH::VFuncSwapHook> vfunc_hook;

	inline ID3D11Device*			d3d11_device			 = nullptr;
	inline ID3D11DeviceContext*		d3d11_device_context	 = nullptr;
	inline ID3D11RenderTargetView*  main_render_target_view  = nullptr;
	inline IDXGISwapChain*			p_swap_chain			 = nullptr;

	HRESULT __stdcall hooked_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
	HRESULT __stdcall hooked_buffer(IDXGISwapChain* p_swap_chain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swap_chain_flags);

	bool initiliaze();
	void remove();
	void create_render_target();

	void init_imgui(IDXGISwapChain* device);
	void render();

	void load_styles();

	inline ImFont* g_titleFont;
	inline ImFont* g_mainFont;

	ImFont* get_title_font();
	ImFont* get_main_font();
}