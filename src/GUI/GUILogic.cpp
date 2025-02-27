#include "GUI/GUILogic.h"

#include "Controls.h"

#include <imgui.h>
void GUILogic_draw()
{
    /*
    std::vector<std::shared_ptr<LogicElements::LogicGate>> selected_logics =
    Controls::Controls_get_selected_logic(); for (size_t i = 0; i <selected_logics.size() ; i++)
    {
        if (selected_logics[i])
        {
            //ImGui::Begin(selected_logics[i]->name.c_str());
            ImGui::Begin("new window");
            int two = 2;
            //ImGui::InputText("name", (char*)selected_logics[i]->name); // so much work :(
            ImGui::InputInt("input no", &two); // I dont know not decided how to yet
            ImGui::InputInt("output no", &two); // I dont know not decided how to yet
            int pos[2] = { selected_logics[i]->bd.x  , selected_logics[i]->bd.y };
            ImGui::InputInt2("pos", pos);
            ImGui::End();
        }

    } */
}