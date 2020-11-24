#include "Pacman.h"
#include <sstream>
#include <time.h>
//local variable


Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cCherryFrameTime(100)
{
	//Structures
	_pacman = new Player{1.0f, 350};
	_start = new Start();
	_menu = new Menu();
	_map = new Map();

	//local variable
	
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		_cherry[i] = new Cherry();
		_cherry[i]->CurrentFrameTime = 0;
		_cherry[i]->frameCount = rand()% 2;
		_cherry[i]->_randCherryFrameTime = rand() % 500 + 50;
	}



	//Enemy Initialization
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghost[i] = new MovingEnemy();
		_ghost[i]->_ghostDirection = 0;
		_ghost[i]->_ghostSpeed = 0.2f;
		_ghost[i]->_ghost1_frame = 2;
		_ghost[i]->i_frames = 0;
	}




	//Pause and Start
	_paused = false;
	_pKeyDown = false;
	_start->_started = false;
	_start->_SpaceKeyDown = false;





	// Pacman Directions
	_pacman->_pacmanDirection = 0;

	//Animation Variables
	_pacman->_pacmanCurrentFrameTime = 0;
	_pacman->_pacmanFrame = 0;
	_pacman->speedMultiplier = 1.0f;
	_pacman->dead = false;

	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();

}

Pacman::~Pacman()
{

	delete _pacman->_pacmanTexture;
	delete _pacman->_pacmanSourceRect;
	
	for (int i = 0; i < CHERRYCOUNT; i++)
	{

			delete _cherry[i]->_cherries;
			delete[] _cherry;
			delete _cherry[i]->_cherries;
			delete _cherry[i]->_cherryRect;
			delete _cherry[i];

	}

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		delete _ghost[i]->_ghostPosition;
		delete _ghost[i]->_ghostRect;
		delete _ghost[i]->_ghostTexture;
	}
	delete _map;
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
	_pacman->_pacmanTexture->Load("Textures/Pacman.tga", false);
	_pacman->_pacmanPosition = new Vector2(32.0f, 250.0f);
	_pacman->_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);

	//Load Enemy
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghost[i]->_ghostTexture = new Texture2D();
		_ghost[i]->_ghostTexture->Load("Textures/3sprites.png", false);
		_ghost[i]->_ghostPosition = new Vector2(0,0);
		_ghost[i]->_ghostRect = new Rect(0.0f, 0.0f, 32, 32);

		_ghost[i]->_ghost2Position = new Vector2(0,0);
		_ghost[i]->_ghost2Rect = new Rect(64.0f, 0.0f, 32, 32);
	}

	//Map
	_map->_mapTexture = new Texture2D();
	_map->_mapTexture->Load("Textures/Map.png", false);
	_map->_mapPosition = new Vector2(0,0);
	_map->_mapRectangle = new Rect(0, 0, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

	Texture2D* cherryTex = new Texture2D();
	cherryTex->Load("Textures/SpriteCherries.png", false);

	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		//Load Cherries
		_cherry[i]->_cherries = new Texture2D();
		_cherry[i]->_cherries = cherryTex;
		_cherry[i]->_cherries->Load("Textures/SpriteCherries.png", true);
		_cherry[i]->_cherryRect = new Rect(0.0f, 0.0f, 32, 32);
		_cherry[i]->_cherry_position = new Vector2(200.0f, 200.0f);
		_cherry[i]->_cherry_position = new Vector2((rand()% Graphics::GetViewportWidth()), (rand()%Graphics::GetViewportHeight()));
	
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

		for (int i = 0; i < CHERRYCOUNT; i++)
		{
			Random_timer += elapsedTime;

			if (Random_timer > cRandom_timer)
			{
				if (state->IsKeyDown(Input::Keys::R))
				{
					_cherry[i]->_cherry_position->X = rand() % Graphics::GetViewportWidth();
					_cherry[i]->_cherry_position->Y = rand() % Graphics::GetViewportHeight();
					Random_timer = 0;
				}
			}

		}

	if (m_state->LeftButton == Input::ButtonState::PRESSED)
	{
		for (int i = 0; i < CHERRYCOUNT; i++)
		{
			_cherry[i]->_cherry_position->X = m_state->X;
			_cherry[i]->_cherry_position->Y = m_state->Y;
		}
	}
}

//Check methods

void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys SPACE)
{
	//Start Key Bindings
	if (state->IsKeyDown(Input::Keys::SPACE) && !_start->_started)
	{
		_start->_SpaceKeyDown = true;
		_start->_started = !_start->_started;
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
	}
	if (state->IsKeyUp(Input::Keys::P))
		_pKeyDown = false;

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
	
}

