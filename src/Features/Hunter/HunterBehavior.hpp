#pragma once

#include "Core/Contracts/IUnitBehavior.hpp"
#include "Core/Actions/Action.hpp"

namespace sw::features
{
	class HunterBehavior : public core::IUnitBehavior
	{
	public:
		core::actions::Action decide(
			core::UnitId actorId,
			const core::IWorldView& worldView,
			core::IRandom& random) const override;
	};
}
