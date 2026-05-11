#include "SwordsmanBehavior.hpp"
#include "Core/Contracts/IRandom.hpp"

#include "Core/Systems/WorldView.hpp"

namespace sw::features
{
	core::actions::Action SwordsmanBehavior::decide(
		core::UnitId actorId,
		const core::IWorldView& worldView,
		core::IRandom& random) const
	{
		auto adjacentIds = worldView.adjacentUnitsOf(actorId);
		if (!adjacentIds.empty())
		{
			const auto targetIdx = random.pickIndex(adjacentIds.size());
			const auto targetId = adjacentIds[targetIdx];
			
			const auto* actor = worldView.tryGet(actorId);
			const int damage = actor ? actor->attributes.getOr("Strength", 0) : 0;
			
			return core::actions::MeleeAttackAction{actorId, targetId, damage};
		}

		return core::actions::MoveAlongMarchAction{actorId};
	}
}
