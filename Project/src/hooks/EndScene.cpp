#include <pch.h>
#include <base.h>
#include <gui_and_logic.h>

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;

	// One time initialization
	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20.f);

		ImFontConfig config;
		config.MergeMode = true;
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		io.Fonts->AddFontFromMemoryCompressedTTF(fontawesome_webfont, fontawesome_webfont_compressed_size, 20.0f, &config, icon_ranges);
		io.Fonts->Build();

		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX9_Init(pDevice);

		Data::InitImGui = true;

		return Data::oEndScene(pDevice);
	}

	/*
	if (!Data::InitImGui)
	{
		return Data::oEndScene(pDevice);
	}
	*/

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// If menu should be displayed
	if (Data::ShowMenu)
	{
		GUI::SetTheme();
		GUI::Render();
		GUI::ExecuteInterfaceLogic();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	if (Data::ToDetach)
	{
		Base::Detach();
	}

	return Data::oEndScene(pDevice);
}