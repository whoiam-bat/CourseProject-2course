#pragma once
#include "libraries.h"

class InterfacePlayer {

public:

	virtual void initTexture() = 0;
	virtual void initVariables() = 0;
	virtual void initSprite() = 0;
	virtual void initAnimation() = 0;
	//Accessors
	virtual const Sprite& getSprite() const = 0;
	virtual const int& getHP() const = 0;
	virtual const int& getHPMax() const = 0;

	//Functions
	virtual void takeDamage(const int damage) = 0;
	virtual void gainHealth(const int health) = 0;

	virtual void updateWindowBoundsCollision(const RenderTarget* target) = 0;
	virtual void updateAnimation() = 0;
	virtual void updateMovement() = 0;

	virtual void update(const RenderTarget* target) = 0;
	virtual void render(RenderTarget* target) = 0;
};
