#include "definitions.h"
#include "stone.h"

class Bishop : public Stone {
private:

public:
	virtual Position* getpossibleMoves(int& size)override;
	virtual Position* getpossibleRisks(int& size)override;
	void save(std::ofstream& out);
	void load(std::ifstream& in);
};