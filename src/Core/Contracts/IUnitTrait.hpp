#pragma once

#include <vector>

#include "Core/Actions/Action.hpp"
#include "Core/Common/Types.hpp"
#include "Core/Events/Event.hpp"

namespace sw::core
{
	class IRandom;
	class IWorldView;

	class IUnitTrait
	{
	public:
		virtual ~IUnitTrait() = default;
		virtual std::vector<actions::Action> react(
			UnitId selfId,
			const events::Event& event,
			const IWorldView& worldView,
			IRandom& random) const = 0;
	};
}
