#pragma once
#include "stone.h"

class ChessBoard
{
private:
	Stone* _stones[ROWSCHESS][COLSCHESS] = { nullptr };

public:

	ChessBoard(bool initBoard);
	bool isNullptrStone(Position pos) const;
	void display()const;
	bool isValidPos(Position pos)const;
	NumPlayer getNumPlayerForPos(Position pos) const;
	Stone* getStone(Position pos) ;
	void deleteStone(Position pos);
	void moveEatStone(Position posFrom, Position posTo);

	Position* getRisks(Stone* stone, int& size);
	Position* getMoves(Stone* stone, int& size);
	void moveStone(Position posFrom, Position posTo);
	void save(std::ofstream& out);
	void load(std::ifstream& in);

	void deleteBoard();


};


