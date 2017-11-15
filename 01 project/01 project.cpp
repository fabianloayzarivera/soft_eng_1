// 01 project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "base.h"



void initGame(Player player);
void movePlayerLeft(Player &player, Mushroom &mushroom);
void movePlayerRight(Player &player, Mushroom &mushroom);
void fireRight(Player player, list<Bullet*> &listBullets);
void fireLeft(Player player, list<Bullet*> &listBullets);
void generateMushroom(Mushroom &mushroom, int randPos);
void paintMushroom(Mushroom mushroom);


int main() {

	int key				= 0;
	char gamePrev[100]	= "";
	int maxMonsters		= 3;

	Player player(Game::worldSize / 2, '|');
	Mushroom mushroom;
	list<Monster*> listMonsters;
	list<Bullet*>  listBullets;
	

	initGame(player);
	cout << endl << endl << endl << endl;
	printf("		%s  ", Game::world);
	printf("LIVES: %4d   SCORE: %5d", Game::lives, Game::score);
	while (key != KEY_ESCAPE) {
		// Get input.
		strcpy(gamePrev, Game::world);

		if (_kbhit()) {
			key = _getch();	
			//cout << key;
			if (key == KEY_LEFT)
				movePlayerLeft(player, mushroom);
			if (key == KEY_RIGHT)
				movePlayerRight(player, mushroom);
			if (key == KEY_FIRE_LEFT)
				fireLeft(player,listBullets);
			if (key == KEY_FIRE_RIGHT)
				fireRight( player, listBullets);
			
		}
		// Update.
		

		if (Monster::amount < 3) {

			int direction = rand() % 2;
			generateMonster(direction, listMonsters);
			
		}
		
		moveBullet(listBullets, listMonsters);
		moveMonsters(listMonsters, player);
		
		if (Mushroom::mushroomAmount < 1) {
			int randPos = rand() % (Game::worldSize)+1;
			generateMushroom(mushroom, randPos);
			Mushroom::mushroomAmount++;

		}
		else {
			paintMushroom(mushroom);
		}
		
		// Print.
		if (Game::lives > 0) {
			if (strcmp(gamePrev, Game::world) != 0) {
				//system("cls");
				printf("\r");
				printf("		%s  ", Game::world);
				printf("LIVES: %4d   SCORE: %5d", Game::lives, Game::score);
			}
		}
		else {
			cout << "			GAME OVER !     " << endl;
			getchar();
		}

		Sleep(50);
	}

}

void initGame(Player player) {
	int i;
	for (i = 0; i < Game::worldSize; i++) {
		Game::world[i] = Game::floorChar;
		if (i == Game::worldSize / 2) {
			Game::world[i] = player.graphic;
		}
	}
	
}

void movePlayerLeft(Player &player, Mushroom &mushroom) {
	
	if (player.pos > 0) {
		
		if ((player.pos - 1) == mushroom.pos) {
			mushroom.pos = -1;
			Game::score += mushroom.bonusPoints;
			Mushroom::mushroomAmount--;
		}
		Game::world[player.pos - 1] = player.graphic;
		Game::world[player.pos] = Game::floorChar;
		player.pos--;
	
	}
}

void movePlayerRight(Player &player, Mushroom &mushroom) {

	if (player.pos < Game::worldSize -1) {
		
		if ((player.pos + 1) == mushroom.pos) {
			mushroom.pos = -1;
			Game::score += mushroom.bonusPoints;
			Mushroom::mushroomAmount--;
		}

		Game::world[player.pos + 1] = player.graphic;
		Game::world[player.pos] = Game::floorChar;
		player.pos++;
		
	}
}

void fireLeft(Player player, list<Bullet*> &listBullets) {
	if (player.pos > 0) {
		Bullet* bullet = new Bullet;
		bullet->direction = 0;
		bullet->pos = player.pos - 1;
		Game::world[bullet->pos] = bullet->graphicLeft;
		listBullets.push_back(bullet);
		Bullet::bulletAmount++;
	}
}

void fireRight(Player player, list<Bullet*> &listBullets) {
	if (player.pos < Game::worldSize -1) {
		Bullet* bullet = new Bullet;
		bullet->direction = 1;
		bullet->pos = player.pos + 1;
		Game::world[bullet->pos] = bullet->graphicRight;
		listBullets.push_back(bullet);
		Bullet::bulletAmount++;
	}
}

bool checkPlayerDead(int nextPos, int actualPos, Player player) {
	if ((nextPos == player.pos) || (actualPos == player.pos))
		return true;
	else
		return false;
}

void generateMushroom(Mushroom &mushroom, int randPos) {
	mushroom.pos = randPos;
	Game::world[mushroom.pos] = mushroom.graphic;
}

void paintMushroom(Mushroom mushroom) {
	Game::world[mushroom.pos] = mushroom.graphic;
}