#pragma once
#include "Organism.h"
class Plant :
    public Organism
{
private:

    Organism* CreateOrganism(int x, int y, World* world) override;

public:

    Plant(string name, char symbol, int strength, int age, int x, int y, World* world);
    void Action() override;
    void Collision(Organism* attacker) override;
    void Sewing(Organism* organism);
    bool IsAnimal() override;
    void Escape(int numberOfPossibilities, int* possibleX, int* possibleY) override;
};

