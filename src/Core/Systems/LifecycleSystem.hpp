#pragma once

#include <vector>

#include "Core/Events/Event.hpp"
#include "Core/Model/World.hpp"

namespace sw::core
{
	class LifecycleSystem
	{
	public:
		std::vector<events::Event> purgePending(World& world) const;
	};
}
