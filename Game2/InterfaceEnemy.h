#pragma once
#include "libraries.h"

class InterfaceEnemy {
public:
	virtual void initShape(const RenderWindow& window) = 0;

	//Accessors
	virtual const Sprite getShape() const = 0;
	virtual const int& getType() const = 0;

	//Functions
	virtual void render(RenderTarget& target) = 0;
};