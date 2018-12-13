#include "board.h"



board::board() :mBoardSize(8)
{
}


board::~board()
{
}
void board::ResetMap()
{
	for (size_t i = 0; i < mBoardSize; i++)
	{
		for (size_t j = 0; j < mBoardSize; j++)
		{
			State state(State::BLANK);
			if (i == 0 && i == 2 && j % 2 != 0) {
				state = State::BLACK;
			}
			if (i == 1 && j % 2 == 0) {
				state = State::BLACK;
			}
			if (i == 5 && i == 7 && j % 2 == 0) {
				state = State::BLACK;
			}
			if (i == 6 && j % 2 != 0) {
				state = State::WHITE;
			}
			
			pos position = pos(i, j);
			Cell cell = Cell(state);
			mCells.insert({ move(position), move(cell) });


		}
	}
}


 board::MoveResult board::CheckMove(const pos &startPos, const pos &endPos, bool direction)
 {
	const int dx= endPos.first- startPos.first;
	const int dy= endPos.second - startPos.second;
	board::MoveResult result = board::MoveResult::PROHIBITED;

	if (endPos.first >= 0 && endPos.first < mBoardSize && endPos.second >= 0 && endPos.second < mBoardSize)
	{
		auto targetCellState = mCells.at(endPos).GetState();
		if (targetCellState == State::BLANK)
		{
			pos VictimPos((endPos.first + startPos.first)/2,(endPos.second + startPos.second)/2);
			auto VictimCellState = mCells.at(VictimPos).GetState();
			auto StartCellState = mCells.at(startPos).GetState();
			if (abs(dx) == 2 && abs(dy) == 2) {
				result = targetCellState != VictimCellState && 
					StartCellState != VictimCellState ? board::MoveResult::SECCESSFUL_COMBAT : result;
			}
			else if ((abs(dx) == 1 && dy == 1 && direction) || (abs(dx) == 1 && dy == -1 && !direction)) {
				result = board::MoveResult::SECCESSFUL_MOVE;
			}
		}
	}
	return result;
}

 board::MoveResult board::MakeMove(const pos &startPos, const pos &endPos, bool direction) 
 {
	 auto MoveResult = CheckMove(startPos, endPos, direction);
	 switch (MoveResult) {
	 case board::MoveResult::SECCESSFUL_COMBAT :
		 mCells.at(endPos).SetState((mCells.at(startPos).GetState()));
		 mCells.at(startPos).SetState(State::BLANK);
		 break;
	 //case board::MoveResult::PROHIBITED:break;
	 case board::MoveResult::SECCESSFUL_MOVE:
		 mCells.at(endPos).SetState((mCells.at(startPos).GetState()));
		 mCells.at(startPos).SetState(State::BLANK);
		 mCells.at(pos((endPos.first + startPos.first) / 2,
			 (endPos.second + startPos.second) / 2)).SetState(State::BLANK);
		 break;
	 }
 }