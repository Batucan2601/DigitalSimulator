#ifndef GUISETTINGS2_H
#define GUISETTINGS2_H
#include <GUI/include.h>

namespace GUI
{
    class Settings : public BaseWindow
    {
      public:
        Settings() : BaseWindow("Settings") {}

        void Draw(SP_Circuit circuit) override;

      protected:
    };
}  // namespace GUI

#endif  // GUISETTINGS_H