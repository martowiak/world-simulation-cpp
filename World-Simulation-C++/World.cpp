#include "World.h"
#include "Organism.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Antelope.h"
#include "Turtle.h"
#include "Fox.h"
#include "Grass.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "SosnowskysHogweed.h"
#include "SowThistle.h"
#include "Human.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

#define ALL_SPECIES 10
#define MINIMUM_FREE_CELLS 20

using namespace std;

World::World(int x, int y) {

	N = x;
	M = y;
	turn = 0;
	numberOfOrganisms = 0;
	numberOfNewBorns = 0;
	numberOfKilledDuringTurn = 0;
	human = nullptr;
	abilityActivated = false;
	turnsWithAbility = 0;

	organisms = new Organism * [N * M];

	cells = new Organism * *[M + 2];
	for (int y = 0; y < (M + 2); y++)
	{
		cells[y] = new Organism * [N + 2];
	}

	for (int y = 0; y < (M + 2); y++)
	{
		for (int x = 0; x < (N + 2); x++)
		{
			cells[y][x] = nullptr;
		}
	}
}

void World::GenerateACellForNewAnimal(World* world, int* x, int* y) {


	do {
		*y = rand() % M + 1;
		*x = rand() % N + 1;
	} while (world->GetCell(*x, *y) != nullptr);

	return;
}

void World::GenerateEmptyCells(int* possibleX, int* possibleY, int* numberOfPossibilities, int x, int y)
{

	if (y - 1 != 0 && GetCell(x, y - 1) == nullptr) //UP
	{
		possibleX[*numberOfPossibilities] = x;
		possibleY[*numberOfPossibilities] = y - 1;
		(*numberOfPossibilities)++;
	}
	if (x + 1 != N + 1 && GetCell(x + 1, y) == nullptr) //RIGHT
	{
		possibleX[*numberOfPossibilities] = x + 1;
		possibleY[*numberOfPossibilities] = y;
		(*numberOfPossibilities)++;
	}
	if (y + 1 != M + 1 && GetCell(x, y + 1) == nullptr) //DOWN
	{
		possibleX[*numberOfPossibilities] = x;
		possibleY[*numberOfPossibilities] = y + 1;
		(*numberOfPossibilities)++;
	}
	if (x - 1 != 0 && GetCell(x - 1, y) == nullptr) //LEFT
	{
		possibleX[*numberOfPossibilities] = x - 1;
		possibleY[*numberOfPossibilities] = y;
		(*numberOfPossibilities)++;
	}
}

void World::CreateNewWorld(World* world) {

	int numberOfOrganismsPerSpecies = N * M / (ALL_SPECIES + MINIMUM_FREE_CELLS);
	int posX, posY;

	GenerateACellForNewAnimal(world, &posX, &posY);
	Organism* human1 = new Human(posX, posY, world);
	world->AddOrganism(human1);
	human = human1;

	for (int i = 0; i < numberOfOrganismsPerSpecies; i++) {
		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* sheep = new Sheep(posX, posY, world);
		world->AddOrganism(sheep);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* wolf = new Wolf(posX, posY, world);
		world->AddOrganism(wolf);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* antelope = new Antelope(posX, posY, world);
		world->AddOrganism(antelope);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* fox = new Fox(posX, posY, world);
		world->AddOrganism(fox);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* turtle = new Turtle(posX, posY, world);
		world->AddOrganism(turtle);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* grass = new Grass(posX, posY, world);
		world->AddOrganism(grass);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* sowThistle = new SowThistle(posX, posY, world);
		world->AddOrganism(sowThistle);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* guarana = new Guarana(posX, posY, world);
		world->AddOrganism(guarana);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* belladonna = new Belladonna(posX, posY, world);
		world->AddOrganism(belladonna);

		GenerateACellForNewAnimal(world, &posX, &posY);
		Organism* sosnowskysHogweed = new SosnowskysHogweed(posX, posY, world);
		world->AddOrganism(sosnowskysHogweed);
	}
}

