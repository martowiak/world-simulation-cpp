#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Antelope.h"
#include "Turtle.h"
#include "Fox.h"
#include "Plant.h"
#include "Grass.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "SosnowskysHogweed.h"
#include "SowThistle.h"

#include <conio.h>
#include <iostream>
#include <fstream>

#define ENTER 13
#define NEW 110
#define QUIT 113
#define SAVE 115
#define LOAD 108
#define ALL_SPECIES 10
#define MINIMUM_FREE_CELLS 20

int main() {

	srand(time(NULL));
	int sizeX, sizeY;
	bool quit = false;
	char choice = NEW;
	World* world = NULL;

	do {
		switch (choice) {
		case NEW:

			system("cls");
			do {
				cout << "Please set the size of your world: " << endl;
				cout << "Size X: ";
				cin >> sizeX;
				cout << "Size Y: ";
				cin >> sizeY;
				cout << endl;
			} while (sizeX * sizeY < ALL_SPECIES + MINIMUM_FREE_CELLS);

			if (world == NULL) {
				world = new World(sizeX, sizeY);
			}
			else {
				world->~World();
				world = new World(sizeX, sizeY);
			}
			world->CreateNewWorld(world);
			cout << "ENTER to start the world simulation" << endl;
			break;

		case ENTER:

			system("cls");
			world->DrawWorld();
			world->MakeTurn();
			cout << endl;

			cout << "MENU:" << endl;
			cout << "1. Press 'ENTER' to make next turn." << endl;
			cout << "2. Press 'n' to create new world." << endl;
			cout << "3. Press 'q' to quit the world simulation." << endl;
			cout << "4. Press 's' to save the world state." << endl;
			cout << "5. Press 'l' to load the world state." << endl;
			break;

		case SAVE:

			world->SaveWorld();
			break;

		case LOAD:

			system("cls");
			world->~World();

			const string file = "world.txt";
			ifstream read(file.c_str());
			if (read.good())
			{
				int sizeX, sizeY;
				read >> sizeX >> sizeY;
				world = new World(sizeX, sizeY);

				world->LoadWorld(read, world);

				read.close();
				cout << "The world state has been successfully loaded" << endl;
			}
			else
			{
				cout << "There were some problems during loading the world state" << endl;
			}
			cout << "ENTER to start the world simulation" << endl;
			break;
		}

		choice = _getch();

	} while (choice != QUIT);

	system("cls");
	cout << "The final state of the simulation:" << endl;
	world->DrawWorld();

	delete world;
	return 0;
}