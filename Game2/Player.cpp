#include "Player.h"

//Private functions
void Player::initTexture() {
	if (!this->playerTexture.loadFromFile("images/player.png")) {
		cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file.\n";
	}
}
void Player::initVariables() {
	this->movementSpeed = 1.5f;
	this->healPointMax = 10;
	this->healPoint = this->healPointMax;
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}
void Player::initSprite() {
	/*this->shape.setFillColor(Color::Green);
	this->shape.setSize(Vector2f(50.f, 50.f));*/
	this->shape.setTexture(this->playerTexture);
	this->currentFrame = IntRect(48, 5, 46, 48);
	this->shape.setTextureRect(this->currentFrame);

	this->shape.setScale(Vector2f(1.7, 1.7));
}
void Player::initAnimation() {
	this->animationTimer.restart();
}


//Constructors and Destructors
Player::Player(float x, float y) {
	//Setting starting position for player
	this->shape.setPosition(x, y);
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initVariables();
}
Player::~Player() {
	
}

//Accessors
const Sprite& Player::getSprite() const {
	return this->shape;
}
const int& Player::getHP() const {
	return this->healPoint;
}
const int& Player::getHPMax() const {
	return this->healPointMax;
}

//Functions
void Player::takeDamage(const int damage) {
	if (this->healPoint > 0) {
		this->healPoint -= damage;
	}
	if (this->healPoint < 0) {
		this->healPoint = 0;
	}
}
void Player::gainHealth(const int health) {
	if (this->healPoint < this->healPointMax) {
		this->healPoint += health;
	}
	if (this->healPoint >= this->healPointMax) {
		this->healPoint = this->healPointMax;
	}
}

void Player::updateWindowBoundsCollision(const RenderTarget* target) {
	/*FloatRect has 4 values:
		- left: x coordinate
		- top: y coordinate
		- height / width
	*/
	//Left bound collision
	if (this->shape.getGlobalBounds().left + 10.f <= 0.f) {
		this->shape.setPosition(-10.f, this->shape.getGlobalBounds().top);
	}
	//Right bound collision 
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width - 11.f >= target->getSize().x) {
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width + 11.f, this->shape.getGlobalBounds().top);
	}
	//Top bound collision
	if (this->shape.getGlobalBounds().top <= 0.f) {
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}
	//Bottom bound collision 
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y) {
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}
}
void Player::updateMovement() {

	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	//Left movement
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		this->shape.move(-this->movementSpeed, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	//Right movement
	else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		this->shape.move(this->movementSpeed, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	//Upwards movement
	else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		this->shape.move(0.f, -this->movementSpeed);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UPWARDS;
	}
	//Downwards movemnt
	else  if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		this->shape.move(0.f, this->movementSpeed);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_DOWNWARDS;
	}
}

void Player::updateAnimation() {
	if (this->healPoint <= 0) {
		this->currentFrame.top = 342;
		this->currentFrame.left = 486;
		this->currentFrame.width = 35;
		this->currentFrame.height = 42;
		this->shape.setTextureRect(this->currentFrame);
	}
	else {
		if (this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWNWARDS) {
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
				this->currentFrame.top = 0.f;
				this->currentFrame.left += 48.f;
				if (this->currentFrame.left >= 144.f) {
					this->currentFrame.left = 0;
				}
				this->animationTimer.restart();
				this->shape.setTextureRect(this->currentFrame);
			}
		}
		else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
				this->currentFrame.top = 48.f;
				this->currentFrame.left += 48.f;
				if (this->currentFrame.left >= 144.f) {
					this->currentFrame.left = 0;
				}
				this->animationTimer.restart();
				this->shape.setTextureRect(this->currentFrame);
			}
		}
		else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
				this->currentFrame.top = 98.f;
				this->currentFrame.left += 48.f;
				if (this->currentFrame.left >= 144.f) {
					this->currentFrame.left = 0;
				}
				this->animationTimer.restart();
				this->shape.setTextureRect(this->currentFrame);
			}
		}
		else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_UPWARDS) {
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
				this->currentFrame.top = 148.f;
				this->currentFrame.left += 48.f;
				if (this->currentFrame.left >= 144.f) {
					this->currentFrame.left = 0;
				}
				this->animationTimer.restart();
				this->shape.setTextureRect(this->currentFrame);
			}
		}
	}
}
void Player::update(const RenderTarget* target) {
	//Keyboard input
	this->updateMovement();
	this->updateAnimation();
	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(RenderTarget* target) {
	target->draw(this->shape);
}




