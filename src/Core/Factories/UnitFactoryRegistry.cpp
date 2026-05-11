#include "UnitFactoryRegistry.hpp"

#include <stdexcept>

namespace sw::core
{
	void UnitFactoryRegistry::add(std::shared_ptr<const IUnitFactory> factory)
	{
		if (!factory)
		{
			throw std::runtime_error("Factory must not be null");
		}

		factories_[std::string(factory->typeName())] = std::move(factory);
	}

	const IUnitFactory* UnitFactoryRegistry::find(std::string_view typeName) const
	{
		const auto iterator = factories_.find(std::string(typeName));
		return iterator == factories_.end() ? nullptr : iterator->second.get();
	}
}
