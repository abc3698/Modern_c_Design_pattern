#include <iostream>
#include <string>

class LightSwitch;

struct State
{
    virtual void on(LightSwitch* ls)
    {
        std::cout << "Light is already on" << std::endl;
    }
    virtual void off(LightSwitch* ls)
    {
        std::cout << "Light is already off" << std::endl;        
    }
};

struct OnState : State
{
    OnState()
    {
        std::cout << "Light turned on" << std::endl;
    }

    void off(LightSwitch* ls) override;
};

struct OffState : State
{
    OffState()
    {
        std::cout << "Light turned off" << std::endl;
    }

    void on(LightSwitch* ls) override;
};

class LightSwitch
{
    State* state;
     
public:
    LightSwitch()
    {
        state = new OffState();
    }

    void set_state(State* state)
    {
        this->state = state;
    }

    void on() { state->on(this); }
    void off() { state->off(this); }
};

void OnState::off(LightSwitch* ls)
{
    std::cout << "Switching light off..." << std::endl;
    ls->set_state(new OffState());
    delete this;
}

void OffState::on(LightSwitch* ls)
{
    std::cout << "Switching light on..." << std::endl;
    ls->set_state(new OnState());
    delete this;
}

void main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();    
}