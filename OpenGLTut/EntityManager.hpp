#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <queue>
#include <string>
using namespace std;
class EntityManager
{
	std::uint32_t _curid;
public:
	EntityManager()
	{
		_curid = 0;
	}

	Entity CreateEntity(string name = "")
	{
		_curid++;
		mEntityNameMap[_curid] = (name == "") ? std::to_string(_curid) : name;
		return _curid;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	string GetEntityName(Entity entity)
	{
		return mEntityNameMap[entity];
	}

private:
	std::queue<Entity> mAvailableEntities{};
	uint32_t mLivingEntityCount{};
	std::unordered_map<Entity, string> mEntityNameMap;
};
