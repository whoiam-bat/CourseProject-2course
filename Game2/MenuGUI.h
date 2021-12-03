#pragma once
#include "libraries.h"
#include "Game.h"

class MenuGUI {
private:
	RenderWindow* window;
	VideoMode videoMode;

	Vector2i mousePosition;
	Vector2f mousePosView;

	bool isMenuRuns;
	bool isClickOnPlay;
	bool isClickOnExit;

	Texture backgroundTexture;
	Texture playButtonTexture;
	Texture exitButtonTexture;

	Sprite background;
	Sprite playButton;
	Sprite exitButton;

	//Private functions
	void initWindow();
	void initTextures();
	void initSprites();
	void initVariables();
public:
	//Constructors and destructors
	MenuGUI();
	~MenuGUI();

	//Accessors
	const bool& running() const;

	//Functions
	void runMenu();

	void pollEvents();

	void updateUserCollisionWithButtons();

	void updateMousePosition();
	void update();

	void renderGUI();
	void render();


};

