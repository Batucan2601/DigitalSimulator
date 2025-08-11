#ifndef GUISETTINGS2_H
#define GUISETTINGS2_H
#include <GUI/include.h>

namespace GUI
{
    class Settings : public BaseWindow
    {
      public:
        Settings() : BaseWindow("Settings") {}

        void Draw(std::shared_ptr<CircuitController> circuit) override;
        void Update(std::shared_ptr<CircuitController> circuit) override;
      protected:
    };
}  // namespace GUI

#endif  // GUISETTINGS_H