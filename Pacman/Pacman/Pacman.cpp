#include "Pacman.h"
#include <sstream>
#include <time.h>
#include <iostream>
#include<fstream>
#include "CherryObj.h"
//local variable

using namespace std;
using namespace Audio;
using namespace S2D;


Pacman::Pacman(int argc, char* argv[], int _cherryCount) : Game(argc, argv), _cCherryFrameTime(100)
{

	_cherry = new CherryObj();



	//Structures
	_pacman = new Player{0.5f, 150};
	_start = new Start();
	_menu = new Menu();
	_sound = new Sound();
	_gameOver = new GameOver();
	_stats = new Stats();
	
	ifstream inFile("Scores.txt");
	ofstream outFile("Scores.txt");
	int scoreStore;

	//bool INPUT Flag
	bool inputFlag;


	//Stats Variable
	_stats->_cherryscore = 0;
	_stats->_finalscore = _stats->_cherryscore+ _stats->_sunscore;
	_stats->_sunscore = 0;
	
	//Tiles
	for (int i = 0; i < 4; i++)
	{
		_tiles = new Tiles[4];
	}



	//Sun Variables
	for (int i = 0; i < SUNCOUNT; i++)
	{
		_sun[i] = new Sun();
		_sun[i]->_cSunCurrentFrameTime = 100;
		_sun[i]->_sunCurrentFrame = 0;
		_sun[i]->_sunFrameCount = rand() % 2;
		_sun[i]->_sunTotalFrames = 2;
		_sun[i]->_sunCurrentFrameTime = rand() % 500 + 10;
	}



	//Ghost Initialization
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghost[i] = new MovingEnemy();
		_ghost[i]->_ghostDirection = 0;
		_ghost[i]->_ghostSpeed = 0.1f;
		_ghost[i]->_ghost1_frame = 2;
		_ghost[i]->i_frames = 0;
		_ghost[i]->_ghostDirectionTime = 0;
		srand(time(NULL));
	}

	// Bomb
	for (int i = 0; i < BOMBCOUNT; i++)
	{
		_bomb[i] = new Bomb();
		_bomb[i]->_bombCurrentFrameTime = 0;
		_bomb[i]->_bombFrameCount = 0;
		_bomb[i]->_bombTotalFrames = 10;
		_bomb[i]->_cBombFrameTime = 75;

		_bomb[i]->_bombBlastTotalFrames = 6;
		_bomb[i]->_bombBlastCurrentFrameTime = 0;
		_bomb[i]->_cBombBlastFrameTime = 100;
		_bomb[i]->_bombBlastFrameCount = 4;
		_bomb[i]->_CanBlast = false;
	}




	//Pause, Start and GameOver
	_paused = false;
	_pKeyDown = false;
	_start->_started = false;
	_start->_SpaceKeyDown = false;
	_gameOver->_gameOver = false;
	_returnKeyDown = false;



	// Pacman Directions
	_pacman->_pacmanDirection = 0;

	//Animation Variables
	_pacman->_pacmanCurrentFrameTime = 0;
	_pacman->_pacmanFrame = 0;
	_pacman->speedMultiplier = 1.0f;
	_pacman->dead = false;

	//Initialise important Game aspects
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();



	if (!Audio::IsInitialised())
	{
		cout << "Audio is not initialised " << endl;
	}
	if (!_sound->_popSound->IsLoaded())
	{
		cout << "_pop member sound effect not loaded " << endl;
	}


	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();

}

Pacman::~Pacman()
{
	delete _pacman->_pacmanTexture;
	delete _pacman->_pacmanSourceRect;
	for (int i = 0; i < BOMBCOUNT; i++)
	{
		delete _bomb[i];
		delete _bomb[i]->_bombPosition;
		delete _bomb[i]->_bombTexture;
		delete _bomb[i]->_bombRect;
		delete _bomb[i]->_bombBlastPosition;
		delete _bomb[i]->_bombBlastRect;

		if (_gameOver->_gameOver)
		{
			delete _bomb[i]->_bombPosition;
			delete _bomb[i]->_bombTexture;
			delete _bomb[i]->_bombRect;
			delete _pacman->_pacmanPosition;
			delete _pacman->_pacmanSourceRect;
			delete _pacman->_pacmanTexture;
			delete _pacman->_deadTexture;
		}

	}
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		delete _ghost[i]->_ghostPosition;
		delete _ghost[i]->_ghostRect;
		delete _ghost[i]->_ghostTexture;
	}
	delete _sound->_popSound;
	delete _sound->_pauseSound;
	delete _sound->_backgroundSound;
	delete _gameOver->_gameOverBackground;
	delete _gameOver->_gameOverRectangle;
	delete _gameOver->_gameOverPosition;

	for (int i = 0; i < SUNCOUNT; i++)
	{
		delete _sun[i]->_sunPosition;
		delete _sun[i]->_sunRect;
		delete _sun[i]->_sunTexture;
	}

	for (int i = 0; i < 4; i++)
	{
		delete _tiles[i]._tilesPosition;
		delete _tiles[i]._tilesRect;
		delete _tiles[i]._tilesTecture;
	}
}

