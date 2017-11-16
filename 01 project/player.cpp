#include "stdafx.h"
#include "player.h"


Player::Player(int p, char g) {
	pos		= p;
	graphic = g;
}
void Player::fireLeft( list<Bullet*> &listBullets) {
	if (pos > 0) {
		Bullet* bullet = new Bullet;
		bullet->direction = 0;
		bullet->pos = pos - 1;
		Game::world[bullet->pos] = bullet->graphicLeft;
		listBullets.push_back(bullet);
		Bullet::bulletAmount++;
	}
}

void Player::fireRight( list<Bullet*> &listBullets) {
	if (pos < Game::worldSize - 1) {
		Bullet* bullet = new Bullet;
		bullet->direction = 1;
		bullet->pos = pos + 1;
		Game::world[bullet->pos] = bullet->graphicRight;
		listBullets.push_back(bullet);
		Bullet::bulletAmount++;
	}
}

void Player::movePlayerLeft(Mushroom &mushroom) {

	if (pos > 0) {

		if ((pos - 1) == mushroom.pos) {
			mushroom.pos = -1;
			Game::score += mushroom.bonusPoints;
			Mushroom::mushroomAmount--;
		}
		Game::world[pos - 1] = graphic;
		Game::world[pos] = Game::floorChar;
		pos--;

	}
}

void Player::movePlayerRight(Mushroom &mushroom) {

	if (pos < Game::worldSize - 1) {

		if ((pos + 1) == mushroom.pos) {
			mushroom.pos = -1;
			Game::score += mushroom.bonusPoints;
			Mushroom::mushroomAmount--;
		}

		Game::world[pos + 1] = graphic;
		Game::world[pos] = Game::floorChar;
		pos++;

	}
}