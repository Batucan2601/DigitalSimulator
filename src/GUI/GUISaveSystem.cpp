#include "GUI/GUISaveSystem.h"

#include "main.h"
namespace GUISaveSystem
{
    State state = State::STATE_IDLE;

    std::shared_ptr<CircuitElements::Circuit> localCircuit;

    void ShowSaveWindow(std::shared_ptr<CircuitElements::Circuit> globalCircuit)
    {
        localCircuit = globalCircuit;
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_SAVE;
    }

    void ShowLoadWindow()
    {
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_LOAD;
    }

    void draw()
    {
        switch (state)
        {
            case State::STATE_IDLE:
                break;
            case State::STATE_SAVE:
                drawSaveWindow();
                break;
            case State::STATE_LOAD:
                drawLoadWindow();
                break;
            default:
                break;
        }
    }

    void drawSaveWindow()
    {
        IGFD::FileDialogConfig config;
        config.flags = ImGuiFileDialogFlags_Modal;
        config.path = std::filesystem::path(PROJECT_ROOT_DIR).string();

        ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save Circuit", ".dr", config);

        if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                saveCircuit(filePath);
            }
            // Close the file dialog.
            ImGuiFileDialog::Instance()->Close();
            state = State::STATE_IDLE;
        }
    }

    void drawLoadWindow()
    {
        IGFD::FileDialogConfig config;
        config.flags = ImGuiFileDialogFlags_Modal;
        config.path = std::filesystem::path(PROJECT_ROOT_DIR).string();
        ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlgKey", "Load Circuit", ".dr", config);
        // In your rendering loop, display and handle the dialog:
        if (ImGuiFileDialog::Instance()->Display("LoadFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                loadCircuit(filePath);
            }
            // Close the file dialog.
            ImGuiFileDialog::Instance()->Close();
            state = State::STATE_IDLE;
        }
    }

    bool saveCircuit(std::string fileName)
    {
        std::cout << "Saving file to: " << fileName << std::endl;
        jsonParser::saveCircuit(*localCircuit.get(), fileName);
        return true;
    }

    std::shared_ptr<LogicElements::LogicGate> findGateAtPosition(int x, int y)
    {
        for (auto& gate : localCircuit.get()->gates)
        {
            if (gate->getPosition().x == x && gate->getPosition().y == y)
            {
                return gate;  // ✅ Return shared_ptr instead of raw pointer
            }
        }
        return nullptr;  // Return nullptr if not found
    }

    bool loadCircuit(std::string fileName)
    {
        std::cout << "Loading file from: " << fileName << std::endl;

        auto loaded_circuit = jsonParser::loadCircuit(fileName);

        setLoadedCircuit(loaded_circuit);

        return true;
    }

}  // namespace GUISaveSystem