void Pacman::LoadContent()
{

	//Set my Start Menu Parameters
	_start->_startBackground = new Texture2D();
	_start->_startBackground->Load("Textures/Transparency.png", false);
	_start->_startRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_start->_startStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	//Set my Pause Menu Parameters
	_menu->_menuBackground = new Texture2D();
	_menu->_menuBackground->Load("Textures/Transparency.png", false);
	_menu->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_menu->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);
	// Load Pacman
	_pacman->_pacmanTexture = new Texture2D();
	_pacman->_pacmanTexture->Load("Textures/Pacman.png", false);
	_pacman->_pacmanPosition = new Vector2(500.0f, 250.0f);
	_pacman->_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_pacman->_deadTexture = new Texture2D();
	_pacman->_deadTexture->Load("Textures/pacmanDestroy.png", false);
	_pacman->_DeadpacmanPosition = new Vector2(32.0f, 250.0f);
	_pacman->_DeadpacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);


	_cherry->Load();
	//Gave Over
	_gameOver->_gameOverBackground = new Texture2D();
	_gameOver->_gameOverBackground->Load("Textures/Gameover.png", false);
	_gameOver->_gameOverRectangle = new Rect(0,0, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_gameOver->_gameOverPosition = new Vector2(0, 0);

	//Load Enemy
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghost[i]->_ghostTexture = new Texture2D();
		_ghost[i]->_ghostTexture->Load("Textures/3sprites.png", false);
		_ghost[i]->_ghostPosition = new Vector2(100,250);
		_ghost[i]->_ghostRect = new Rect(0.0f, 0.0f, 32, 32);

		_ghost[i]->_ghost2Position = new Vector2(0,0);
		_ghost[i]->_ghost2Rect = new Rect(64.0f, 0.0f, 32, 32);
	}

	//Sounds
	_sound->_popSound = new SoundEffect();
	_sound->_pauseSound = new SoundEffect();
	_sound->_backgroundSound = new SoundEffect();
	_sound->_startSound = new SoundEffect();
	_sound->_bombBlast = new SoundEffect();
	_sound->_sunSound = new SoundEffect();

	_sound->_popSound->Load("Sounds/pop.wav");
	_sound->_pauseSound->Load("Sounds/pause.wav");
	_sound->_backgroundSound->Load("Sounds/_background.wav");
	_sound->_startSound->Load("Sounds/start.wav");
	_sound->_bombBlast->Load("Sounds/blast.wav");
	_sound->_sunSound->Load("Sounds/sun.wav");

	//Stats
	_stats->_collisionStatsPosition = new Vector2(786, 662);

	////Bomb
	for (int i = 0; i < BOMBCOUNT; i++)
	{
		_bomb[i]->_bombTexture = new Texture2D();
		_bomb[i]->_bombTexture->Load("Textures/BombBlast.png", false);
		_bomb[i]->_bombPosition = new Vector2((rand() % Graphics::GetViewportWidth()-32), (rand() % Graphics::GetViewportHeight()-32));
		_bomb[i]->_bombRect = new Rect(10.0f, 10.0f, 32, 32);

		//Blast effect
		_bomb[i]->_bombBlastRect = new Rect(200.0f, 200.0f, 32, 32);
		_bomb[i]->_bombBlastPosition = new Vector2((rand() % Graphics::GetViewportWidth()-32), (rand() % Graphics::GetViewportHeight()-32));
	}


	//Sun
	Texture2D* sunTex = new Texture2D();
	sunTex->Load("Textures/Sun.png", false);
	for (int i = 0; i < SUNCOUNT; i++)
	{
		_sun[i]->_sunPosition = new Vector2(200.0f, 200.0f);
		_sun[i]->_sunPosition = new Vector2((rand() % Graphics::GetViewportWidth()-32), (rand() % Graphics::GetViewportHeight()-32));
		_sun[i]->_sunRect = new Rect(0, 0, 32, 32);
		_sun[i]->_sunTexture = new Texture2D();
		_sun[i]->_sunTexture = sunTex;
		_sun[i]->_sunTexture->Load("Textures/Sun.png", true);
	}

	//Tiles Load
	for (int i = 0; i < 4; i++)
	{
		if (i == 0) //Top
		{
			_tiles[i]._tilesTecture = new Texture2D();
			_tiles[i]._tilesTecture->Load("Tiles/X_up.png",false);
			_tiles[i]._tilesPosition = new Vector2(0,0);
			_tiles[i]._tilesRect = new Rect(0, 0, 448, 64);
		}
		if (i == 1) //Bottom
		{
			_tiles[i]._tilesTecture = new Texture2D();
			_tiles[i]._tilesTecture->Load("Tiles/X_down.png", false);
			_tiles[i]._tilesPosition = new Vector2(0, 704);
			_tiles[i]._tilesRect = new Rect(0, 0, 448, 64);
		}
		if (i == 2) //Left
		{
			_tiles[i]._tilesTecture = new Texture2D();
			_tiles[i]._tilesTecture->Load("Tiles/Y_left.png", false);
			_tiles[i]._tilesPosition = new Vector2(0, 256);
			_tiles[i]._tilesRect = new Rect(0, 0, 64, 448);
		}
		if (i == 3) //Right
		{
			_tiles[i]._tilesTecture = new Texture2D();
			_tiles[i]._tilesTecture->Load("Tiles/Y_right.png", false);
			_tiles[i]._tilesPosition = new Vector2(960, 0);
			_tiles[i]._tilesRect = new Rect(0, 0, 64, 448);
		}
	}
	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);
}
enum class S2D_API ButtonState
{
	RELEASED = 0,
	PRESSED
};


//Input methods
void Pacman::Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* m_state)
{

	//Storing the calculation in a single variable
	float _pacmanSpeed = _pacman->_cPacmanSpeed * elapsedTime * _pacman->speedMultiplier;
	
	if (_start->_started == true && _gameOver->_gameOver== false)
	{
		// Movements
		if (state->IsKeyDown(Input::Keys::D))
		{
			_pacman->_pacmanPosition->X += _pacmanSpeed; //Moves Pacman across X axis
			_pacman->_pacmanDirection = 0;
		}
		else if (state->IsKeyDown(Input::Keys::S))
		{
			_pacman->_pacmanPosition->Y += _pacmanSpeed; //Moves Pacman across -Y axis
			_pacman->_pacmanDirection = 1;
		}
		else if (state->IsKeyDown(Input::Keys::A))
		{
			_pacman->_pacmanPosition->X -= _pacmanSpeed; //Moves Pacman across -X axis
			_pacman->_pacmanDirection = 2;
		}
		else if (state->IsKeyDown(Input::Keys::W))
		{
			_pacman->_pacmanPosition->Y -= _pacmanSpeed; //Moves Pacman across -Y axis
			_pacman->_pacmanDirection = 3;
		}
		if (state->IsKeyDown(Input::Keys::LEFTSHIFT))
		{
			//Apply Multiplier
			_pacman->speedMultiplier = 2.0f;
		}
		else
		{
			// Reset multiplier
			_pacman->speedMultiplier = 1.0f;
		}

		//for (int i = 0; i < CHERRYCOUNT; i++)
		//{
		//	Random_timer += elapsedTime;
		//	if (Random_timer > cRandom_timer)
		//	{
		//		if (state->IsKeyDown(Input::Keys::R))
		//		{
		//			_cherry[i]->_cherry_position->X = rand() % Graphics::GetViewportWidth();
		//			_cherry[i]->_cherry_position->Y = rand() % Graphics::GetViewportHeight();
		//			Random_timer = 0;
		//		}
		//	}
		//}
		//if (m_state->LeftButton == Input::ButtonState::PRESSED)
		//{
		//	for (int i = 0; i < CHERRYCOUNT; i++)
		//	{
		//		_cherry[i]->_cherry_position->X = m_state->X;
		//		_cherry[i]->_cherry_position->Y = m_state->Y;
		//	}
		//}
	}
}



