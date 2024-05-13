#include "Player.h"
#include <iostream>

Player::Player()
{
	setPosition(sf::Vector2f(100, 100));
	setSize(sf::Vector2f(100, 100));

	// dino texture is 24x24px. Frames for walk are 4 - 9, inclusive.
	for (int i = 4; i < 10; ++i)
	{
		walk.addFrame(sf::IntRect(i * 24.f, 0.f, 24.f, 24.f));
	}
	for (int i = 0; i < 4; ++i)
	{
		kick.addFrame(sf::IntRect(i * 24.f + 240.f, 0.f, 24.f, 24.f));
	}
	damaged.addFrame(sf::IntRect(0, 0, 24, 24));
	damaged.addFrame(sf::IntRect(15 * 24, 0, 24, 24));
	damaged.setFrameSpeed(1.f / 4.f);
	currentAnimation = &walk;
	walk.setFrameSpeed(1.f / 10.f);
	//kick.setLooping(false);

	velocity = { 0,0 };
}

Player::~Player()
{
}


void Player::loadCharacter(int ch)
{

	switch (ch) {
	case 1:
		hp = 1;
		dino.loadFromFile("gfx/dinoZach.png");
		break;
	case 2: 
		hp = 2;
		dino.loadFromFile("gfx/dinoChris.png");
		break;
	case 3:
		hp = 3;
		dino.loadFromFile("gfx/dinoTomar.png");
		break;
	}

	setTexture(&dino); // set that texture to this object.

	// dino texture is 24x24px. Frames for walk are 4 - 9, inclusive.
	for (int i = 4; i < 10; ++i)
	{
		walk.addFrame(sf::IntRect(i * 24.f, 0.f, 24.f, 24.f));
	}
	for (int i = 0; i < 4; ++i)
	{
		kick.addFrame(sf::IntRect(i * 24.f + 240.f, 0.f, 24.f, 24.f));
	}
	damaged.addFrame(sf::IntRect(0, 0, 24, 24));
	damaged.addFrame(sf::IntRect(15 * 24, 0, 24, 24));
	damaged.setFrameSpeed(1.f / 4.f);
	currentAnimation = &walk;
	walk.setFrameSpeed(1.f / 10.f);
}
void Player::setJumping(float jumpH, float jumpLength)
{
	jumpTime = jumpLength;
	jumpTimeElapsed = 0;
	jumpHeight = jumpH;
}

bool Player::isKicking()
{
	return kickTimeElapsed > 0 && kickTimeElapsed < kickTime;
}

void Player::setKicking(float t)
{
	kick.setFrameSpeed(t / kick.getSize());
	kick.reset();
	currentAnimation = &kick;
	kickTime = t;
	kickTimeElapsed = 0.f;
}

bool Player::canJump() const
{
	return jumpTime == 0;
}

void Player::setFlipped(bool f)
{
	currentAnimation->setFlipped(f);
}

void Player::handleInput(float dt)
{

}

bool Player::isDamaged()
{
	return currentAnimation == &damaged;
}

void Player::setDamaged(float timer)
{
	currentAnimation = &damaged;
	damageLength = timer;
}

void Player::update(float dt)
{
	if (currentAnimation == &damaged)
		damagedTimer += dt;
	if (damagedTimer > damageLength)
	{
		currentAnimation = &walk;
		damagedTimer = 0.f;
	}

	// check for jump
	if (jumpTimeElapsed < jumpTime)
	{

		jumpTimeElapsed += dt;
		// go up.
		if (jumpTimeElapsed < jumpTime * 0.2)
		{
			move(0, -jumpHeight * dt / (jumpTime * 0.2));
		}
		// hover for a bit
		// go down.
		if (jumpTimeElapsed > jumpTime * 0.7)
		{
			move(0, jumpHeight * dt / (jumpTime * 0.3));
		}

	}
	else
	{
		jumpHeight = 0;
		jumpTimeElapsed = 0.f;
		jumpTime = 0.f;
	}

	// check for kick status.
	if (kickTime != 0)
	{
		if (kickTimeElapsed < kickTime) kickTimeElapsed += dt;
		else
		{
			currentAnimation = &walk;
			kickTime = 0.f;
			kickTimeElapsed = 0.f;
		}
	}

	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

}

int Player::getHP()
{
	return hp;
}

void Player::setHP(int h)
{
	hp = h;
}