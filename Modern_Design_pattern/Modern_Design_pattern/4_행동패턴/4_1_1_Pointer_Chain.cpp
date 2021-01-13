#include <iostream>
#include <string>

struct Creature
{
	std::string name;
	int attack, defense;

    Creature(const std::string& name, const int attack, const int defense)
        : name(name), attack(attack), defense(defense){}

    friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
    {
        return os
            << "name: " << obj.name
            << " attack: " << obj.attack
            << " defense: " << obj.defense;
    }
};

class CreatureModifier
{
    CreatureModifier* next{ nullptr };

protected:
    Creature& creature;

public:
    explicit CreatureModifier(Creature& creature)
        : creature(creature) {}    

    void add(CreatureModifier* cm)
    {
        if (next) next->add(cm);
        else next = cm;
    }

    virtual void handle()
    {
        if (next) next->handle();
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    explicit DoubleAttackModifier(Creature& creature)
        : CreatureModifier(creature) {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    explicit IncreaseDefenseModifier(Creature& creature)
        : CreatureModifier(creature) {}

    void handle() override
    {
        if (creature.attack <= 2)
            creature.defense += 1;
        
        CreatureModifier::handle();
    }
};

class NoBonuseModifier : public CreatureModifier
{
public:
    explicit NoBonuseModifier(Creature& creature)
        : CreatureModifier(creature) {}

    void handle() override
    {
        
    }
};

int main()
{
    Creature goblin{ "Goblin", 1, 1 };
    CreatureModifier root{ goblin };

    NoBonuseModifier r{ goblin };
    DoubleAttackModifier r1{ goblin };
    DoubleAttackModifier r2{ goblin };
    IncreaseDefenseModifier r3{ goblin };

    root.add(&r);
    root.add(&r1);
    root.add(&r2);
    root.add(&r3);    

    root.handle();

    std::cout << goblin << std::endl;
}