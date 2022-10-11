#include "chessBoard.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#include <iostream>
using namespace std;

ChessBoard::ChessBoard(bool initBoard)
{
	if (initBoard == true)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Position curPos;
				curPos.row = i + 1;
				curPos.col = j + 1;

				//set powns
				if (i == 1 || i == 6)
				{
					_stones[i][j] = new Pawn;
					_stones[i][j]->setPos(curPos);
					_stones[i][j]->setType(ChessStoneType::PAWN);
					if (i == 1)
						_stones[i][j]->setOwner(NumPlayer::P2);
					else
						_stones[i][j]->setOwner(NumPlayer::P1);
				}

				if (i == 0 || i == 7)
				{
					//set rooks
					if (j == 0 || j == 7)
					{
						_stones[i][j] = new Rook;
						_stones[i][j]->setPos(curPos);
						_stones[i][j]->setType(ChessStoneType::ROOK);

						if (i == 0)
							_stones[i][j]->setOwner(NumPlayer::P2);
						else
							_stones[i][j]->setOwner(NumPlayer::P1);
					}

					//set knight
					if (j == 1 || j == 6)
					{
						_stones[i][j] = new Knight;
						_stones[i][j]->setPos(curPos);
						_stones[i][j]->setType(ChessStoneType::KNIGHT);

						if (i == 0)
							_stones[i][j]->setOwner(NumPlayer::P2);
						else
							_stones[i][j]->setOwner(NumPlayer::P1);
					}

					//set bishop
					if (j == 2 || j == 5)
					{
						_stones[i][j] = new Bishop;
						_stones[i][j]->setPos(curPos);
						_stones[i][j]->setType(ChessStoneType::BISHOP);

						if (i == 0)
							_stones[i][j]->setOwner(NumPlayer::P2);
						else
							_stones[i][j]->setOwner(NumPlayer::P1);
					}

					//set queen
					if (j == 3)
					{
						_stones[i][j] = new Queen;
						_stones[i][j]->setPos(curPos);
						_stones[i][j]->setType(ChessStoneType::QUEEN);

						if (i == 0)
							_stones[i][j]->setOwner(NumPlayer::P2);
						else
							_stones[i][j]->setOwner(NumPlayer::P1);
					}

					//set king
					if (j == 4)
					{
						_stones[i][j] = new King;
						_stones[i][j]->setPos(curPos);
						_stones[i][j]->setType(ChessStoneType::KING);
						if (i == 0)
							_stones[i][j]->setOwner(NumPlayer::P2);
						else
							_stones[i][j]->setOwner(NumPlayer::P1);
					}

				}

			}
		}

	}


}

bool ChessBoard::isNullptrStone(Position pos) const
{
	if (this->_stones[pos.row - 1][pos.col - 1] == nullptr)
		return true;
	return false;
}

void ChessBoard::display() const
{
	char letters[2][6] = { { 'Q','R','B','N','P','K'} , {'q','r','b','n','p','k'} };
	for (int r = 0; r < ROWSCHESS; r++) {
		cout << "   " << r + 1;
	}
	cout << endl;
	for (int r = 0; r < ROWSCHESS; r++) {
		cout << "----";
	}
	cout << endl;

	for (int r = 0; r < ROWSCHESS; r++)
	{
		cout << r + 1;
		for (int c = 0; c < COLSCHESS; c++)
		{
			if (this->_stones[r][c] == nullptr)
			{
				cout << "|   ";
			}
			else
			{
				cout << "| " << letters[(int)_stones[r][c]->getOwner()][(int)_stones[r][c]->getType()] << " ";
			}
		}
		cout << endl;
	}
}

bool ChessBoard::isValidPos(Position pos) const
{
	if (pos.row > ROWSCHESS || pos.row < 1 || pos.col > COLSCHESS || pos.col < 1)
		return false;
	return true;
}

NumPlayer ChessBoard::getNumPlayerForPos(Position pos) const
{
	if (isNullptrStone(pos) == true)
		return NumPlayer::None;
	else
		return _stones[pos.row - 1][pos.col - 1]->getOwner();
}

