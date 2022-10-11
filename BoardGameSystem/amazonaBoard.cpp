#include "amazonaBoard.h"
#include <iostream>
using namespace std;

AmazonaBoard::AmazonaBoard(bool initBoard)
{
	if (initBoard == true)
	{
		for (int i = 0; i < ROWSAMAZONES; i++)
		{
			for (int j = 0; j < COLSAMAZONES; j++)
			{
				Position curPos;
				curPos.row = i;
				curPos.col = j;

				//set stones to player 1
				if ((j == 3 || j == 6) && (i == 0))
				{
					_stones[i][j] = new Stone;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setOwner(NumPlayer::P1);
					_stones[i][j]->setType(Type::AMAZON);

				}
				else if ((j == 0 || j == 9) && (i == 3))
				{
					_stones[i][j] = new Stone;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setOwner(NumPlayer::P1);
					_stones[i][j]->setType(Type::AMAZON);
				}


				//set stones to player 2
				if ((j == 3 || j == 6) && (i == 9))
				{
					_stones[i][j] = new Stone;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setOwner(NumPlayer::P2);
					_stones[i][j]->setType(Type::AMAZON);
				}
				else if ((j == 0 || j == 9) && (i == 6))
				{
					_stones[i][j] = new Stone;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setOwner(NumPlayer::P2);
					_stones[i][j]->setType(Type::AMAZON);
				}

			}
		}

	}
}

bool AmazonaBoard::isNullptrStone(Position pos) const
{
	if (this->_stones[pos.row - 1][pos.col - 1] == nullptr)
		return true;
	return false;
}

bool AmazonaBoard::isAmazonStone(Position pos) const {
	if (this->_stones[pos.row - 1][pos.col - 1]->getType() == (int)Type::AMAZON)
		return true;
	return false;
}

NumPlayer AmazonaBoard::getNumPlayerForPos(Position pos) const
{
	if (isNullptrStone(pos) == true)
		return NumPlayer::None;
	else
		return _stones[pos.row - 1][pos.col - 1]->getOwner();
}

Stone* AmazonaBoard::getStone(Position pos) const
{
	//assuming valid pos
	return _stones[pos.row - 1][pos.col - 1];
}

void AmazonaBoard::moveStone(Position posFrom, Position posTo)
{
	//no error checks - checked in gameController
	_stones[posFrom.row - 1][posFrom.col - 1]->setPos(posTo);
	_stones[posTo.row - 1][posTo.col - 1] = _stones[posFrom.row - 1][posFrom.col - 1];
	_stones[posFrom.row - 1][posFrom.col - 1] = nullptr;
}

Position* AmazonaBoard::getMoves(Position pos, int& size)const
{
	size = 0;
	Position* moves = nullptr;

	if (this->getStone(pos) == nullptr || !this->isAmazonStone(pos))/*check the case the pos is'nt amazon*/
		size = -1;

	//if the stone is amazon
	else
	{
		moves = new Position[AMAZONA_MAXIMUM_NUM_MOVES];
		Position curPos;

		//check  up  
		curPos.row = pos.row - 1;
		curPos.col = pos.col;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.row = curPos.row - 1;
		}

		//check  down  
		curPos.row = pos.row + 1;
		curPos.col = pos.col;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.row = curPos.row + 1;
		}

		//check  right  
		curPos.row = pos.row;
		curPos.col = pos.col + 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.col = curPos.col + 1;
		}

		//check  left  
		curPos.row = pos.row;
		curPos.col = pos.col - 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.col = curPos.col - 1;
		}


		//check the slant up right 
		curPos.row = pos.row - 1;
		curPos.col = pos.col + 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.row = curPos.row - 1;
			curPos.col = curPos.col + 1;
		}

		//check the slant up left 
		curPos.row = pos.row - 1;
		curPos.col = pos.col - 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.row = curPos.row - 1;
			curPos.col = curPos.col - 1;
		}

		//check the slant down right 
		curPos.row = pos.row + 1;
		curPos.col = pos.col + 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.row = curPos.row + 1;
			curPos.col = curPos.col + 1;
		}

		//check the slant down left 
		curPos.row = pos.row + 1;
		curPos.col = pos.col - 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			moves[size] = curPos;
			size++;

			curPos.row = curPos.row + 1;
			curPos.col = curPos.col - 1;
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

