#include "Game.h"

void Game::initTexture() {
	this->backgroundTexture.loadFromFile("images/floor.png");
	this->restartTexture.loadFromFile("images/restart.png");
}
void Game::initSprite() {
	//Set background sprite
	this->background.setTexture(this->backgroundTexture);
	this->background.setPosition(Vector2f(-60, -60));
	this->background.setScale(Vector2f(1.5, 1.5));

	//Set restart button
	this->restartButton.setTexture(this->restartTexture);
	this->restartButton.setTextureRect(IntRect(20, 20, 470, 130));
	this->restartButton.setScale(Vector2f(0.4, 0.4));
	this->restartButton.setPosition(Vector2f(
		this->window->getSize().x / 2.f - this->restartButton.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f
	));
}
void Game::initFonts() {
	if (!this->fontGUI.loadFromFile("Fonts/gui.ttf")) {
		cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD gui.ttf\n";
	}
	if (!this->gameOver.loadFromFile("Fonts/game-over.ttf")) {
		cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD game-over.ttf\n";
	}
}
void Game::initGUI() {

	//GUI text init
	this->guiText.setFont(this->fontGUI);
	this->guiText.setPosition(Vector2f(static_cast<float>(this->window->getSize().x - 330.f), 6.f));
	this->guiText.setFillColor(Color::White);
	this->guiText.setCharacterSize(26);

	//Health text init
	this->healthText.setFont(this->fontGUI);
	this->healthText.setPosition(Vector2f(static_cast<float>(this->healthBarBack.getGlobalBounds().width / 2.f + 100.f), 4.f));
	this->healthText.setFillColor(Color::White);
	this->healthText.setCharacterSize(20);


	// Init player GUI health points
	this->healthBar.setSize(Vector2f(300.f, 25.f));
	this->healthBar.setFillColor(Color::Red);
	this->healthBar.setPosition(Vector2f(5.f, 5.f));
	this->healthBarBack = this->healthBar;
	this->healthBarBack.setFillColor(Color(25, 25, 25, 200));

	//Game over text init
	this->endGameText.setFont(this->gameOver);
	this->endGameText.setStyle(Text::Bold);
	this->endGameText.setFillColor(Color::Red);
	this->endGameText.setCharacterSize(100);
	this->endGameText.setString("Game Over!");
	this->endGameText.setPosition(
		this->window->getSize().x / 2.f - this->endGameText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->endGameText.getGlobalBounds().height * 2 
	);
}

void Game::initVariables() {

	//Set player starting position
	this->isClickOnRestart = false;
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;

	this->path = "Score.txt";
	this->setScore();

	this->maxAmountDamaging = 4;
	this->maxAmountHealling = 3;
	this->amountDamaging = 0;
	this->amountHealling = 0;

}
void Game::initWindow()  {
	this->videoMode = VideoMode(1024, 720);
	this->window = new RenderWindow(this->videoMode, "Game 2", Style::Close | Style::Titlebar);

	//Defines how fast will move objects in the window
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

//Constructors and Destructors
Game::Game() {
	this->initWindow();
	this->initTexture();
	this->initSprite();
	this->initFonts();
	this->initVariables();
	this->initGUI();
}
Game::~Game() {
	delete this->window;
}

//Gmame loop 
void Game::runGame() {
	while (this->running()) {
		this->pollEvents();
		if (this->endGame == true) {
			this->updateMousePosition();
			this->updateUserCollisionWithButtons();

			if (this->isClickOnRestart == true) {
				this->window->close();
				Game game;
				game.runGame();
			}
		}
		else {
			this->update();
		}
		this->render();
	}
}

const bool& Game::getEndGame() const {
	return this->endGame;
}

//Functions
const bool Game::running() const {
	return this->window->isOpen();//&& this->endGame == false;
}
void Game::pollEvents() {
	Event sfmlEvent;

	while (this->window->pollEvent(sfmlEvent)) {
		switch (sfmlEvent.type) {
		case (Event::Closed): {
			this->window->close();
			break;
		}
		case (Event::KeyPressed): {
			if (sfmlEvent.key.code == Keyboard::Escape) {
				this->window->close();
			}
			if (sfmlEvent.key.code == Keyboard::R) {
				this->window->close();
				Game game;
				game.runGame();
			}
			break;
		}
		}
	}
}
void Game::spawnSwagBalls() {
	//Timer
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.f;
	}
	else {
		if (this->swagBalls.size() < this->maxSwagBalls) {
			int tempType = this->randBallType();
		
			if (tempType == SwagBallsTypes::DAMAGING) {
				if (this->amountDamaging < this->maxAmountDamaging) {
					this->swagBalls.push_back(new SwagBall(*this->window, tempType));
					this->amountDamaging++;
				}
				else {
					tempType = this->randBallType();
				}
			}
			else if (tempType == SwagBallsTypes::HEALING) {
				if (this->amountHealling < this->maxAmountHealling) {
					this->swagBalls.push_back(new SwagBall(*this->window, tempType));
					this->amountHealling++;
				}
				else {
					tempType = this->randBallType();
				}
			}
			else if(tempType == SwagBallsTypes::DEFAULT){
				this->swagBalls.push_back(new SwagBall(*this->window, tempType));
			}
			this->spawnTimer = 0.f;
		}
	}
}

