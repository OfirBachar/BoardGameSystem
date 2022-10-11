#pragma once
#include "definitions.h"
#include <iostream>
#include <fstream>

class Player;
class Game;

class Stone {
protected:
	Position pos;
	int type = 0;
	NumPlayer owner;
	bool isKing = false;

public:
	virtual Position* getpossibleMoves(int& size);
	virtual Position* getpossibleRisks(int& size);

	Position getPos()const;
	void setPos(Position pos);
	NumPlayer getOwner()const;
	void setOwner(NumPlayer player);
	void setType(Type type);
	void setType(ChessStoneType type);
	int getType()const;
	bool getIsKing() const;
	void setIsKing(bool isKing);
	bool isValidPos(Position pos) const;
	virtual void save(std::ofstream& out);
	virtual void load(std::ifstream& in);

};

