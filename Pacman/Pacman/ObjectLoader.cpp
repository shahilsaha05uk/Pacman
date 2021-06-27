#include "ObjectLoader.h"

ObjectLoader::ObjectLoader(Texture2D* obj, string path)
{
	Load(obj, path);
}

ObjectLoader::~ObjectLoader()
{
}

void ObjectLoader::Load(Texture2D* obj, string path)
{
	obj->Load(path.c_str(), false);
}
