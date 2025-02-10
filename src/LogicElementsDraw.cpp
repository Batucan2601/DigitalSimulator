#include "LogicElementsDraw.h"

static void DrawAnd(const std::shared_ptr<LogicGate> gate)
{
	// 1- drawstraight line
	DrawLine(gate->bd.x, gate->bd.y, gate->bd.x , gate->bd.y + gate->bd.height , BLACK);
	// 2 - draw circle 
	Vector2 center;
	center.x = gate->bd.x;
	center.y = gate->bd.y + gate->bd.height / 2;
	DrawCircleSectorLines(center, gate->bd.height / 2, -90, 90, 16, BLACK);
}
void DrawCircuit(const std::shared_ptr<Circuit> circuit)
{
	//1 - draw gates
	for (size_t i = 0; i < circuit->gates.size(); i++)
	{
		if ((*circuit->gates[i]).type == "and")
		{
			DrawAnd((circuit->gates[i]));
		}
	}
	//2 - drawConnections
	for (size_t i = 0; i < circuit->connections.size(); i++)
	{

	}
}