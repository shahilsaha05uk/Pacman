#include "BombObj.h"

BombObj::BombObj() : Characters()
{

		objCurrentFrameTime = 0;
		objFrameCount = 0;
		objTotalFrames = 10;

		_bombBlastTotalFrames = 6;
		_bombBlastCurrentFrameTime = 0;
		_cBombBlastFrameTime = 100;
		_bombBlastFrameCount = 4;
		_CanBlast = false;
}

BombObj::~BombObj()
{

}

void BombObj::Load()
{
	objTexture = new Texture2D();
	objLoad = new ObjectLoader(objTexture, "Textures/BombBlast.png");
	objRect = new Rect(10.0f, 10.0f, 32, 32);
	objPosition = new Vector2((rand() % Graphics::GetViewportWidth() - 32), (rand() % Graphics::GetViewportHeight() - 32));

}

void BombObj::Update(float elapsedTime)
{
	for (int i = 0; i < BOMBCOUNT; i++)
	{

		if (Collision::Instance()->Box())
		{

			objCurrentFrameTime += elapsedTime;
			if (objCurrentFrameTime > _cBombBlastFrameTime)
			{
				_bombBlastFrameCount++;

				if (_bombBlastFrameCount > 3)
				{
					//_pacman->dead = true;
					cout << "Pacman Dead" << endl;
				}
				objCurrentFrameTime = 0;
				objRect->X = objRect->Width * _bombBlastFrameCount;
				objRect->Y = objRect->Height * _bombBlastFrameCount;
			}
		}
		else
		{
			objCurrentFrameTime += elapsedTime;
			if (objCurrentFrameTime > _cBombFrameTime)
			{
				objFrameCount++;
				if (objFrameCount > 3)
				{
					objFrameCount = 0;
				}
				objCurrentFrameTime = 0;
				objRect->X = objRect->Width * objFrameCount;
				objRect->Y = objRect->Height * objFrameCount;
			}
		}

	}

}

void BombObj::Draw()
{
	SpriteBatch::Draw(objTexture, objPosition, objRect);

}

void BombObj::Animation()
{
	objCurrentFrameTime = 0;
	objFrameCount = rand() % 2;
	objRandFrameTime = rand() % 500 + 50;
}
