#pragma once
#pragma once
#include <list>
#include "Game.h"

using namespace std;


class GameControler {

private:
	list<Game*> games;
	list<Game*>::iterator curGame;

public:
	void runGames();

private:

	UserChoice showMenuAndGetUserChoice();
	void displayGame() const;
	void addGame();
	void MoveToNextGame();
	void removeGame();
	void showValidMovesForStone()const;
	void showRisksForStone()const;
	void moveStone();
	void quit();
	void saveGame();
	void loadGame();

};
