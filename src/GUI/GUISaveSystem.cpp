#include "GUI/GUISaveSystem.h"
namespace GUISaveSystem
{
	enum class State {  // sorting for filetering of the file lsit
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
	static bool loadCircuit();
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
			saveState =  State::STATE_SAVING_FIRST_TIME;
		}
		return true; 
	}

	void draw()
	{
		if (saveState == State::STATE_SAVING_FIRST_TIME || saveState == State::STATE_CLICKED)
		{
			// open Dialog Simple
			IGFD::FileDialogConfig config;
			config.path = ".";
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".dr", config);
			// display
			if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
				if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
					std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
					// action
					saveCircuit(filePath);
				}

				// close
				ImGuiFileDialog::Instance()->Close();

			}
		}
		if (is_on_load)
		{
			IGFD::FileDialogConfig config;
			config.path = ".";
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".dr", config);
			// In your rendering loop, display and handle the dialog:
			if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
			{
				if (ImGuiFileDialog::Instance()->IsOk())
				{
					// Retrieve the complete file path that the user entered.
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

					// Use standard file I/O to create (or overwrite) the file.
					std::ofstream outFile(filePathName, std::ios::out);
					if (outFile.is_open())
					{
						// Write the contents you want to save.
						outFile << "Your data to be saved";
						outFile.close();
					}
					else
					{
						// Optionally handle the error, such as notifying the user.
					}
				}
				// Close the file dialog.
				ImGuiFileDialog::Instance()->Close();
			}
		}
	}

	static bool saveCircuit(std::string fileName)
	{
		
	}
}