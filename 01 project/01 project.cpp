// 01 project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "base.h"

int main() {

	int key				= 0;
	char gamePrev[100]	= "";
	int maxMonsters		= 3;
	int rainPrev		= -1;

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
			if (key == KEY_LEFT)
				player.movePlayerLeft(mushroom);
			if (key == KEY_RIGHT)
				player.movePlayerRight(mushroom);
			if (key == KEY_FIRE_LEFT)
				player.fireLeft(listBullets);
			if (key == KEY_FIRE_RIGHT)
				player.fireRight(listBullets);
			
		}
		// Update.		
		
		if (Monster::amount < 3) {
			int direction = rand() % 2;
			generateMonster(direction, listMonsters);			
		}		

		moveBullet(listBullets, listMonsters);
		moveMonsters(listMonsters, player);
		rain(rainPrev);
		
		
		if (Mushroom::mushroomAmount < 1) {
			int randPos = rand() % (Game::worldSize)+1;
			mushroom.generateMushroom(randPos);
			Mushroom::mushroomAmount++;

		}
		else {
			mushroom.paintMushroom();
		}
		
		// Print.
		if (Game::lives > 0) {
			if (strcmp(gamePrev, Game::world) != 0) {
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

