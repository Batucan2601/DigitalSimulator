#include "Clock.h"
#include "appSettings.h"
#include <chrono>
#include "ComponentTextures.h"
Clock::Clock(const std::string& name, unsigned int tickRate)
    : Component(name), tick_rate(tickRate)
{
    m_logger.info("Clock created with name: " + name + " and tick rate: " + std::to_string(tickRate));
    ns = 1e9 / tick_rate;
    Signal Clk("clk", SignalVal::SIGNAL_0);
    this->outputs.push_back(Clk); // Add output signal for clock
    Signal Reset("reset", SignalVal::SIGNAL_0);
    this->inputs.push_back(Reset); // Add reset input signal
    this->m_texture = LogicElements::compTexture_getTexture(CircuitElements::ComponentType::INPUT_1);
    this->m_type = CircuitElements::ComponentType::CLK; // Set type to CLK
    setInOutPositions();

    InputResolver::RegisterHandler(this);

    // crea
}
void Clock::evaluate()
{
    using namespace std::chrono;

    static auto lastTime = high_resolution_clock::now();

    auto currentTime = high_resolution_clock::now();
    auto elapsed = duration_cast<nanoseconds>(currentTime - lastTime);

    if (elapsed.count() >= ns)
    {
        this->outputs[0].val = signal_not(this->outputs[0].val); // Toggle signal
        lastTime = currentTime;
    }
}

void Clock::setInOutPositions()
{
    // output
    // int no_of_grid_points = this->bd.width / AppSettings::appSettings.GRID_POINT_SIZE + 1;
    for (size_t i = 0; i < this->outputs.size(); i++)
    {
        float x = this->bd.x;
        float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
        this->outputs[i].pos = {x, y};
    }
    //reset
    float x = this->bd.x + this->bd.width / 2;
    float y = this->bd.y;
    this->inputs[0].pos = {x, y};  // Reset input positions
    
}
void Clock::reset()
{
    this->outputs[0].val = SignalVal::SIGNAL_0; // Reset output to 0
}

nlohmann::json Clock::serialize() const {
    nlohmann::json j;
    j["id"] = getID();
    j["type"] = getType();
    j["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
    //j["inputs"] = getInputs();
    //j["outputs"] = getOutputs();
    return j;
}

void Clock::onInputChanged()
{
    this->evaluate();  // Automatically reevaluate when input changes
}