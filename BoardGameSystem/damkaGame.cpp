#pragma once
#include "damkaGame.h"
#include "definitions.h"

using namespace std;

void DamkaGame::addStonesToPlayers()
{
	//set every stone to it's player
	for (int r = 0; r < ROWSDAMKA; r++)
	{
		for (int c = 0; c < COLSDAMKA; c++)
		{
			Position pos;
			pos.row = r + 1;
			pos.col = c + 1;
			if (_board.isNullptrStone(pos) == false)
			{
				if (_board.getNumPlayerForPos(pos) == NumPlayer::P1)
					this->getCurPlayer()->addStone(_board.getStone(pos));
				else if (_board.getNumPlayerForPos(pos) == NumPlayer::P2)
					this->getNextPlayer()->addStone(_board.getStone(pos));
			}
		}
	}

}

DamkaGame::DamkaGame(bool initBoard)
	:Game(GameType::DAMKA),_board(initBoard)
{
	if(initBoard == true)
		addStonesToPlayers();
	setStatus(false); //update the status game to false.
}

void DamkaGame::showBoard() const
{
	_board.display();
}

DamkaBoard* DamkaGame::getBoard()
{
	return &this->_board;
}

Position* DamkaGame::getRisks(int row, int col, int& size)const
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.getRisks(pos, size);
}

Move* DamkaGame::getMoves(int row, int col, int& size)const
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.getMoves(pos, size);
}

bool DamkaGame::isValidPos(int row, int col) const
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.isValidPos(pos);
}

bool DamkaGame::isStoneBelongsToCurPlayer(int row, int col)const
{
	Position p = { row, col };
	return curPlayer->isItMyStone(_board.getStone(p));
}

void DamkaGame::moveStone()
{
	int curRow, curCol;
	int nextRow, nextCol;
	if (isFinish == true)
	{
		cout << "Game over!" << endl;
		return;
	}
	cout << "please enter the row and col of the stone that you would like to move." << endl;
	cin >> curRow >> curCol;

	while (isValidPos(curRow, curCol) == false || isStoneBelongsToCurPlayer(curRow, curCol) == false)
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the stone." << endl;
		cin >> curRow >> curCol;
	}
	cout << endl;

	Position curPos;
	curPos.row = curRow;
	curPos.col = curCol;

	cout << "please enter the row and col of the position that you would like to move the stone to." << endl;
	cin >> nextRow >> nextCol;

	while (isValidPos(nextRow, nextCol) == false) //check valid position
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the stone." << endl;
		cin >> nextRow >> nextCol;
	}
	cout << endl;

	int size = 0;

	Position nextPos;
	nextPos.row = nextRow;
	nextPos.col = nextCol;

	Move* moves = new Move[MAXIMUM_NUM_MOVES_FOR_KING];
	moves = getMoves(curRow, curCol, size);

	Move* curMove;

	curMove = getValidMove(moves, size, nextPos);
	while (curMove == nullptr)
	{
		cout << endl;
		cout << "The move is not valid. ";
		cout << "please enter the row and col of the stone." << endl;
		cin >> nextRow >> nextCol;
		nextPos.row = nextRow;
		nextPos.col = nextCol;

		curMove = getValidMove(moves, size, nextPos);
	}
	cout << endl;

	if (curMove->wasAte == WasAte::YES)
	{
		//delete the eaten stone
		
		getNextPlayer()->removeStone(_board.getStone(curMove->eatenPos));
		_board.deleteStone(curMove->eatenPos);

		//winning situation - if the number of the stones that were eaten is 12.
		if (getNextPlayer()->getNumStones() == 0)
		{
			setWinner(curPlayer); // the current player is the winner
			setStatus(true); // set the game status to finish.
		}
	}

	//update board
	_board.moveStone(curPos, nextPos);

	//switch the current player
	Player* tempPlayer;
	tempPlayer = curPlayer;
	setCurPlayer(getNextPlayer());
	setNextPlayer(tempPlayer);

	//check if the stone became king
	if (nextPos.row == 1 || nextPos.row == 8)
	{
		_board.getStone(curMove->pos)->setIsKing(true);
	}

}

void DamkaGame::showValidMovesForStone()
{
	int r, c;
	cout << "please enter the row and col of the stone." << endl;
	cin >> r >> c;

	while (isValidPos(r, c) == false)
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the stone." << endl;
		cin >> r >> c;
	}
	cout << endl;

	int size;
	Move* arr = this->getMoves(r, c, size);

	if (size == -1)
		cout << "The stone is not exist" << endl;

	else if (size == 0)
		cout << "No valid moves" << endl;
	else
	{
		cout << "the possiable moves are:" << endl;

		for (int i = 0; i < size; i++)
		{
			cout << arr[i].pos.row << "," << arr[i].pos.col << endl;
		}
	}

}

void DamkaGame::showRisksForStone()
{
	int r, c;
	cout << "please enter the row and col of the stone." << endl;
	cin >> r >> c;

	while (isValidPos(r, c) == false)
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the stone." << endl;
		cin >> r >> c;
	}
	cout << endl;
	int size;

	Position* arr = getRisks(r, c, size);
	if (size == 0)
		cout << "no danger" << endl;
	else
	{
		cout << "be careful - danger." << endl;

		for (int i = 0; i < size; i++)
		{
			cout << arr[i].row << "," << arr[i].col << endl;
		}
	}
}

void DamkaGame::save(ofstream& out)
{
	Game::save(out);

	_board.save(out); //_board
}

void DamkaGame::load(ifstream& in)
{
	Game::load(in);
	_board.load(in); //_board
	addStonesToPlayers();
}

DamkaGame::~DamkaGame()
{
	_board.deleteBoard();
}
