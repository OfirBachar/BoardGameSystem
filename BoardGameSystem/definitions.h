#pragma once
#pragma once
#include <exception>

//enum classes
enum class Winning {
	LOSE = 0,
	WIN = 1,
	NOTYET = 2
};
enum class NumPlayer {
	P1 = 0,
	P2 = 1,
	None = 2
};
enum class WasAte {
	NO = 0,
	YES = 1,
};
enum class Type {
	AMAZON = 0,
	MARKED = 1
};
enum class BoardPosStatus {
	NO_STONE = 0,
	HAS_STONE = 1
};
enum class UserChoice {
	AddGame = 1,
	MoveToNextGame = 2,
	RemoveGame = 3,
	DisplayGame = 4,
	ShowMoves = 5,
	ShowRisks = 6,
	MoveStone = 7,
	Exit = 8,
	SaveGame = 9,
	LoadGame =10
};
enum class ChessStoneType {
	QUEEN = 0,
	ROOK = 1,
	BISHOP = 2,
	KNIGHT = 3,
	PAWN = 4,
	KING = 5
};
enum class GameType {
	DAMKA = 1,
	AMAZONA,
	CHESS
};

//constexpr nums
int constexpr COLSDAMKA = 8;
int constexpr ROWSDAMKA = 8;
int constexpr COLSAMAZONES = 10;
int constexpr ROWSAMAZONES = 10;
int constexpr COLSCHESS = 8;
int constexpr ROWSCHESS = 8;
int constexpr NUM_OF_STONES = 16;
int constexpr MAXIMUM_NUM_RISKS = 2;
int constexpr MAXIMUM_NUM_MOVES_FOR_KING = 13;
int constexpr MAXIMUM_NUM_MOVES = 2;
int constexpr AMAZONA_MAXIMUM_NUM_MOVES = 36;
int constexpr AMAZONA_NUM_OF_STONES = 4;
int constexpr AMAZONA_MAXIMUM_NUM_RISKS = 36;
int constexpr CHESS_MAX_POS_MOVES = 27;

//structs
typedef struct pos {
	int row;
	int col;
}Position;

typedef struct move {
	Position pos;
	WasAte wasAte;
	Position eatenPos;
}Move;