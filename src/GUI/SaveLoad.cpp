#include "GUI/SaveLoad.h"

#include "main.h"
#include "SubCircuit.h"
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
                drawSaveWindow(circuit);
                break;
            case State::STATE_LOAD:
                drawLoadWindow(circuit);
                break;
            case State::STATE_LOADSUBCIRCUIT:
                drawSubcircuitWindow(circuit);
            default:
                break;
        }
    }

    void SaveLoad::Update(std::shared_ptr<CircuitController> circuit)
    {
        (void)circuit;
    }
    void SaveLoad::ShowSaveWindow()
    {
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_SAVE;
    }

    void SaveLoad::ShowLoadWindow()
    {
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_LOAD;
    }
    void SaveLoad::ShowLoadSubCircuitWindow()
    {
        ImGuiFileDialog::Instance()->Close();  // Ensure other dialogs are closed
        state = State::STATE_LOADSUBCIRCUIT;
    }

    void SaveLoad::drawSaveWindow(SP_Circuit circuit)
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
                localCircuit = circuit;
                saveCircuit(filePath);
            }
            // Close the file dialog.
            ImGuiFileDialog::Instance()->Close();
            state = State::STATE_IDLE;
        }
    }

    void SaveLoad::drawLoadWindow(SP_Circuit circuit)
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
                localCircuit = circuit;
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                loadCircuit(filePath);
            }
            // Close the file dialog.
            ImGuiFileDialog::Instance()->Close();
            state = State::STATE_IDLE;
        }
    }
     void SaveLoad::drawSubcircuitWindow(SP_Circuit circuit)
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
                localCircuit = circuit;
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                loadSubCircuit(filePath);
            }
            // Close the file dialog.
            ImGuiFileDialog::Instance()->Close();
            state = State::STATE_IDLE;
        }
    }
    bool SaveLoad::saveCircuit(std::string fileName)
    {
        jsonparser_saveCircuit(*localCircuit.get(), fileName);
        return true;
    }

    bool SaveLoad::loadCircuit(std::string fileName)
    {
        std::cout << "Loading file from: " << fileName << std::endl;

        auto loaded_circuit = jsonparser_loadCircuit(fileName);

        setLoadedCircuit(loaded_circuit);

        return true;
    }
     bool SaveLoad::loadSubCircuit(std::string fileName)
    {
        std::cout << "Loading file from: " << fileName << std::endl;
        
        auto loaded_circuit = jsonparser_loadCircuit(fileName);
        std::shared_ptr<SubcircuitComponent> ptr = std::make_shared<SubcircuitComponent>(loaded_circuit, "new_circuit");
        addComponent(ptr);

        return true;
    }
}  // namespace GUI