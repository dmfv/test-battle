#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include "IUnitFactory.hpp"

namespace sw::core
{
	class UnitFactoryRegistry
	{
	public:
		void add(std::shared_ptr<const IUnitFactory> factory);
		const IUnitFactory* find(std::string_view typeName) const;

	private:
		std::unordered_map<std::string, std::shared_ptr<const IUnitFactory>> factories_{};
	};
}
