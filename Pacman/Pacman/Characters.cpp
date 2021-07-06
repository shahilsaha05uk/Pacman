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
	return Rect(objPosition->X, objPosition->Y, _position.Width, _position.Height);
}
