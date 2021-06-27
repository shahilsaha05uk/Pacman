#include "Characters.h"

Characters::Characters()
{

}

Characters::~Characters()
{

}

void Characters::Update(float deltaTime)
{

}

Rect Characters::GetPosition()
{
	return Rect(_position.X, _position.Y, spriteWidth, spriteHeight);
}
