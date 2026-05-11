#include "HunterFactory.hpp"
#include "HunterBehavior.hpp"
#include "Core/Model/Unit.hpp"

namespace sw::features
{
	core::Unit HunterFactory::create(const core::SpawnRequest& request) const
	{
		core::Unit unit;
		unit.id = request.unitId;
		unit.typeName = "Hunter";
		unit.creationOrder = request.creationOrder;
		unit.position = request.position;
		
		// HP initialization
		core::Health health;
		health.maximum = request.attributes.getOr("HP", 0);
		health.current = *health.maximum;
		unit.health = health;
		
		// Attributes
		unit.attributes.set("Agility", request.attributes.getOr("Agility", 0));
		unit.attributes.set("Strength", request.attributes.getOr("Strength", 0));
		unit.attributes.set("Range", request.attributes.getOr("Range", 0));
		
		// Capabilities
		unit.attributes.set("canMove", true);
		unit.attributes.set("occupiesCell", true);
		unit.attributes.set("canBeTargetedByMelee", true);
		unit.attributes.set("canBeTargetedByRanged", true);
		unit.attributes.set("moveStepsPerTurn", 1);
		
		unit.behavior = std::make_shared<HunterBehavior>();
		
		return unit;
	}
}
