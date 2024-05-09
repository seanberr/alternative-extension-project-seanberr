#include <string>
// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state
// @author Paul Robertson

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class State {
	LEVEL,
	TITLE,
	PAUSE,
	CHARSELECT,
	PRE_ONE,
	PRE_TWO,
	PRE_THREE,
	ENDGAME,
	RUNNER,
	WIZARD,
	RESET
};

enum class Character {
	C1,
	C2,
	C3
};


struct runResults
{
public:
	float L1Time;
	int L1Deaths;
	float L1Success;
	float L2Time;
	int L2Deaths;
	float L2Success;
	float L3Time;
	int L3Deaths;
	float L3Success;
};

class GameState
{
public:
	// Set the current state
	void setCurrentState(State s);
	// Set the current character selected
	void setCurrentCharacter(Character c);
	// Returns the current state.
	State getCurrentState();
	// Returns the current character selected
	Character getCurrentCharacter();

	void addResult(std::string attr, float v);
	runResults* getResults();
	bool getSingleRun();
	void setSingleRun(bool t);


protected:
	Character currentCharacter;
	State currentState;
	runResults* results = new runResults();
	bool singleRun;
};