#pragma once
#include "World.h"
#include <string>

using namespace std;

class World;

class Organism
{
protected:

	int strength, initiative, age, pos_x, pos_y;
	string name;
	char symbol;
	World* world;
	virtual Organism* CreateOrganism(int x, int y, World* world) = 0;

public:
	//constructor
	Organism(string Name, char Symbol, int Strength, int Initiative, int Age, int x, int y, World* World);

	//setters
	void SetStrength(int Strength);
	void SetInitiative(int Initiative);
	void SetPosition(int x, int y);
	void SetAge(int Age);

	//getters
	int GetStrength() const;
	int GetInitiative() const;
	int GetX() const;
	int GetY() const;
	int GetAge() const;
	char GetSymbol() const;
	string GetName() const;

	//functional methods
	virtual void Action() = 0;
	virtual void Collision(Organism* attacker) = 0;
	virtual bool IsAnimal() = 0;
	virtual void Escape(int numberOfPossibilities, int* possibleX, int* possibleY) = 0;

	string WriteAllInformation();
	void Draw();

	//destructor
	virtual ~Organism();
};

