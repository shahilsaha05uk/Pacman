#include "PacmanChr.h"

PacmanChr::PacmanChr()
{

}

PacmanChr::~PacmanChr()
{

}

void PacmanChr::Load()
{
	objTexture = new Texture2D();
	objTexture->Load("Textures/Pacman.png", false);
	objPosition = new Vector2(500.0f, 250.0f);
	objSourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_position = *objSourceRect;

	//_pacman->_deadTexture = new Texture2D();
	//_pacman->_deadTexture->Load("Textures/pacmanDestroy.png", false);
	//_pacman->_DeadpacmanPosition = new Vector2(32.0f, 250.0f);
	//_pacman->_DeadpacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);

}

void PacmanChr::Update(float deltaTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();

	Input(deltaTime, keyboardState, mouseState);
	Animations(deltaTime);
}

void PacmanChr::Animations(float deltaTime)
{
	//Changing frames time
	objSourceRect->Y = objSourceRect->Height * objDirection;
	objCurrentFrameTime += deltaTime;
	if (objCurrentFrameTime > _cPacmanFrameTime) {
		objFrame++;
		if (objFrame >= 4) {
			objFrame = 0;
		}
		objCurrentFrameTime = 0;
	}
	objSourceRect->X = objSourceRect->Width * objFrame;
}

void PacmanChr::CollisionCheck()
{
	
}

void PacmanChr::Draw()
{
	SpriteBatch::Draw(objTexture, objPosition, objSourceRect); // Draws Pacman
}

void PacmanChr::Input(int deltaTime, Input::KeyboardState* state, Input::MouseState* m_state)
{
	//Storing the calculation in a single variable
	float _pacmanSpeed = _cPacmanSpeed * deltaTime;

	//if (_start->_started == true && _gameOver->_gameOver == false)
	//{
		// Movements
		if (state->IsKeyDown(Input::Keys::D))
		{
			objPosition->X += _pacmanSpeed; //Moves Pacman across X axis
			objDirection = 0;
		}
		else if (state->IsKeyDown(Input::Keys::S))
		{
			objPosition->Y += _pacmanSpeed; //Moves Pacman across -Y axis
			objDirection = 1;
		}
		else if (state->IsKeyDown(Input::Keys::A))
		{
			objPosition->X -= _pacmanSpeed; //Moves Pacman across -X axis
			objDirection = 2;
		}
		else if (state->IsKeyDown(Input::Keys::W))
		{
			objPosition->Y -= _pacmanSpeed; //Moves Pacman across -Y axis
			objDirection = 3;
		}
		if (state->IsKeyDown(Input::Keys::LEFTSHIFT))
		{
			//Apply Multiplier
			speedMultiplier = 2.0f;
		}
		else
		{
			// Reset multiplier
			speedMultiplier = 1.0f;
		}

		//for (int i = 0; i < CHERRYCOUNT; i++)
		//{
		//	Random_timer += deltaTime;
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
	//}
}

