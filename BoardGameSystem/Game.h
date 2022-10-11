#pragma once

#include "definitions.h"
#include "player.h"
#include <fstream>

class Game
{
protected:
	Player p1;
	Player p2;
	Player* curPlayer = &p1;
	Player* nextPlayer = &p2;
	Player* winner = nullptr;
	GameType gameType;
protected:
	bool isFinish = false;


public:
	Game(GameType type):gameType(type){}

	virtual void moveStone() = 0;
	virtual void showBoard() const = 0;
	virtual void showValidMovesForStone() = 0;
	virtual void showRisksForStone() = 0;

	void displayGame()const;
	GameType getGameType();
	void setWinner(Player* winner);
	Player* getCurPlayer()const;
	int getCurPlayerNum()const;
	bool getStatus()const;
	Player* getNextPlayer()const;
	void setNextPlayer(Player* p);
	void setCurPlayer(Player* p);
	virtual void save(std::ofstream& out);
	virtual void load(std::ifstream& in);

protected:
	void setStatus(bool b);
	Move* getValidMove(Move* moves, int size, Position nextPos);

};

