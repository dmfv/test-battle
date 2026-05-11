#pragma once

#include <vector>
#include "Core/Actions/Action.hpp"
#include "Core/Events/Event.hpp"

namespace sw::core
{
	class World;

	class IActionHandler
	{
	public:
		virtual ~IActionHandler() = default;
		virtual std::vector<events::Event> handle(World& world, const actions::Action& action) const = 0;
	};
}
