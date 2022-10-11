#include "stone.h"
using namespace std;

Position* Stone::getpossibleMoves(int& size)
{
	return nullptr;
}

Position* Stone::getpossibleRisks(int& size)
{
	
	return nullptr;
}

bool Stone::isValidPos(Position pos)const
{
	if (pos.row > ROWSCHESS || pos.row < 1 || pos.col > COLSCHESS || pos.col < 1)
		return false;
	return true;
}

void  Stone::setOwner(NumPlayer player) {
	this->owner = player;
}

void Stone::setType(Type type) {
	this->type = (int)type;
}

void Stone::setType(ChessStoneType type) {
	this->type = (int)type;
}

void Stone::setPos(Position pos) {
	this->pos.row = pos.row;
	this->pos.col = pos.col;
}

Position Stone::getPos()const {
	return this->pos;
}

NumPlayer Stone::getOwner()const {
	return this->owner;
}

int Stone::getType()const {
	return this->type;
}

bool Stone::getIsKing() const
{
	return isKing;
}

void Stone::setIsKing(bool isKing)
{
	this->isKing = isKing;
}

void Stone::save(std::ofstream& out)
{
	if (!out.good())
		throw runtime_error("cannot write to file");
	out.write(reinterpret_cast<const char*>(&type), sizeof(type)); //type
	//pos
	out.write(reinterpret_cast<const char*>(&pos.row), sizeof(pos.row)); //pos.row
	out.write(reinterpret_cast<const char*>(&pos.col), sizeof(pos.col)); //pos.col
	out.write(reinterpret_cast<const char*>(&owner), sizeof(owner)); //owner
	out.write(reinterpret_cast<const char*>(&isKing), sizeof(isKing)); //isKing
}

void Stone::load(std::ifstream& in) 
{
	if (!in.good())
		throw runtime_error("cannot read from file");
	in.read(reinterpret_cast< char*>(&type), sizeof(type)); //type
	//pos
	in.read(reinterpret_cast<char*>(&pos.row), sizeof(pos.row)); //pos.row
	in.read(reinterpret_cast<char*>(&pos.col), sizeof(pos.col)); //pos.col
	in.read(reinterpret_cast<char*>(&owner), sizeof(owner)); //owner
	in.read(reinterpret_cast<char*>(&isKing), sizeof(isKing)); //isKing
}
