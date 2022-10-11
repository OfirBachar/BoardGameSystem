#pragma once
#include <iostream>

#include "Game.h"
#include "amazonaBoard.h"
#include "player.h"

class AmazonaGame : public Game
{
private:
	AmazonaBoard _board;


	bool isValidPos(int row, int col)const;
	Position* getMoves(int row, int col, int& size)const;
	bool IsValidMove(Position curPos, Position posNext);
	bool IsValidToMark(Position posNext, Position posMark);


public:
	AmazonaGame(bool initBoard);
	void addStonesToPlayers();
	virtual void showBoard() const;
	virtual void showValidMovesForStone();
	virtual void showRisksForStone();
	virtual void moveStone();
	virtual void save(std::ofstream& out)override;
	virtual void load(std::ifstream& in)override;

	AmazonaBoard* getBoard();
	Position* getRisks(int row, int col, int& size);
	bool IsCurWinner();
	~AmazonaGame();

};