Position* AmazonaBoard::getRisks(Position pos, int& size)const
{
	size = 0;
	Position* risks = nullptr;

	if (this->getStone(pos) != nullptr)/*check the case the pos isn't nullptr*/
		size = -1;

	//if the stone is nullptr
	else
	{
		risks = new Position[AMAZONA_MAXIMUM_NUM_RISKS];
		Position curPos;

		//check  up  
		curPos.row = pos.row - 1;
		curPos.col = pos.col;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.row = curPos.row - 1;
		}

		//check  down  
		curPos.row = pos.row + 1;
		curPos.col = pos.col;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.row = curPos.row + 1;
		}

		//check  right  
		curPos.row = pos.row;
		curPos.col = pos.col + 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.col = curPos.col + 1;
		}

		//check  left  
		curPos.row = pos.row;
		curPos.col = pos.col - 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.col = curPos.col - 1;
		}


		//check the slant up right 
		curPos.row = pos.row - 1;
		curPos.col = pos.col + 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.row = curPos.row - 1;
			curPos.col = curPos.col + 1;
		}

		//check the slant up left 
		curPos.row = pos.row - 1;
		curPos.col = pos.col - 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.row = curPos.row - 1;
			curPos.col = curPos.col - 1;
		}

		//check the slant down right 
		curPos.row = pos.row + 1;
		curPos.col = pos.col + 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.row = curPos.row + 1;
			curPos.col = curPos.col + 1;
		}

		//check the slant down left 
		curPos.row = pos.row + 1;
		curPos.col = pos.col - 1;

		while (this->isValidPos(curPos) && this->isNullptrStone(curPos))
		{
			risks[size] = curPos;
			size++;

			curPos.row = curPos.row + 1;
			curPos.col = curPos.col - 1;
		}
	}

	// no possiable moves
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

bool AmazonaBoard::isValidPos(Position pos) const
{
	if (pos.row > ROWSAMAZONES || pos.row < 1 || pos.col > COLSAMAZONES || pos.col < 1)
		return false;
	return true;
}

void AmazonaBoard::display() const
{
	char letters[3] = { 'X', 'O', 'M' };
	cout << " ";
	for (int r = 0; r < ROWSAMAZONES; r++) {
		cout << "   " << r + 1;
	}
	cout << endl;
	cout << "---";
	for (int r = 0; r < ROWSAMAZONES; r++) {
		cout << "----";
	}
	cout << endl;

	for (int r = 0; r < ROWSAMAZONES; r++)
	{
		if (r == 9)
			cout << r + 1;
		else
			cout << " " << r + 1;
		for (int c = 0; c < COLSAMAZONES; c++)
		{

			if (this->_stones[r][c] == nullptr)
			{
				cout << "|   ";
			}
			else
			{
				cout << "| " << letters[(int)_stones[r][c]->getOwner()] << " ";
			}
		}
		cout << endl;
	}
}

void AmazonaBoard::deleteStone(Position pos)
{
	delete _stones[pos.row - 1][pos.col - 1];
	_stones[pos.row - 1][pos.col - 1] = nullptr;
}

void AmazonaBoard::deleteBoard()
{
	for (int i = 0; i < ROWSAMAZONES; i++)
	{
		for (int j = 0; j < COLSAMAZONES; j++)
		{
			delete (_stones[i][j]);
		}
	}

}

void AmazonaBoard::setNewMarked(Position posMarked)
{
	this->_stones[posMarked.row - 1][posMarked.col - 1] = new Stone;
	this->_stones[posMarked.row - 1][posMarked.col - 1]->setPos(posMarked);
	this->_stones[posMarked.row - 1][posMarked.col - 1]->setOwner(NumPlayer::None);
	this->_stones[posMarked.row - 1][posMarked.col - 1]->setType(Type::MARKED);
}

void AmazonaBoard::save(ofstream& out)
{
	for (int i = 0; i < ROWSAMAZONES; i++)
	{
		for (int j = 0; j < COLSAMAZONES; j++)
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

void AmazonaBoard::load(ifstream& in)
{
	BoardPosStatus status;

	for (int i = 0; i < ROWSAMAZONES; i++)
	{
		for (int j = 0; j < COLSAMAZONES; j++)
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
						for (int s = 0; s < COLSAMAZONES; s++)
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