//Update methods
void Pacman::UpdatePacman(int elapsedTime)
{
	//Changing frames time
	_pacman->_pacmanSourceRect->Y = _pacman->_pacmanSourceRect->Height * _pacman->_pacmanDirection;
	_pacman->_pacmanCurrentFrameTime += elapsedTime;
	if (_pacman->_pacmanCurrentFrameTime > _pacman->_cPacmanFrameTime) {
		_pacman->_pacmanFrame++;
		if (_pacman->_pacmanFrame >= 4) {
			_pacman->_pacmanFrame=0;
		}
		_pacman->_pacmanCurrentFrameTime = 0;
	}
	_pacman->_pacmanSourceRect->X = _pacman->_pacmanSourceRect->Width * _pacman->_pacmanFrame;

	if (_pacman->dead)
	{
		DeadAnimation(elapsedTime);
	}

}
void Pacman::DeadAnimation(int elapsedTime)
{
	if (_pacman->dead)
	{
		if (_pacman->_pacmanCurrentFrameTime > _pacman->_cPacmanFrameTime) {
			_pacman->_pacmanFrame++;
			_pacman->_pacmanCurrentFrameTime = 0;
		}
		_pacman->_DeadpacmanSourceRect->X = _pacman->_DeadpacmanSourceRect->Width * _pacman->_deadFrameCount;
	}
}

//void Pacman::UpdateCherry(Cherry*, int elapsedTime)
//{
//	for (int i = 0; i < CHERRYCOUNT; i++)
//	{
//		_cherry[i]->CurrentFrameTime += elapsedTime;
//		if (_cherry[i]->CurrentFrameTime > _cCherryFrameTime)
//		{
//			_cherry[i]->frameCount++;
//			if (_cherry[i]->frameCount >= 2) {
//				_cherry[i]->frameCount = 0;
//			}
//			_cherry[i]->CurrentFrameTime = 0;
//
//			_cherry[i]->_cherryRect->X = _cherry[i]->_cherryRect->Width * _cherry[i]->frameCount;
//			_cherry[i]->_cherryRect->Y = _cherry[i]->_cherryRect->Height * _cherry[i]->frameCount;
//
//		}
//	}
//}

void Pacman::UpdateSun(Sun*, int elapsedTime)
{
	for (int i = 0; i < SUNCOUNT; i++)
	{
			_sun[i]->_sunCurrentFrameTime += elapsedTime;
			if (_sun[i]->_sunCurrentFrameTime > _sun[i]->_cSunCurrentFrameTime)
			{
				_sun[i]->_sunFrameCount++;
				if (_sun[i]->_sunFrameCount > 2) {
					_sun[i]->_sunFrameCount = 0;
				}
				_sun[i]->_sunCurrentFrameTime = 0;

				_sun[i]->_sunRect->X = _sun[i]->_sunRect->Width * _sun[i]->_sunFrameCount;
				_sun[i]->_sunRect->Y = _sun[i]->_sunRect->Height * _sun[i]->_sunFrameCount;

			}
	}
}

void Pacman::UpdateBomb(Bomb*, int elapsedTime)
{
	for (int i = 0; i < BOMBCOUNT; i++)
	{

		if (CheckBombCollisions(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _bomb[i]->_bombPosition->X, _bomb[i]->_bombPosition->Y, _bomb[i]->_bombRect->Width, _bomb[i]->_bombRect->Height))
		{

			_bomb[i]->_bombCurrentFrameTime += elapsedTime;
			if (_bomb[i]->_bombCurrentFrameTime > _bomb[i]->_cBombBlastFrameTime)
			{
				_bomb[i]->_bombBlastFrameCount++;

				if (_bomb[i]->_bombBlastFrameCount >  3)
				{
					_pacman->dead = true;
					_gameOver->_gameOver = true;
				}
				_bomb[i]->_bombCurrentFrameTime = 0;
				_bomb[i]->_bombRect->X = _bomb[i]->_bombRect->Width * _bomb[i]->_bombBlastFrameCount;
				_bomb[i]->_bombRect->Y = _bomb[i]->_bombRect->Height * _bomb[i]->_bombBlastFrameCount;
			}
		}
		else
		{
			_bomb[i]->_bombCurrentFrameTime += elapsedTime;
			if (_bomb[i]->_bombCurrentFrameTime > _bomb[i]->_cBombFrameTime)
			{
				_bomb[i]->_bombFrameCount++;
				if (_bomb[i]->_bombFrameCount > 3)
				{
					_bomb[i]->_bombFrameCount = 0;
				}
				_bomb[i]->_bombCurrentFrameTime = 0;
				_bomb[i]->_bombRect->X = _bomb[i]->_bombRect->Width * _bomb[i]->_bombFrameCount;
				_bomb[i]->_bombRect->Y = _bomb[i]->_bombRect->Height * _bomb[i]->_bombFrameCount;
			}
		}

	}
}

