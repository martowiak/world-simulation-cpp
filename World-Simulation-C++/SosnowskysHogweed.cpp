#include "SosnowskysHogweed.h"

SosnowskysHogweed::SosnowskysHogweed(int x, int y, World* world) : Plant("Sosnowsky's hogweed", '@', 0, 0, x, y, world)
{
}

void SosnowskysHogweed::Collision(Organism* attacker)
{
	cout << this->GetName() << ": was eaten by " << attacker->GetName() << endl;
	cout << attacker->GetName() << ": was killed by eating " << this->GetName() << endl;
	world->SetCell(attacker->GetX(), attacker->GetY(), nullptr);
	world->DeleteOrganism(attacker);
	world->DeleteOrganism(this);
}

void SosnowskysHogweed::Action()
{
	if (rand() % 100 < 10) {
		Sewing(this);
	}
	CheckNeighbourhood();
}

void SosnowskysHogweed::CheckNeighbourhood()
{
	if (world->GetCell(pos_x, pos_y - 1) != nullptr && world->GetCell(pos_x, pos_y - 1)->IsAnimal() == true) //if there is an animal in a higher cell
	{
		cout << world->GetCell(pos_x, pos_y - 1)->GetName() << ": was killed by " << this->GetName() << " by standing next to it" << endl;
		world->DeleteOrganism(world->GetCell(pos_x, pos_y - 1));
		world->SetCell(pos_x, pos_y - 1, nullptr);
	}
	if (world->GetCell(pos_x, pos_y + 1) != nullptr && world->GetCell(pos_x, pos_y + 1)->IsAnimal() == true) //if there is an animal in a lower cell
	{
		cout << world->GetCell(pos_x, pos_y + 1)->GetName() << ": was killed by " << this->GetName() << " by standing next to it" << endl;
		world->DeleteOrganism(world->GetCell(pos_x, pos_y + 1));
		world->SetCell(pos_x, pos_y + 1, nullptr);
	}
	if (world->GetCell(pos_x - 1, pos_y) != nullptr && world->GetCell(pos_x - 1, pos_y)->IsAnimal() == true) //if there is an animal in a left cell
	{
		cout << world->GetCell(pos_x - 1, pos_y)->GetName() << ": was killed by " << this->GetName() << " by standing next to it" << endl;
		world->DeleteOrganism(world->GetCell(pos_x - 1, pos_y));
		world->SetCell(pos_x - 1, pos_y, nullptr);
	}
	if (world->GetCell(pos_x + 1, pos_y) != nullptr && world->GetCell(pos_x + 1, pos_y)->IsAnimal() == true) //if there is an animal in a right cell
	{
		cout << world->GetCell(pos_x + 1, pos_y)->GetName() << ": was killed by " << this->GetName() << " by standing next to it" << endl;
		world->DeleteOrganism(world->GetCell(pos_x + 1, pos_y));
		world->SetCell(pos_x + 1, pos_y, nullptr);
	}
}
