#pragma once

class Object;
class Component

{
public:
	friend class Object;
	//todo : friend class Object;
	//Object will init all components
	virtual void Initialize() {};
	virtual ~Component() {  };
	Object* GetOwner() const { return pOwner; }
	void SetOwner(Object* owner) { pOwner = owner; }
	Object* pOwner;

};