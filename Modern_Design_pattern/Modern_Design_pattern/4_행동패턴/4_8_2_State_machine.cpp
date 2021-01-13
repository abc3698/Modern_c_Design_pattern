#include <iostream>
#include <string>
#include <map>
#include <vector>

enum class State
{
	off_hook, // 수화기 든 상태
	connecting, // 연결 시도 상태
	connected, // 연결된 상태
	on_hold, // 대기 상태
	on_hook, // 수회기 내린 상태
};

enum class Trigger
{
	call_dialed,		// 전화 걸기
	hung_up,			// 전화 끊기
	call_connected,		// 전화 연결됨
	placed_on_hold,		// 대기
	taken_off_hold,		// 대기 종료
	left_message,		// 메시지 남기기
	stop_using_phone	// 전화 사용 종료
};

inline std::ostream& operator<<(std::ostream& os, const State& s)
{
    switch (s)
    {
    case State::off_hook:
        os << "off the hook";
        break;
    case State::connecting:
        os << "connecting";
        break;
    case State::connected:
        os << "connected";
        break;
    case State::on_hold:
        os << "on hold";
        break;
    case State::on_hook:
        os << "on the hook";
        break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Trigger& t)
{
    switch (t)
    {
    case Trigger::call_dialed:
        os << "call dialed";
        break;
    case Trigger::hung_up:
        os << "hung up";
        break;
    case Trigger::call_connected:
        os << "call connected";
        break;
    case Trigger::placed_on_hold:
        os << "placed on hold";
        break;
    case Trigger::taken_off_hold:
        os << "taken off hold";
        break;
    case Trigger::left_message:
        os << "left message";
        break;
    case Trigger::stop_using_phone:
        os << "putting phone on hook";
        break;
    default: break;
    }
    return os;
}

int main()
{
    std::map<State, std::vector<std::pair<Trigger, State>>> rules;
    
    rules[State::off_hook] = {
        {Trigger::call_dialed, State::connecting},
        {Trigger::stop_using_phone, State::on_hook}
    };

    rules[State::connecting] = {
        {Trigger::hung_up, State::off_hook},
        {Trigger::call_connected, State::connected}
    };

    rules[State::connected] = {
        {Trigger::left_message, State::off_hook},
        {Trigger::hung_up, State::off_hook},
        {Trigger::placed_on_hold, State::on_hold}
    };

    rules[State::on_hold] = {
        {Trigger::taken_off_hold, State::connected},
        {Trigger::hung_up, State::off_hook}
    };

    State currentState{ State::off_hook };
    State exitState{ State::on_hook };

    while (true)
    {
        std::cout << "The phone is currently " << currentState << std::endl;

    // go to 구문
    select_trigger:
        std::cout << "Select a trigger:" << std::endl;

        int i = 0;
        for (auto item : rules[currentState])
        {
            std::cout << i++ << ". " << item.first << std::endl;
        }

        int input;
        std::cin >> input;
        if (input < 0 || (input + 1) > rules[currentState].size())
        {
            std::cout << "Incorrect option. Please try again." << std::endl;
            goto select_trigger;
        }

        currentState = rules[currentState][input].second;
        if (currentState == exitState) break;
    }

    std::cout << "We are done using the phone" << std::endl;
    return 0;
}