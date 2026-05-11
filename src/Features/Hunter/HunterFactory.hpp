#pragma once

#include "Core/Factories/IUnitFactory.hpp"
#include <memory>

namespace sw::features
{
	class HunterFactory : public core::IUnitFactory
	{
	public:
		core::Unit create(const core::SpawnRequest& request) const override;
		std::string_view typeName() const override { return "Hunter"; }
	};
}
