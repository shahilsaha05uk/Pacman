#pragma once

#include "S2D/S2D.h"
#include <string>
using namespace S2D;

class ObjectLoader
{
private:

public:
	ObjectLoader(Texture2D *obj, string path);
	~ObjectLoader();

	void Load(Texture2D* obj, string path);
};

