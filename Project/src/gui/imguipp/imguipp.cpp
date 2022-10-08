#include <pch.h>
#include <imguipp/imguipp.h>

namespace imguipp
{
	float getx()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float gety()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	void button(const char* label, int& currentTab, int newTab, ImVec2 size)
	{
		if (ImGui::Button(label, size))
			currentTab = newTab;
	}

	bool toggle_button(const char* str_id, bool* v)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;
		bool  isClicked = false;

		ImGui::InvisibleButton(str_id, ImVec2(width, height));
		if (ImGui::IsItemClicked())
		{
			*v = !*v;
			isClicked = true;
		}

		float t = *v ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.08f;
		if (g.LastActiveId == g.CurrentWindow->GetID(str_id)) // && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
			t = *v ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		return isClicked;
	}

	void line(int newId)
	{
		std::string id = ("imguipp_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void line_vertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
	}

	void center_text(const char* text, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			line(lineId);
	}

	void center_text_ex(const char* text, float width_available, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width_available / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			line(lineId);
	}

	namespace helper
	{
		float get_window_size_x()
		{
			return ImGui::GetWindowSize().x;
		}

		float get_window_size_y()
		{
			return ImGui::GetWindowSize().y;
		}

		ImVec2 get_window_size()
		{
			return ImGui::GetWindowSize();
		}

		char* get_window_name()
		{
			return ImGui::GetCurrentWindow()->Name;
		}

		ImDrawList* get_drawlist()
		{
			return ImGui::GetCurrentWindow()->DrawList;
		}
	}

	ImVec4 to_vec4(float r, float g, float b, float a)
	{
		return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}
}