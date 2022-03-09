#include "pch.h"
#include "FontAwesomeIcons.h"

std::once_flag init_device;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LONG_PTR original_wndproc;

LRESULT __stdcall wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) 
{
	WndProcEvent::window_procedure(hwnd, msg, w_param, l_param);

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param))
		return true;
	return CallWindowProcW((WNDPROC)original_wndproc, hwnd, msg, w_param, l_param);
}

HRESULT __stdcall DxHook::hooked_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags)
{
	std::call_once(init_device, [&]() {
		init_imgui(p_swap_chain);
		});
	render();
	HRESULT ret = ((tDxPresent)directx_vtable.at(PresentIndex))(p_swap_chain, sync_interval, flags);
	return ret;
}

HRESULT __stdcall DxHook::hooked_buffer(IDXGISwapChain* p_swap_chain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swap_chain_flags)
{
	if (main_render_target_view) {
		main_render_target_view->Release();
		main_render_target_view = nullptr;
	}

	HRESULT ret = ((tDxResizeBuffer)directx_vtable.at(ResizeBufferIndex))(p_swap_chain, buffer_count, width, height, new_format, swap_chain_flags);
	create_render_target();
	return ret;
}

bool DxHook::initiliaze()
{
	auto material_registry = reinterpret_cast<DWORD(__stdcall*)()>(Patchables::materialRegistry)();
	auto swap_chain = *reinterpret_cast<IDXGISwapChain**>(material_registry + static_cast<__int32>(Offsets::Gui::swapChain));

	PLH::VFuncMap redirect = { {(uint16_t)PresentIndex, (uint64_t)hooked_present},  {(uint16_t)ResizeBufferIndex, (uint64_t)hooked_buffer} };
	vfunc_hook = std::make_unique<PLH::VFuncSwapHook>((char*)swap_chain, redirect, &directx_vtable);

	if (vfunc_hook->hook())
		return true;
	else
		return false;
}

void DxHook::remove()
{
	SetWindowLongPtr(*reinterpret_cast<HWND*>(Patchables::riotWindow), GWLP_WNDPROC, original_wndproc);
	vfunc_hook->unHook();
}

void DxHook::create_render_target()
{
	ID3D11Texture2D* back_buffer;
	p_swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
	d3d11_device->CreateRenderTargetView(back_buffer, NULL, &main_render_target_view);
	back_buffer->Release();
}

void DxHook::init_imgui(IDXGISwapChain* device)
{
	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	load_styles();
	auto hwnd = *reinterpret_cast<HWND*>(Patchables::riotWindow);
	ImGui_ImplWin32_Init(hwnd);
	p_swap_chain = device;
	p_swap_chain->GetDevice(__uuidof(d3d11_device), reinterpret_cast<void**>(&(d3d11_device)));
	d3d11_device->GetImmediateContext(&d3d11_device_context);
	create_render_target();
	ImGui_ImplDX11_Init(d3d11_device, d3d11_device_context);
	ImGui_ImplDX11_CreateDeviceObjects();
	original_wndproc = SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wnd_proc);
}

static bool g_console_flag = true;


void DrawCircle(Vector3 world_pos, float radius, ImColor color, float thickness)
{
	float step = 6.2831f / 100;
	float theta = 0.f;
	ImVec2 points[200];

	for (int i = 0; i < 200; i++, theta += step) {
		auto world_space = Vector3(world_pos.x + radius * cos(theta), world_pos.y, world_pos.z - radius * sin(theta));

		Vector2 screen_space = Renderer::instance()->world_to_screen(world_space);
		points[i].x = screen_space.x;
		points[i].y = screen_space.y;
	}

	ImGui::GetBackgroundDrawList()->AddPolyline(points, 200, color, true, thickness);
}

void DxHook::render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	WindowManager::instance()->update();
	WindowManager::instance()->render();

	ImGui::Begin("Time");
	ImGui::Text("%f", Globals::get_game_time());
	ImGui::End();

	
	Console::instance()->Draw("Console", &g_console_flag);

	ImGui::EndFrame();
	ImGui::Render();

	d3d11_device_context->OMSetRenderTargets(1, &main_render_target_view, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void DxHook::load_styles()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_WindowBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.88f);
	style->Colors[ImGuiCol_TitleBg]           = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive]     = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_Header]            = ImVec4(0.53f, 0.00f, 0.24f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered]     = ImVec4(0.89f, 0.12f, 0.48f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive]      = ImVec4(0.53f, 0.00f, 0.24f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip]        = ImVec4(0.53f, 0.00f, 0.24f, 0.67f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.89f, 0.12f, 0.48f, 0.67f);
	style->Colors[ImGuiCol_ResizeGripActive]  = ImVec4(0.89f, 0.12f, 0.48f, 0.67f);
	style->Colors[ImGuiCol_SeparatorActive]   = ImVec4(0.53f, 0.00f, 0.24f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered]     = ImVec4(0.89f, 0.12f, 0.48f, 1.00f);
	style->Colors[ImGuiCol_FrameBg]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered]    = ImVec4(0.90f, 0.31f, 0.58f, 0.54f);
	style->Colors[ImGuiCol_FrameBgActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style->Colors[ImGuiCol_CheckMark]         = ImVec4(1.00f, 0.85f, 0.30f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab]        = ImVec4(1.00f, 0.88f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive]  = ImVec4(1.00f, 0.85f, 0.30f, 1.00f);
	style->Colors[ImGuiCol_Button]            = ImVec4(0.53f, 0.00f, 0.24f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered]     = ImVec4(0.89f, 0.12f, 0.48f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive]      = ImVec4(0.53f, 0.00f, 0.24f, 1.00f);

	style->WindowPadding                      = ImVec2(8, 8);
	style->FramePadding                       = ImVec2(4, 3);
	style->WindowBorderSize                   = 0.0f;
	style->WindowRounding                     = 9.0f;
	style->FrameRounding                      = 3.0f;
	style->WindowTitleAlign                   = ImVec2(0.50f, 0.95f);
	style->WindowMenuButtonPosition           = ImGuiDir_None;

	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig icons_config; 
	icons_config.PixelSnapH = true;
	
	g_mainFont  = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 14.0f, &icons_config);
	g_titleFont = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 16.0f, &icons_config);
}

ImFont* DxHook::get_title_font()
{
	return g_titleFont;
}

ImFont* DxHook::get_main_font()
{
	return g_mainFont;
}
