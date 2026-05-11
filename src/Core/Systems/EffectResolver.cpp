#include "EffectResolver.hpp"
#include "IActionHandler.hpp"
#include "TraitEngine.hpp"

#include <deque>

namespace sw::core
{
	EffectResolver::EffectResolver(
		TraitEngine& traitEngine,
		const IWorldView& worldView,
		IEventSink& eventSink,
		IRandom& random)
		: traitEngine_(traitEngine)
		, worldView_(worldView)
		, eventSink_(eventSink)
		, random_(random)
	{
	}

	void EffectResolver::resolve(World& world, const actions::Action& action)
	{
		std::deque<actions::Action> queue;
		queue.push_back(action);

		while (!queue.empty())
		{
			const auto current = queue.front();
			queue.pop_front();

			std::vector<events::Event> producedEvents;
			
			// Рассылка действия подписчикам (Observer pattern)
			for (auto& handler : subscribers_)
			{
				auto result = handler->handle(world, current);
				producedEvents.insert(producedEvents.end(), result.begin(), result.end());
			}

			for (const auto& event : producedEvents)
			{
				dispatch(world, event);
			}
		}
	}

	void EffectResolver::dispatch(World& world, const events::Event& event)
	{
		emit(world, event);
	}

	void EffectResolver::emit(World& world, const events::Event& event)
	{
		eventSink_.publish(event);

		// Реакции (трейты)
		auto reactions = traitEngine_.collectReactions(world, worldView_, event, random_);
		for (auto& reaction : reactions)
		{
			resolve(world, reaction);
		}
	}

	void EffectResolver::resolveSingle(World&, const actions::Action&)
	{
	}
}
