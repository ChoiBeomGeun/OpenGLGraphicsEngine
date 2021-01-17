#pragma once
typedef unsigned int ObjectID;
#include <vector>
#include "Component.h"
class Object
{

public:

	Object();
	~Object();
	//Init the object
	void Initialize();

	std::vector <Component*>mVcomponetList;

	// Properly destroy the object by delay destruction
	void Destroy();
	bool IsLoadingObject = false;
	template <typename Component>
	void AddComponent();

	template <typename Component>
	Component * GetComponent();

	template <typename Component>
	bool HasComponent();
	ObjectID objID;

};


template <typename Component>
bool Object::HasComponent()
{
	for (auto inComponentList : mVcomponetList)
	{

		if (typeid(*inComponentList).name() == typeid(Component).name())
			return true;
	}
	return false;

}



template<typename Component>
void Object::AddComponent()
{
	if (HasComponent<>()) {
		return;
	}
	Component* temp = new Component();
	dynamic_cast<Component*>(temp)->SetOwner(this);
	this->mVcomponetList.push_back(temp);



}

template<typename ComponentType>
ComponentType* Object::GetComponent()
{
	for (auto inComponentList : mVcomponetList)
	{

		if (typeid(*inComponentList).name() == typeid(ComponentType).name())
			return dynamic_cast<ComponentType*>(inComponentList);
	}
	return nullptr;

}