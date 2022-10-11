#pragma once
#pragma once
#include <iostream>

#include "Game.h"
#include "damkaBoard.h"
#include "player.h"

class DamkaGame : public Game {
private:
	DamkaBoard _board;

	bool isValidPos(int row, int col)const;
	bool isStoneBelongsToCurPlayer(int row, int col)const;
	Move* getMoves(int row, int col, int& size)const;

public:
	DamkaGame(bool initBoard);
	void addStonesToPlayers();
	virtual void moveStone();
	virtual void showBoard() const;
	virtual void showValidMovesForStone();
	virtual void showRisksForStone();
	virtual void save(std::ofstream& out)override;
	virtual void load(std::ifstream& in)override;

	DamkaBoard* getBoard();
	Position* getRisks(int row, int col, int& size)const;
	
	~DamkaGame();

};
