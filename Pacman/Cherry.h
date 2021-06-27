#pragma once
#include "Objects.h"



class Cherry : public Objects
{
private:

public:
	Cherry();
	~Cherry();

	Texture2D* _objectTex;

	Vector2* _position;
	Texture2D* _object;
	Rect* _objectRect;
	Vector2* off_object_Position;


	void Load();
	void Update(int deltatime);
	void Draw();

};

