#pragma once

#include <random>

#include "Core/Contracts/IRandom.hpp"

namespace sw::core
{
	class DefaultRandom final : public IRandom
	{
	public:
		explicit DefaultRandom(std::uint32_t seed = std::random_device{}());

		std::size_t pickIndex(std::size_t exclusiveUpperBound) override;

	private:
		std::mt19937 engine_;
	};
}
