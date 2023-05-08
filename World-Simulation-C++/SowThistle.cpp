#include "SowThistle.h"

SowThistle::SowThistle(int x, int y, World* world) : Plant("Sow thistle", '*', 0, 0, x, y, world)
{
}

void SowThistle::Action()
{
	for (int i = 0; i < 3; i++) {//it has 3 opportunities to multiply
		if (rand() % 100 < 20) {//possibility is 10 %
			Sewing(this);
		}
	}
}
