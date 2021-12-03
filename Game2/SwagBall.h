#pragma once
#include "InterfaceEnemy.h"

enum SwagBallsTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class SwagBall: public InterfaceEnemy {
private:
	Sprite shape;

	Texture damagingTexture;
	Texture heallingTexture;
	Texture defaultTexture;

	//CircleShape shape;
	int type;

	//Private functions
	virtual void initShape(const RenderWindow& window);
public:
	//Constructors and Destructors
	SwagBall(const RenderWindow& window, int type);
	virtual ~SwagBall();
	
	//Accessors
	virtual const Sprite getShape() const;
	virtual const int& getType() const;


	//Functions
	virtual void render(RenderTarget& target);
};

 