#pragma once

#include "Types.hpp"
#include <array>
#include <cassert>
#include <unordered_map>
#include <iostream>

class IComponentVector
{
public:
	virtual ~IComponentVector() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentVector : public IComponentVector
{
public:
	void InsertData(Entity entity, T *component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end
		size_t newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentVector.push_back(component);
		++mSize;
	}

	void RemoveData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1;
		mComponentVector[indexOfRemovedEntity] = mComponentVector[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		--mSize;
	}

	T * GetData(Entity entity)
	{
		if (mEntityToIndexMap.find(entity) == mEntityToIndexMap.end())
		{
			return nullptr;
		}
		return mComponentVector[mEntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::vector<T*> mComponentVector{};
	std::unordered_map<Entity, size_t> mEntityToIndexMap{};
	std::unordered_map<size_t, Entity> mIndexToEntityMap{};
	size_t mSize{};
};
