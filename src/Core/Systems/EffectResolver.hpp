#pragma once

#include "Core/Actions/Action.hpp"
#include "Core/Contracts/IEventSink.hpp"
#include "Core/Contracts/IRandom.hpp"
#include "Core/Contracts/IWorldView.hpp"
#include "Core/Model/World.hpp"
#include <vector>
#include <memory>

namespace sw::core
{
	class IActionHandler;
	class CombatSystem;
	class LifecycleSystem;
	class MovementSystem;
	class TraitEngine;

	class EffectResolver
	{
	public:
		EffectResolver(
			TraitEngine& traitEngine,
			const IWorldView& worldView,
			IEventSink& eventSink,
			IRandom& random);

		void resolve(World& world, const actions::Action& action);
		void dispatch(World& world, const events::Event& event);

		// Подписка на шину обработки действий
		void subscribe(std::shared_ptr<IActionHandler> handler)
		{
			subscribers_.push_back(std::move(handler));
		}

	private:
		void resolveSingle(World& world, const actions::Action& action);
		void emit(World& world, const events::Event& event);

		TraitEngine& traitEngine_;
		const IWorldView& worldView_;
		IEventSink& eventSink_;
		IRandom& random_;

		std::vector<std::shared_ptr<IActionHandler>> subscribers_;
	};
}
