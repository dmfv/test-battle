#pragma once

#include <string_view>

#include "Core/Model/Unit.hpp"
#include "SpawnRequest.hpp"

namespace sw::core
{
	class IUnitFactory
	{
	public:
		virtual ~IUnitFactory() = default;
		virtual std::string_view typeName() const = 0;
		virtual Unit create(const SpawnRequest& request) const = 0;
	};
}
