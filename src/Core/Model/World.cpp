#include "World.hpp"

#include <stdexcept>

namespace sw::core
{
	void World::setMap(MapBounds bounds)
	{
		mapBounds_ = bounds;
	}

	bool World::hasMap() const
	{
		return mapBounds_.has_value();
	}

	const MapBounds& World::map() const
	{
		if (!mapBounds_)
		{
			throw std::runtime_error("World map is not initialized");
		}

		return *mapBounds_;
	}

	void World::addUnit(Unit unit)
	{
		if (units_.find(unit.id) != units_.end())
		{
			throw std::runtime_error("Unit with the same id already exists");
		}

		orderedUnitIds_.push_back(unit.id);
		units_.emplace(unit.id, std::move(unit));
	}

	bool World::containsUnit(UnitId unitId) const
	{
		return units_.find(unitId) != units_.end();
	}

	Unit* World::tryGetUnit(UnitId unitId)
	{
		const auto iterator = units_.find(unitId);
		return iterator == units_.end() ? nullptr : &iterator->second;
	}

	const Unit* World::tryGetUnit(UnitId unitId) const
	{
		const auto iterator = units_.find(unitId);
		return iterator == units_.end() ? nullptr : &iterator->second;
	}

	Unit& World::requireUnit(UnitId unitId)
	{
		auto* unit = tryGetUnit(unitId);
		if (unit == nullptr)
		{
			throw std::runtime_error("Requested unit does not exist");
		}

		return *unit;
	}

	const Unit& World::requireUnit(UnitId unitId) const
	{
		auto* unit = tryGetUnit(unitId);
		if (unit == nullptr)
		{
			throw std::runtime_error("Requested unit does not exist");
		}

		return *unit;
	}

	void World::removeUnit(UnitId unitId)
	{
		units_.erase(unitId);
	}

	std::vector<UnitId> World::orderedUnitIds() const
	{
		return orderedUnitIds_;
	}

	bool World::isCellBlocked(const Position& position, std::optional<UnitId> ignoreUnitId) const
	{
		for (const auto& [unitId, unit] : units_)
		{
			if (ignoreUnitId && *ignoreUnitId == unitId)
			{
				continue;
			}

			if (unit.lifeState == LifeState::Removed)
			{
				continue;
			}

			if (unit.attributes.getOr("occupiesCell", 1) && unit.position == position)
			{
				return true;
			}
		}

		return false;
	}

	std::size_t World::remainingUnitCount() const
	{
		return units_.size();
	}

	std::size_t World::actionableUnitCount() const
	{
		std::size_t count = 0;
		for (const auto& [_, unit] : units_)
		{
			if (unit.canAct())
			{
				++count;
			}
		}
		return count;
	}

	CreationOrder World::nextCreationOrder() const
	{
		return static_cast<CreationOrder>(orderedUnitIds_.size()) + 1;
	}
}
