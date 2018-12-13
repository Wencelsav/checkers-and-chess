#pragma once
#include "Cell.h"
#include <unordered_map>
using namespace std;



class board
{	const size_t mBoardSize = 8;
	unordered_map<pos, Cell> mCells;
public:
	enum class MoveResult { SECCESSFUL_MOVE, SECCESSFUL_COMBAT, PROHIBITED };
	board();
	~board();
	void ResetMap();
	MoveResult CheckMove(const pos &startPos, const pos &endPos, bool direction);
	MoveResult MakeMove(const pos &startPos, const pos &endPos, bool direction);
};

