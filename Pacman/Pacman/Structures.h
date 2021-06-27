#pragma once
#include "S2D/S2D.h"


using namespace S2D;


//Others
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

	int _cherryCollisionCount = 0;
	int _sunCollisionCount = 0;
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
	bool _CanBlast = false;

	Rect* _bombBlastRect;
	Vector2* _bombBlastPosition;
	Texture2D* _blastTexture;
};

//Characters
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

//Objects
struct CherryObject
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