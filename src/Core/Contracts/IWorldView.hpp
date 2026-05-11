#pragma once

#include <optional>
#include <vector>

#include "Core/Common/Types.hpp"
#include "Core/Model/Position.hpp"

namespace sw::core
{
	struct Unit;

	class IWorldView
	{
	public:
		virtual ~IWorldView() = default;

		virtual const Unit& require(UnitId unitId) const = 0;
		virtual const Unit* tryGet(UnitId unitId) const = 0;
		virtual std::vector<UnitId> unitIds() const = 0;
		virtual std::vector<UnitId> adjacentUnitsOf(UnitId unitId) const = 0;
		virtual std::vector<UnitId> unitsInRangeOf(UnitId unitId, int minRange, int maxRange) const = 0;
		virtual bool isInsideMap(const Position& position) const = 0;
		virtual bool isCellBlocked(const Position& position, std::optional<UnitId> ignoreUnitId = std::nullopt) const = 0;
	};
}
