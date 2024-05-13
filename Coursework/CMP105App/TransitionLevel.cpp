#include "TransitionLevel.h"

TransitionLevel::TransitionLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm)
{
	// store parameters in local references.
	window = hwnd;
	input = in;
	textMan = tm;
	audio = aud;
	gameState = gs;

	// set the text object
	font.loadFromFile("font/montS.ttf");
	explain.setFont(font);
	explain.setPosition(sf::Vector2f(10, 10));
	explain.setCharacterSize(40);

	// initialise background. base size: 5760, 3240
	bg.setTexture(&textMan->getTexture("redSkyBG"));
	float bgScalar = std::max(hwnd->getSize().x / 5760.f, hwnd->getSize().y / 3240.f);
	bg.setSize(sf::Vector2f(5760 * bgScalar, 3240 * bgScalar));

}

TransitionLevel::~TransitionLevel()
{
}

void TransitionLevel::handleInput(float dt)
{
	if (input->isPressed(sf::Keyboard::Enter))
	{
		switch (gameState->getCurrentState())
		{
		case State::PRE_ONE:
			nextState = State::LEVEL;
			gameState->setCurrentState(State::CHARSELECT);
			break;
		case State::PRE_TWO:
			nextState = State::RUNNER;
			gameState->setCurrentState(State::CHARSELECT);
			break; 
		case State::PRE_THREE:
			nextState = State::WIZARD;
			gameState->setCurrentState(State::CHARSELECT);
			break;
		case State::PRE_FOUR:
			nextState = State::TUTORIAL;
			gameState->setCurrentState(State::CHARSELECT);
			break;
		case State::ENDGAME:
			gameState->setCurrentState(State::TITLE);
			break;
		}
	}

		if (gameState->getCurrentState() == State::CHARSELECT)
		{
			if (input->isPressed(sf::Keyboard::Num1))
			{
				gameState->setCurrentCharacter(Character::C1);
			}

			if (input->isPressed(sf::Keyboard::Num2))
			{
				gameState->setCurrentCharacter(Character::C2);
			}

			if (input->isPressed(sf::Keyboard::Num3))
			{
				gameState->setCurrentCharacter(Character::C3);
			}

			if (input->isPressed(sf::Keyboard::Space))
			{
				gameState->setCurrentState(nextState);
			}
			
		} 
}

void TransitionLevel::update(float dt)
{
	// set text object by state.
	switch (gameState->getCurrentState())
	{
	case State::PRE_ONE:
		explain.setString("Move with WASD.\nMove in time with the claps.\nAvoid tanks and pits.\nThey are metaphors for adversary.\nThere is a checkpoint halfway round.\nIt will be yellow when enabled.\nYou cannot pause.\nYou will have assistance.\nYou will be motivated.\nIt will not be helpful.\nHit Enter.");
		break;
	case State::PRE_TWO:
		explain.setString("Kick (enter) wooden boxes.\nJump over (space) metal ones.\nYou got this.\nGood Luck.\nHit Enter");
		break;
	case State::PRE_THREE:
		explain.setString("Move with WASD.\nMove in time with the claps.\nAvoid Tanks and Pits.\nThere is a checkpoint.\nYou will be assisted.\nKind of.\nHit Enter.\nGood Luck.");
		break;
	case State::PRE_FOUR:
		explain.setString("Welcome to Unforbidden Rhythms!\nMove with WASD.\nMove in time with the claps.\nAvoid Tanks and Pits.\nThere is a checkpoint.\nHit Enter.\nGood Luck.");
		break;
	case State::CHARSELECT:
		explain.setString("Select your character!\nThere are three options:\n1. Dino Zach (1HP, Hard)\n2. Dino Chris (2HP, Easy)\n3. Dino Tomar (3HP, Baby)\nPress 1, 2, or 3 to make your selection, then press space to start.");
		break;
	case State::ENDGAME:
		runResults* results = gameState->getResults();
		std::string resultsString;
		if (results->L1Time > 0)
		{
			resultsString += "Level 1 deaths:\t\t\t" + std::to_string(results->L1Deaths) + "\n";
			resultsString += "Level 1 time:\t\t\t" + std::to_string(results->L1Time) + " seconds\n\n";
		}
		if (results->L2Time > 0)
		{
			resultsString += "Level 2 mistakes:\t\t\t" + std::to_string(results->L2Deaths) + "\n";
			resultsString += "Level 2 time:\t\t\t" + std::to_string(results->L2Time) + " seconds\n\n";
		}
		if (results->L3Time > 0)
		{
			resultsString += "Level 3 deaths:\t\t\t" + std::to_string(results->L3Deaths) + "\n";
			resultsString += "Level 3 time:\t\t\t" + std::to_string(results->L3Time) + " seconds\n";
		}
		explain.setString(resultsString + "\nPress Enter to continue.");
		break;
	}
}

void TransitionLevel::render()
{
	beginDraw();
	window->draw(bg);
	window->draw(explain);
	endDraw();
}
