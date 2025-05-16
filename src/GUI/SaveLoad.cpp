#include "GUI/SaveLoad.h"

#include "main.h"
namespace GUI
{
    SP_Circuit localCircuit;

    void SaveLoad::Draw(SP_Circuit circuit)
    {
        (void)circuit;
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

    void SaveLoad::Update(SP_Circuit circuit)
    {

    }
    void SaveLoad::ShowSaveWindow(SP_Circuit globalCircuit)
    {
        localCircuit = globalCircuit;
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_SAVE;
    }

    void SaveLoad::ShowLoadWindow()
    {
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_LOAD;
    }

    void SaveLoad::drawSaveWindow()
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

    void SaveLoad::drawLoadWindow()
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

    bool SaveLoad::saveCircuit(std::string fileName)
    {
        std::cout << "Saving file to: " << fileName << std::endl;
        jsonParser::saveCircuit(*localCircuit.get(), fileName);
        return true;
    }

    bool SaveLoad::loadCircuit(std::string fileName)
    {
        std::cout << "Loading file from: " << fileName << std::endl;

        auto loaded_circuit = jsonParser::loadCircuit(fileName);

        setLoadedCircuit(loaded_circuit);

        return true;
    }

}  // namespace GUI