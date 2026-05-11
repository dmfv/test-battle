#pragma once

#include <string_view>

#include "Core/Actions/Action.hpp"
#include "Core/Common/Types.hpp"
#include "Core/Contracts/IEventSink.hpp"
#include "Core/Contracts/IRandom.hpp"
#include "Core/Factories/SpawnRequest.hpp"
#include "Core/Factories/UnitFactoryRegistry.hpp"
#include "Core/Model/MapBounds.hpp"
#include "Core/Model/Position.hpp"
#include "Core/Model/World.hpp"
#include "Core/Systems/CombatSystem.hpp"
#include "Core/Systems/EffectResolver.hpp"
#include "Core/Systems/LifecycleSystem.hpp"
#include "Core/Systems/MovementSystem.hpp"
#include "Core/Systems/TraitEngine.hpp"
#include "Core/Systems/WorldView.hpp"

namespace sw::core
{
	class Simulation
	{
	public:
		Simulation(IRandom& random, IEventSink& eventSink);

		UnitFactoryRegistry& factories();
		const World& world() const;

		void createMap(int width, int height);
		void spawn(std::string_view typeName, SpawnRequest request);
		void assignMarch(UnitId unitId, const Position& destination);
		void advanceOneTick();
		void run();

		Tick currentTick() const;

	private:
		bool shouldStop() const;

		World world_{};
		WorldView worldView_;
		IEventSink& eventSink_;
		IRandom& random_;
		UnitFactoryRegistry factories_{};
		MovementSystem movementSystem_{};
		CombatSystem combatSystem_{};
		LifecycleSystem lifecycleSystem_{};
		TraitEngine traitEngine_{};
		EffectResolver effectResolver_;
		Tick currentTick_{1};
	};
}
