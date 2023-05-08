#include "Organism.h"
#include <string>

Organism::Organism(string Name, char Symbol, int Strength, int Initiative, int Age, int x, int y, World* World) {

	name = Name;
	symbol = Symbol;
	strength = Strength;
	initiative = Initiative;
	age = Age;
	pos_x = x;
	pos_y = y;
	world = World;
}

void Organism::SetStrength(int Strength)
{
	strength = Strength;
}

void Organism::SetInitiative(int Initiative)
{
	initiative = Initiative;
}

void Organism::SetPosition(int x, int y)
{
	pos_x = x + 1;
	pos_y = y + 1;
}

void Organism::SetAge(int Age)
{
	age = Age;
}

int Organism::GetStrength() const
{
	return strength;
}

int Organism::GetInitiative() const
{
	return initiative;
}

int Organism::GetX() const
{
	return pos_x;
}

int Organism::GetY() const
{
	return pos_y;
}

int Organism::GetAge() const
{
	return age;
}

char Organism::GetSymbol() const
{
	return symbol;
}

string Organism::GetName() const
{
	return name;
}

string Organism::WriteAllInformation()
{
	string info = name + " " + to_string(strength) + " " + to_string(initiative) + " " + to_string(pos_x) + " " + to_string(pos_y) + " " + to_string(age);
	return info;
}

void Organism::Draw() {

	world->SetCell(pos_x, pos_y, this);
}

Organism::~Organism()
{
}
