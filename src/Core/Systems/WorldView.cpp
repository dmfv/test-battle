#include "WorldView.hpp"

#include "Core/Model/Position.hpp"

namespace sw::core
{
	WorldView::WorldView(const World& world)
		: world_(world)
	{
	}

	const Unit& WorldView::require(UnitId unitId) const
	{
		return world_.requireUnit(unitId);
	}

	const Unit* WorldView::tryGet(UnitId unitId) const
	{
		return world_.tryGetUnit(unitId);
	}

	std::vector<UnitId> WorldView::unitIds() const
	{
		return world_.orderedUnitIds();
	}

	std::vector<UnitId> WorldView::adjacentUnitsOf(UnitId unitId) const
	{
		std::vector<UnitId> result;
		const auto& source = world_.requireUnit(unitId);

		for (const auto otherId : world_.orderedUnitIds())
		{
			if (otherId == unitId)
			{
				continue;
			}

			const auto* other = world_.tryGetUnit(otherId);
			if (other == nullptr || other->lifeState == LifeState::Removed)
			{
				continue;
			}

			if (chebyshevDistance(source.position, other->position) == 1)
			{
				result.push_back(otherId);
			}
		}

		return result;
	}

	std::vector<UnitId> WorldView::unitsInRangeOf(UnitId unitId, int minRange, int maxRange) const
	{
		std::vector<UnitId> result;
		const auto& source = world_.requireUnit(unitId);

		for (const auto otherId : world_.orderedUnitIds())
		{
			if (otherId == unitId)
			{
				continue;
			}

			const auto* other = world_.tryGetUnit(otherId);
			if (other == nullptr || other->lifeState == LifeState::Removed)
			{
				continue;
			}

			const auto distance = chebyshevDistance(source.position, other->position);
			if (distance >= minRange && distance <= maxRange)
			{
				result.push_back(otherId);
			}
		}

		return result;
	}

	bool WorldView::isInsideMap(const Position& position) const
	{
		return world_.hasMap() && world_.map().contains(position);
	}

	bool WorldView::isCellBlocked(const Position& position, std::optional<UnitId> ignoreUnitId) const
	{
		return world_.isCellBlocked(position, ignoreUnitId);
	}
}
