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
// Just need to include main header file
#include "S2D/S2D.h"

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

struct Menu 
{
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
};



// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:

	//Map
	Map* _map;

	//*************PACMAN**************************

	Player* _pacman;

	//*********************START************************************************************

	Start* _start;

	//*****************************************MENU*************************************************

	Menu* _menu;

	//*********************PAUSE***************************************************************

	bool _paused;
	bool _pKeyDown;

	//**************************************STRING********************************************

	Vector2* _stringPosition;
	//**********************CHERRIES***********************************************************

	Cherry* _cherry[CHERRYCOUNT];
	const int _cCherryFrameTime;

	//cherry randomizer
	int cRandom_timer = 500;
	int Random_timer;

	//**********************ENEMY***********************************************************

	MovingEnemy* _ghost[GHOSTCOUNT];
	

	//**********************METHODS***********************************************************
	//Input methods
	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* m_state);


	//Check methods
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void CheckViewportCollision();
	void CheckGhostCollisions();

	//Update methods
	void UpdatePacman(int elapsedTime);
	void UpdateCherry(Cherry*, int elapsedTime);
	void UpdateGhost(MovingEnemy*, int elapsedTime);
	//******************************************************************************************





public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);




	bool CollisionCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
	{
		int leftPacman = x1;
		int topPacman = y1;
		int rightPacman = x1 + w1;
		int bottomPacman = y1 + h1;



		int leftCherry = x2;
		int topCherry = y2;
		int rightCherry = x2 + w2;
		int bottomCherry = y2 + h2;


		if (bottomPacman < topCherry)
		{
			return false;
		}
		if (topPacman > bottomCherry)
		{
			return false;
		}
		if (rightPacman < leftCherry)
		{
			return false;
		}
		if (leftPacman > rightCherry)
		{
			return false;
		}

		return true;
	}



	//Game runtime

};