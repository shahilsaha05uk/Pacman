#include "CherryObj.h"

CherryObj::CherryObj() : Characters()
{

}
CherryObj::~CherryObj()
{

}
void CherryObj::Load()
{
	objTexture = new Texture2D();
	objLoad = new ObjectLoader(objTexture, "Textures/SpriteCherries.png");
	objRect = new Rect(0.0f, 0.0f, 32, 32);
	objPosition = new Vector2((rand() % Graphics::GetViewportWidth() - 32), (rand() % Graphics::GetViewportHeight()));
}
void CherryObj::Update(float elapsedTime)
{
	objCurrentFrameTime += elapsedTime;
	if (objCurrentFrameTime > _cCherryFrameTime)
	{
		objFrameCount++;
		if (objFrameCount >= 2) {
			objFrameCount = 0;
		}
		objCurrentFrameTime = 0;

		objRect->X = objRect->Width * objFrameCount;
		objRect->Y = objRect->Height * objFrameCount;

	}
}

void CherryObj::Draw()
{


	SpriteBatch::Draw(objTexture, objPosition, objRect);

	//if (CollisionCherryCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, _pacman->_pacmanSourceRect->Width, _pacman->_pacmanSourceRect->Height, _cherry->_cherry_position->X, _cherry->_cherry_position->Y, _cherry->_cherryRect->Width, _cherry->_cherryRect->Height))
	//{
	//	SpriteBatch::Draw(_cherry->_cherries, _cherry->_cherry_position, _cherry->_cherryRect);
	//}

}
void CherryObj::Animation()
{
	objCurrentFrameTime = 0;
	objFrameCount = rand() % 2;
	objRandFrameTime = rand() % 500 + 50;
}
