#include "gameControler.h"
#include "definitions.h"
#include <iostream>
#include <fstream>
#include <string>
#include "damkaGame.h"
#include "amazonaGame.h"
#include "chessGame.h"

using namespace std;

//show menu
UserChoice GameControler::showMenuAndGetUserChoice()
{
	int choice = -1;

	while (choice == -1)
	{
		cout << endl << "Please choose:" << endl;
		cout << "1. Add a new game." << endl;
		cout << "2. Move to the next game." << endl;
		cout << "3. Erase the current game." << endl;
		cout << "4. Display game status." << endl;
		cout << "5. Show valid moves for stone." << endl;
		cout << "6. Show risks for stone." << endl;
		cout << "7. Add new step for the current game." << endl;
		cout << "8. Exit." << endl;
		cout << "9. Save game." << endl;
		cout << "10. Load game." << endl;

		cin >> choice;

		if (choice > 0 && choice < 11)
			return (UserChoice)choice;
		else
		{
			cout << "Invalid choice. ";
			choice = -1;
		}
	}
}

//control the game
void GameControler::runGames()
{
	UserChoice choice;

	choice = showMenuAndGetUserChoice();
	while (choice != UserChoice::Exit)
	{

		switch (choice)
		{
			//option 1
		case UserChoice::AddGame:
			addGame();
			break;

			//option 2
		case UserChoice::MoveToNextGame:
			MoveToNextGame();
			break;

			//option 3
		case UserChoice::RemoveGame:
			removeGame();
			break;

			//option 4
		case UserChoice::DisplayGame:
			displayGame();
			break;

			//option 5
		case UserChoice::ShowMoves:
			showValidMovesForStone();
			break;

			//option 6
		case UserChoice::ShowRisks:
			showRisksForStone();
			break;

			//option 7
		case UserChoice::MoveStone:
			moveStone();
			break;

			//option 9
		case UserChoice::SaveGame:
			saveGame();
			break;

			//option 10
		case UserChoice::LoadGame:
			loadGame();
			break;

		default:
			break;
		}

		choice = showMenuAndGetUserChoice();
	}
	quit();
	cout << "Thank you for playing with us, Goodbye" << endl;
}

//option 1
void GameControler::addGame()
{
	int gameType;
	cout << "Please enter game type" << endl << "1. Damka" << endl << "2. Amazones" << endl << "3. Chess" << endl;
	cin >> gameType;

	while (gameType < 1 || gameType > 3)
	{
		cout << "Invalid choice" << endl;
		cout << "Please enter game type" << endl << "1. Damka" << endl << "2. Amazones" << endl << "3. Chess" << endl;
		cin >> gameType;
	}

	Game* newGame = nullptr;

	switch ((GameType)gameType)
	{
	case GameType::DAMKA:
		//add damka game
		newGame = new DamkaGame(true);
		break;
	case GameType::AMAZONA:
		//add amazones game
		newGame = new AmazonaGame(true);
		break;
	case GameType::CHESS:
		//add chess game
		newGame = new ChessGame(true);
		break;

	default:
		break;
	}

	games.push_back(newGame);
	curGame = prev(games.end());
}

//option 2
void GameControler::MoveToNextGame()
{
	if (games.empty())
	{
		cout << "There are no games" << endl;
		return;
	}
	else
	{
		if (games.back() == *curGame)
			curGame = games.begin();
		else
			curGame++; 
	}
}

//option 3
void GameControler::removeGame()
{
	if (games.empty())
	{
		cout << "No game to erase" << endl;
		return;
	}

	list<Game*>::iterator gameToDelete = curGame;
	MoveToNextGame();
	delete[] *gameToDelete;
	games.erase(gameToDelete);
}

//option 4
void GameControler::displayGame()const
{
	(*curGame)->displayGame();
}

//option 5
void GameControler::showValidMovesForStone()const
{
	(*curGame)->showValidMovesForStone();
}

//option 6
void GameControler::showRisksForStone()const
{
	(*curGame)->showRisksForStone();
}

//option 7
void GameControler::moveStone()
{
	(*curGame)->moveStone();
}

//option 8
void GameControler::quit()
{
	list<Game*>::iterator curr = games.begin();
	list<Game*>::iterator temp ;

	while(curr!= games.end())
	{ 
		temp= curr;
		delete [] *temp;
		curr++;
	}

	games.clear();
}

//option 9
void GameControler::saveGame()
{
	string nameOfFile;
	cout << "Please enter the name of file" << endl;
	cin >> nameOfFile;

	ofstream out(nameOfFile, ios::binary | ios::out);
	if (!out.is_open())
	{
		cout << "Error with opening file to write" << endl;
		return;
	}
	GameType type = (*curGame)->getGameType();
	out.write(reinterpret_cast<const char*>(&type), sizeof(type));

	try {
		(*curGame)->save(out);
	}
	catch (runtime_error& error)
	{
		cout << "Could not save game to file. Error message: " << error.what() << endl;
	}

}

//option 10
void GameControler::loadGame()
{

	string nameOfFile;
	cout << "Please enter the name of file" << endl;
	cin >> nameOfFile;

	ifstream in(nameOfFile, ios::binary | ios::out);
	if (!in.is_open())
	{
		cout << "Error with opening file to read" << endl;
		return;
	}

	GameType gameType;
	in.read(reinterpret_cast<char*>(&gameType), sizeof(gameType));

	Game* newGame = nullptr;

	switch (gameType)
	{
	case GameType::DAMKA:
		newGame = new DamkaGame(false);
		break;
	case GameType::AMAZONA:
		newGame = new AmazonaGame(false);
		break;
	case GameType::CHESS:
		newGame = new ChessGame(false);
		break;

	default:
		break;
	}

	try {
		(newGame)->load(in);
		games.push_back(newGame);
		curGame = prev(games.end());
	}
	catch (runtime_error& error)
	{
		games.pop_back();
		delete[] newGame;
		cout << "Could not load game from file. Error message: " << error.what() << endl;
	}

}