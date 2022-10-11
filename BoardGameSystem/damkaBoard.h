#pragma once
#include "stone.h"


class DamkaBoard {
private:
	Stone* _stones[ROWSDAMKA][COLSDAMKA] = { nullptr };

public:
	DamkaBoard(bool initBoard);
	bool isNullptrStone(Position pos) const;
	Position* getRisks(Position pos, int& size)const;
	Move* getMoves(Position pos, int& size)const;
	void display()const;
	bool isValidPos(Position pos)const;
	NumPlayer getNumPlayerForPos(Position pos) const;
	Stone* getStone(Position pos) const;
	void moveStone(Position posFrom, Position posTo);
	void deleteStone(Position pos);
	void deleteBoard();
	void save(std::ofstream& out);
	void load(std::ifstream& in);


};