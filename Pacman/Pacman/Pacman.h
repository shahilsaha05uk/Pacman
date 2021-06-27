#pragma once
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif


#include "S2D/S2D.h"
#include <iostream>
#include <fstream>
#include "Collision.h"
//New Header Includes
#include "Structures.h"


class CherryObj;

class Pacman : public Game
{
private:


	CherryObj* _cherry;

	//Characters
	Player *_pacman;
	MovingEnemy* _ghost[GHOSTCOUNT];

	//Collectibles
	Sun* _sun[SUNCOUNT];

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




