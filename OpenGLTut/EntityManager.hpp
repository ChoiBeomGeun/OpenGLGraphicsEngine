#pragma once

#include "Types.h"
#include <array>
#include <cassert>
#include <queue>


class EntityManager
{
	std::uint32_t _curid;
public:
	EntityManager()
	{
		_curid = 0;
	}

	Entity CreateEntity()
	{
		_curid++;
		return _curid;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}



private:
	std::queue<Entity> mAvailableEntities{};
	uint32_t mLivingEntityCount{};
};
