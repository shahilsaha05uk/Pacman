#include "Collision.h"

Collision* Collision::m_instance = nullptr;

Collision::Collision()
{

}

Collision::~Collision()
{
	m_instance = nullptr;

}

Collision* Collision::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collision();
	}
	return m_instance;
}

bool Collision::Box(Rect rect1, Rect rect2)
{
	if (rect1.X + (rect1.Width / 2) > rect2.X &&
		rect1.X + (rect1.Width / 2) < rect2.X + rect2.Width &&
		rect1.Y + (rect1.Height / 2) > rect2.Y &&
		rect1.Y + (rect1.Height / 2) < rect2.Y + rect2.Height)
	{
		return true;
	}
	return false;
}