void Pacman::UpdateGhost(MovingEnemy*, int elapsedTime)
{
	for (int i = 0; i < GHOSTCOUNT; i++)
	{

		RandomGhostDirection(_ghost[i],elapsedTime);
		CheckTileCollision(elapsedTime);
		
		
			

		switch (_ghost[i]->_ghostDirection)
		{
		case 0: //Right

			_ghost[i]->_ghostPosition->X += _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		case 1: //Left

			_ghost[i]->_ghostPosition->X -= _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		case 2: //Up

			_ghost[i]->_ghostPosition->Y -= _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		case 3: //Down

			_ghost[i]->_ghostPosition->Y += _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		}

		ChaseCheck(elapsedTime);

		if (_ghost[i]->_ghostPosition->X <= 0)
		{
			_ghost[i]->_ghostDirection = 0;
			break;
		}
		if (_ghost[i]->_ghostPosition->X + _ghost[i]->_ghostRect->Width >= Graphics::GetViewportWidth())
		{
			_ghost[i]->_ghostDirection = 1;
			break;
		}
		if (_ghost[i]->_ghostPosition->Y <= 0)
		{
			_ghost[i]->_ghostDirection = 3;
			break;
		}
		if (_ghost[i]->_ghostPosition->Y + _ghost[i]->_ghostRect->Width >= Graphics::GetViewportHeight())
		{
			_ghost[i]->_ghostDirection = 2;
			break;
		}

		////GHOST 2
		switch (_ghost[i]->_ghost2Direction)
		{
		case 0: //Right
			_ghost[i]->_ghost2Position->X += _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		case 1: //Left
			_ghost[i]->_ghost2Position->X -= _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		case 2: //Up
			_ghost[i]->_ghost2Position->Y -= _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		case 3: //Down
			_ghost[i]->_ghost2Position->Y += _ghost[i]->_ghostSpeed * elapsedTime;
			break;
		}
		CheckTileCollision(elapsedTime);
		if (_ghost[i]->_ghost2Position->X <= 0)
		{
			_ghost[i]->_ghost2Direction = 0;
		}
		if (_ghost[i]->_ghost2Position->X + _ghost[i]->_ghost2Rect->Width >= Graphics::GetViewportWidth())
		{
			_ghost[i]->_ghost2Direction = 1;
		}
		if (_ghost[i]->_ghost2Position->Y <= 0)
		{
			_ghost[i]->_ghost2Direction = 3;
		}
		if (_ghost[i]->_ghost2Position->Y + _ghost[i]->_ghost2Rect->Height >= Graphics::GetViewportHeight())
		{
			_ghost[i]->_ghost2Direction = 2;
		}

	}
}

void Pacman::Update(int elapsedTime)
{

	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
	cout << boolalpha;

	_cherry->Update(elapsedTime);

	if (!_start->_started)
	{
		//check for start
		CheckStart(keyboardState, Input::Keys::SPACE);
	}
	else
	{
		CheckPaused(keyboardState, Input::Keys::P);
		if (!_paused)
		{
			
			//Collisions
			CheckViewportCollision();
			CheckTileCollision(elapsedTime);
			//Input
			Input(elapsedTime, keyboardState, mouseState);

			//Updating Pacman
			UpdatePacman(elapsedTime);

			//Ghost
			for (int i = 0; i < GHOSTCOUNT; i++)
			{
				UpdateGhost(_ghost[0], elapsedTime);

				if (CheckGhostCollisions(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _ghost[0]->_ghostPosition->X, _ghost[0]->_ghostPosition->Y, _ghost[0]->_ghostRect->Width, _ghost[0]->_ghostRect->Height))
				{
					DeadAnimation(elapsedTime);
					_gameOver->_gameOver = true;
				}
			}

			//Cherry
			//for (int i = 0; i < CHERRYCOUNT; i++)
			//{
			//	UpdateCherry(_cherry[i], elapsedTime);
			//	if (CollisionCherryCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _cherry[i]->_cherry_position->X, _cherry[i]->_cherry_position->Y, _cherry[i]->_cherryRect->Width, _cherry[i]->_cherryRect->Height))
			//	{
			//		_cherry[i]->_cherry_position->X = rand() % Graphics::GetViewportWidth();
			//		_cherry[i]->_cherry_position->Y = rand() % Graphics::GetViewportHeight();
			//		Audio::Play(_sound->_popSound);
			//		_stats->_cherryCollisionCount++;
			//		_stats->_cherryscore += _stats->cherrypoint;
			//		_stats->_finalscore += _stats->_cherryscore;
			//		_stats->_cherryscore = 0;
			//	}
			//}
			

			//Sun
			for (int i = 0; i < SUNCOUNT; i++)
			{
				UpdateSun(_sun[i], elapsedTime);
				if (CollisionSunCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _sun[i]->_sunPosition->X, _sun[i]->_sunPosition->Y, _sun[i]->_sunRect->Width, _sun[i]->_sunRect->Height))
				{

					_sun[i]->_sunPosition->X = rand() % Graphics::GetViewportWidth();
					_sun[i]->_sunPosition->Y = rand() % Graphics::GetViewportHeight();
					Audio::Play(_sound->_sunSound);
					_stats->_sunCollisionCount++;
					_stats->_sunscore += _stats->sunpoint;
					_stats->_finalscore += _stats->_sunscore;
					_stats->_sunscore = 0;
				}
			}

			//Sound
			SetLooping(true);

			//Bomb
			for (int i = 0; i < BOMBCOUNT; i++)
			{
				UpdateBomb(_bomb[i], elapsedTime);
				if (_bomb[i]->_CanBlast == true)
				{
					break;
				}

				if (CheckBombCollisions(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _bomb[i]->_bombPosition->X, _bomb[i]->_bombPosition->Y, _bomb[i]->_bombRect->Width, _bomb[i]->_bombRect->Height))
				{
					Play(_sound->_bombBlast);
					_pacman->dead = true;
					_bomb[i]->_CanBlast = true;
				}
			}
		}
		else if (_paused)
		{
			SetLooping(false);
		}
	}
	ifstream inFile;
	ofstream outFile;
	bool b = false;
	if (_gameOver->_gameOver)
	{
		Stop(_sound->_backgroundSound);	
	}

}


