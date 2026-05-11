#include "SwordsmanFactory.hpp"
#include "SwordsmanBehavior.hpp"
#include "Core/Model/Unit.hpp"

namespace sw::features
{
	core::Unit SwordsmanFactory::create(const core::SpawnRequest& request) const
	{
		core::Unit unit;
		unit.id = request.unitId;
		unit.typeName = "Swordsman";
		unit.creationOrder = request.creationOrder;
		unit.position = request.position;
		
		// HP initialization
		core::Health health;
		health.maximum = request.attributes.getOr("HP", 0);
		health.current = *health.maximum;
		unit.health = health;
		
		// Attributes
		unit.attributes.set("Strength", request.attributes.getOr("Strength", 0));
		
		// Capabilities (using the newly refactored attribute-based approach)
		unit.attributes.set("canMove", true);
		unit.attributes.set("occupiesCell", true);
		unit.attributes.set("canBeTargetedByMelee", true);
		unit.attributes.set("canBeTargetedByRanged", true);
		unit.attributes.set("moveStepsPerTurn", 1);
		
		unit.behavior = std::make_shared<SwordsmanBehavior>();
		
		return unit;
	}
}
