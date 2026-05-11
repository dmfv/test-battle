#pragma once

#include "IActionHandler.hpp"
#include "MovementSystem.hpp"
#include "CombatSystem.hpp"

namespace sw::core
{
	class MovementHandler : public IActionHandler
	{
	public:
		explicit MovementHandler(MovementSystem& system) : system_(system) {}
		std::vector<events::Event> handle(World& world, const actions::Action& action) const override
		{
			if (auto* a = std::get_if<actions::MoveAlongMarchAction>(&action))
			{
				return system_.moveAlongMarch(world, a->actorId);
			}
			return {};
		}
	private:
		MovementSystem& system_;
	};

	class MeleeAttackHandler : public IActionHandler
	{
	public:
		explicit MeleeAttackHandler(CombatSystem& system) : system_(system) {}
		std::vector<events::Event> handle(World& world, const actions::Action& action) const override
		{
			if (auto* a = std::get_if<actions::MeleeAttackAction>(&action))
			{
				return system_.meleeAttack(world, a->actorId, a->targetId, a->damage);
			}
			return {};
		}
	private:
		CombatSystem& system_;
	};

	class RangedAttackHandler : public IActionHandler
	{
	public:
		explicit RangedAttackHandler(CombatSystem& system) : system_(system) {}
		std::vector<events::Event> handle(World& world, const actions::Action& action) const override
		{
			if (auto* a = std::get_if<actions::RangedAttackAction>(&action))
			{
				return system_.rangedAttack(world, a->actorId, a->targetId, a->damage);
			}
			return {};
		}
	private:
		CombatSystem& system_;
	};

	class HealHandler : public IActionHandler
	{
	public:
		explicit HealHandler(CombatSystem& system) : system_(system) {}
		std::vector<events::Event> handle(World& world, const actions::Action& action) const override
		{
			if (auto* a = std::get_if<actions::HealAction>(&action))
			{
				return system_.heal(world, a->actorId, a->targetId, a->amount);
			}
			return {};
		}
	private:
		CombatSystem& system_;
	};

	class SelfDestructHandler : public IActionHandler
	{
	public:
		explicit SelfDestructHandler(CombatSystem& system) : system_(system) {}
		std::vector<events::Event> handle(World& world, const actions::Action& action) const override
		{
			if (auto* a = std::get_if<actions::SelfDestructAction>(&action))
			{
				return system_.selfDestruct(world, a->actorId);
			}
			return {};
		}
	private:
		CombatSystem& system_;
	};
}