Stone* ChessBoard::getStone(Position pos) 
{
	//assuming valid pos
	return _stones[pos.row - 1][pos.col - 1];
}

void ChessBoard::deleteStone(Position pos)
{
	delete _stones[pos.row - 1][pos.col - 1];
	_stones[pos.row - 1][pos.col - 1] = nullptr;
}

Position* ChessBoard::getRisks(Stone* stone, int& size)
{
	size = 0;
	Position* risks = nullptr;

	// if the stone is nullptr
	if (stone == nullptr)
		size = -1;

	risks = stone->getpossibleRisks(size);
	
	// no possiable risks
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

Position* ChessBoard::getMoves(Stone* stone, int& size)
{
	size = 0;
	Position* moves = nullptr;

	// if the stone is nullptr
	if (stone == nullptr)
		size = -1;

	moves = stone->getpossibleMoves(size);

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

void ChessBoard::moveStone(Position posFrom, Position posTo)
{
	_stones[posFrom.row - 1][posFrom.col - 1]->setPos(posTo);
	_stones[posTo.row - 1][posTo.col - 1] = _stones[posFrom.row - 1][posFrom.col - 1];
	_stones[posFrom.row - 1][posFrom.col - 1] = nullptr;
}

void ChessBoard::moveEatStone(Position posFrom, Position posTo)
{
	this->deleteStone(posTo);
	_stones[posFrom.row - 1][posFrom.col - 1]->setPos(posTo);
	_stones[posTo.row - 1][posTo.col - 1] = _stones[posFrom.row - 1][posFrom.col - 1];
	_stones[posFrom.row - 1][posFrom.col - 1] = nullptr;
}

void ChessBoard::deleteBoard()
{
	for (int i = 0; i < ROWSCHESS; i++)
	{
		for (int j = 0; j < COLSCHESS; j++)
		{
			delete (_stones[i][j]);
		}
	}
}

void ChessBoard::save(std::ofstream& out)
{
	for (int i = 0; i < ROWSCHESS; i++)
	{
		for (int j = 0; j < COLSCHESS; j++)
		{
			BoardPosStatus status;
			status = BoardPosStatus::NO_STONE;
			if (_stones[i][j] == nullptr)
			{
				out.write(reinterpret_cast<const char*>(&status), sizeof(status));
			}
			else
			{
				status = BoardPosStatus::HAS_STONE;
				out.write(reinterpret_cast<const char*>(&status), sizeof(status));
				int stoneType = _stones[i][j]->getType();
				out.write(reinterpret_cast<const char*>(&stoneType), sizeof(stoneType)); //type
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

void ChessBoard::load(std::ifstream& in)
{
	BoardPosStatus status;

	for (int i = 0; i < ROWSCHESS; i++)
	{
		for (int j = 0; j < COLSCHESS; j++)
		{
			in.read(reinterpret_cast<char*>(&status), sizeof(status));

			if (status == BoardPosStatus::NO_STONE)
				_stones[i][j] = nullptr;
			else
			{
				int stoneType;
				in.read(reinterpret_cast<char*>(&stoneType), sizeof(stoneType)); //type
				switch (stoneType)
				{
				case ((int)ChessStoneType::PAWN):
					_stones[i][j] = new Pawn();
					break;
				case ((int)ChessStoneType::BISHOP):
					_stones[i][j] = new Bishop();
					break;
				case ((int)ChessStoneType::KING):
					_stones[i][j] = new King();
					break;
				case ((int)ChessStoneType::KNIGHT):
					_stones[i][j] = new Knight();
					break;
				case ((int)ChessStoneType::QUEEN):
					_stones[i][j] = new Queen();
					break;
				case ((int)ChessStoneType::ROOK):
					_stones[i][j] = new Rook();
					break;
				
				default:
					_stones[i][j] = nullptr;
					break;
				}

				try {
					_stones[i][j]->load(in);
				}
				catch (runtime_error& error)
				{
					for (int k = 0; k < i; k++)
					{
						for (int s = 0; s < COLSCHESS; s++)
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