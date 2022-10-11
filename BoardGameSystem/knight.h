#include "stone.h"

class Knight : public Stone
{


public:
	virtual Position* getpossibleMoves(int& size)override;
	virtual Position* getpossibleRisks(int& size)override;
	void save(std::ofstream& out);
	void load(std::ifstream& in);
};