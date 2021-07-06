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

	_position = *objRect;
}
void CherryObj::Update(float deltaTime)
{
	//cout << "Position X: " << objPosition->X << endl;
	//cout << "Position Y: " << objPosition->Y << endl;
	//cout << "Width: " << _position.Width << endl;
	//cout << "Height: " << _position.Height << endl;

	Animation(deltaTime);
}

void CherryObj::Draw()
{
	SpriteBatch::Draw(objTexture, objPosition, objRect);
}
void CherryObj::Animation(float deltaTime)
{
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		objCurrentFrameTime = 0;
		objFrameCount = rand() % 2;
		objRandFrameTime = rand() % 500 + 50;

		objCurrentFrameTime += deltaTime;
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
}
