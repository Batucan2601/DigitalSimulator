#include "GUI/GUIStyle.h"
#include <imgui.h>
void GUIStyle_init()
{
	ImGuiStyle& style = ImGui::GetStyle();
	// Customize colors
	style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.5f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.6f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(47.0f / 255.0f, 79.0f / 255.0f, 79.0f / 255.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(47.0f / 255.0f, 79.0f / 255.0f, 79.0f / 255.0f, 1.0f);

}