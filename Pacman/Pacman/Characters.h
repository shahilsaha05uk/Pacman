#pragma once
#include "Structures.h"
#include "Constants.h"
#include "ObjectLoader.h"
#include "Collision.h"
#include <iostream>


using namespace std;
using namespace S2D;


class Characters
{
private:


protected:

	Rect _position;
	float spriteWidth;
	float spriteHeight;

	Vector2* objPosition;
	Texture2D* objTexture;
	Rect* objRect;
	//Vector2* offCherryPosition;

	int objTotalFrames;
	int objCurrentFrameTime;
	int objRandFrameTime;
	int objFrameCount;

	ObjectLoader* objLoad;


public:
	Characters();
	~Characters();

	void Update(float deltaTime);

	Rect GetPosition();
};

