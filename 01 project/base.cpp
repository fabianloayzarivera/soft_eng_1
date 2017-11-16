#include "stdafx.h"
#include "base.h"

void initGame(Player player) {
	int i;
	for (i = 0; i < Game::worldSize; i++) {
		Game::world[i] = Game::floorChar;
		if (i == Game::worldSize / 2) {
			Game::world[i] = player.graphic;
		}
	}

}

void generateMonster(int direction, list<Monster*> &listMonsters) {

	Monster* monster = new Monster;
	monster->direction = direction;
	if (!direction) {
		monster->pos = Game::worldSize - 1;
	}
	else {
		monster->pos = 0;
	}
	Game::world[monster->pos] = monster->graphic;
	listMonsters.push_back(monster);
	Monster::amount++;

}

void moveMonsters(list<Monster*> &listMonsters, Player &player) {
	int nextPos;

	for (auto mon = listMonsters.begin(); mon != listMonsters.end();)
	{
		if (!(*mon)->direction)
			nextPos = (*mon)->pos - 1;
		else
			nextPos = (*mon)->pos + 1;

		if ((nextPos >= 0) && (nextPos <= Game::worldSize - 1)) {

			if ((nextPos == player.pos) || ((*mon)->pos == player.pos)) {
				//Player Dead
				Game::lives--;
				player.pos = Game::worldSize / 2;
				Game::world[player.pos] = player.graphic;
			}

			Game::world[nextPos] = (*mon)->graphic;
			Game::world[(*mon)->pos] = Game::floorChar;
			(*mon)->pos = nextPos;
			mon++;
		}
		else {
			if (nextPos < 0)
				Game::world[(*mon)->pos] = Game::floorChar;
			else
				Game::world[(*mon)->pos] = Game::floorChar;

			mon = listMonsters.erase(mon);
			Monster::amount--;
		}


	}
}

void moveBullet(list<Bullet*> &listBullets, list<Monster*> &listMonsters) {

	int nextPos;
	char graph;

	for (auto bull = listBullets.begin(); bull != listBullets.end();)
	{
		if (!(*bull)->direction) {
			nextPos = (*bull)->pos - 1;
			graph = (*bull)->graphicLeft;

		}
		else {
			nextPos = (*bull)->pos + 1;
		graph = (*bull)->graphicRight;
		}

		if ((nextPos >= 0) && (nextPos <= Game::worldSize - 1)) {

			if (checkHit(nextPos, (*bull)->pos, listMonsters)) {
				//hit monster
				Game::score++;
				Game::world[nextPos] = Game::floorChar;
				Game::world[(*bull)->pos] = Game::floorChar;
				bull = listBullets.erase(bull);
			}
			else {
				Game::world[nextPos] = graph;
				Game::world[(*bull)->pos] = Game::floorChar;
				(*bull)->pos = nextPos;
				bull++;
			}
		}
		else {

			Game::world[(*bull)->pos] = Game::floorChar;
			bull = listBullets.erase(bull);
			Bullet::bulletAmount--;
		}


	}


}

bool checkHit(int nextPos, int actualPos, list<Monster*> &listMonsters) {
	bool hit = false;

	for (auto mon = listMonsters.begin(); mon != listMonsters.end();)
	{
		if (((*mon)->pos == nextPos) || ((*mon)->pos == actualPos)) {
			//EnemyHit
			hit = true;
			mon = listMonsters.erase(mon);
			Monster::amount--;
		}
		else {
			mon++;
		}

	}
	return hit;
}

bool checkPlayerDead(int nextPos, int actualPos, Player player) {
	if ((nextPos == player.pos) || (actualPos == player.pos))
		return true;
	else
		return false;
}

void rain(int &rainPrev) {
	int randPos = rand() % Game::worldSize;

	if (Game::world[rainPrev] == ',')
		Game::world[rainPrev] = Game::floorChar;

	if (Game::world[randPos] == Game::floorChar)
		Game::world[randPos] = ',';

	rainPrev = randPos;

}