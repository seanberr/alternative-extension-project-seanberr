#include "Heart.h"

Heart::Heart() {}
Heart::~Heart() {}
void Heart::updateHealthDisplay(int hp, TextureManager* textMan, int heartNum)
{
	std::cout << "HP: " << hp << "\n";
	std::cout << "HeartNum: " << heartNum << "\n";
	setTexture(&textMan->getTexture("heart"));
	if (heartNum > hp)
	{
		std::cout << "Heart num is greater than HP" << "\n";
		setTexture(&textMan->getTexture("blackHeart"));
	}
	
	
	
}