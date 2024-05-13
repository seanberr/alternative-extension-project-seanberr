#pragma once
#include "Framework/GameObject.h"
#include "TextureManager.h"
class Heart : public GameObject
{
public:
	Heart();
	~Heart();

	void updateHealthDisplay(int hp, TextureManager* textMan, int heartNum);


private:

};

