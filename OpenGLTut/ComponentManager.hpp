#pragma once

#include "ComponentVector.hpp"
#include "Types.hpp"
#include <any>
#include <memory>
#include <unordered_map>
#include <iostream>
class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

		mComponentTypes.insert({typeName, mNextComponentType});
		mComponentVectors.insert({typeName, std::make_shared<ComponentVector<T>>()});

		++mNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return mComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T * component)
	{
		auto comVec = GetComponentVector<T>();

		if (comVec != nullptr)
		{
			comVec->InsertData(entity, component);
		}
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentVector<T>()->RemoveData(entity);
	}

	template<typename T>
	T * GetComponent(Entity entity)
	{
		auto cv = GetComponentVector<T>();
		if (cv == nullptr)
		{
			return nullptr;
		}
		return GetComponentVector<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mComponentVectors)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentVector>> mComponentVectors{};
	ComponentType mNextComponentType{};


	template<typename T>
	std::shared_ptr<ComponentVector<T>> GetComponentVector()
	{
		const char* typeName = typeid(T).name();

		if (mComponentTypes.find(typeName) == mComponentTypes.end())
		{
			std::cout << "Component is not found. Type Name is :" << typeName;
			return nullptr;
		}

		return std::static_pointer_cast<ComponentVector<T>>(mComponentVectors[typeName]);
	}
};