void Pacman::CheckGhostCollisions()
{
	int i = 0;

	int leftPacman= _pacman->_pacmanPosition->X + _pacman->_pacmanSourceRect->Width;
	int rightPacman = _pacman->_pacmanPosition->X;
	int topPacman= _pacman->_pacmanPosition->Y;
	int bottomPacman= _pacman->_pacmanPosition->Y+ _pacman->_pacmanSourceRect->Height;


	int leftGhost=0;
	int rightGhost=0;
	int topGhost=0;
	int bottomGhost=0;


	for (i = 0; i < GHOSTCOUNT; i++)
	{
		int leftGhost = _ghost[i]->_ghostPosition->X + _ghost[i]->_ghostRect->Width;
		int rightGhost = _ghost[i]->_ghostPosition->X;
		int topGhost = _ghost[i]->_ghostPosition->Y;
		int bottomGhost = _ghost[i]->_ghostPosition->Y + _ghost[i]->_ghostRect->Height;


		if ((leftPacman < rightGhost) && (rightPacman > leftGhost) && (bottomPacman > topGhost) && (topPacman < bottomGhost))
		{
			_pacman->dead = true;
			i = GHOSTCOUNT;
		}
		else
		{
			_pacman->dead = false;
		}
		
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
		if (_pacman->_pacmanFrame >= 2) {
			_pacman->_pacmanFrame=0;
			_pacman->_pacmanCurrentFrameTime = 0;
		}
	}
	_pacman->_pacmanSourceRect->X = _pacman->_pacmanSourceRect->Width * _pacman->_pacmanFrame;
}

void Pacman::UpdateCherry(Cherry*, int elapsedTime)
{
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		_cherry[i]->CurrentFrameTime += elapsedTime;
		if (_cherry[i]->CurrentFrameTime > _cCherryFrameTime)
		{
			_cherry[i]->frameCount++;
			if (_cherry[i]->frameCount >= 2) {
				_cherry[i]->frameCount = 0;
			}
			_cherry[i]->CurrentFrameTime = 0;

			_cherry[i]->_cherryRect->X = _cherry[i]->_cherryRect->Width * _cherry[i]->frameCount;
			_cherry[i]->_cherryRect->Y = _cherry[i]->_cherryRect->Height * _cherry[i]->frameCount;

		}
	}
}

void Pacman::UpdateGhost(MovingEnemy*, int elapsedTime)
{

	for (int i = 0; i < GHOSTCOUNT; i++)
	{

		_ghost[i]->_ghost1_frame++;

			if (_ghost[i]->_ghostDirection == 0) // left
			{
				_ghost[i]->_ghostPosition->X -= _ghost[i]->_ghostSpeed * elapsedTime;
			}
			if (_ghost[i]->_ghostDirection == 1) // right
			{
				_ghost[i]->_ghostPosition->X += _ghost[i]->_ghostSpeed * elapsedTime;
			}
			if (_ghost[i]->_ghostDirection == 2) // top
			{
				_ghost[i]->_ghostPosition->Y -= _ghost[i]->_ghostSpeed * elapsedTime;
			}
			if (_ghost[i]->_ghostDirection == 3) // bottom
			{
				_ghost[i]->_ghostPosition->Y += _ghost[i]->_ghostSpeed * elapsedTime;
			}



			if (_ghost[i]->_ghostPosition->X + _ghost[i]->_ghostRect->Width <= 0) //left to right
			{
				_ghost[i]->_ghostDirection = 1;
			}
			if (_ghost[i]->_ghostPosition->Y + _ghost[i]->_ghostRect->Height <= 0) // bottom to top
			{
				_ghost[i]->_ghostDirection = 2;
			}
			if (_ghost[i]->_ghostPosition->X + _ghost[i]->_ghostRect->Width >= Graphics::GetViewportWidth()) //right to bottom
			{
				_ghost[i]->_ghostDirection = 3;
			}
			if (_ghost[i]->_ghostPosition->Y + _ghost[i]->_ghostRect->Height >= Graphics::GetViewportHeight()) //bottom to left
			{
				_ghost[i]->_ghostDirection = 0;
			}



			//if (_ghost[i]->_ghostPosition->Y + _ghost[i]->_ghostRect->Height <= Graphics::GetViewportHeight()) // bottom to top
			//{
			//	_ghost[i]->_ghostDirection = 2;
			//}



			//if (_ghost[i]->_ghostPosition->X + _ghost[i]->_ghostRect->Height <= 0 && _ghost[i]->_ghostDirection == 0) //bottom to top
			//{
			//		_ghost[i]->_ghostDirection = 2;	
			//}





			if (_ghost[i]->_ghost2Direction == 0) // Left
			{
				_ghost[i]->_ghost2Position->X -= _ghost[i]->_ghostSpeed * elapsedTime;
			}
			if (_ghost[i]->_ghost2Direction == 1) // Right
			{
				_ghost[i]->_ghost2Position->X += _ghost[i]->_ghostSpeed * elapsedTime;
			}
			if (_ghost[i]->_ghost2Direction == 2) // Top
			{
				_ghost[i]->_ghost2Position->Y -= _ghost[i]->_ghostSpeed * elapsedTime;
			}
			if (_ghost[i]->_ghost2Direction == 3) // Bottom
			{
				_ghost[i]->_ghost2Position->Y += _ghost[i]->_ghostSpeed * elapsedTime;
			}



			if (_ghost[i]->_ghost2Position->Y + _ghost[i]->_ghost2Rect->Width <= Graphics::GetViewportWidth())
			{
				_ghost[i]->_ghost2Direction = 3; // Top to bottom 
			}
			if (_ghost[i]->_ghost2Position->Y + _ghost[i]->_ghost2Rect->Height >= Graphics::GetViewportHeight())
			{
				_ghost[i]->_ghost2Direction = 1; //  Bottom to right
			}
			if (_ghost[i]->_ghost2Position->X + _ghost[i]->_ghost2Rect->Width >= Graphics::GetViewportWidth())
			{
				_ghost[i]->_ghost2Direction = 2; // right to top
			}

			if (_ghost[i]->_ghost2Position->X + _ghost[i]->_ghost2Rect->Width >= Graphics::GetViewportWidth() && _ghost[i]->_ghost2Position->Y + _ghost[i]->_ghost2Rect->Width <= Graphics::GetViewportWidth())
			{
					_ghost[i]->_ghost2Direction = 0; // top to left
			}


	}

}



