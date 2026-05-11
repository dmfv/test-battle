#pragma once

#include <vector>

#include "Core/Actions/Action.hpp"
#include "Core/Contracts/IRandom.hpp"
#include "Core/Contracts/IWorldView.hpp"
#include "Core/Events/Event.hpp"
#include "Core/Model/World.hpp"

namespace sw::core
{
	class TraitEngine
	{
	public:
		std::vector<actions::Action> collectReactions(
			const World& world,
			const IWorldView& worldView,
			const events::Event& event,
			IRandom& random) const;
	};
}
