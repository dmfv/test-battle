#pragma once

#include <vector>

#include "Core/Common/Types.hpp"
#include "Core/Events/Event.hpp"
#include "Core/Model/World.hpp"

namespace sw::core
{
	class CombatSystem
	{
	public:
		std::vector<events::Event> meleeAttack(World& world, UnitId attackerId, UnitId targetId, int damage) const;
		std::vector<events::Event> rangedAttack(World& world, UnitId attackerId, UnitId targetId, int damage) const;
		std::vector<events::Event> heal(World& world, UnitId sourceId, UnitId targetId, int amount) const;
		std::vector<events::Event> selfDestruct(World& world, UnitId actorId) const;

	private:
		std::vector<events::Event> attack(World& world, UnitId attackerId, UnitId targetId, int damage, bool ranged) const;
	};
}
