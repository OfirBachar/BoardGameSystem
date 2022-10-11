#include "Game.h"
#include <iostream>
using namespace std;

Move* Game::getValidMove(Move* moves, int size, Position nextPos)
{
	for (int i = 0; i < size; i++)
	{
		if (moves[i].pos.row == nextPos.row && moves[i].pos.col == nextPos.col)
			return &moves[i];
	}
	return nullptr;
}

GameType Game::getGameType()
{ 
	return gameType;
}

void Game::setStatus(bool b)
{
	this->isFinish = b;
}

bool Game::getStatus()const
{
	return this->isFinish;
}

void Game::setWinner(Player* winner)
{
	this->winner = winner;
}

Player* Game::getCurPlayer()const
{
	return this->curPlayer;
}

int Game::getCurPlayerNum()const
{
	if (curPlayer == &p1)
		return 1;
	else
		return 2;
}

void Game::displayGame()const
{
	//print current board
	cout << "The board for the current game:" << endl << endl;
	showBoard();
	//print game status
	if (getStatus())
		cout << "Game is over." << endl << endl;
	else
	{
		cout << "Game is on." << endl << endl;
		//print the current player 
		cout << "The turn belongs to player: " << getCurPlayerNum() << endl;
	}

}

Player* Game::getNextPlayer()const
{
	return this->nextPlayer;
}

void Game::setNextPlayer(Player* p)
{
	this->nextPlayer = p;
}

void Game::setCurPlayer(Player* p)
{
	this->curPlayer = p;
}

void Game::save(ofstream& out)
{
	int currPlayer = 1;
	int nexttPlayer = 2;
	if (curPlayer == &p2)	
	{
		currPlayer = 2;
		nexttPlayer = 1;
	}
	out.write(reinterpret_cast<const char*>(&currPlayer), sizeof(currPlayer)); //curPlayer
	out.write(reinterpret_cast<const char*>(&nexttPlayer), sizeof(currPlayer)); //nextPlayer

	int winnerr = 1;
	if (winner == nullptr)
	{
		winnerr = 0;
	}
	else if (winner == &p2)
	{
		winnerr = 2;
	}
	out.write(reinterpret_cast<const char*>(&winnerr), sizeof(winnerr)); //winner

	out.write(reinterpret_cast<const char*>(&isFinish), sizeof(isFinish));	//ifFinish

}

void Game::load(std::ifstream& in)
{

	int currPlayer;
	int nexttPlayer;
	in.read(reinterpret_cast<char*>(&currPlayer), sizeof(currPlayer)); //curPlayer
	in.read(reinterpret_cast<char*>(&nexttPlayer), sizeof(currPlayer)); //nextPlayer
	
	curPlayer = &p1;
	nextPlayer = &p2;
	if (currPlayer == 2 && nexttPlayer == 1)
	{
		curPlayer = &p2;
		nextPlayer = &p1;
	}

	int winnerr;
	winner = &p2;
	in.read(reinterpret_cast<char*>(&winnerr), sizeof(winnerr)); //winner	
	if (winnerr == 0)
	{
		winner = nullptr;
	}
	else if (winnerr == 2)
	{
		winner = &p2;
	}

	in.read(reinterpret_cast<char*>(&isFinish), sizeof(isFinish));	//ifFinish

}
