#include "MovementSystem.hpp"

#include "Core/Model/Position.hpp"

namespace sw::core
{
	std::vector<events::Event> MovementSystem::moveAlongMarch(World& world, UnitId unitId) const
	{
		std::vector<events::Event> events;

		auto* unit = world.tryGetUnit(unitId);
		if (unit == nullptr || unit->lifeState == LifeState::Removed || !unit->attributes.getOr("canMove", true) || !unit->march || !unit->march->active)
		{
			return events;
		}

		const auto steps = std::max(0, unit->attributes.getOr("moveStepsPerTurn", 1));
		for (int step = 0; step < steps; ++step)
		{
			if (!unit->march || !unit->march->active || unit->position == unit->march->destination)
			{
				break;
			}

			const auto nextPosition = stepToward(unit->position, unit->march->destination);
			if (!world.map().contains(nextPosition) || world.isCellBlocked(nextPosition, unit->id))
			{
				break;
			}

			const auto previous = unit->position;
			unit->position = nextPosition;
			events.push_back(events::UnitMovedEvent{unit->id, previous, unit->position});
		}

		if (unit->march && unit->position == unit->march->destination)
		{
			unit->march->active = false;
			events.push_back(events::MarchCompletedEvent{unit->id, unit->position});
		}

		return events;
	}
}
