#include "bishop.h"

Position* Bishop::getpossibleMoves(int& size)
{
	size = 0;
	Position* moves = new Position[CHESS_MAX_POS_MOVES];
	Position curPos;

	//slant up right 
	curPos.row = pos.row - 1;
	curPos.col = pos.col + 1;
	
	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.row = curPos.row - 1;
		curPos.col = curPos.col + 1;
	}

	//slant up left 
	curPos.row = pos.row - 1;
	curPos.col = pos.col - 1;

	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.row = curPos.row - 1;
		curPos.col = curPos.col - 1;
	}

	//slant down right 
	curPos.row = pos.row + 1;
	curPos.col = pos.col + 1;

	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.row = curPos.row + 1;
		curPos.col = curPos.col + 1;
	}

	//slant down left 
	curPos.row = pos.row + 1;
	curPos.col = pos.col - 1;

	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.row = curPos.row + 1;
		curPos.col = curPos.col - 1;
	}

	return moves;

}

Position* Bishop::getpossibleRisks(int& size)
{
	return nullptr;

}

void Bishop::save(std::ofstream& out)
{
	Stone::save(out);
}

void Bishop::load(std::ifstream& in)
{
	Stone::load(in);
}