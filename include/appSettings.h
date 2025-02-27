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
    };

    extern AppSettings::Settings settings;

}  // namespace AppSettings

#endif  // APP_SETTINGS_H