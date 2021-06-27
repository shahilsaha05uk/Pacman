#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#define CHERRYCOUNT 1
#define GHOSTCOUNT 1
#define BOMBCOUNT 1
#define SUNCOUNT 1


// Just need to include main header file
#include "S2D/S2D.h"
#include <iostream>
#include <fstream>
// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

//Structures

struct Player
{
	const float _cPacmanSpeed;
	const int _cPacmanFrameTime;

	bool dead;

	int _pacmanFrame;
	int _pacmanCurrentFrameTime;
	Vector2* _pacmanPosition;
	Rect* _pacmanSourceRect;
	Texture2D* _pacmanTexture;
	int _pacmanDirection;
	Texture2D* _deadTexture;
	Vector2* _DeadpacmanPosition;
	Rect* _DeadpacmanSourceRect;
	int _deadFrameCount;
	float speedMultiplier;
};

struct Cherry
{

	// My Cherry variables

	Vector2* _cherry_position;
	Texture2D* _cherries;
	Rect* _cherryRect;
	Vector2* offCherryPosition;

	int _cherrytotalFrames;
	int CurrentFrameTime;
	int _randCherryFrameTime;
	int frameCount;
	

	Texture2D* cherryTex;
};
struct Sun
{
	Texture2D* _sunTexture;
	Vector2* _sunPosition;
	Rect* _sunRect;

	int _sunTotalFrames;
	int _sunCurrentFrame;
	int _cSunCurrentFrameTime;
	int _sunCurrentFrameTime;
	int _sunFrameCount;


};

struct MovingEnemy
{
	Vector2* _ghostPosition;
	Texture2D* _ghostTexture;
	Rect* _ghostRect;
	int _ghostDirection;
	float _ghostSpeed;
	int _ghost1_frame;
	int i_frames;

	Rect* _ghost2Rect;
	Vector2* _ghost2Position;
	int _ghost2Direction;

	//int randomtime = rand() % 5250;
	int _cghostDirecttionTime = 3000;
	int _ghostDirectionTime;
	int _ghostRandomDirection;
};

struct Map
{
	Vector2* _mapPosition;
	Rect* _mapRectangle;
	Texture2D* _mapTexture;
};

struct Start
{
	Texture2D* _startBackground;
	Rect* _startRectangle;
	Vector2* _startStringPosition;
	bool _started;
	bool _SpaceKeyDown;
};

struct GameOver
{
	Texture2D* _gameOverBackground;
	Rect* _gameOverRectangle;
	Vector2* _gameOverPosition;
	bool _gameOver;
	bool _RkeyDown;


};

struct Menu 
{
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
};

struct Bomb
{
	Texture2D* _bombTexture;
	Vector2* _bombPosition;
	Rect* _bombRect;

	//frames
	int _bombTotalFrames;
	int _bombCurrentFrameTime;
	int _cBombFrameTime;
	int _bombFrameCount;

	int _bombBlastTotalFrames;
	int _bombBlastCurrentFrameTime;
	int _cBombBlastFrameTime;
	int _bombBlastFrameCount;
	bool _CanBlast=false;

	Rect* _bombBlastRect;
	Vector2* _bombBlastPosition;
	Texture2D* _blastTexture;
};

struct Sound
{
	SoundEffect* _popSound;
	SoundEffect* _pauseSound;
	SoundEffect* _backgroundSound;
	SoundEffect* _startSound;
	SoundEffect* _bombBlast;
	SoundEffect* _sunSound;

};

struct Stats
{
	int _cherryscore;
	int _sunscore;
	int _finalscore;

	int _cherryCollisionCount=0;
	int _sunCollisionCount=0;
	Vector2* _collisionStatsPosition;
	const int sunpoint = 10;
	const int cherrypoint = 5;
	
};

struct Tiles
{
	Texture2D* _tilesTecture;
	Vector2* _tilesPosition;
	Rect* _tilesRect;
};


// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:

	//Characters
	Player *_pacman;
	MovingEnemy* _ghost[GHOSTCOUNT];

	//Collectibles
	Sun* _sun[SUNCOUNT];
	Cherry** _cherry;

	//Explosives
	Bomb* _bomb[BOMBCOUNT];

	//Sounds
	Sound* _sound;

	//Stats
	Stats* _stats;
	//UI
	Start* _start;
	GameOver* _gameOver;
	Menu* _menu;

	//Tiles
	Tiles* _tiles;


	//Extra Variables
	Texture2D* _restartTexture;
	Vector2* _restartPosition;
	Rect* _restartRect;

	bool _paused;
	bool _pKeyDown;
	bool _returnKeyDown;

	Vector2* _stringPosition;

	const int _cCherryFrameTime;
	int cRandom_timer = 500;
	int Random_timer;


	//**********************METHODS***********************************************************
	//Input methods
	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* m_state);

	//Check methods
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void CheckViewportCollision();
	bool CheckGhostCollisions(int pac_x1, int pac_y1, int pac_w1, int pac_h1, int ghost_x2, int ghost_y2, int ghost_w2, int ghost_h2);

	//Update methods;;
	void UpdatePacman(int elapsedTime);
	void UpdateCherry(Cherry*, int elapsedTime);
	void UpdateGhost(MovingEnemy*, int elapsedTime);
	void UpdateSun(Sun*, int elapsedTime);
	void UpdateBomb(Bomb*, int elapsedTime);
	void DeadAnimation(int elapsedTime);

	void gameover();
	//******************************************************************************************

	void ChaseCheck(int elapsedTime);
	void SetLooping(bool loop);
	bool CollisionCherryCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool CollisionSunCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool CheckBombCollisions(int pac_x1, int pac_y1, int pac_w1, int pac_h1, int bomb_x2, int bomb_y2, int bomb_w2, int bomb_h2);
	void CheckTileCollision(int elapsedTime);
	void RandomGhostDirection(MovingEnemy*, int elapsedTime);

	void ScoreTable();
public:

	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[], int _cherryCount);


	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);







};




