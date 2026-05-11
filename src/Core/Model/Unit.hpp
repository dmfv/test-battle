#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Attributes.hpp"
#include "Core/Common/Types.hpp"
#include "Health.hpp"
#include "MarchState.hpp"

namespace sw::core
{
	class IUnitBehavior;
	class IUnitTrait;

	enum class LifeState
	{
		Active,
		PendingRemoval,
		Removed,
	};

	struct Unit
	{
		UnitId id{};
		std::string typeName{};
		CreationOrder creationOrder{};
		Position position{};
		std::optional<Health> health{};
		Attributes attributes{};
		std::optional<MarchState> march{};
		LifeState lifeState{LifeState::Active};
		std::shared_ptr<const IUnitBehavior> behavior{};
		std::vector<std::shared_ptr<const IUnitTrait>> traits{};

		bool canAct() const
		{
			return behavior != nullptr && lifeState == LifeState::Active;
		}
	};
}
