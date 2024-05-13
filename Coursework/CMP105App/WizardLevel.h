#pragma once
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "TextureManager.h"
#include "StageGrid.h"
#include "Player.h"
#include "Heart.h"
#include "LecturEH.h"
#include <random>
#include <algorithm>

class WizardLevel : public BaseLevel
{
public:
	WizardLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm, int stage);
	~WizardLevel();

	void update(float dt) override;
	void handleInput(float dt) override;
	void render() override;

	void randomiseControls();

	void reset();
	void resetPlayer();

private:
	enum actions {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		FAIL
	};

	TextureManager* textMan;
	LecturEH* lecturer;
	StageGrid grid;
	Player player;
	GameObject gridBoard;
	GameObject target;
	GameObject moveSelected;
	GameObject progressInStep;
	GameObject targetZone;
	GameObject progressInStepBG;
	GameObject levelBG;
	GameObject controlBG;
	std::pair<int, int> playerPosition;
	actions selectedAction;
	actions lastAction;
	std::vector<GameObject> indicators;
	sf::Font font;
	std::vector<sf::Text> controls;
	sf::Vector2i start = { 0,0 };
	sf::Vector2i end = { 19, 9 };
	sf::Vector2i checkPoint{ 10, 4 };
	sf::Vector2i boardDimensions{ 20,10 };
	bool checkPointEnabled = false;
	bool stepFailed = false;
	std::vector<char> currentControls = { 'W', 'A', 'S', 'D' };

	// Default variables for level class.
	const float GRID_Y_MAX_PROPORTION = 0.6f;
	const float TEMPO = 130.0f; //Tempo of claps
	const float TIME_PER_STEP = 120 / TEMPO;	// time for each step (time between claps)
	const float TIME_FOR_ACTION = 0.30f;
	const float TIME_BUFFER = 0.25f;
	const float RESET_TIME = 1.0f;
	const float TIME_BETWEEN_CHANGES = 4.0f;
	float timeInStep = 0.f;
	bool soundPlayed = false;
	float cellDim;
	int beatsPlayed = 0;
	float damagedTimer = 0.f;
	float lastControlChange = 0.f;
	float boardTop, boardRight, boardBottom, boardLeft;

	// analytics values
	float timeTaken = 0.f;
	int misses = 0;
	int deaths = 0;

	//health system
	Heart heart1;
	Heart heart2;
	Heart heart3;

	bool characterLoaded = false;
};

