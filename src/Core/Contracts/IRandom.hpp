#pragma once

#include <cstddef>

namespace sw::core
{
	class IRandom
	{
	public:
		virtual ~IRandom() = default;
		virtual std::size_t pickIndex(std::size_t exclusiveUpperBound) = 0;
	};
}
