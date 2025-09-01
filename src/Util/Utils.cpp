#include "Util/Utils.h"
#include "appSettings.h"
namespace Utils
{
    int SignalValToBit()
    {
        return -1;
    }
    int BitsToDecimal(const std::vector<SignalVal>& bits, bool msbFirst ) 
    {
        int value = 0;

        if (msbFirst) 
        {
            // Left-to-right: [MSB, ..., LSB]
            for (auto b : bits) 
            {
                value <<= 1;  // shift left (multiply by 2)
                if (b == SignalVal::SIGNAL_1) value |= 1;
                else if (b == SignalVal::SIGNAL_X || b == SignalVal::SIGNAL_Z) {
                    // handle unknowns — here we just stop, or could throw
                    return -1; // or mark as invalid
                }
            }

        } 
        else 
        {
            // Right-to-left: [LSB, ..., MSB]
            for (size_t i = 0; i < bits.size(); i++) 
            {
                if (bits[i] == SignalVal::SIGNAL_1) {
                    value |= (1 << i);
                } else if (bits[i] == SignalVal::SIGNAL_X || bits[i] == SignalVal::SIGNAL_Z) {
                    // same handling for unknowns
                    return -1; 
                }
            }
        }
        return value; 
    }
	bool CheckNearWire(SP_Circuit circuit, const Vector2& mousePosition,
                       CircuitElements::Connection& con)
    {
        for (int i = 0; i < (int)circuit->connections.size(); i++)
        {
            if (circuit->connections[i].get()->physCon.wires.size() == 0)
            {
                continue; 
            }
            for (int j = 0; j < (int)circuit->connections[i].get()->physCon.wires.size() - 1; j++)
            {
                Vector2 start = circuit->connections[i].get()->physCon.wires[j];
                Vector2 end = circuit->connections[i].get()->physCon.wires[j + 1];
                Rectangle col = {0, 0, 0, 0};

                if (std::abs(end.x - start.x) < AppSettings::appSettings.SPACING_SIZE)
                {
                    col = {start.x - AppSettings::appSettings.MOUSE_SELECTION_OFFSET, start.y,
                           (float)(AppSettings::appSettings.SPACING_SIZE + AppSettings::appSettings.MOUSE_SELECTION_OFFSET),
                           std::abs(end.y - start.y)};
                }
                else if (std::abs(end.y - start.y) < AppSettings::appSettings.SPACING_SIZE)
                {
                    col = {start.x, start.y + -AppSettings::appSettings.MOUSE_SELECTION_OFFSET,
                           std::abs(end.x - start.x),
                           (float)(AppSettings::appSettings.SPACING_SIZE + AppSettings::appSettings.MOUSE_SELECTION_OFFSET)};
                }
                if (CheckCollisionPointRec(mousePosition, col))
                {
                    con = *circuit->connections[i].get();
                    return true;
                }
            }
        }
        return false;
    }
    Vector2 SnapToNearestGrid(const Rectangle& rect)
    {
        Vector2 nearest_grid_point;
        nearest_grid_point.x =
            std::round(rect.x / AppSettings::appSettings.SPACING_SIZE) * AppSettings::appSettings.SPACING_SIZE;
        nearest_grid_point.y =
            std::round(rect.y / AppSettings::appSettings.SPACING_SIZE) * AppSettings::appSettings.SPACING_SIZE;
        // TODO: Highlight the nearest grid point
        return nearest_grid_point;
    }


}
