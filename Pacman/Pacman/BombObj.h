#pragma once
#include "Characters.h"
#include "Structures.h"
#include "Constants.h"


class BombObj : public Characters
{
private:
	const int _cBombFrameTime = 100;
	int _bombBlastTotalFrames;
	int _bombBlastCurrentFrameTime;
	int _cBombBlastFrameTime;
	int _bombBlastFrameCount;
	bool _CanBlast = false;


public:

	BombObj();
	~BombObj();

	void Load();
	void Update(float deltaTime);
	void Draw();
	void Animation(float deltaTime);

};

