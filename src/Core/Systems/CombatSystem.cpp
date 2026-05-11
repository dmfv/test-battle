#include "CombatSystem.hpp"

#include <algorithm>

namespace sw::core
{
	std::vector<events::Event> CombatSystem::meleeAttack(World& world, UnitId attackerId, UnitId targetId, int damage) const
	{
		return attack(world, attackerId, targetId, damage, false);
	}

	std::vector<events::Event> CombatSystem::rangedAttack(World& world, UnitId attackerId, UnitId targetId, int damage) const
	{
		return attack(world, attackerId, targetId, damage, true);
	}

	std::vector<events::Event> CombatSystem::heal(World& world, UnitId sourceId, UnitId targetId, int amount) const
	{
		std::vector<events::Event> events;
		auto* target = world.tryGetUnit(targetId);
		if (target == nullptr || target->lifeState == LifeState::Removed || !target->health)
		{
			return events;
		}

		const auto oldHp = target->health->current;
		target->health->current += amount;

		if (target->health->maximum)
		{
			target->health->current = std::min(target->health->current, *target->health->maximum);
		}

		return {};
	}

	std::vector<events::Event> CombatSystem::selfDestruct(World& world, UnitId actorId) const
	{
		std::vector<events::Event> events;
		auto* actor = world.tryGetUnit(actorId);
		if (actor == nullptr || actor->lifeState != LifeState::Active)
		{
			return events;
		}

		actor->lifeState = LifeState::PendingRemoval;
		events.push_back(events::UnitMarkedForRemovalEvent{actorId});
		return events;
	}

	std::vector<events::Event> CombatSystem::attack(World& world, UnitId attackerId, UnitId targetId, int damage, bool ranged) const
	{
		std::vector<events::Event> events;

		auto* attacker = world.tryGetUnit(attackerId);
		auto* target = world.tryGetUnit(targetId);
		if (attacker == nullptr || target == nullptr || attacker->lifeState == LifeState::Removed || target->lifeState == LifeState::Removed)
		{
			return events;
		}

		if ((!ranged && !target->attributes.getOr("canBeTargetedByMelee", true)) || (ranged && !target->attributes.getOr("canBeTargetedByRanged", true)))
		{
			return events;
		}

		if (!target->health || !target->health->receivesDamage)
		{
			return events;
		}

		const auto oldHp = target->health->current;
		target->health->current -= damage;

		events.push_back(events::DamageAppliedEvent{
			attackerId,
			targetId,
			damage,
			target->health->current,
			ranged,
		});

		if (target->health->current <= 0 && target->health->removedWhenDepleted && target->lifeState == LifeState::Active)
		{
			target->lifeState = LifeState::PendingRemoval;
			events.push_back(events::UnitMarkedForRemovalEvent{targetId});
		}

		return events;
	}
}
