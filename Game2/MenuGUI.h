#pragma once
#include "libraries.h"
#include "Game.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio.hpp"

class MenuGUI {
private:
	RenderWindow* window;
	VideoMode videoMode;

	Vector2i mousePosition;
	Vector2f mousePosView;

	bool isMenuRuns;
	bool isClickOnPlay;
	bool isClickOnExit;

	//Animation
	Texture backgroundTexture;
	Texture playButtonTexture;
	Texture exitButtonTexture;

	Sprite background;
	Sprite playButton;
	Sprite exitButton;

	//Sounds and music
	SoundBuffer clickBuffer;
	Sound clickSound;
	Music backgroundSound;

	//Private functions
	void initWindow();
	void initTextures();
	void initSprites();
	void initVariables();
	void initSounds();

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

