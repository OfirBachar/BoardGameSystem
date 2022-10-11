#include "queen.h"

Position* Queen::getpossibleMoves(int& size)
{
	size = 0;
	Position* moves = new Position[CHESS_MAX_POS_MOVES];
	Position curPos;

	//check  up  
	curPos.row = pos.row - 1;
	curPos.col = pos.col;
	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.row = curPos.row - 1;
	}

	//check  down  
	curPos.row = pos.row + 1;
	curPos.col = pos.col;

	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.row = curPos.row + 1;
	}

	//check  right  
	curPos.row = pos.row;
	curPos.col = pos.col + 1;

	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.col = curPos.col + 1;
	}

	//check  left  
	curPos.row = pos.row;
	curPos.col = pos.col - 1;

	while (this->isValidPos(curPos))
	{
		moves[size] = curPos;
		size++;
		curPos.col = curPos.col - 1;
	}


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

Position* Queen::getpossibleRisks(int& size)
{
	return nullptr;

}

void Queen::save(std::ofstream& out)
{
	Stone::save(out);
}

void Queen::load(std::ifstream& in)
{
	Stone::load(in);
}