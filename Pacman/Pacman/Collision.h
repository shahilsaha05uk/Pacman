#pragma once
#include "Structures.h"


class Collision
{
private:
	Collision();
	static Collision* m_instance;

public:
	~Collision();

	static Collision* Instance();
	bool Box(Rect rect1, Rect rect2);

};

