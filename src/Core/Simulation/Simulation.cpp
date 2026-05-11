#include "Simulation.hpp"
#include "Core/Systems/DefaultActionHandlers.hpp"
#include <memory>
#include <stdexcept>
#include "Core/Contracts/IUnitBehavior.hpp"

namespace sw::core
{
	Simulation::Simulation(IRandom& random, IEventSink& eventSink)
		: worldView_(world_)
		, eventSink_(eventSink)
		, random_(random)
		, effectResolver_(traitEngine_, worldView_, eventSink_, random_)
	{
		effectResolver_.subscribe(std::make_shared<MovementHandler>(movementSystem_));
		effectResolver_.subscribe(std::make_shared<MeleeAttackHandler>(combatSystem_));
		effectResolver_.subscribe(std::make_shared<RangedAttackHandler>(combatSystem_));
		effectResolver_.subscribe(std::make_shared<HealHandler>(combatSystem_));
		effectResolver_.subscribe(std::make_shared<SelfDestructHandler>(combatSystem_));
	}

	UnitFactoryRegistry& Simulation::factories()
	{
		return factories_;
	}

	const World& Simulation::world() const
	{
		return world_;
	}

	void Simulation::createMap(int width, int height)
	{
		world_.setMap(MapBounds{width, height});
		effectResolver_.dispatch(world_, events::MapCreatedEvent{width, height});
	}

	void Simulation::spawn(std::string_view typeName, SpawnRequest request)
	{
		const auto* factory = factories_.find(typeName);
		if (factory == nullptr)
		{
			throw std::runtime_error("Requested unit factory is not registered");
		}

		request.creationOrder = world_.nextCreationOrder();
		auto unit = factory->create(request);
		world_.addUnit(unit);
		effectResolver_.dispatch(world_, events::UnitSpawnedEvent{unit.id, unit.typeName, unit.position});
	}

	void Simulation::assignMarch(UnitId unitId, const Position& destination)
	{
		auto& unit = world_.requireUnit(unitId);
		unit.march = MarchState{destination, true};
		effectResolver_.dispatch(world_, events::MarchAssignedEvent{unitId, unit.position, destination});
	}

	void Simulation::advanceOneTick()
	{
		for (const auto& event : lifecycleSystem_.purgePending(world_))
		{
			effectResolver_.dispatch(world_, event);
		}

		for (const auto unitId : world_.orderedUnitIds())
		{
			auto* unit = world_.tryGetUnit(unitId);
			if (unit == nullptr || !unit->canAct())
			{
				continue;
			}

			const auto action = unit->behavior->decide(unitId, worldView_, random_);
			effectResolver_.resolve(world_, action);
		}

		++currentTick_;
	}

	void Simulation::run()
	{
		while (!shouldStop())
		{
			advanceOneTick();
		}
	}

	Tick Simulation::currentTick() const
	{
		return currentTick_;
	}

	bool Simulation::shouldStop() const
	{
		return world_.remainingUnitCount() <= 1 || world_.actionableUnitCount() == 0;
	}
}
