#include "LifecycleSystem.hpp"

namespace sw::core
{
	std::vector<events::Event> LifecycleSystem::purgePending(World& world) const
	{
		std::vector<events::Event> events;
		for (const auto unitId : world.orderedUnitIds())
		{
			auto* unit = world.tryGetUnit(unitId);
			if (unit == nullptr || unit->lifeState != LifeState::PendingRemoval)
			{
				continue;
			}

			unit->lifeState = LifeState::Removed;
			world.removeUnit(unitId);
		}

		return {};
	}
}