//Set palayer score
void Game::setScore() {
	try {
		ifstream fin(this->path);

		if (!fin.is_open()) {
			throw "! ERROR::OF::OPENING::FILE::Score.txt\n";
		}
		fin>> this->rateScore;
	}
	catch (const string& str) {
		cout << str;
	}

}

//Randomize types balls 
const int Game::randBallType() {
	int type = SwagBallsTypes::DEFAULT;

	int randValue = rand() % 100 + 1;

	if (randValue >= 60 && randValue <= 80) {
		type = SwagBallsTypes::DAMAGING;
	}
	else if (randValue > 80 && randValue <= 100) {
		type = SwagBallsTypes::HEALING;
	}

	return type;
}

void Game::updateMousePosition() {
	//Get mouse position relative window in pixels
	this->mousePositionPixels = Mouse::getPosition(*this->window);

	//Convert pixels in coordinates x, y
	this->mousePositionCoordinates = this->window->mapPixelToCoords(this->mousePositionPixels);
}
void Game::updateUserCollisionWithButtons() {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (this->restartButton.getGlobalBounds().contains(this->mousePositionCoordinates)) {
			this->isClickOnRestart = true;
		}
	}
}
void Game::updateGUI() {
	stringstream score;
	score << "Score: " << this->points << " / "
		<< this->rateScore << "\n";
	this->guiText.setString(score.str());

	stringstream health;
	health << this->player.getHP() << " / " << this->player.getHPMax() << "\n";
	this->healthText.setString(health.str());
	 

//Update player health bar 
	float healthPercent = static_cast<float>(this->player.getHP()) / this->player.getHPMax();
	this->healthBar.setSize(Vector2f(300.f * healthPercent, this->healthBar.getSize().y));
}
void Game::updateCollision()  {
	//Check the collision and delete swagBall
	for (int i = 0; i < this->swagBalls.size(); i++) {
		FloatRect playerBounds = this->player.getSprite().getGlobalBounds();
		FloatRect enemyBounds = this->swagBalls[i]->getShape().getGlobalBounds();

		if (playerBounds.intersects(enemyBounds)) {

			switch (this->swagBalls[i]->getType()) {
			case SwagBallsTypes::DEFAULT: {
				if (this->points < this->rateScore) {
					this->points++;
				}
				else {
					this->points++;
					this->rateScore++;
				}
				break;
			}
			case SwagBallsTypes::DAMAGING: {
				this->player.takeDamage(3);
				this->amountDamaging--;
				break;
			}
			case SwagBallsTypes::HEALING: {
				this->player.gainHealth(2);
				this->amountHealling--;
				break;
			}
			}

			//Remove the ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
	
}
void Game::updatePlayer() {
	this->player.update(this->window);

	if (this->player.getHP() <= 0) {
		try {
			ofstream fout(this->path);

			if (!fout.is_open()) {
				throw "! ERROR::OF::OPENING::FILE::Score.txt\n";
			}
			fout << this->rateScore;
		}
		catch (const string& str) {
			cout << str;
		}
		this->endGame = true;
	}
}
void Game::update() {
	this->spawnSwagBalls();
	this->updatePlayer();
	this->updateCollision();
	this->updateGUI();
	
	if (this->endGame == true) {
		this->updateMousePosition();
		this->updateUserCollisionWithButtons();
	}
}

void Game::renderGUIButtons() {
	//Render restart button
	this->window->draw(this->restartButton);
}
void Game::renderGUI(RenderTarget* target) {
	target->draw(this->guiText);

	target->draw(this->healthBarBack);
	target->draw(this->healthBar);
	target->draw(this->healthText);
}
void Game::render() {
	//Clear old stuff
	this->window->clear();

	//Render new stuff
	//Render player 
	this->window->draw(this->background);

	this->player.render(this->window);
	
	//Render each swagBall
	for (auto i : this->swagBalls) {
		i->render(*this->window);
	}

	//Render text
	this->renderGUI(this->window);

	//Render game over text
	if (this->endGame == true) {
		this->window->draw(this->endGameText);
		this->renderGUIButtons();
	}

	this->window->display();
}
