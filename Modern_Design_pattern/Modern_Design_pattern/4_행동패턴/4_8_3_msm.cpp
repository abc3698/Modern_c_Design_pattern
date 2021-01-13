#include <iostream>
#include <string>
#include <vector>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

std::vector<std::string> state_names
{
  "off hook",
  "connecting",
  "connected",
  "on hold",
  "destroyed"
};

struct CallDialed {};
struct CallConnected {};
struct PlacedOnHold {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : boost::msm::front::state_machine_def<PhoneStateMachine>
{
	bool angry{ false };

	struct offHook : boost::msm::front::state<> {};

	struct Connecting : boost::msm::front::state<>
	{
		template<typename Event, typename FSM>
		void on_entry(Event const& evt, FSM&)
		{
			std::cout << "We are connecting..." << std::endl;
		}

		// on_exit도 구현이 가능하다
	};

	struct Connected : boost::msm::front::state<> {};
	struct OnHold : boost::msm::front::state<> {};
	struct PhoneDestroyed : boost::msm::front::state<> {};

	struct PhoneBeingDestroyed
	{
		template<typename Event, typename FSM, typename SourceState, typename TargetState>
		void operator()(Event const&, FSM&, SourceState&, TargetState&)
		{
			std::cout << "Phone breaks into a million pieces" << std::endl;
		}
	};

	struct CanDestroyPhone
	{
		template<typename Event, typename FSM, typename SourceState, typename TargetState>
		bool operator()(Event const&, FSM& fsm, SourceState&, TargetState&)
		{
			return fsm.angry;
		}
	};

	struct transition_table : boost::mpl::vector<
		boost::msm::front::Row<offHook, CallDialed, Connecting>,
		boost::msm::front::Row<Connecting, CallConnected, Connected>,
		boost::msm::front::Row<Connected, PlacedOnHold, OnHold>,		
		boost::msm::front::Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed,
			PhoneBeingDestroyed, CanDestroyPhone>
	> {};

	typedef offHook initial_state;

	template<typename FSM, typename Event>
	void no_transition(Event const& e, FSM&, int state)
	{
		std::cout << "No transition from state " << state_names[state]
			<< " on event " << typeid(e).name() << std::endl;
	}
};

int main()
{
	boost::msm::back::state_machine<PhoneStateMachine> phone;

	auto info = [&]()
	{
		auto i = phone.current_state()[0];
		std::cout << "The phone is currently " << state_names[i] << std::endl;
	};

	info();
	phone.process_event(CallDialed{});
	info();
	phone.process_event(CallConnected{});
	info();
	phone.process_event(PlacedOnHold{});
	info();
	phone.process_event(PhoneThrownIntoWall{});
	info();

	// process_event는 여기서 수행
	phone.process_event(CallDialed{});

	std::cout << "We are done using the phone" << std::endl;
}