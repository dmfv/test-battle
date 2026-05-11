#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <Core/Simulation/Simulation.hpp>
#include <Core/Systems/DefaultRandom.hpp>
#include <Features/Swordsman/SwordsmanFactory.hpp>
#include <Features/Hunter/HunterFactory.hpp>

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/March.hpp>

#include <IO/Events/MapCreated.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>

#include <fstream>
#include <iostream>
#include <memory>

using namespace sw;

class io_event_sink : public core::IEventSink
{
public:
    io_event_sink(EventLog& log, const core::Simulation* sim = nullptr) : _log(log), _sim(sim) {}

    void publish(const core::events::Event& event) override
    {
        std::visit([this](auto&& e) { this->handle(e); }, event);
    }

    void setSimulation(const core::Simulation* sim) { _sim = sim; }

private:
    void handle(const core::events::MapCreatedEvent& e)
    {
        _log.log(currentTick(), io::MapCreated{static_cast<uint32_t>(e.width), static_cast<uint32_t>(e.height)});
    }

    void handle(const core::events::UnitSpawnedEvent& e)
    {
        _log.log(currentTick(), io::UnitSpawned{e.unitId, e.unitType, static_cast<uint32_t>(e.position.x), static_cast<uint32_t>(e.position.y)});
    }

    void handle(const core::events::MarchAssignedEvent& e)
    {
        _log.log(currentTick(), io::MarchStarted{
            e.unitId, 
            static_cast<uint32_t>(e.origin.x), static_cast<uint32_t>(e.origin.y),
            static_cast<uint32_t>(e.destination.x), static_cast<uint32_t>(e.destination.y)
        });
    }

    void handle(const core::events::UnitMovedEvent& e)
    {
        _log.log(currentTick(), io::UnitMoved{e.unitId, static_cast<uint32_t>(e.to.x), static_cast<uint32_t>(e.to.y)});
    }

    void handle(const core::events::DamageAppliedEvent& e)
    {
        _log.log(currentTick(), io::UnitAttacked{e.sourceId, e.targetId, static_cast<uint32_t>(e.damage), static_cast<uint32_t>(e.targetHp.value_or(0))});
    }

    void handle(const core::events::UnitMarkedForRemovalEvent& e)
    {
        _log.log(currentTick(), io::UnitDied{e.unitId});
    }
    
    void handle(const core::events::MarchCompletedEvent& e)
    {
        _log.log(currentTick(), io::MarchEnded{e.unitId, static_cast<uint32_t>(e.at.x), static_cast<uint32_t>(e.at.y)});
    }

    uint32_t currentTick() const { return _sim ? _sim->currentTick() : 0; }

    EventLog& _log;
    const core::Simulation* _sim = nullptr;
};

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <scenario_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Error: File not found - " << argv[1] << std::endl;
        return 1;
    }

    EventLog eventLog;
    core::DefaultRandom random;
    
    // IO integration
    io_event_sink eventSink(eventLog);

    // Core engine
    core::Simulation simulation(random, eventSink);
    eventSink.setSimulation(&simulation);

    // Register factories
    simulation.factories().add(std::make_shared<features::SwordsmanFactory>());
    simulation.factories().add(std::make_shared<features::HunterFactory>());

    io::CommandParser parser;
    parser.add<io::CreateMap>([&](auto cmd) {
        simulation.createMap(cmd.width, cmd.height);
    }).add<io::SpawnSwordsman>([&](auto cmd) {
        core::SpawnRequest req;
        req.unitId = cmd.unitId;
        req.position = {static_cast<int>(cmd.x), static_cast<int>(cmd.y)};
        req.attributes.set("HP", cmd.hp);
        req.attributes.set("Strength", cmd.strength);
        simulation.spawn("Swordsman", req);
    }).add<io::SpawnHunter>([&](auto cmd) {
        core::SpawnRequest req;
        req.unitId = cmd.unitId;
        req.position = {static_cast<int>(cmd.x), static_cast<int>(cmd.y)};
        req.attributes.set("HP", cmd.hp);
        req.attributes.set("Agility", cmd.agility);
        req.attributes.set("Strength", cmd.strength);
        req.attributes.set("Range", cmd.range);
        simulation.spawn("Hunter", req);
    }).add<io::March>([&](auto cmd) {
        simulation.assignMarch(cmd.unitId, {static_cast<int>(cmd.targetX), static_cast<int>(cmd.targetY)});
    });

    parser.parse(file);
    simulation.run();

    return 0;
}
