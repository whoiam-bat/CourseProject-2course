#include "SwagBall.h"

//Private functions
void SwagBall::initShape(const RenderWindow* window) {
	switch (this->type) {
	case SwagBallsTypes::DEFAULT: {
		this->defaultTexture.loadFromFile("images/coin.png");
		this->shape.setTexture(this->defaultTexture);
		this->shape.setTextureRect(IntRect(0, 0, 105, 105));
		this->shape.setScale(Vector2f(0.3, 0.3));
		break;
	}
	case SwagBallsTypes::DAMAGING: {
		this->damagingTexture.loadFromFile("images/tnt.png");
		this->shape.setTexture(this->damagingTexture);
		this->shape.setTextureRect(IntRect(39, 41, 360, 360));
		this->shape.setScale(Vector2f(0.12, 0.12));
		break;
	}
	case SwagBallsTypes::HEALING: {
		this->heallingTexture.loadFromFile("images/heart.png");
		this->shape.setTexture(this->heallingTexture);
		this->shape.setTextureRect(IntRect(0, 4, 110, 105));
		this->shape.setScale(Vector2f(0.4, 0.4));
		break;
	}
	}
	float xCoord = static_cast<float>(
		rand() % window->getSize().x - this->shape.getGlobalBounds().width
		);
	float yCoord = static_cast<float>(
		rand() % window->getSize().y - this->shape.getGlobalBounds().height
		);
	//Check out wether coordinates spawn enemy is in window
	//Check top and bottom bounds
	if(yCoord <= 0 | yCoord >= window->getSize().y) {
		yCoord = static_cast<float>(
			rand() % window->getSize().y - this->shape.getGlobalBounds().height
			);
	}
	//Check right and left bounds
	if (xCoord <= 0 | xCoord >= window->getSize().x) {
		xCoord = static_cast<float>(
			rand() % window->getSize().x - this->shape.getGlobalBounds().width
			);
	}
	Vector2f position(xCoord, yCoord);
	this->shape.setPosition(position);
}

//Constructors and Destructors
SwagBall::SwagBall(const RenderWindow* window, int type) : type(type) {
	this->initShape(window);

}
SwagBall::~SwagBall() {

}

const Sprite SwagBall::getShape() const {
	return (this->shape);
}

const int& SwagBall::getType() const { 
	return this->type;
}

//Functions
void SwagBall::render(RenderTarget* target) {
	target->draw(this->shape);
}
