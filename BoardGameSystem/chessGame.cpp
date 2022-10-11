#include "chessGame.h"
#include <iostream>


void ChessGame::addStonesToPlayers()
{
	//set every stone to it's player
	for (int r = 0; r < ROWSCHESS; r++)
	{
		for (int c = 0; c < COLSCHESS; c++)
		{
			Position pos;
			pos.row = r + 1;
			pos.col = c + 1;
			if (_board.isNullptrStone(pos) == false)
			{
				if (_board.getNumPlayerForPos(pos) == NumPlayer::P1)
					p1.addStone(_board.getStone(pos));
				else if (_board.getNumPlayerForPos(pos) == NumPlayer::P2)
					p2.addStone(_board.getStone(pos));
			}
		}
	}
}

ChessGame::ChessGame(bool initBoard)
	:Game(GameType::CHESS), _board(initBoard)
{
	curPlayer = &p1;
	nextPlayer = &p2;
	if (initBoard == true)
		addStonesToPlayers();
	setStatus(false); //update the status game to false.
}

void ChessGame::showBoard() const
{
	_board.display();
}

void ChessGame::moveStone()
{
	int rowChess, colChess;

	cout << "please enter the row and col that you would like to move." << endl;
	cin >> rowChess >> colChess;
	Position posChess;
	posChess = { rowChess , colChess };

	NumPlayer curPlayer;
	if (getCurPlayerNum() == 1)
		curPlayer = NumPlayer::P1;
	else
		curPlayer = NumPlayer::P2;

	while (this->isStoneBelongsToCurPlayer(rowChess, colChess)==false)
	{
		cout << "Invalid position. " << endl;
		cout << "please enter the row and col that you would like to move." << endl;
		cin >> rowChess >> colChess;
		posChess = { rowChess , colChess };
	}

	int rowNext, colNext;
	cout << "please enter the row and col of the position you want to move." << endl;
	cin >> rowNext >> colNext;
	Position posNext;
	posNext = { rowNext , colNext };

	while (IsValidMove(posChess, posNext) == false)
	{
		cout << "Invalid position. " << endl;
		cout << "please enter the row and col of the position you want to move." << endl;
		cin >> rowNext >> colNext;
		posNext = { rowNext , colNext };
	}

	//update board
	ChessBoard* b = getBoard();
	if (eatingSituation(posChess, posNext) == false)
	{
		b->moveStone(posChess, posNext);
	}
	else //eating situation
	{
		b->moveEatStone(posChess, posNext);
	}

	//winning situation - check risks of next moves of king
	bool winningSituation = isChessMat();

	if (winningSituation) //there are risks on the king = winning situation
	{
		setWinner(getCurPlayer()); // the current player is the winner
		setStatus(true); // set the game status to finish.
	}

	//switch the current player
	Player* tempPlayer;
	tempPlayer = getCurPlayer();
	setCurPlayer(getNextPlayer());
	setNextPlayer(tempPlayer);
}

bool ChessGame::isChessMat()
{
	//get the position of the king:
	Stone* kingStone = new Stone;
	kingStone = getKingStoneOfNextPlayer();

	int size = 0;
	Position* kingMoves = getMoves(kingStone->getPos().row, kingStone->getPos().col ,size);

	int numOfRisks = 0;
	Position* kingRisksForNextMove; //only for get what the function returns

	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
			kingRisksForNextMove = getRisks(kingMoves[i].row, kingMoves[i].col, numOfRisks);
			if (numOfRisks == 0)
				return false;
		}
	}
	return true;
}

Stone* ChessGame::getKingStoneOfNextPlayer()
{
	Stone** stonesArr = nextPlayer->getStoneArr();
	for (int i = 0; i < NUM_OF_STONES; i++)
	{
		if (stonesArr[i]->getType() == (int)ChessStoneType::KING)
			return stonesArr[i];
	}
	return nullptr;
}

bool ChessGame::eatingSituation(Position posChess, Position posNext)
{
	//if the next pos is belongs to the other player
	if (_board.isNullptrStone(posNext) == false && this->isStoneBelongsToCurPlayer(posNext.row, posNext.col) == false)
		return true;
	return false;
}

