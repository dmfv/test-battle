#pragma once

#include "Core/Actions/Action.hpp"
#include "Core/Common/Types.hpp"

namespace sw::core
{
	class IRandom;
	class IWorldView;

	class IUnitBehavior
	{
	public:
		virtual ~IUnitBehavior() = default;
		virtual actions::Action decide(UnitId selfId, const IWorldView& worldView, IRandom& random) const = 0;
	};
}
