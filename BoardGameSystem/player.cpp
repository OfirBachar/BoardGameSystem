#include "player.h"
#include "definitions.h"

void Player::addStone(Stone* stone)
{
	_stones[_numStones] = stone;
	_numStones++;
}

int Player::getNumStones()const
{
	return this->_numStones;
}

bool Player::isItMyStone(Stone* stone)const
{
	for (int i = 0; i < _numStones; i++)
	{
		if (_stones[i] == stone)
			return true;
	}
	return false;
}

void Player::removeStone(Stone* stone)
{
	int delPos, j;
	for (delPos = 0; delPos < _numStones && stone != _stones[delPos]; delPos++)
	{
		//move to the position of this stone
	}
	if (delPos == _numStones)
		// not found the stone
		return;

	for (j = delPos + 1; j < _numStones; j++)
		_stones[j - 1] = _stones[j];
	_numStones--;

}

Stone** Player::getStoneArr()
{
	return _stones;
}
