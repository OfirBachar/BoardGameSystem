#include "pawn.h"

Position* Pawn::getpossibleMoves(int& size)
{

	Position* moves = new Position[4];
	size = 0;
	Position possiblePosition;

	if (isFirstStep == true)
	{
		if (this->getOwner() == NumPlayer::P1)
		{
			//front
			possiblePosition = { pos.row - 1, pos.col };
			if (isValidPos(possiblePosition) )
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
				possiblePosition = { pos.row - 2, pos.col };
				if (isValidPos(possiblePosition) )
				{
					moves[size].row = possiblePosition.row;
					moves[size].col = possiblePosition.col;
					size++;
				}
			}
			//left slant
			possiblePosition = { pos.row - 1, pos.col - 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			//right slant
			possiblePosition = { pos.row - 1, pos.col + 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
		}
		else //the owner is p2
		{
			//front
			possiblePosition = { pos.row + 1, pos.col };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			possiblePosition = { pos.row + 2, pos.col };
			if (isValidPos(possiblePosition) )
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}

			//left slant
			possiblePosition = { pos.row + 1, pos.col - 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			//right slant
			possiblePosition = { pos.row + 1, pos.col + 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
		}

		isFirstStep = false;

	}
	else // this is not the first step
	{
		if (getOwner() == NumPlayer::P1)
		{
			//front
			Position possiblePosition = { pos.row - 1, pos.col };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			//left slant
			possiblePosition = { pos.row - 1, pos.col - 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			//right slant
			possiblePosition = { pos.row - 1, pos.col + 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
		}
		else //the owner is p2
		{
			//front
			Position possiblePosition = { pos.row + 1, pos.col };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			//left slant
			possiblePosition = { pos.row + 1, pos.col - 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
			//right slant
			possiblePosition = { pos.row + 1, pos.col + 1 };
			if (isValidPos(possiblePosition))
			{
				moves[size].row = possiblePosition.row;
				moves[size].col = possiblePosition.col;
				size++;
			}
		}
	
	}

	return moves;
}

Position* Pawn::getpossibleRisks(int& size)
{
	return nullptr;

}

void Pawn::save(std::ofstream& out)
{
	Stone::save(out);

	out.write(reinterpret_cast<const char*>(&isFirstStep), sizeof(isFirstStep)); // isFirstStep
}

void Pawn::load(std::ifstream& in)
{
	Stone::load(in);

	in.read(reinterpret_cast< char*>(&isFirstStep), sizeof(isFirstStep)); // isFirstStep
}

