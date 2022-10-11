#pragma once
#include "stone.h"


class AmazonaBoard {
private:
	Stone* _stones[ROWSAMAZONES][COLSAMAZONES] = { nullptr };

public:

	AmazonaBoard(bool initBoard);
	bool isNullptrStone(Position pos) const;
	bool isAmazonStone(Position pos) const;
	void display()const;
	bool isValidPos(Position pos)const;
	NumPlayer getNumPlayerForPos(Position pos) const;
	Stone* getStone(Position pos) const;
	Position* getMoves(Position pos, int& size)const;
	Position* getRisks(Position pos, int& size)const;
	void moveStone(Position posFrom, Position posTo);
	void deleteStone(Position pos);
	void deleteBoard();
	void setNewMarked(Position posMarked);
	void save(std::ofstream& out);
	void load(std::ifstream& in);



};