//Draw
void Pacman::Draw(int elapsedTime)
{

	// Allows us to easily create a string
	std::stringstream stream;

	stream << "Pacman X: " << _pacman->_pacmanPosition->X << " Y: " << _pacman->_pacmanPosition->Y << endl;

	stream << "\nYour Score is: " << _stats->_finalscore << endl;



	//Draw Pacman
	SpriteBatch::BeginDraw(); // Starts Drawing
	std::stringstream collectioblesCount;
	collectioblesCount << "Cherries Collected: " << _stats->_cherryCollisionCount << endl;
	collectioblesCount << "Sun Collected: " << _stats->_sunCollisionCount << endl;
	/*collectioblesCount << "Last Highest Score was: " << scoreStore << endl;*/
	SpriteBatch::DrawString(collectioblesCount.str().c_str(), _stats->_collisionStatsPosition, Color::Yellow);

		//Draw Tiles
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			SpriteBatch::Draw(_tiles[0]._tilesTecture, _tiles[0]._tilesPosition, _tiles[0]._tilesRect);
		}
		if (i == 1)
		{
			SpriteBatch::Draw(_tiles[1]._tilesTecture, _tiles[1]._tilesPosition, _tiles[1]._tilesRect);
		}
		if (i == 2)
		{
			SpriteBatch::Draw(_tiles[2]._tilesTecture, _tiles[2]._tilesPosition, _tiles[2]._tilesRect);
		}
		if (i == 3)
		{
			SpriteBatch::Draw(_tiles[3]._tilesTecture, _tiles[3]._tilesPosition, _tiles[3]._tilesRect);
		}

	}


	SpriteBatch::Draw(_pacman->_pacmanTexture, _pacman->_pacmanPosition, _pacman->_pacmanSourceRect); // Draws Pacman

	if (_pacman->dead) 
	{
		SpriteBatch::Draw(_pacman->_deadTexture, _pacman->_pacmanPosition, _pacman->_pacmanSourceRect);
	}

	_cherry->Draw();
	//Draw Sun
	for (int i = 0; i < SUNCOUNT; i++)
	{
		SpriteBatch::Draw(_sun[i]->_sunTexture, _sun[i]->_sunPosition, _sun[i]->_sunRect);

		if (CollisionSunCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _sun[i]->_sunPosition->X, _sun[i]->_sunPosition->Y, _sun[i]->_sunRect->Width, _sun[i]->_sunRect->Height))
		{
			SpriteBatch::Draw(_sun[i]->_sunTexture, _sun[i]->_sunPosition, _sun[i]->_sunRect);
		}
	}

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);

	// Start key
	if (!_start->_started) 
	{
		std::stringstream menuStream;
		menuStream << "Press SPACE to Start!!";
		SpriteBatch::Draw(_menu->_menuBackground, _menu->_menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menu->_menuStringPosition, Color::Green);
	}


	//Pause
	if (_paused) {
		std::stringstream menuStream;
		menuStream << "PAUSED!!";
		SpriteBatch::Draw(_menu->_menuBackground, _menu->_menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menu->_menuStringPosition, Color::Red);
	}

	//Draw Enemy
	for (int i = 0; i < GHOSTCOUNT; i++)
	{

		SpriteBatch::Draw(_ghost[i]->_ghostTexture, _ghost[i]->_ghostPosition, _ghost[i]->_ghostRect);
		SpriteBatch::Draw(_ghost[i]->_ghostTexture, _ghost[i]->_ghost2Position, _ghost[i]->_ghost2Rect);

		//Draw bomb
		//for (int i = 0; i < BOMBCOUNT; i++)
		//{
		//	SpriteBatch::Draw(_bomb[i]->_bombTexture, _bomb[i]->_bombPosition, _bomb[i]->_bombRect);
		//	if (CheckBombCollisions(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _bomb[i]->_bombPosition->X, _bomb[i]->_bombPosition->Y, _bomb[i]->_bombRect->Width, _bomb[i]->_bombRect->Height))
		//	{
		//		SpriteBatch::Draw(_bomb[i]->_bombTexture, _bomb[i]->_bombPosition, _bomb[i]->_bombRect);
		//	}
		//}
		if (_gameOver->_gameOver == true && _bomb[i]->_bombBlastFrameCount > _bomb[i]->_bombBlastTotalFrames)
		{
			SpriteBatch::Draw(_gameOver->_gameOverBackground, _gameOver->_gameOverPosition, _gameOver->_gameOverRectangle);
		}
	}

		SpriteBatch::EndDraw(); // Ends Drawing
	
}


