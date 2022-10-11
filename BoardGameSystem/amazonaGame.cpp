#include "amazonaGame.h"
#include <iostream>
using namespace std;

void AmazonaGame::addStonesToPlayers()
{
	//set every stone to it's player
	for (int r = 0; r < ROWSAMAZONES; r++)
	{
		for (int c = 0; c < COLSAMAZONES; c++)
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

AmazonaGame::AmazonaGame(bool initBoard)
	:Game(GameType::AMAZONA), _board(initBoard)
{
	setCurPlayer(&p2);
	setNextPlayer(&p1);
	
	if (initBoard == true)
		addStonesToPlayers();
	setStatus(false); //update the status game to false.
}

void AmazonaGame::showBoard() const
{
	_board.display();
}

void AmazonaGame::showValidMovesForStone()
{
	int r, c;
	cout << "please enter the row and col of the amazon." << endl;
	cin >> r >> c;

	while (isValidPos(r, c) == false)
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the amazon." << endl;
		cin >> r >> c;
	}
	cout << endl;

	int size;
	Position* arr = getMoves(r, c, size);

	if (size == -1)
		cout << "The amazon stone is not exist" << endl;

	else if (size == 0)
		cout << "No valid moves" << endl;
	else
	{
		cout << "the possiable moves are:" << endl;

		for (int i = 0; i < size; i++)
		{
			cout << arr[i].row << "," << arr[i].col << endl;
		}
	}

}

void AmazonaGame::showRisksForStone()
{
	int r, c;
	cout << "please enter the row and col of the square." << endl;
	cin >> r >> c;

	while (isValidPos(r, c) == false)
	{
		cout << endl;
		cout << "Invalid position. ";
		cout << "please enter the row and col of the square." << endl;
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

void AmazonaGame::moveStone()
{
	int rowAmazon, colAmazon;

	cout << "please enter the row and col of the Amazon that you would like to move." << endl;
	cin >> rowAmazon >> colAmazon;
	Position posAmazon;
	posAmazon = { rowAmazon , colAmazon };

	NumPlayer curPlayer;
	if (getCurPlayerNum() == 1)
		curPlayer = NumPlayer::P1;
	else
		curPlayer = NumPlayer::P2;

	while (getBoard()->getStone(posAmazon)->getType() != (int)Type::AMAZON || getBoard()->getStone(posAmazon)->getOwner() != curPlayer)
	{
		cout << "Invalid position. " << endl;
		cout << "please enter the row and col of the Amazon that you would like to move." << endl;
		cin >> rowAmazon >> colAmazon;
		posAmazon = { rowAmazon , colAmazon };
	}

	int rowNext, colNext;
	cout << "please enter the row and col of the position you want to move." << endl;
	cin >> rowNext >> colNext;
	Position posNext;
	posNext = { rowNext , colNext };

	while (IsValidMove(posAmazon, posNext) == false)
	{
		cout << "Invalid position. " << endl;
		cout << "please enter the row and col of the position you want to move." << endl;
		cin >> rowNext >> colNext;
		posNext = { rowNext , colNext };
	}

	int rowMarked, colMarked;
	cout << "please enter the row and col of the position you want to mark." << endl;
	cin >> rowMarked >> colMarked;
	Position posMarked;
	posMarked = { rowMarked , colMarked };

	while (IsValidToMark(posNext, posMarked) == false)
	{
		cout << "Invalid position. " << endl;
		cout << "please enter the row and col of the position you want to mark." << endl;
		cin >> rowMarked >> colMarked;
		posMarked = { rowMarked , colMarked };
	}

	//update board
	AmazonaBoard* b = getBoard();
	b->moveStone(posAmazon, posNext);

	//marking the choosen marked position
	getBoard()->setNewMarked(posMarked);

	//winning situation
	if (IsCurWinner())
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

AmazonaBoard* AmazonaGame::getBoard()
{
	return &this->_board;
}

bool AmazonaGame::isValidPos(int row, int col) const
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.isValidPos(pos);
}

Position* AmazonaGame::getMoves(int row, int col, int& size)const
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.getMoves(pos, size);
}

bool AmazonaGame::IsValidMove(Position curPos, Position posNext)
{
	Position* moves = new Position[AMAZONA_MAXIMUM_NUM_MOVES];
	int size = 0;
	moves = this->getMoves(curPos.row, curPos.col, size);
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

Position* AmazonaGame::getRisks(int row, int col, int& size)
{
	Position pos;
	pos.row = row;
	pos.col = col;
	return _board.getRisks(pos, size);
}

bool AmazonaGame::IsValidToMark(Position posNext, Position posMark)
{
	Position* marked = new Position[AMAZONA_MAXIMUM_NUM_MOVES];
	int size = 0;
	marked = this->getRisks(posNext.row, posNext.col, size);
	for (int i = 0; i < size; i++)
	{
		if (marked[i].row == posMark.row && marked[i].col == posMark.col)
		{
			delete[] marked;
			return true;
		}
	}
	delete[] marked;
	return false;
}

bool AmazonaGame::IsCurWinner()
{
	Stone** stones = new Stone * [AMAZONA_NUM_OF_STONES];
	stones = this->nextPlayer->getStoneArr();
	int size = 0;

	for (int i = 0; i < AMAZONA_NUM_OF_STONES; i++)
	{
		Position curPos = (*stones)->getPos();
		this->getMoves(curPos.row, curPos.col, size);
		if (size != 0)
			return false;
	}
	return true;
}

void AmazonaGame::save(ofstream& out)
{
	Game::save(out);

	_board.save(out); //_board
}

void AmazonaGame::load(ifstream& in)
{
	Game::load(in);
	_board.load(in); //_board
	addStonesToPlayers();
}

AmazonaGame::~AmazonaGame()
{
	_board.deleteBoard();
}

