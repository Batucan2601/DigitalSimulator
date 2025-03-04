#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <map>
#include <string>
#include <vector>

namespace AppSettings
{
    typedef enum
    {
        DarkMode,
        LightMode
    } Theme;

    struct Settings
    {
        Theme theme;
        unsigned int screenWidth = 600;
        unsigned int screenHeight = 600;
        const unsigned int targetFps = 60;

        bool isDrawingBoundaryBox = false;
        bool showDemoWindow = false;
        int SPACING_SIZE = 25;
        int MOUSE_SELECTION_OFFSET = SPACING_SIZE / 2;
        float GRID_POINT_SIZE = 3;
        float SLICE_SIZE = 40;
        float IN_OUT_RECT_WIDTH = GRID_POINT_SIZE * 5;
        float IN_OUT_INTERACTION = IN_OUT_RECT_WIDTH * 2;
    };

    extern AppSettings::Settings appSettings;

}  // namespace AppSettings

#endif  // APP_SETTINGS_H