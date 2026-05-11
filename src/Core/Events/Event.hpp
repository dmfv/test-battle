#pragma once

#include <optional>
#include <string>
#include <variant>

#include "Core/Common/Types.hpp"
#include "Core/Model/Position.hpp"

namespace sw::core::events
{
	struct MapCreatedEvent
	{
		int width{};
		int height{};
	};

	struct UnitSpawnedEvent
	{
		UnitId unitId{};
		std::string unitType{};
		Position position{};
	};

	struct MarchAssignedEvent
	{
		UnitId unitId{};
		Position origin{};
		Position destination{};
	};

	struct UnitMovedEvent
	{
		UnitId unitId{};
		Position from{};
		Position to{};
	};

	struct MarchCompletedEvent
	{
		UnitId unitId{};
		Position at{};
	};

	struct DamageAppliedEvent
	{
		UnitId sourceId{};
		UnitId targetId{};
		int damage{};
		std::optional<int> targetHp{};
		bool ranged{};
	};

	struct UnitMarkedForRemovalEvent
	{
		UnitId unitId{};
	};

	using Event = std::variant<
		MapCreatedEvent,
		UnitSpawnedEvent,
		MarchAssignedEvent,
		UnitMovedEvent,
		MarchCompletedEvent,
		DamageAppliedEvent,
		UnitMarkedForRemovalEvent>;
}
