#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "Core/Common/Types.hpp"
#include "MapBounds.hpp"
#include "Unit.hpp"

namespace sw::core
{
	class World
	{
	public:
		void setMap(MapBounds bounds);
		bool hasMap() const;
		const MapBounds& map() const;

		void addUnit(Unit unit);
		bool containsUnit(UnitId unitId) const;
		Unit* tryGetUnit(UnitId unitId);
		const Unit* tryGetUnit(UnitId unitId) const;
		Unit& requireUnit(UnitId unitId);
		const Unit& requireUnit(UnitId unitId) const;
		void removeUnit(UnitId unitId);

		std::vector<UnitId> orderedUnitIds() const;
		bool isCellBlocked(const Position& position, std::optional<UnitId> ignoreUnitId = std::nullopt) const;
		std::size_t remainingUnitCount() const;
		std::size_t actionableUnitCount() const;
		CreationOrder nextCreationOrder() const;

	private:
		std::optional<MapBounds> mapBounds_{};
		std::unordered_map<UnitId, Unit> units_{};
		std::vector<UnitId> orderedUnitIds_{};
	};
}
