#pragma once
#include "Characters.h"

class PacmanChr : public Characters
{
private:
	const float _cPacmanSpeed = 0.5f;
	const int _cPacmanFrameTime = 150;
	int objDirection;
	int objFrame;
	int objSpeed;
	float speedMultiplier;

public:
	PacmanChr();
	~PacmanChr();

	void Load();
	void Input(int deltaTime, Input::KeyboardState* state, Input::MouseState* m_state);
	void Update(float deltaTime);
	void Animations(float deltaTime);

	void CollisionCheck();


	void Draw();
};

