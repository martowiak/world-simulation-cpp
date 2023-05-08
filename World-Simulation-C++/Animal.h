#pragma once
#include "Organism.h"
class Animal :
    public Organism
{
private:
	Organism* CreateOrganism(int x, int y, World* world) override;

public:

	//constructor
	Animal(string name, char symbol, int strength, int initiative, int age, int x, int y, World* world);

	//functional methods
	void GeneratePossibleMoves(int lengthOfMove, int* possibleX, int* possibleY, int* numberOfPossibilities);
	void Movement(int* possibleX, int* possibleY, int* numberOfPossibilities);
	void Breeding(Organism* organism);
	void Action() override;
	void Collision(Organism* attacker) override;
	bool IsAnimal() override;
	void Escape(int numberOfPossibilities, int* possibleX, int* possibleY) override;
};

