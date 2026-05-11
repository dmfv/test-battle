#pragma once

#include <vector>

#include "Core/Common/Types.hpp"
#include "Core/Events/Event.hpp"
#include "Core/Model/World.hpp"

namespace sw::core
{
	class MovementSystem
	{
	public:
		std::vector<events::Event> moveAlongMarch(World& world, UnitId unitId) const;
	};
}
