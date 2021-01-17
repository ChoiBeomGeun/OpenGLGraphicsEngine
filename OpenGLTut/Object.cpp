

#include "Object.h"

Object::Object()
{
}
Object::~Object()
{

	for (auto inComponentList : mVcomponetList)
	{
		delete inComponentList;

	}
	mVcomponetList.clear();

}





void Object::Initialize()
{
	for (auto components : this->mVcomponetList)
	{
		components->Initialize();
	}

}


void Object::Destroy() {




}
