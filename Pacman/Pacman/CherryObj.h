#pragma once

#include "Structures.h"
#include "Characters.h"
#include "Constants.h"

using namespace S2D;

class CherryObj  : public Characters
{
private:

	const int _cCherryFrameTime=100;
	int cRandom_timer = 500;
	int Random_timer;

	

public:
	CherryObj();
	~CherryObj();

	void Load();
	void Update(float deltaTime);
	void Draw();
	void Animation(float deltaTime);

};

