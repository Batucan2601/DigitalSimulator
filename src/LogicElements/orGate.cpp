#include <orGate.h>

namespace LogicElements::Gates
{
    OrGate::OrGate(std::string &logger_name) : LogicGate(logger_name)
    {
        inputs["A"] = false;
        inputs["B"] = false;
        outputs["Out"] = false;
        type = GateType::OR;
        m_logger.info("Or Gate Created.");

        // Construct the full path for the image
        std::string file_path = "assets/gates/test_or.png"; // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

        // Check if the file exists
        if (!std::filesystem::exists(full_path))
        {
            m_logger.error("File does not exist: ", full_path);
            throw std::runtime_error("Failed to find file: " + full_path);
        }

        // Load image and texture
        Image image = LoadImage(full_path.c_str());
        if (!image.data)
        {
            m_logger.error("Failed to load image: ", full_path);
            throw std::runtime_error("Failed to load image: " + full_path);
        }

        m_texture = LoadTextureFromImage(image);
        if (!m_texture.id)
        {
            m_logger.error("Failed to load texture from image: ", full_path);
            UnloadImage(image); // Free resources if texture loading fails
            throw std::runtime_error("Failed to load texture from image: " + full_path);
        }
    }

    void OrGate::evaluate()
    {
        outputs["Out"] = inputs["A"] || inputs["B"];
    }

}
