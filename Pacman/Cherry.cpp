#include "Cherry.h"

Cherry::Cherry() : Objects()
{
	_object_CurrentFrameTime = 0;
	_rand_object_FrameTime = rand() % 500 + 50;
	_object_frameCount = rand() % 2;
}

Cherry::~Cherry()
{

}

void Cherry::Load()
{
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		_objectTex = new Texture2D();
		 _objectTex->Load("Textures/SpriteCherries.png", true);
		 _objectRect = new Rect(0.0f, 0.0f, 32, 32);
		 _position = new Vector2((rand() % Graphics::GetViewportWidth() - 32), (rand() % Graphics::GetViewportHeight()));
	}
}

void Cherry::Update(int deltatime)
{
	_object_CurrentFrameTime += deltatime;
	if (_object_CurrentFrameTime > _object_ConstantFrameTime)
	{
		_object_frameCount++;
		if (_object_frameCount >= 2) {
			_object_frameCount = 0;
		}
		_object_CurrentFrameTime = 0;

		_objectRect->X = _objectRect->Width * _object_frameCount;
		_objectRect->Y = _objectRect->Height * _object_frameCount;

	}

}

void Cherry::Draw()
{
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		//Draw red cherry
		SpriteBatch::Draw(_objectTex, _position, _objectRect);

		//if (CollisionCherryCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _cherry[i]->_cherry_position->X, _cherry[i]->_cherry_position->Y, _cherry[i]->_cherryRect->Width, _cherry[i]->_cherryRect->Height))
		//{
		//	SpriteBatch::Draw(_cherry[i]->_cherries, _cherry[i]->_cherry_position, _cherry[i]->_cherryRect);
		//}
	}

}
