#include "stone.h"

class Pawn : public Stone {

	bool isFirstStep = true;

public:
	virtual Position* getpossibleMoves(int& size)override;
	virtual Position* getpossibleRisks(int& size)override;
	virtual void save(std::ofstream& out)override;
	virtual void load(std::ifstream& in)override;
};