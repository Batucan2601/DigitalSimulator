#include "GUI/GUIStyle.h"
#include <string>

namespace GUIStyle
{
    void SetFuturisticImGuiStyle();
    ImFont* font;
    void init()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        // Customize colors
        /*style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.5f, 0.8f, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.6f, 0.9f, 1.0f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(47.0f / 255.0f, 79.0f / 255.0f, 79.0f / 255.0f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(47.0f / 255.0f, 79.0f / 255.0f, 79.0f / 255.0f, 1.0f);
        */
        SetFuturisticImGuiStyle();
    }

    void SetFuturisticImGuiStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        //  Backgrounds
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.12f, 0.15f, 0.95f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.10f, 0.12f, 0.90f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.12f, 0.15f, 0.98f);

        //  Text and Highlights
        colors[ImGuiCol_Text] = ImVec4(0.80f, 0.85f, 0.88f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.50f, 0.55f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.50f, 0.90f, 0.75f);  // Cool Blue Highlights
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.60f, 1.00f, 0.85f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.65f, 1.10f, 0.95f);

        //  Buttons & Frames
        colors[ImGuiCol_Button] = ImVec4(0.18f, 0.22f, 0.30f, 0.85f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.22f, 0.32f, 0.40f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.38f, 0.50f, 1.00f);

        //  Sliders & Input Fields
        colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.15f, 0.20f, 0.85f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.22f, 0.30f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.32f, 0.40f, 1.00f);

        //  Progress Bars & Scrollbars
        colors[ImGuiCol_PlotLines] = ImVec4(0.80f, 0.90f, 1.00f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.12f, 0.15f, 0.95f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.22f, 0.25f, 0.30f, 0.95f);

        //  Styling
        style.WindowRounding = 6.0f;
        style.FrameRounding = 6.0f;
        style.PopupRounding = 6.0f;
        style.GrabRounding = 4.0f;
        style.ScrollbarRounding = 6.0f;

        //  Animation Effect (Simulated by Gradual Color Change)
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.60f, 1.00f, 0.75f);  // Dynamic Hover Effect
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.70f, 1.10f, 0.85f);  // Slightly More Intense Active Color

        //  Enable Docking (For Advanced UI Layouts)
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // Menubar Background: Dark but slightly transparent
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.10f, 0.15f, 0.95f); // Deep bluish-black
        // Menubar Text: Bright Neon Cyan
        colors[ImGuiCol_Text] = ImVec4(0.00f, 0.95f, 1.00f, 1.00f); // Electric cyan
        // Hover Effect: Brighter Glow
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.80f, 1.00f, 0.85f); // Vibrant blue glow
        // Clicked/Active: Subtle deep blue
        colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);
        // Load Custom Font (Replace with Your Path)
        /*io.Fonts->AddFontDefault();
        std::string fontstr = PROJECT_ROOT_DIR + std::string("/assets/fonts/Roboto_Condensed-Medium.ttf");
        font = io.Fonts->AddFontFromFileTTF(fontstr.c_str(), 24.0f, NULL, io.Fonts->GetGlyphRangesDefault());
        io.Fonts->Build();
        IM_ASSERT(font != NULL);*/
    }

}