void World::SaveWorld()
{
	ofstream file("world.txt");

	int nrOfOrg = numberOfOrganisms;
	file << N << " " << M << " " << turn << " " << numberOfOrganisms << " " << abilityActivated << " " << turnsWithAbility << endl;
	for (int i = 0; i < numberOfOrganisms; i++)
	{
		file << organisms[i]->WriteAllInformation() << endl;
	}

	file.close();
	cout << "State of the game was successfully saved" << endl;
}

void World::LoadWorld(istream& read, World* world)
{
	int nrOfOrg;
	read >> turn >> nrOfOrg >> abilityActivated >> turnsWithAbility;

	string name, namePart2;
	int strength, initiative, x, y, age;

	for (int i = 0; i < nrOfOrg; i++)
	{
		read >> name;
		if (name == "Sow" || name == "Sosnowsky's")//two part names so the second part has to be loaded
		{
			read >> namePart2;
			name = name + " " + namePart2;
		}
		read >> strength >> initiative >> x >> y >> age;
		world->LoadOrganism(name, strength, initiative, x, y, age, world);
	}
}

void World::LoadOrganism(string name, int strength, int initiative, int x, int y, int age, World* world) {

	Organism* organism = nullptr;

	if (name == "Wolf")
	{
		organism = new Wolf(x, y, world);
	}
	else if (name == "Sheep")
	{
		organism = new Sheep(x, y, world);
	}
	else if (name == "Fox")
	{
		organism = new Fox(x, y, world);
	}
	else if (name == "Turtle")
	{
		organism = new Turtle(x, y, world);
	}
	else if (name == "Antelope")
	{
		organism = new Antelope(x, y, world);
	}
	else if (name == "Grass")
	{
		organism = new Grass(x, y, world);
	}
	else if (name == "Sow thistle")
	{
		organism = new SowThistle(x, y, world);
	}
	else if (name == "Guarana")
	{
		organism = new Guarana(x, y, world);
	}
	else if (name == "Sosnowsky's hogweed")
	{
		organism = new SosnowskysHogweed(x, y, world);
	}
	else if (name == "Belladonna")
	{
		organism = new Belladonna(x, y, world);
	}
	else if (name == "Human")
	{
		organism = new Human(x, y, world);
		human = organism;
	}

	if (organism != nullptr)
	{
		organism->SetStrength(strength);
		organism->SetInitiative(initiative);
		organism->SetAge(age);
		world->AddOrganism(organism);
	}
	else
	{
		cout << "There were some problems during loading " << name << endl;
	}
}

void World::SetCell(int x, int y, Organism* organism) {

	cells[y][x] = organism;
}

void World::SetNumberOfNewBorns(int NumberOfNewBorns)
{
	numberOfNewBorns = NumberOfNewBorns;
}

void World::SetTurnsWithAbility(int TurnsWithAbility)
{
	turnsWithAbility = TurnsWithAbility;
}

void World::ActivateAbility(bool Bool)
{
	abilityActivated = Bool;
}

int World::GetTurnsWithAbility() const
{
	return turnsWithAbility;
}

int World::GetSizeX() const {
	return N;
}

int World::GetSizeY() const {
	return M;
}

int World::GetNumberOfOrganisms() const
{
	return numberOfOrganisms;
}

int World::GetNumberOfNewBorns() const
{
	return numberOfNewBorns;
}

Organism* World::GetCell(int x, int y) const
{
	if ((x > 0) && (x < (N + 2)) && (y > 0) && (y < (M + 2))) // returns a place which is not on the edge
	{
		return cells[y][x];
	}
	return nullptr;
}

bool World::IsAbilityActivated() const
{
	return abilityActivated;
}

