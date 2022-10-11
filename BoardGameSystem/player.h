	#pragma once
#include "definitions.h"
#include "stone.h"
#include <iostream>
#include <fstream>

class Stone;

class Player {
private:
	Stone* _stones[NUM_OF_STONES] = { nullptr };
	int _numStones = 0;//logsize

public:

	int getNumStones()const;
	void addStone(Stone* stone);
	void removeStone(Stone* stone);
	bool isItMyStone(Stone* stone)const;
	Stone** getStoneArr();

};