void ChessGame::showRisksForStone()
{
	int r, c;
	cout << "please enter the row and col of the square." << endl;
	cin >> r >> c;

	Position pos = { r ,c };

	while (isValidPos(r, c) == false || _board.getStone(pos) == nullptr)
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the square." << endl;
		cin >> r >> c;
		pos = { r ,c };
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

bool ChessGame::IsValidMove(Position curPos, Position posNext)
{
	Position* moves = new Position[CHESS_MAX_POS_MOVES];
	int size = 0;
	moves = getMoves(curPos.row, curPos.col, size);
	for (int i = 0; i < size; i++)
	{
		if (moves[i].row == posNext.row && moves[i].col == posNext.col)
		{
			delete[] moves;
			return true;
		}
	}
	delete[] moves;
	return false;
}

Position* ChessGame::getRisks(int row, int col, int& size)
{
	bool found;
	Position* res = new Position[NUM_OF_STONES];
	size = 0;
	Position pos = { row,col };
	Stone** otherPlrStones;
	int otherPlrStonesSize;

	if (_board.getStone(pos)->getOwner() == NumPlayer::P1)
	{
		otherPlrStones = p2.getStoneArr();
		otherPlrStonesSize = p2.getNumStones();
	}
	else
	{
		otherPlrStones = p1.getStoneArr();
		otherPlrStonesSize = p1.getNumStones();
	}
	

	for (int i = 0; i < otherPlrStonesSize; i++)
	{
		found = false;
		int currMovesSize=0;
		Position* currStoneMoves = otherPlrStones[i]->getpossibleMoves(currMovesSize);
		for (int j = 0; j < currMovesSize && found == false; j++)
		{
			if (currStoneMoves[j].row == row && currStoneMoves[j].col == col)
			{
				res[size].row = otherPlrStones[i]->getPos().row;
				res[size].col = otherPlrStones[i]->getPos().col;
				size++;
				found = true;
			}
		}
	}

	return res;
}

ChessBoard* ChessGame::getBoard()
{
	return &this->_board;
}

void ChessGame::showValidMovesForStone()
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
	Position* arr;
	arr = getMoves(r, c, size);
	
	if (size == -1)
		cout << "The stone is not exist" << endl;

	else if (size == 0)
	{
		cout << "No valid moves" << endl;
		delete[] arr;
	}

	else
	{
		cout << "the possiable moves are:" << endl;

		for (int i = 0; i < size; i++)
		{
			cout << arr[i].row << "," << arr[i].col << endl;
		}
	}

	delete[] arr;
}

bool ChessGame::isValidPos(int row, int col)const
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.isValidPos(pos);
}

Position* ChessGame::getMoves(int row, int col, int& size)
{
	Position pos;
	pos.row = row;
	pos.col = col;

	Stone* stone = new Stone;
	stone = _board.getStone(pos);

	Position* moves = _board.getMoves(stone, size);

	int newsize = 0;
	Position* newMoves = new Position[CHESS_MAX_POS_MOVES];

	//remove possible positions that belongs to the cur player
	for (int i = 0; i < size; i++)
	{
		if (_board.isNullptrStone(moves[i]) || ((int)_board.getStone(moves[i])->getOwner()) + 1 != this->getCurPlayerNum())
		{
			// insert position to new array
			newMoves[newsize] = moves[i];
			newsize++;
		}
	}
	size = newsize;
	return newMoves;
}

bool ChessGame::isStoneBelongsToCurPlayer(int row, int col)
{
	Position p = { row, col };
	return curPlayer->isItMyStone(_board.getStone(p));
}

void ChessGame::save(ofstream& out)
{
	Game::save(out);

	_board.save(out); //_board
}

void ChessGame::load(ifstream& in)
{
	Game::load(in);
	_board.load(in); //_board
	addStonesToPlayers();
}

ChessGame::~ChessGame()
{
	_board.deleteBoard();
}