void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
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
			Input(elapsedTime, keyboardState, mouseState);
			UpdatePacman(elapsedTime);

			for (int i = 0; i < GHOSTCOUNT; i++)
			{
				UpdateGhost(_ghost[0], elapsedTime);
			}
			


			CheckGhostCollisions();
			CheckViewportCollision();
			for (int i = 0; i < CHERRYCOUNT; i++)
			{

				UpdateCherry(_cherry[i], elapsedTime);

				if (CollisionCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _cherry[i]->_cherry_position->X, _cherry[i]->_cherry_position->Y, _cherry[i]->_cherryRect->Width, _cherry[i]->_cherryRect->Height))
				{

					_cherry[i]->_cherry_position->X = rand() % Graphics::GetViewportWidth();
					_cherry[i]->_cherry_position->Y = rand() % Graphics::GetViewportHeight();
				}
			}
		}
	}
}

void Pacman::Draw(int elapsedTime)
{

	// Allows us to easily create a string
	std::stringstream stream;

	stream << "Pacman X: " << _pacman->_pacmanPosition->X << " Y: " << _pacman->_pacmanPosition->Y << endl;

	//Draw Pacman
	SpriteBatch::BeginDraw(); // Starts Drawing


	//	//Draw Map
	//SpriteBatch::Draw(_map->_mapTexture, _map->_mapRectangle);


	SpriteBatch::Draw(_pacman->_pacmanTexture, _pacman->_pacmanPosition, _pacman->_pacmanSourceRect); // Draws Pacman


	if (!_pacman->dead) 
	{
		SpriteBatch::Draw(_pacman->_pacmanTexture, _pacman->_pacmanPosition, _pacman->_pacmanSourceRect);
	}

	//Draw Enemy
	for (int i = 0; i < GHOSTCOUNT; i++)
	{	
			
			SpriteBatch::Draw(_ghost[i]->_ghostTexture, _ghost[i]->_ghostPosition, _ghost[i]->_ghostRect);
			SpriteBatch::Draw(_ghost[i]->_ghostTexture, _ghost[i]->_ghost2Position, _ghost[i]->_ghost2Rect);
				
	}


	//Draw Cherry
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		//Draw red cherry
		SpriteBatch::Draw(_cherry[i]->_cherries, _cherry[i]->_cherry_position, _cherry[i]->_cherryRect);

		if (CollisionCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _cherry[i]->_cherry_position->X, _cherry[i]->_cherry_position->Y, _cherry[i]->_cherryRect->Width, _cherry[i]->_cherryRect->Height))
		{

			SpriteBatch::Draw(_cherry[i]->_cherries, _cherry[i]->_cherry_position, _cherry[i]->_cherryRect);
		}
	}

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);

	// Start key
	if (!_start->_started) {
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


	SpriteBatch::EndDraw(); // Ends Drawing
}