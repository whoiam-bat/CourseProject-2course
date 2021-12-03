#include "MenuGUI.h"

void MenuGUI::initWindow() {
	this->videoMode = VideoMode(1024, 720);
	this->window = new RenderWindow(this->videoMode, "Game 2", Style::Close | Style::Titlebar);

	//Defines how fast will move objects in the window
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}
void MenuGUI::initTextures() {
	this->backgroundTexture.loadFromFile("images/floor.png");
	this->playButtonTexture.loadFromFile("images/play.png");
	this->exitButtonTexture.loadFromFile("images/exit.png");
}
void MenuGUI::initSprites() {
	//Set starting parameters background sprite
	this->background.setTexture(this->backgroundTexture);
	this->background.setPosition(Vector2f(-60, -60));
	this->background.setScale(Vector2f(1.5, 1.5));

	//Set starting parameters for UI bttons
	this->playButton.setTexture(this->playButtonTexture);
	this->playButton.setPosition(Vector2f(
		this->window->getSize().x / 2.f - this->playButton.getGlobalBounds().width / 2.4f ,
		this->window->getSize().y / 2.f - this->playButton.getGlobalBounds().height
		));
	this->playButton.setTextureRect(IntRect(59, 49, 470, 170));


	this->exitButton.setTexture(this->exitButtonTexture);
	this->exitButton.setPosition(Vector2f(
		this->window->getSize().x / 2.f - this->exitButton.getGlobalBounds().width / 2.f + 5,
		this->window->getSize().y / 2.f - this->exitButton.getGlobalBounds().top
	));
	this->exitButton.setTextureRect(IntRect(10,10,330,130));
}
void MenuGUI::initVariables() {
	this->isClickOnExit = false;
	this->isClickOnPlay = false;
	this->isMenuRuns = true;
}

//Constructors and destructors
MenuGUI::MenuGUI() {
	this->initWindow();
	this->initTextures();
	this->initSprites();
	this->initVariables();
}
MenuGUI::~MenuGUI() {
	delete this->window;
}

//Accessors
const bool& MenuGUI::running() const {
	return this->window->isOpen();
}

//Functions
void MenuGUI::runMenu() {

	while (this->running()) {
		if (this->isClickOnPlay == true) {
			Game game;
			this->window->close();
			game.runGame();
		}
		else if (this->isClickOnExit == true) {
			this->window->close();
		}
		else {
			this->pollEvents();
			this->update();
			this->render();
		}
	}
}

void MenuGUI::pollEvents() {
	Event ev;
	while (this->window->pollEvent(ev)) {
		switch (ev.type) {
		case (Event::Closed): {
			this->window->close();
			break;
		}
		case (Event::KeyPressed): {
			if (ev.key.code == Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
		}
	}
}

void MenuGUI::updateMousePosition() {
	/***
	* Updates the mouse positions:
	*	relative to the window
	*/
	this->mousePosition = Mouse::getPosition(*this->window);

	//Takes mouse position on screen and converts pixels to coordinates and writes in mousePosView variable
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosition);
}
void MenuGUI::updateUserCollisionWithButtons() {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (this->playButton.getGlobalBounds().contains(this->mousePosView)) {
			this->isClickOnPlay = true;
		}
		else if (this->exitButton.getGlobalBounds().contains(this->mousePosView)) {
			this->isClickOnExit = true;
		}
	}
}
void MenuGUI::update() {
	this->pollEvents();
	this->updateMousePosition();
	this->updateUserCollisionWithButtons();
}

void MenuGUI::renderGUI() {
	this->window->draw(this->playButton);
	this->window->draw(this->exitButton);
}
void MenuGUI::render() {
	this->window->clear();

	//Render background
	this->window->draw(this->background);

	//Render UI buttons
	this->renderGUI();

	this->window->display();
}
