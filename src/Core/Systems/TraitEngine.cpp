#include "TraitEngine.hpp"

#include <iterator>

#include "Core/Contracts/IUnitTrait.hpp"

namespace sw::core
{
	std::vector<actions::Action> TraitEngine::collectReactions(
		const World& world,
		const IWorldView& worldView,
		const events::Event& event,
		IRandom& random) const
	{
		std::vector<actions::Action> reactions;

		for (const auto unitId : world.orderedUnitIds())
		{
			const auto* unit = world.tryGetUnit(unitId);
			if (unit == nullptr || unit->lifeState == LifeState::Removed)
			{
				continue;
			}

			for (const auto& trait : unit->traits)
			{
				if (!trait)
				{
					continue;
				}

				auto actions = trait->react(unitId, event, worldView, random);
				reactions.insert(reactions.end(), std::make_move_iterator(actions.begin()), std::make_move_iterator(actions.end()));
			}
		}

		return reactions;
	}
}