void World::DrawWorld() //function responsible for visualization of the world
{
	cout << "Author of the project: Marta Frackowiak 184423" << endl;
	cout << "State after turn " << turn << endl << endl;

	for (int y = 0; y < (M + 2); y++) {

		for (int x = 0; x < (N + 2); x++) {

			if (GetCell(x, y) == nullptr) {
				if ((y == 0) || (y == M + 1))
					cout << '-';
				else if ((x == 0) || (x == N + 1))
					cout << '|';
				else
					cout << ' ';
			}
			else {
				cout << GetCell(x, y)->GetSymbol();
			}
		}
		cout << endl;
	}
	cout << endl;
}

//I use quick sort to easier manage the queue for performing an action so I firstly sort it by initiative and if its equal by age 
int World::Partition(Organism** organisms, int left, int right)
{
	Organism* pivot = organisms[right];
	int i = (left - 1);

	for (int j = left; j <= right - 1; j++)
	{

		if (organisms[j]->GetInitiative() > pivot->GetInitiative())
		{
			i++;
			swap(organisms[i], organisms[j]);
		}
		else if (organisms[j]->GetInitiative() == pivot->GetInitiative()) {
			if (organisms[j]->GetAge() > pivot->GetAge()) {
				i++;
				swap(organisms[i], organisms[j]);
			}
		}
	}
	swap(organisms[i + 1], organisms[right]);
	return (i + 1);
}

void World::QuickSort(Organism** organisms, int left, int right)
{
	if (left < right)
	{
		int index = Partition(organisms, left, right);

		QuickSort(organisms, left, index - 1);
		QuickSort(organisms, index + 1, right);
	}
}

void World::FixArrayOfOrganisms() {//function needed to fill the gaps made during turn

	int index = 0;
	Organism** temp = organisms;

	for (int i = 0; i < numberOfOrganisms; i++)
	{
		if (temp[i] != nullptr) //if we find gaps in our array
		{
			organisms[index] = temp[i];
			index++;
		}
	}
	numberOfOrganisms = numberOfOrganisms - numberOfKilledDuringTurn;
}

void World::MakeTurn()
{
	turn++;
	cout << "Turn: " << turn << endl;

	QuickSort(organisms, 0, numberOfOrganisms - numberOfNewBorns - 1);

	for (int i = 0; i < numberOfOrganisms - numberOfNewBorns; i++) {
		if (organisms[i] != nullptr) {//if it was not killed during turn

			organisms[i]->Action();

			//management of human special ability
			if (organisms[i] == human && abilityActivated && turnsWithAbility < 5) {
				turnsWithAbility++;
			}
			else if (organisms[i] == human && abilityActivated && turnsWithAbility == 5) {
				abilityActivated = false;
			}
			else if (organisms[i] == human && !abilityActivated && turnsWithAbility > 0) {
				turnsWithAbility--;
			}
		}
	}
	for (int i = 0; i < numberOfOrganisms - numberOfNewBorns; i++) {
		if (organisms[i] != nullptr) {
			organisms[i]->SetAge(organisms[i]->GetAge() + 1); //we make then older
		}
	}
	FixArrayOfOrganisms();
	numberOfNewBorns = 0; 
	numberOfKilledDuringTurn = 0;
}

void World::AddOrganism(Organism* organism) {

	if ((numberOfOrganisms < N * M)) //if there is any place for new organism
	{
		organisms[numberOfOrganisms] = organism; //we add it to array
		numberOfOrganisms++;
		organism->Draw(); //and set cell for it
	}
	else {
		cout << "There is not enough space for next organism!" << endl;
	}
}

void World::DeleteOrganism(Organism* organism)
{
	for (int i = 0; i < numberOfOrganisms; i++)
	{
		if (organisms[i] == organism) //if we find such organism
		{
			organisms[i] = nullptr; //we delete it from array with all organisms
			break;
		}
	}
	numberOfKilledDuringTurn++;
	delete organism;
	organism = nullptr;
}

World::~World() {

	delete[] organisms;
	for (int y = 0; y < M; y++)
	{
		for (int x = 0; x < N; x++)
		{
			delete cells[y][x];
		}
	}
}


