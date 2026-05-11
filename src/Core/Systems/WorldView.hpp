#pragma once

#include "Core/Contracts/IWorldView.hpp"
#include "Core/Model/World.hpp"

namespace sw::core
{
	class WorldView final : public IWorldView
	{
	public:
		explicit WorldView(const World& world);

		const Unit& require(UnitId unitId) const override;
		const Unit* tryGet(UnitId unitId) const override;
		std::vector<UnitId> unitIds() const override;
		std::vector<UnitId> adjacentUnitsOf(UnitId unitId) const override;
		std::vector<UnitId> unitsInRangeOf(UnitId unitId, int minRange, int maxRange) const override;
		bool isInsideMap(const Position& position) const override;
		bool isCellBlocked(const Position& position, std::optional<UnitId> ignoreUnitId = std::nullopt) const override;

	private:
		const World& world_;
	};
}
