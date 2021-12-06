#pragma once
#include"InterfacePlayer.h"

enum PLAYER_ANIMATION_STATES {
	IDLE,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UPWARDS,
	MOVING_DOWNWARDS
}; 

class Player: public InterfacePlayer{
private:
	Sprite shape;
	Texture playerTexture;

	short animState;
	IntRect currentFrame;
	Clock animationTimer;

	float movementSpeed;
	int healPoint;
	int healPointMax;


	//Private functions

	virtual void initTexture();
	virtual void initVariables();
	virtual void initSprite();
	virtual void initAnimation();
public:
	//Constructors and Destructors
	Player(float x = (1024.f / 2.f - 37.f), float y = (720.f / 2.f - 41.f));
	virtual ~Player();

	//Accessors
	virtual const Sprite& getSprite() const;
	virtual const int& getHP() const;
	virtual const int& getHPMax() const;

	//Functions

	virtual void takeDamage(const int damage);
	virtual void gainHealth(const int health);

	virtual void updateWindowBoundsCollision(const RenderTarget* target);

	//Player's movements
	virtual void updateAnimation();
	virtual void updateMovement();

	virtual void update(const RenderTarget* target);
	virtual void render(RenderTarget* target);

};

