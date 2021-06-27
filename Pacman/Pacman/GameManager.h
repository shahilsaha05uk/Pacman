#pragma once

#include "CherryObj.h"
#include "BombObj.h"


class GameManager
{
private:

protected:
	CherryObj* _cherry;
	BombObj* _bomb;


public:
	GameManager();
	~GameManager();
};

