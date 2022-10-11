#pragma once
#include <iostream>
using namespace std;

#include "Game.h"
#include "chessBoard.h"
#include "player.h"

class ChessGame : public Game
{
public:
	ChessBoard _board;

	ChessGame(bool initBoard);
	void addStonesToPlayers();


	virtual void moveStone();
	virtual void showBoard() const;
	virtual void showValidMovesForStone();
	virtual void showRisksForStone() override;
	virtual void save(ofstream& out)override;
	virtual void load(ifstream& in)override;

	ChessBoard* getBoard();

	bool isValidPos(int row, int col)const;
	Position* getRisks(int row, int col, int& size);
	Position* getMoves(int row, int col, int& size);
	bool isStoneBelongsToCurPlayer(int row, int col);
	bool IsValidMove(Position curPos, Position posNext);
	bool eatingSituation(Position posChess, Position posNext);
	Stone* getKingStoneOfNextPlayer();
	bool isChessMat();

	~ChessGame();
};
	

