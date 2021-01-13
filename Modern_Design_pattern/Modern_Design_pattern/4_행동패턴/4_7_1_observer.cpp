#include <iostream>
#include <string>
#include <any>
#include <vector>
#include <mutex>
#include <thread>

struct Person;

template<typename T>
struct Observer
{
	virtual void filed_changed(T& source, const std::string& field_name) = 0;
};

template<typename T>
struct Observable
{
	void notify(T& source, const std::string& name)
	{
		std::vector<Observer<T>*> observers_copy;
		{
			std::lock_guard<std::mutex_t>{mtx};
			observers_copy = observers;
		}

		//std::scoped_lock<std::mutex> lock{ mtx };
		for (auto obs : observers_copy)
		{
			if(obs)
				obs->filed_changed(source, name);
		}			
	}

	void subscribe(Observer<T>* f)
	{
		std::scoped_lock<std::mutex> lock{ mtx };
		observers.emplace_back(f);
	}

	void unsubscribe(Observer<T>* f)
	{
		//std::scoped_lock<std::mutex> lock{ mtx };
		observers.erase
		(
			std::remove(observers.begin(), observers.end(), f), observers.end()
		);

		/*auto it = std::find(observers.begin(), observers.end(), f);
		if (it != observers.end())
			*it = nullptr;*/
	}

private:
	std::vector<Observer<T>*> observers;
	std::mutex mtx;
};

struct Person : Observable<Person>
{
	Person(const int age) : age{ age } {}

	bool get_can_vote() { return age >= 16; }

	int get_age() { return age; }
	void set_age(const int age)
	{
		if (this->age == age) return;
		if (this->age > age) return;		

		auto old_can_vote = get_can_vote();

		this->age = age;
		notify(*this, "age");

		// 변화가 있을 때만 울린다.
		if(old_can_vote != get_can_vote())
			notify(*this, "can_vote");
	}

private:
	int age;
};

struct ConsolePersonObserver : Observer<Person>
{
	void filed_changed(Person& source, const std::string& field_name) override
	{
		std::cout << "Person's " << field_name << " has changed to " <<
			source.get_age() << std::endl;
	}
};

struct TrafficAdministration : Observer<Person>
{
	void filed_changed(Person& source, const std::string& field_name) override
	{
		if (field_name == "age")
		{
			if (source.get_age() < 17)
			{
				std::cout << "Whoa there, you are not old enough to drive" << std::endl;
			}
			else
			{
				std::cout << "We no longer care" << std::endl;
				source.unsubscribe(this);
			}
		}
	}
};



int main()
{
	Person p{ 10 };
	ConsolePersonObserver cpo;
	p.subscribe(&cpo);

	p.set_age(16);
	//p.set_age(22);

	//p.set_age(-1);
}