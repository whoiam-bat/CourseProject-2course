#pragma once
#include "Player.h"
#include "SwagBall.h"

class Game {
private:
	VideoMode videoMode;
	RenderWindow* window;

	Player player;
	string path;

	Vector2i mousePositionPixels;
	Vector2f mousePositionCoordinates;

	//Player GUI
	RectangleShape healthBar;
	RectangleShape healthBarBack;

	Font fontGUI;
	Font gameOver;

	Text guiText;

	Text healthText;
	Text endGameText;

	Texture backgroundTexture;
	Sprite background;

	Texture restartTexture;
	Sprite restartButton;

	vector<SwagBall*> swagBalls;

	//Variables for spawning balls
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;
	int points;
	int rateScore;

	//For control amount of damaging and healing enemies
	int amountDamaging;
	int maxAmountDamaging;
	int amountHealling;
	int maxAmountHealling;

	//For restart button
	bool isClickOnRestart;

	//For ending game
	bool endGame;

	bool isBeatRecord;

	//Sounds
	SoundBuffer restartBuffer;
	Sound restartSound;

	SoundBuffer healBuffer;
	Sound healSound;

	SoundBuffer damagBuffer;
	Sound damagSound;

	SoundBuffer coinBuffer;
	Sound coinSound;

	SoundBuffer deathBuffer;
	Sound deathSound;

	SoundBuffer recordBuffer;
	Sound recordSound;

	//Private functions
	void initSprite();
	void initTexture();
	void initFonts();
	void initGUI();
	void initVariables();
	void initWindow();

	void initSounds();

public:
	//Constructors and Destructors
	Game();
	~Game();

	void runGame();

	//Accessors
	const bool& getEndGame() const;

	//Functions
	void setScore();
	const bool running() const;

	void spawnSwagBalls();
	const int randBallType();

	void pollEvents();

	void updateMousePosition();

	void updateUserCollisionWithButtons();

	void updateGUI();
	void updateCollision();
	void updatePlayer();
	void update();

	void renderGUIButtons();
	void renderGUI(RenderTarget* tagret);
	void render();
};

