#include "king.h"

Position* King::getpossibleMoves(int& size)
{
	Position* possibleMoves;
	possibleMoves = new Position[8];
	
	for (int r = -1; r <= 1 ; r++)
	{
		for (int c = -1; c <= 1 ; c++)
		{
			if (r != 0 || c != 0)
			{
				Position possiblePos{ pos.row + r ,  pos.col + c };
				if (isValidPos(possiblePos))
				{
					possibleMoves[size].row = possiblePos.row ;
					possibleMoves[size].col = possiblePos.col ;
					size++;
				}
			}

		}
	}

	return possibleMoves;

}

Position* King::getpossibleRisks(int& size)
{
	return nullptr;

}

void King::save(std::ofstream& out)
{
	Stone::save(out);
}

void King::load(std::ifstream& in)
{
	Stone::load(in);
}