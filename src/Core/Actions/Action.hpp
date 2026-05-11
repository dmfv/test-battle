#pragma once

#include <variant>

#include "Core/Common/Types.hpp"

namespace sw::core::actions
{
	struct NoAction
	{
		UnitId actorId{};
	};

	struct MoveAlongMarchAction
	{
		UnitId actorId{};
	};

	struct MeleeAttackAction
	{
		UnitId actorId{};
		UnitId targetId{};
		int damage{};
	};

	struct RangedAttackAction
	{
		UnitId actorId{};
		UnitId targetId{};
		int damage{};
	};

	struct HealAction
	{
		UnitId actorId{};
		UnitId targetId{};
		int amount{};
	};

	struct SelfDestructAction
	{
		UnitId actorId{};
	};

	using Action = std::variant<
		NoAction,
		MoveAlongMarchAction,
		MeleeAttackAction,
		RangedAttackAction,
		HealAction,
		SelfDestructAction>;
}
