#include "rook.h"

Position* Rook::getpossibleMoves(int& size)
{
	size = 0;
	Position* possibleMoves;
	possibleMoves = new Position[14];

	for (int i = 0; i < ROWSCHESS; i++)
	{
		if (i != pos.row - 1)
		{
			possibleMoves[size].row = i+1;
			possibleMoves[size].col = pos.col;
			size++;
		}
		if (i != pos.col - 1)
		{
			possibleMoves[size].row = pos.row;
			possibleMoves[size].col = i+1;
			size++;
		}
	}
	return possibleMoves;
}

Position* Rook::getpossibleRisks(int& size)
{
	return nullptr;
}

void Rook::save(std::ofstream& out)
{
	Stone::save(out);
}

void Rook::load(std::ifstream& in)
{
	Stone::load(in);
}