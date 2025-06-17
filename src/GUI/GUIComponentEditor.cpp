#pragma once
#include "GUI/GUIComponentEditor.h"
#include <imgui.h>
#include <memory>

// Forward declarations
class LogicGate;
using SP_LogicGate = std::shared_ptr<LogicGate>;

//namespace GUI
//{
//    class ComponentGateWindow : public BaseWindow
//    {
//    public:
//
//        void SetTarget(SP_LogicGate gate)
//        {
//            targetGate = gate;
//        }
//
//        void Draw(SP_Circuit circuit) override
//        {
//            if (!visible || !targetGate)
//                return;
//
//            ImGui::Begin(title.c_str(), &visible);
//
//            // Editable label
//            char labelBuffer[64];
//            //strncpy(labelBuffer, targetGate->GetLabel().c_str(), sizeof(labelBuffer));
//            if (ImGui::InputText("Label", labelBuffer, sizeof(labelBuffer)))
//            {
//                //targetGate->SetLabel(labelBuffer);
//            }
//
//
//            // Input/output counts
//            int inputCount = targetGate->GetInputCount();
//            if (ImGui::SliderInt("Inputs", &inputCount, 1, 8))
//            {
//                targetGate->SetInputCount(inputCount);
//            }
//
//            int outputCount = targetGate->GetOutputCount();
//            if (ImGui::SliderInt("Outputs", &outputCount, 1, 4))
//            {
//                targetGate->SetOutputCount(outputCount);
//            }
//
//            // Enabled toggle
//            bool enabled = targetGate->IsEnabled();
//            if (ImGui::Checkbox("Enabled", &enabled))
//            {
//                targetGate->SetEnabled(enabled);
//            }
//
//            // Optional: color picker for visual feedback
//            float* color = targetGate->GetColor();
//            if (ImGui::ColorEdit3("Color", color))
//            {
//                targetGate->SetColor(color);
//            }
//
//            ImGui::Separator();
//            if (ImGui::Button("Close"))
//            {
//                Hide();
//            }
//
//            ImGui::End();
//        }
//
//        void Update(SP_Circuit /*circuit*/) override
//        {
//            // LogicGateWindow doesn't need continuous updates
//        }
//
//    private:
//        SP_LogicGate targetGate = nullptr;
//    };
//}
