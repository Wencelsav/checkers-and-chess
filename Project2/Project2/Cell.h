#pragma once
#include <utility>
using namespace std;
using pos = pair<size_t, size_t>;
enum class State { BLACK , WHITE, BLANK};
class Cell
{
	State mState;
public:
	Cell(State state);
	~Cell();
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
};

