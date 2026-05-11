#pragma once

#include <optional>

#include "Core/Common/Types.hpp"
#include "Core/Model/Attributes.hpp"
#include "Core/Model/Health.hpp"
#include "Core/Model/Position.hpp"

namespace sw::core
{
	struct SpawnRequest
	{
		UnitId unitId{};
		Position position{};
		CreationOrder creationOrder{};
		std::optional<Health> health{};
		Attributes attributes{};
	};
}
