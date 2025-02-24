#include "GUI/GUISaveSystem.h"
namespace GUISaveSystem
{
    enum class State
    {  // sorting for filetering of the file lsit
        STATE_IDLE,
        STATE_CLICKED,
        STATE_CANCELLED,
        STATE_COMPLETE,
        STATE_SAVING_FIRST_TIME,
    };
    State saveState = State::STATE_IDLE;
    std::string saveFilePath = "";
    bool is_on_save = false;
    bool is_on_load = false;
    std::shared_ptr<CircuitElements::Circuit> localCircuit;

    static bool saveCircuit(std::string name);
    static bool loadCircuit(std::string name);
    bool loadFile(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        localCircuit = circuit;
        is_on_load = true;
        return true;
    }
    bool saveFile(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        localCircuit = circuit;
        if (saveFilePath == "")
        {
            saveState = State::STATE_SAVING_FIRST_TIME;
        }
        return true;
    }

    void draw()
    {
        if (saveState == State::STATE_SAVING_FIRST_TIME || saveState == State::STATE_CLICKED)
        {
            IGFD::FileDialogConfig config;
            config.path = ".";
            ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save Circuit", ".dr",
                                                    config);

            if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                    saveCircuit(filePath);
                }
                else
                {
                    saveState = State::STATE_CANCELLED;
                }
                ImGuiFileDialog::Instance()->Close();
            }
        }
        if (is_on_load)
        {
            IGFD::FileDialogConfig config;
            config.path = ".";
            ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlgKey", "Load Circuit", ".dr",
                                                    config);
            // In your rendering loop, display and handle the dialog:
            if (ImGuiFileDialog::Instance()->Display("LoadFileDlgKey"))
            {
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                    loadCircuit(filePath);
                }
                else
                {
                    saveState = State::STATE_CANCELLED;
                }
                // Close the file dialog.
                ImGuiFileDialog::Instance()->Close();
            }
        }
    }

    static bool saveCircuit(std::string fileName)
    {
        std::cout << "Saving file to: " << fileName << std::endl;
        std::ofstream outFile(fileName);
        if (outFile.is_open())
        {
            outFile << "Circuit" << std::endl;
            for (auto& gate : localCircuit.get()->gates)
            {
                outFile << (int)gate->getType() << " " << gate->getPosition().x << " "
                        << gate->getPosition().y << std::endl;
            }

            outFile << "Connections" << std::endl;
            for (auto& conn : localCircuit.get()->connections)
            {
                outFile << (int)conn.sourceGate->getType() << " "
                        << conn.sourceGate->getPosition().x << " "
                        << conn.sourceGate->getPosition().y << " " << conn.sourceLogic << " "
                        << (int)conn.targetGate->getType() << " "
                        << conn.targetGate->getPosition().x << " "
                        << conn.targetGate->getPosition().y << " " << conn.targetLogic << std::endl;
                outFile << "Wires" << std::endl;
                for (auto& wire : conn.physCon.wires)
                {
                    outFile << wire.x << " " << wire.y << std::endl;
                }
            }

            outFile.close();
        }
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

    static bool loadCircuit(std::string fileName)
    {
        std::cout << "Loading file from: " << fileName << std::endl;
        std::ifstream inFile(fileName);
        if (!inFile.is_open())
        {
            std::cerr << "Error: Could not open file " << fileName << std::endl;
            return false;
        }

        // ✅ Clear existing circuit before loading a new one
        localCircuit.get()->gates.clear();
        localCircuit.get()->connections.clear();

        std::string line;
        bool parsingConnections = false;  // Track whether we're parsing the "Connections" section

        while (std::getline(inFile, line))
        {
            // ✅ Identify section headers
            if (line == "Circuit")
            {
                parsingConnections = false;
                continue;
            }
            else if (line == "Connections")
            {
                parsingConnections = true;
                continue;
            }

            std::istringstream iss(line);

            if (!parsingConnections)
            {
                // ✅ Parsing Circuit (Gate Definition): `type x y`
                int type, x, y;
                if (!(iss >> type >> x >> y))
                {
                    std::cerr << "Error: Invalid gate format in line: " << line << std::endl;
                    continue;
                }

                auto gate = LogicElements::LogicElementFactory::createGate(
                    static_cast<LogicElements::GateType>(type), "logger");

                if (gate)
                {
                    gate->setPosition(x, y);
                    localCircuit.get()->addGate(gate);
                }
            }
            else
            {
                // ✅ Parsing Connections: `sourceType sx sy sourceLogic targetType tx ty
                // targetLogic`
                int sourceType, sx, sy, targetType, tx, ty;
                std::string sourceLogic, targetLogic;

                if (!(iss >> sourceType >> sx >> sy >> sourceLogic >> targetType >> tx >> ty >>
                      targetLogic))
                {
                    std::cerr << "Error: Invalid connection format in line: " << line << std::endl;
                    continue;
                }

                auto sourceGate = findGateAtPosition(sx, sy);
                auto targetGate = findGateAtPosition(tx, ty);

                if (sourceGate && targetGate)
                {
                    localCircuit.get()->addConnection(sourceGate, sourceLogic, targetGate,
                                                      targetLogic);
                }
                else
                {
                    std::cerr << "Error: Could not find gates for connection: "
                              << " Source (" << sx << ", " << sy << ") -> " << sourceLogic
                              << " Target (" << tx << ", " << ty << ") -> " << targetLogic
                              << std::endl;
                }
            }
        }

        inFile.close();
        return true;
    }

}  // namespace GUISaveSystem