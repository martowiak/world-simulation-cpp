#pragma once

#include "Organism.h"
#include <iostream>
using namespace std;

class Organism;

class World
{
private:

	Organism** organisms;
	Organism*** cells;
	Organism* human;

	bool abilityActivated;
	int turnsWithAbility;

	int N; //size x of the world board
	int M; //size y of the world board
	int numberOfOrganisms, numberOfNewBorns, numberOfKilledDuringTurn, turn;

	int Partition(Organism** organisms, int left, int right);
	void QuickSort(Organism** organisms, int left, int right);

public:

	//constructor
	World(int x, int y);

	void GenerateACellForNewAnimal(World* world, int* x, int* y);
	void GenerateEmptyCells(int* possibleX, int* possibleY, int* numberOfPossibilities, int x, int y);
	void CreateNewWorld(World* world);

	//setters
	void SetCell(int x, int y, Organism* organism);
	void SetNumberOfNewBorns(int NumberOfNewBorns);
	void SetTurnsWithAbility(int TurnsWithAbility);
	void ActivateAbility(bool Bool);

	//getters
	int GetTurnsWithAbility() const;
	int GetSizeX() const;
	int GetSizeY() const;
	int GetNumberOfOrganisms() const;
	int GetNumberOfNewBorns() const;
	Organism* GetCell(int x, int y) const;
	bool IsAbilityActivated() const;

	//functional methods
	void AddOrganism(Organism* organism);
	void DeleteOrganism(Organism* organism);
	void DrawWorld();
	void MakeTurn();
	void FixArrayOfOrganisms();

	void SaveWorld();
	void LoadWorld(istream& read, World* world);
	void LoadOrganism(string name, int strength, int initiative, int x, int y, int age, World* world);

	//destructor
	~World();
};

