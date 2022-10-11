#include "damkaBoard.h"
#include <iostream>
using namespace std;

DamkaBoard::DamkaBoard(bool initBoard)
{
	if (initBoard == true)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j += 2)
			{
				Position curPos;
				curPos.row = i;
				curPos.col = j;

				//set stones to player 1
				if (i == 0 || i == 2)
				{
					_stones[i][j] = new Stone;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setOwner(NumPlayer::P1);
				}
				else if (i == 1)
				{
					_stones[i][j + 1] = new Stone;
					_stones[i][j + 1]->setPos(curPos);
					_stones[i][j + 1]->setOwner(NumPlayer::P1);
				}

				//set stones to player 2
				else if (i == 6)
				{
					_stones[i][j] = new Stone;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setOwner(NumPlayer::P2);
				}
				else if (i == 5 || i == 7)
				{
					_stones[i][j + 1] = new Stone;
					_stones[i][j + 1]->setPos(curPos);
					_stones[i][j + 1]->setOwner(NumPlayer::P2);
				}

			}
		}
	}
}

bool DamkaBoard::isNullptrStone(Position pos) const
{
	if (this->_stones[pos.row - 1][pos.col - 1] == nullptr)
		return true;
	return false;
}

NumPlayer DamkaBoard::getNumPlayerForPos(Position pos) const
{
	if (isNullptrStone(pos) == true)
		return NumPlayer::None;
	else
		return _stones[pos.row - 1][pos.col - 1]->getOwner();
}

Stone* DamkaBoard::getStone(Position pos) const
{
	//assuming valid pos
	return _stones[pos.row - 1][pos.col - 1];
}

void DamkaBoard::moveStone(Position posFrom, Position posTo)
{
	//no error checks - checked in gameController
	_stones[posFrom.row-1][posFrom.col-1]->setPos(posTo);
	_stones[posTo.row-1][posTo.col-1] = _stones[posFrom.row-1][posFrom.col-1];
	_stones[posFrom.row-1][posFrom.col-1] = nullptr;
}

Position* DamkaBoard::getRisks(Position pos, int& size)const
{
	Position* risks = new Position[MAXIMUM_NUM_RISKS];
	size = 0;
	Position blocker;
	Position attacker;
	//assuming pos is valid!
	if (_stones[pos.row - 1][pos.col - 1] != nullptr && _stones[pos.row - 1][pos.col - 1]->getOwner() == NumPlayer::P1)
	{
		//risk from right
		blocker.row = pos.row - 1;
		blocker.col = pos.col - 1;

		if (isValidPos(blocker) && _stones[blocker.row - 1][blocker.col - 1] == nullptr)
		{
			//possible risk from bottom right	
			attacker.row = pos.row + 1;
			attacker.col = pos.col + 1;
			if (isValidPos(attacker) &&
				_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
				_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P2)
			{
				risks[size] = attacker;
				size++;
			}
			else
			{
				while (isValidPos(attacker) && _stones[attacker.row - 1][attacker.col - 1] == nullptr)
				{
					attacker.row++;
					attacker.col++;
				}
				if (isValidPos(attacker) &&
					_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
					_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P2 &&
					_stones[attacker.row - 1][attacker.col - 1]->getIsKing() == true)
				{
					risks[size] = attacker;
					size++;
				}
			}
		}

		//risk from left
		blocker.row = pos.row - 1;
		blocker.col = pos.col + 1;

		if (isValidPos(blocker) && _stones[blocker.row - 1][blocker.col - 1] == nullptr)
		{
			//possible risk from bottom right	
			attacker.row = pos.row + 1;
			attacker.col = pos.col - 1;
			if (isValidPos(attacker) &&
				_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
				_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P2)
			{
				risks[size] = attacker;
				size++;
			}
			else
			{
				while (isValidPos(attacker) && _stones[attacker.row - 1][attacker.col - 1] == nullptr)
				{
					attacker.row++;
					attacker.col--;
				}
				if (isValidPos(attacker) &&
					_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
					_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P2 &&
					_stones[attacker.row - 1][attacker.col - 1]->getIsKing() == true)
				{
					risks[size] = attacker;
					size++;
				}
			}
		}

	}
	else if (_stones[pos.row - 1][pos.col - 1] != nullptr && _stones[pos.row - 1][pos.col - 1]->getOwner() == NumPlayer::P2)
	{ //NumPlayer::P2
		//risk from right
		blocker.row = pos.row + 1;
		blocker.col = pos.col - 1;

		if (isValidPos(blocker) && _stones[blocker.row - 1][blocker.col - 1] == nullptr)
		{
			//possible risk from bottom right	
			attacker.row = pos.row - 1;
			attacker.col = pos.col + 1;
			if (isValidPos(attacker) &&
				_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
				_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P1)
			{
				risks[size] = attacker;
				size++;
			}
			else
			{
				while (isValidPos(attacker) && _stones[attacker.row - 1][attacker.col - 1] == nullptr)
				{
					attacker.row--;
					attacker.col++;
				}
				if (isValidPos(attacker) &&
					_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
					_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P1 &&
					_stones[attacker.row - 1][attacker.col - 1]->getIsKing() == true)
				{
					risks[size] = attacker;
					size++;
				}
			}
		}

		//risk from left
		blocker.row = pos.row + 1;
		blocker.col = pos.col + 1;

		if (isValidPos(blocker) && _stones[blocker.row - 1][blocker.col - 1] == nullptr)
		{
			//possible risk from bottom right	
			attacker.row = pos.row - 1;
			attacker.col = pos.col - 1;
			if (isValidPos(attacker) &&
				_stones[attacker.row - 1][attacker.col - 1] != nullptr &&
				_stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P1)
			{
				risks[size] = attacker;
				size++;
			}
			else
			{
				while (isValidPos(attacker) && _stones[attacker.row - 1][attacker.col - 1] == nullptr)
				{
					attacker.row--;
					attacker.col--;
				}
				if (isValidPos(attacker) && _stones[attacker.row - 1][attacker.col - 1]->getOwner() == NumPlayer::P1
					&& _stones[attacker.row - 1][attacker.col - 1]->getIsKing() == true)
				{
					risks[size] = attacker;
					size++;
				}
			}
		}
	}

	if (size == 0)
	{
		delete[] risks;
		return nullptr;
	}
	else
	{
		return risks;
	}

}

