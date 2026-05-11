#include "HunterBehavior.hpp"
#include "Core/Contracts/IRandom.hpp"
#include "Core/Systems/WorldView.hpp"

namespace sw::features
{
	core::actions::Action HunterBehavior::decide(
		core::UnitId actorId,
		const core::IWorldView& worldView,
		core::IRandom& random) const
	{
		const auto adjacentIds = worldView.adjacentUnitsOf(actorId);

		// Если в соседних клетках есть другие юниты, стрелять нельзя
		if (adjacentIds.empty())
		{
			const auto* actor = worldView.tryGet(actorId);
			if (actor)
			{
				const int range = actor->attributes.getOr("Range", 0);
				const auto targets = worldView.unitsInRangeOf(actorId, 2, range);
				if (!targets.empty())
				{
					const auto targetIdx = random.pickIndex(targets.size());
					const auto targetId = targets[targetIdx];
					const int damage = actor->attributes.getOr("Agility", 0);
					return core::actions::RangedAttackAction{actorId, targetId, damage};
				}
			}
		}
		else
		{
			// Удар из тени (ближний бой)
			const auto targetIdx = random.pickIndex(adjacentIds.size());
			const auto targetId = adjacentIds[targetIdx];
			
			const auto* actor = worldView.tryGet(actorId);
			const int damage = actor ? actor->attributes.getOr("Strength", 0) : 0;
			
			return core::actions::MeleeAttackAction{actorId, targetId, damage};
		}

		return core::actions::MoveAlongMarchAction{actorId};
	}
}
