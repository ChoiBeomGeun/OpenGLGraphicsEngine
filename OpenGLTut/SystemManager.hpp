#pragma once

#include "System.hpp"
#include "Types.h"
#include <cassert>
#include <memory>
#include <unordered_map>


class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}


	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;


			system->mEntities.erase(entity);
		}
	}

	template<typename T>
	void AddEntityToSystem(Entity entity)
	{
		const char* typeName = typeid(T).name();
		mSystems[typeName]->mEntities.insert(entity);
	}
private:

	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};
