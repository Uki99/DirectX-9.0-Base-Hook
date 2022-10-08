#include <pch.h>
#include <gui_and_logic.h>

int Settings::tab = 0;

void GUI::SetTheme(void)
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->Colors[ImGuiCol_WindowBg]         = ImColor(24, 24, 24, 255);
	style->Colors[ImGuiCol_Text]             = ImColor(255, 255, 255, 255);

	style->Colors[ImGuiCol_TitleBg]          = ImColor(19, 1, 36, 255);
	style->Colors[ImGuiCol_TitleBgActive]    = ImColor(19, 1, 36, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(10, 1, 30, 255);

	style->Colors[ImGuiCol_Button]           = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonActive]     = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonHovered]    = ImColor(41, 40, 41, 255);

	style->Colors[ImGuiCol_Separator]        = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive]  = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(70, 70, 70, 255);

	style->WindowMinSize    = ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT);
	style->FramePadding     = ImVec2(8, 6);
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
}

void GUI::Render(void)
{
	ImGui::Begin(WINDOW_NAME, nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	// Colors and the rest of used data for menu drawing

	static ImVec4 active   = imguipp::to_vec4(41, 40, 41, 255);
	static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

	// Menu here
	{
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 230);

		ImGui::PushStyleColor(ImGuiCol_Button, Settings::tab == 1 ? active : inactive);
		if (ImGui::Button(ICON_FA_CODE " EXECUTE", ImVec2((230 - 15), 41)))
			Settings::tab = 1;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("I am a tooltip");

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::tab == 2 ? active : inactive);
		if (ImGui::Button(ICON_FA_DOWNLOAD " DUMPER", ImVec2((230 - 15), 41)))
			Settings::tab = 2;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("I am a tooltip");

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::tab == 3 ? active : inactive);
		if (ImGui::Button(ICON_FA_BUG " BLOCKER", ImVec2((230 - 15), 41)))
			Settings::tab = 3;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("I am a tooltip");

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::tab == 4 ? active : inactive);
		if (ImGui::Button(ICON_FA_BOOK " MENUS", ImVec2((230 - 15), 41)))
			Settings::tab = 4;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("I am a tooltip");

		ImGui::PopStyleColor(4);

		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
		imguipp::center_text_ex("Apollyion", 230, 1, false);


		ImGui::NextColumn();
		switch (Settings::tab)
		{
			case 1:
			{
				static bool IsToggledButton_btn_1 = false;
				if (imguipp::toggle_button("btn_1", &IsToggledButton_btn_1))
				{
					// Do something if button is toggled.
				}

				break;
			}
			case 2:
			{

				break;
			}
			case 3:
			{

				break;
			}
			case 4:
			{

				break;
			}
			default:
			{
				break;
			}
		}
	}

	ImGui::End();
}

void GUI::ExecuteInterfaceLogic(void)
{
	// GUI logic here
}