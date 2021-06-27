#pragma once
#include "S2D/S2D.h"
#include "S2D/SpriteBatch.h"
#include "Constants.h"



using namespace S2D;

class Objects
{
private:


protected:

	Texture2D* _objectTex;

	Vector2* _position;
	Texture2D* _object;
	Rect* _objectRect;
	Vector2* off_object_Position;

	int _object_totalFrames;
	int _object_CurrentFrameTime;
	int _rand_object_FrameTime;
	int _object_frameCount;
	int _object_ConstantFrameTime;

public:

	Objects();
	~Objects();

	virtual void Update(int deltatime);
	virtual void Draw();

};