Move* DamkaBoard::getMoves(Position pos, int& size)const
{
	size = 0;
	Move* moves = nullptr;

	// if the stone is not exists
	if (this->getStone(pos) == nullptr)
		size = -1;

	// if the stone is not king
	else if (this->getStone(pos)->getIsKing() == false)
	{
		moves = new Move[MAXIMUM_NUM_MOVES];
		Move possiablePos;

		// player 1
		if (this->getStone(pos)->getOwner() == NumPlayer::P1)
		{
			//check the right side
			possiablePos.pos.row = pos.row + 1;
			possiablePos.pos.col = pos.col + 1;
			possiablePos.wasAte = WasAte::NO;

			//not eating move
			if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) == nullptr)
			{
				moves[size] = possiablePos;
				size++;
			}
			//eating move
			else if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) != nullptr &&
				this->getStone(possiablePos.pos)->getOwner() != this->getStone(pos)->getOwner())
			{
				possiablePos.eatenPos = possiablePos.pos;
				possiablePos.pos.row = possiablePos.pos.row + 1;
				possiablePos.pos.col = possiablePos.pos.col + 1;
				if (this->isValidPos(possiablePos.pos) &&
					this->isNullptrStone(possiablePos.pos))
				{
					possiablePos.wasAte = WasAte::YES;
					moves[size] = possiablePos;
					size++;
				}
			}


			//check the left side
			possiablePos.pos.row = pos.row + 1;
			possiablePos.pos.col = pos.col - 1;
			//not eating move
			if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) == nullptr)
			{
				moves[size] = possiablePos;
				size++;
			}
			//eating move
			else if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) != nullptr &&
				this->getStone(possiablePos.pos)->getOwner() != this->getStone(pos)->getOwner())
			{
				possiablePos.eatenPos = possiablePos.pos;
				possiablePos.pos.row = possiablePos.pos.row + 1;
				possiablePos.pos.col = possiablePos.pos.col - 1;
				if (this->isValidPos(possiablePos.pos) &&
					this->isNullptrStone(possiablePos.pos))
				{
					possiablePos.wasAte = WasAte::YES;
					moves[size] = possiablePos;
					size++;
				}
			}
		}
		// player 2
		else
		{
			//check the right side
			possiablePos.pos.row = pos.row - 1;
			possiablePos.pos.col = pos.col + 1;

			//not eating move
			if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) == nullptr)
			{
				moves[size] = possiablePos;
				size++;
			}
			//eating move
			else if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) != nullptr &&
				this->getStone(possiablePos.pos)->getOwner() != this->getStone(pos)->getOwner())
			{
				possiablePos.eatenPos = possiablePos.pos;
				possiablePos.pos.row = possiablePos.pos.row - 1;
				possiablePos.pos.col = possiablePos.pos.col + 1;
				if (this->isValidPos(possiablePos.pos) &&
					this->isNullptrStone(possiablePos.pos))
				{
					possiablePos.wasAte = WasAte::YES;
					moves[size] = possiablePos;
					size++;
				}
			}
			//check the left side
			possiablePos.pos.row = pos.row - 1;
			possiablePos.pos.col = pos.col - 1;

			//not eating move
			if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) == nullptr)
			{
				moves[size] = possiablePos;
				size++;
			}
			//eating move
			else if (this->isValidPos(possiablePos.pos) &&
				this->getStone(possiablePos.pos) != nullptr &&
				this->getStone(possiablePos.pos)->getOwner() != this->getStone(pos)->getOwner())
			{
				possiablePos.eatenPos = possiablePos.pos;
				possiablePos.pos.row = possiablePos.pos.row - 1;
				possiablePos.pos.col = possiablePos.pos.col - 1;
				if (this->isValidPos(possiablePos.pos) &&
					this->isNullptrStone(possiablePos.pos))
				{
					possiablePos.wasAte = WasAte::YES;
					moves[size] = possiablePos;
					size++;
				}
			}
		}
	}

	//if the stone is king
	else
	{
		moves = new Move[MAXIMUM_NUM_MOVES_FOR_KING];
		Move curPos;

		//check the slant up right 
		curPos.pos.row = pos.row - 1;
		curPos.pos.col = pos.col + 1;
		curPos.wasAte = WasAte::NO;

		//not eating move
		while (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
		{
			moves[size] = curPos;
			size++;

			curPos.pos.row = curPos.pos.row - 1;
			curPos.pos.col = curPos.pos.col + 1;
		}

		if (this->isValidPos(curPos.pos) &&
			!this->isNullptrStone(curPos.pos) &&
			this->getStone(curPos.pos)->getOwner() != this->getStone(pos)->getOwner()) //check if the owner of the stone belongs to the enemy
		{
			//eating move
			curPos.eatenPos = curPos.pos; //only in cases that wasAte will set to yes
			curPos.pos.row = curPos.pos.row - 1;
			curPos.pos.col = curPos.pos.col + 1;
			if (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
			{
				curPos.wasAte = WasAte::YES;
				
				moves[size] = curPos;
				size++;
			}
		}

		//check the slant up left 
		curPos.pos.row = pos.row - 1;
		curPos.pos.col = pos.col - 1;

		//not eating move
		while (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
		{
			moves[size] = curPos;
			size++;

			curPos.pos.row = curPos.pos.row - 1;
			curPos.pos.col = curPos.pos.col - 1;
		}

		if (this->isValidPos(curPos.pos) &&
			!this->isNullptrStone(curPos.pos) &&
			this->getStone(curPos.pos)->getOwner() != this->getStone(pos)->getOwner()) //check if the owner of the stone belongs to the enemy
		{
			//eating move
			curPos.eatenPos = curPos.pos; //only in cases that wasAte will set to yes
			curPos.pos.row = curPos.pos.row - 1;
			curPos.pos.col = curPos.pos.col - 1;
			if (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
			{
				curPos.wasAte = WasAte::YES;
				moves[size] = curPos;
				size++;
			}
		}

		//check the slant down right 
		curPos.pos.row = pos.row + 1;
		curPos.pos.col = pos.col + 1;

		//not eating move
		while (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
		{
			moves[size] = curPos;
			size++;

			curPos.pos.row = curPos.pos.row + 1;
			curPos.pos.col = curPos.pos.col + 1;
		}

		if (this->isValidPos(curPos.pos) &&
			!this->isNullptrStone(curPos.pos) &&
			this->getStone(curPos.pos)->getOwner() != this->getStone(pos)->getOwner()) //check if the owner of the stone belongs to the enemy
		{
			//eating move
			curPos.eatenPos = curPos.pos; //only in cases that wasAte will set to yes
			curPos.pos.row = curPos.pos.row + 1;
			curPos.pos.col = curPos.pos.col + 1;
			if (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
			{
				curPos.wasAte = WasAte::YES;
				moves[size] = curPos;
				size++;
			}
		}

		//check the slant down left 
		curPos.pos.row = pos.row + 1;
		curPos.pos.col = pos.col - 1;

		//not eating move
		while (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
		{
			moves[size] = curPos;
			size++;

			curPos.pos.row = curPos.pos.row + 1;
			curPos.pos.col = curPos.pos.col - 1;
		}

		if (this->isValidPos(curPos.pos) &&
			!this->isNullptrStone(curPos.pos) &&
			this->getStone(curPos.pos)->getOwner() != this->getStone(pos)->getOwner()) //check if the owner of the stone belongs to the enemy
		{
			//eating move
			curPos.eatenPos = curPos.pos; //only in cases that wasAte will set to yes
			curPos.pos.row = curPos.pos.row + 1;
			curPos.pos.col = curPos.pos.col - 1;
			if (this->isValidPos(curPos.pos) && this->isNullptrStone(curPos.pos))
			{
				curPos.wasAte = WasAte::YES;
				moves[size] = curPos;
				size++;
			}
		}

	}

	// no possiable moves
	if (size == 0)
	{
		delete[] moves;
		return nullptr;
	}
	else
	{
		return moves;
	}
}

bool DamkaBoard::isValidPos(Position pos) const
{
	if (pos.row > ROWSDAMKA || pos.row < 1 || pos.col > COLSDAMKA || pos.col < 1)
		return false;
	return true;
}

void DamkaBoard::display() const
{
	char letters[2][2] = { { 'o','x' }, { 'O','X'} };
	for (int r = 0; r < ROWSDAMKA; r++) {
		cout << "   " << r + 1;
	}
	cout << endl;
	for (int r = 0; r < ROWSDAMKA; r++) {
		cout << "----";
	}
	cout << endl;

	for (int r = 0; r < ROWSDAMKA; r++)
	{
		cout << r + 1;
		for (int c = 0; c < COLSDAMKA; c++)
		{
			if (this->_stones[r][c] == nullptr)
			{
				cout << "|   ";
			}
			else
			{
				cout << "| " << letters[(int)_stones[r][c]->getIsKing()][(int)_stones[r][c]->getOwner()] << " ";
			}
		}
		cout << endl;
	}
}

void DamkaBoard::deleteStone(Position pos)
{
	delete _stones[pos.row-1][pos.col-1];
	_stones[pos.row-1][pos.col-1] = nullptr;
}

void DamkaBoard::deleteBoard()
{
	for (int i = 0; i < ROWSDAMKA; i++)
	{
		for (int j = 0; j < COLSDAMKA; j++)
		{
			delete (_stones[i][j]);
		}
	}

}

void DamkaBoard::save(ofstream& out)
{
	for (int i = 0; i < ROWSDAMKA; i++)
	{
		for (int j = 0; j < COLSDAMKA; j++)
		{
			BoardPosStatus status;
			status = BoardPosStatus::NO_STONE;
			if (_stones[i][j] == nullptr)
			{
				status = BoardPosStatus::NO_STONE;
				out.write(reinterpret_cast<const char*>(&status), sizeof(status));
			}
			else
			{
				status = BoardPosStatus::HAS_STONE;
				out.write(reinterpret_cast<const char*>(&status), sizeof(status));

				try {
					_stones[i][j]->save(out);
				}
				catch (runtime_error& error)
				{
					throw error;
				}
			}
		}
	}
}

void DamkaBoard::load(ifstream& in)
{
	BoardPosStatus status;

	for (int i = 0; i < ROWSDAMKA; i++)
	{
		for (int j = 0; j < COLSDAMKA; j++)
		{
			in.read(reinterpret_cast<char*>(&status), sizeof(status));

			if (status == BoardPosStatus::NO_STONE)
				_stones[i][j] = nullptr;
			else
			{
				_stones[i][j] = new Stone;
				try {
					_stones[i][j]->load(in);
				}
				catch (runtime_error& error)
				{
					for (int k = 0; k < i; k++)
					{
						for (int s = 0; s < COLSDAMKA; s++)
						{
							delete _stones[k][s];
						}
					}
					for (int s = 0; s <= j; s++)
					{
						delete _stones[i][s];
					}
					throw error;
				}
			}
		}
	}
}