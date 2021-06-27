#pragma once
#include "S2D/S2D.h"



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