//Checks
void Pacman::ChaseCheck(int elapsedTime)
{
	float pacPosX = _pacman->_pacmanPosition->X;
	float pacPosY = _pacman->_pacmanPosition->Y;
	float ghostPosX = _ghost[0]->_ghostPosition->X;
	float ghostPosY = _ghost[0]->_ghostPosition->Y;



	const float positiveBound = 150;
	const float negativeBound = -150;

	bool timeUp = false;

		if ((pacPosX - ghostPosX <= positiveBound) && (pacPosX - ghostPosX >= negativeBound) && (pacPosY - ghostPosY <= positiveBound) && (pacPosY - ghostPosY >= negativeBound))
		{
			if (pacPosX > ghostPosX && pacPosY < ghostPosY)
			{
				if (_ghost[0]->_ghostPosition->X != _pacman->_pacmanPosition->X)
				{
					_ghost[0]->_ghostPosition->X += _ghost[0]->_ghostSpeed * elapsedTime;

				}
				else if (_ghost[0]->_ghostPosition->Y != _pacman->_pacmanPosition->Y)
				{
					_ghost[0]->_ghostPosition->Y -= _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}
			if (pacPosX > ghostPosX && pacPosY > ghostPosY)
			{
				if (_ghost[0]->_ghostPosition->X != _pacman->_pacmanPosition->X)
				{
					_ghost[0]->_ghostPosition->X += _ghost[0]->_ghostSpeed * elapsedTime;

				}
				else if (_ghost[0]->_ghostPosition->Y != _pacman->_pacmanPosition->Y)
				{
					_ghost[0]->_ghostPosition->Y += _ghost[0]->_ghostSpeed * elapsedTime;
				}

			}
			if (pacPosX < ghostPosX && pacPosY < ghostPosY)
			{
				if (_ghost[0]->_ghostPosition->X != _pacman->_pacmanPosition->X)
				{
					_ghost[0]->_ghostPosition->X -= _ghost[0]->_ghostSpeed * elapsedTime;

				}
				else if (_ghost[0]->_ghostPosition->Y != _pacman->_pacmanPosition->Y)
				{
					_ghost[0]->_ghostPosition->Y -= _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}
			if (pacPosX < ghostPosX && pacPosY > ghostPosY)
			{
				if (_ghost[0]->_ghostPosition->X != _pacman->_pacmanPosition->X)
				{
					_ghost[0]->_ghostPosition->X -= _ghost[0]->_ghostSpeed * elapsedTime;

				}
				else if (_ghost[0]->_ghostPosition->Y != _pacman->_pacmanPosition->Y)
				{
					_ghost[0]->_ghostPosition->Y += _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}

			if (pacPosY < ghostPosY)
			{

				if (_ghost[0]->_ghostPosition->Y != _pacman->_pacmanPosition->Y)
				{
					_ghost[0]->_ghostPosition->Y -= _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}
			if (pacPosX < ghostPosX)
			{
				if (_ghost[0]->_ghostPosition->X != _pacman->_pacmanPosition->X)
				{
					_ghost[0]->_ghostPosition->X -= _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}
			if (pacPosY > ghostPosY)
			{
				if (_ghost[0]->_ghostPosition->Y != _pacman->_pacmanPosition->Y)
				{
					_ghost[0]->_ghostPosition->Y += _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}
			if (pacPosX > ghostPosX)
			{
				if (_ghost[0]->_ghostPosition->X != _pacman->_pacmanPosition->X)
				{
					_ghost[0]->_ghostPosition->X += _ghost[0]->_ghostSpeed * elapsedTime;
				}
			}
		}
}

void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys SPACE)
{
	//Start Key Bindings
	if (state->IsKeyDown(Input::Keys::SPACE) && !_start->_started)
	{
		_start->_SpaceKeyDown = true;
		_start->_started = !_start->_started;
		Play(_sound->_startSound);
	}
	if (state->IsKeyUp(Input::Keys::SPACE))
	{
		_start->_SpaceKeyDown = false;
	}
}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys P)
{
	//Pause Key bindings
	if (state->IsKeyDown(Input::Keys::P) && !_pKeyDown)
	{
		_pKeyDown = true;
		_paused = !_paused;
		Play(_sound->_pauseSound);
	}
	if (state->IsKeyUp(Input::Keys::P))
		_pKeyDown = false;
}



//Movements
void Pacman::RandomGhostDirection(MovingEnemy*, int elapsedTime)
{
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		/*_ghost[i]->randomtime;*/
		_ghost[i]->_ghostDirectionTime += elapsedTime;


		if (_ghost[i]->_ghostDirectionTime > _ghost[i]->_cghostDirecttionTime)
		{
			_ghost[i]->_ghostRandomDirection = rand() % 4;
			_ghost[i]->_ghostDirection = _ghost[i]->_ghostRandomDirection;
			/*cout << "Random Direction: " << _ghost[i]->_ghostRandomDirection << endl;*/

			_ghost[i]->_ghostDirectionTime = 0;


		}
	}
}


//Sounds
void Pacman::SetLooping(bool loop)
{
	if (loop == true)
	{
		if (_sound->_backgroundSound->GetState() == SoundEffectState::STOPPED) // if the sound is stopped then play the sound
		{
			Audio::Play(_sound->_backgroundSound);
		}
		if (_sound->_backgroundSound->GetState() == SoundEffectState::PAUSED)
		{
			Audio::Resume(_sound->_backgroundSound);
		}
	}
	else
	{
		Audio::Pause(_sound->_backgroundSound);
	}

}


//Collisions
bool Pacman::CheckBombCollisions(int pac_x1, int pac_y1, int pac_w1, int pac_h1, int bomb_x2, int bomb_y2, int bomb_w2, int bomb_h2)
{
	int pac_left = pac_x1;
	int pac_top = pac_y1;
	int pac_right = pac_x1 + pac_w1;
	int pac_bottom = pac_y1 + pac_h1;

	int bomb_left = bomb_x2;
	int bomb_top = bomb_y2;
	int bomb_right = bomb_x2 + bomb_w2;
	int bomb_bottom = bomb_h2 + bomb_y2;


	if (pac_bottom <= bomb_top)
	{
		return false;
	}
	if (pac_top >= bomb_bottom)
	{
		return false;
	}
	if (pac_left >= bomb_right)
	{
		return false;
	}
	if (pac_right <= bomb_left)
	{
		return false;
	}

	return true;
}

//bool Pacman::CollisionCherryCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
//{
//	int leftPacman = x1;
//	int topPacman = y1;
//	int rightPacman = x1 + w1;
//	int bottomPacman = y1 + h1;
//
//	int leftCherry = x2;
//	int topCherry = y2;
//	int rightCherry = x2 + w2;
//	int bottomCherry = y2 + h2;
//
//
//	if (bottomPacman < topCherry)
//	{
//		return false;
//	}
//	if (topPacman > bottomCherry)
//	{
//		return false;
//	}
//	if (rightPacman < leftCherry)
//	{
//		return false;
//	}
//	if (leftPacman > rightCherry)
//	{
//		return false;
//	}
//
//	return true;
//}

bool Pacman::CollisionSunCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int leftPacman = x1;
	int topPacman = y1;
	int rightPacman = x1 + w1;
	int bottomPacman = y1 + h1;



	int leftSun = x2;
	int topSun = y2;
	int rightSun = x2 + w2;
	int bottomSun = y2 + h2;


	if (bottomPacman < topSun)
	{
		return false;
	}
	if (topPacman > bottomSun)
	{
		return false;
	}
	if (rightPacman < leftSun)
	{
		return false;
	}
	if (leftPacman > rightSun)
	{
		return false;
	}

	return true;
}

void Pacman::CheckViewportCollision()
{
	//bottom
	if (_pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height > Graphics::GetViewportHeight())
	{
		_pacman->_pacmanPosition->Y = 0 + _pacman->_pacmanSourceRect->Height;
	}
	//top
	if (_pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height < 0 + 32)
	{
		_pacman->_pacmanPosition->Y = 768 - _pacman->_pacmanSourceRect->Height;
	}
	//left
	if (_pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width < 0 + 32)
	{
		_pacman->_pacmanPosition->X = 1024 - _pacman->_pacmanSourceRect->Width;
	}
	//right
	if (_pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width > Graphics::GetViewportWidth())
	{
		_pacman->_pacmanPosition->X = 0 + _pacman->_pacmanSourceRect->Width;
	}

	// Tiles Collision

}

void Pacman::CheckTileCollision(int elapsedTime)
{

	int tile_top = 0;
	int tile_bottom = 0;
	int tile_left = 0;
	int tile_right = 0;

	//Pacman-Wall Collision
	int pac_top = _pacman->_pacmanPosition->Y;
	int pac_bottom = _pacman->_pacmanPosition->Y + _pacman->_pacmanSourceRect->Height;
	int pac_left = _pacman->_pacmanPosition->X;
	int pac_right = _pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width;

	//Ghost1 Wall Collision
	int ghost1_top = _ghost[0]->_ghostPosition->Y;
	int ghost1_bottom = _ghost[0]->_ghostPosition->Y + _ghost[0]->_ghostRect->Height;
	int ghost1_left = _ghost[0]->_ghostPosition->X;
	int ghost1_right = _ghost[0]->_ghostPosition->X + _ghost[0]->_ghostRect->Width;

	//Ghost2 Wall Collision
	int ghost2_top = _ghost[0]->_ghost2Position->Y;
	int ghost2_bottom = _ghost[0]->_ghost2Position->Y + _ghost[0]->_ghost2Rect->Height;
	int ghost2_left = _ghost[0]->_ghost2Position->X;
	int ghost2_right = _ghost[0]->_ghost2Position->X + _ghost[0]->_ghost2Rect->Width;

	//Bomb Collision
	int bomb_left = _bomb[0]->_bombPosition->X;
	int bomb_top = _bomb[0]->_bombPosition->Y;
	int bomb_right = _bomb[0]->_bombPosition->X + _bomb[0]->_bombRect->Width;
	int bomb_bottom = _bomb[0]->_bombPosition->Y + _bomb[0]->_bombRect->Height;

	//Sun Collision
	int leftSun = _sun[0]->_sunPosition->X;
	int topSun = _sun[0]->_sunPosition->Y;
	int rightSun = _sun[0]->_sunPosition->X + _sun[0]->_sunRect->Width;
	int bottomSun = _sun[0]->_sunPosition->Y + _sun[0]->_sunRect->Height;

	////Cherry Collision
	//int leftCherry = _cherry[0]->_cherry_position->X;
	//int topCherry = _cherry[0]->_cherry_position->Y;
	//int rightCherry = _cherry[0]->_cherry_position->X + _cherry[0]->_cherryRect->Width;
	//int bottomCherry = _cherry[0]->_cherry_position->Y + _cherry[0]->_cherryRect->Height;




	for (int i = 0; i < 4; i++)
	{
		tile_top = _tiles[i]._tilesPosition->Y;
		tile_bottom = _tiles[i]._tilesPosition->Y + _tiles[i]._tilesRect->Height;
		tile_left = _tiles[i]._tilesPosition->X;
		tile_right = _tiles[i]._tilesPosition->X + _tiles[i]._tilesRect->Width;
		if (pac_top <= tile_bottom && pac_bottom >= tile_top && pac_left <= tile_right && pac_right >= tile_left)
		{
			if (i == 0) //Top
			{
				_pacman->_pacmanPosition->Y = _tiles[0]._tilesPosition->Y + _tiles[0]._tilesRect->Height;
			}
			if (i == 1) //Bottom
			{
				_pacman->_pacmanPosition->Y = _tiles[1]._tilesPosition->Y - _pacman->_pacmanSourceRect->Height;

			}
			if (i == 2) //left
			{
				_pacman->_pacmanPosition->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;

			}
			if (i == 3) //Right
			{
				_pacman->_pacmanPosition->X = _tiles[3]._tilesPosition->X - _pacman->_pacmanSourceRect->Width;

			}

			////if pacman moving right collides with wall to right
			//if (_pacman->_pacmanDirection == 0)
			//{
			//	//take wall left (tile_left) and put pacman -width away
			//	_pacman->_pacmanPosition->X = tile_left - _pacman->_pacmanSourceRect->Width;
			//}
			//if (_pacman->_pacmanDirection == 1) //Bottom
			//{
			//	_pacman->_pacmanPosition->Y = _tiles[1]._tilesPosition->Y - _pacman->_pacmanSourceRect->Height;
			//}
			//if (_pacman->_pacmanDirection == 2)
			//{
			//	//take wall left (tile_left) and put pacman -width away
			//	_pacman->_pacmanPosition->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;
			//}
			//if (_pacman->_pacmanDirection == 3) //Right
			//{
			//	_pacman->_pacmanPosition->X = _tiles[3]._tilesPosition->X - _pacman->_pacmanSourceRect->Width;
			//}

		}

		//Ghost 1
		for (int j = 0; j < GHOSTCOUNT; j++)
		{
			if (ghost1_top <= tile_bottom && ghost1_bottom >= tile_top && ghost1_left <= tile_right && ghost1_right >= tile_left)
			{
				if (i == 0) //Top
				{
					_ghost[j]->_ghostPosition->Y = _tiles[0]._tilesPosition->Y + _tiles[0]._tilesRect->Height;
				}
				if (i == 1) //Bottom
				{
					_ghost[j]->_ghostPosition->Y = _tiles[1]._tilesPosition->Y - _ghost[j]->_ghostRect->Height;
					cout << "bottom wall collision" << endl;
				}
				if (i == 2) //left
				{
					_ghost[j]->_ghostPosition->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;
					cout << "left wall collision" << endl;
				}
				if (i == 3) //Right
				{
					_ghost[j]->_ghostPosition->X = _tiles[3]._tilesPosition->X - _ghost[j]->_ghostRect->Width;
					cout << "right wall collision" << endl;
				}
			}
		}
		//for (int j = 0; j < CHERRYCOUNT; j++)
		//{
		//	if (topCherry <= tile_bottom && bottomCherry >= tile_top && leftCherry <= tile_right && rightCherry >= tile_left)
		//	{
		//		if (i == 0) //Top
		//		{
		//			_cherry[j]->_cherry_position->Y = _tiles[0]._tilesPosition->Y + _tiles[0]._tilesRect->Height;
		//			cout << " wall collision" << endl;
		//		}
		//		if (i == 1) //Bottom
		//		{
		//			_cherry[j]->_cherry_position->Y = _tiles[1]._tilesPosition->Y - _cherry[j]->_cherryRect->Height;
		//			cout << " wall collision" << endl;
		//		}
		//		if (i == 2) //left
		//		{
		//			_cherry[j]->_cherry_position->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;
		//			cout << " wall collision" << endl;
		//		}
		//		if (i == 3) //Right
		//		{
		//			_cherry[j]->_cherry_position->X = _tiles[3]._tilesPosition->X - _cherry[j]->_cherryRect->Width;
		//			cout << " wall collision" << endl;
		//		}
		//	}
		//}


		//Ghost 2
		for (int j = 0; j < GHOSTCOUNT; j++)
		{
			if (ghost2_top <= tile_bottom && ghost2_bottom >= tile_top && ghost2_left <= tile_right && ghost2_right >= tile_left)
			{
				if (i == 0) //Top
				{
					_ghost[j]->_ghost2Position->Y = _tiles[0]._tilesPosition->Y + _tiles[0]._tilesRect->Height;
				}
				if (i == 1) //Bottom
				{
					_ghost[j]->_ghost2Position->Y = _tiles[1]._tilesPosition->Y - _ghost[j]->_ghost2Rect->Height;
					cout << "bottom wall collision" << endl;
				}
				if (i == 2) //left
				{
					_ghost[j]->_ghost2Position->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;
					cout << "left wall collision" << endl;
				}
				if (i == 3) //Right
				{
					_ghost[j]->_ghost2Position->X = _tiles[3]._tilesPosition->X - _ghost[j]->_ghost2Rect->Width;
					cout << "right wall collision" << endl;
				}
			}
		}

		//Bomb
		for (int j = 0; j < BOMBCOUNT; j++)
		{
			if (bomb_top <= tile_bottom && bomb_bottom >= tile_top && bomb_left <= tile_right && bomb_right >= tile_left)
			{
				if (i == 0) //Top
				{
					_bomb[j]->_bombPosition->Y = _tiles[0]._tilesPosition->Y + _tiles[0]._tilesRect->Height;
				}
				if (i == 1) //Bottom
				{
					_bomb[j]->_bombPosition->Y = _tiles[1]._tilesPosition->Y - _bomb[j]->_bombRect->Height;
					cout << "bottom wall collision" << endl;
				}
				if (i == 2) //left
				{
					_bomb[j]->_bombPosition->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;
					cout << "left wall collision" << endl;
				}
				if (i == 3) //Right
				{
					_bomb[j]->_bombPosition->X = _tiles[3]._tilesPosition->X - _bomb[j]->_bombRect->Width;
					cout << "right wall collision" << endl;
				}
			}
		}

		//Sun
		for (int j = 0; j < SUNCOUNT; j++)
		{
			if (topSun <= tile_bottom && bottomSun >= tile_top && leftSun <= tile_right && rightSun >= tile_left)
			{
				if (i == 0) //Top
				{
					_sun[j]->_sunPosition->Y = _tiles[0]._tilesPosition->Y + _tiles[0]._tilesRect->Height;
				}
				if (i == 1) //Bottom
				{
					_sun[j]->_sunPosition->Y = _tiles[1]._tilesPosition->Y - _sun[j]->_sunRect->Height;
					cout << "bottom wall collision" << endl;
				}
				if (i == 2) //left
				{
					_sun[j]->_sunPosition->X = _tiles[2]._tilesPosition->X + _tiles[2]._tilesRect->Width;
					cout << "left wall collision" << endl;
				}
				if (i == 3) //Right
				{
					_sun[j]->_sunPosition->X = _tiles[3]._tilesPosition->X - _sun[j]->_sunRect->Width;
					cout << "right wall collision" << endl;
				}
			}
		}
	}
}

bool Pacman::CheckGhostCollisions(int pac_x1, int pac_y1, int pac_w1, int pac_h1, int ghost_x2, int ghost_y2, int ghost_w2, int ghost_h2)
{
	int i = 0;

	int pac_left = pac_x1;
	int pac_top = pac_y1;
	int pac_right = pac_x1 + pac_w1;
	int pac_bottom = pac_y1 + pac_h1;


	int leftGhost = ghost_x2;
	int rightGhost = ghost_x2+ ghost_w2;
	int topGhost = ghost_y2;
	int bottomGhost = ghost_y2+ ghost_h2;


	for (i = 0; i < GHOSTCOUNT; i++)
	{
		if (pac_bottom <= topGhost)
		{
			return false;
		}
		if (pac_top >= bottomGhost)
		{
			return false;
		}
		if (pac_left >= rightGhost)
		{
			return false;
		}
		if (pac_right <= leftGhost)
		{
			return false;
		}

		return true;
	}
}
