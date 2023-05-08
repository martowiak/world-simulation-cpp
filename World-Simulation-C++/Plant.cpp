#include "Plant.h"
#include "Grass.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "SosnowskysHogweed.h"
#include "SowThistle.h"
#include <iostream>

using namespace std;

Organism* Plant::CreateOrganism(int x, int y, World* world)
{
	if (typeid(*this) == typeid(Grass))
	{
		Grass* plant = new Grass(x, y, world);
		return plant;
	}
	else if (typeid(*this) == typeid(Guarana))
	{
		Guarana* plant = new Guarana(x, y, world);
		return plant;
	}
	else if (typeid(*this) == typeid(Belladonna))
	{
		Belladonna* plant = new Belladonna(x, y, world);
		return plant;
	}
	else if (typeid(*this) == typeid(SosnowskysHogweed))
	{
		SosnowskysHogweed* plant = new SosnowskysHogweed(x, y, world);
		return plant;
	}
	else if (typeid(*this) == typeid(SowThistle))
	{
		SowThistle* plant = new SowThistle(x, y, world);
		return plant;
	}
}

Plant::Plant(string name, char symbol, int strength, int age, int x, int y, World* world) : Organism(name, symbol, strength, 0, age, x, y, world)
{
}

void Plant::Action()
{
	if (rand() % 100 < 30) {
		Sewing(this);
	}
}

void Plant::Collision(Organism* attacker)
{
	cout << this->GetName() << ": was eaten by " << attacker->GetName() << endl;
	world->DeleteOrganism(this);
	attacker->Draw();
}

void Plant::Sewing(Organism* organism)
{
	int* possibleX = new int[4];
	int* possibleY = new int[4];
	int numberOfPossibilities = 0;

	world->GenerateEmptyCells(possibleX, possibleY, &numberOfPossibilities, organism->GetX(), organism->GetY());

	if (numberOfPossibilities != 0)
	{
		int random = rand() % numberOfPossibilities;
		Organism* newBorn = this->CreateOrganism(possibleX[random], possibleY[random], world);
		world->AddOrganism(newBorn);
		cout << newBorn->GetName() << ": spread to (" << possibleX[random] << ", " << possibleY[random] << ")" << endl;
		world->SetNumberOfNewBorns(world->GetNumberOfNewBorns() + 1);
	}

	delete[] possibleX;
	delete[] possibleY;
}

bool Plant::IsAnimal()
{
	return false;
}

void Plant::Escape(int numberOfPossibilities, int* possibleX, int* possibleY)
{
	cout << "Plants can't move so they don't escape" << endl;
}
