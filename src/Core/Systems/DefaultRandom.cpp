#include "DefaultRandom.hpp"

#include <stdexcept>

namespace sw::core
{
	DefaultRandom::DefaultRandom(std::uint32_t seed)
		: engine_(seed)
	{
	}

	std::size_t DefaultRandom::pickIndex(std::size_t exclusiveUpperBound)
	{
		if (exclusiveUpperBound == 0)
		{
			throw std::runtime_error("Cannot pick random index from empty range");
		}

		std::uniform_int_distribution<std::size_t> distribution(0, exclusiveUpperBound - 1);
		return distribution(engine_);
	}
}
