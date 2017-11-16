#pragma once

#include "game.h"

class Mushroom {
public:
	static int mushroomAmount;
	int pos;
	int bonusPoints = 10;
	char graphic = '@';

	void generateMushroom(int randPos);
	void paintMushroom();
};