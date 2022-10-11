#include "knight.h"

Position* Knight::getpossibleMoves(int& size)
{
	Position* possibleMoves;
	possibleMoves = new Position[8];
	
	for (int r = -2; r <= 2; r++)
	{
		for (int c = -2; c <= 2; c++)
		{
			Position possiblePosition = { pos.row + r, pos.col + c };
			if (r != c && r != -c && r != 0 && c != 0 && isValidPos(possiblePosition))
			{
				possibleMoves[size].row = possiblePosition.row;
				possibleMoves[size].col = possiblePosition.col;

				size++;
			}
		}
	}

	return possibleMoves;
}

Position* Knight::getpossibleRisks(int& size)
{
	return nullptr;

}

void Knight::save(std::ofstream& out)
{
	Stone::save(out);
}

void Knight::load(std::ifstream& in)
{
	Stone::load(in);
}