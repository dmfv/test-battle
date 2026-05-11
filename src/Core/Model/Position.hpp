#pragma once

#include <algorithm>
#include <cstdlib>

namespace sw::core
{
	struct Position
	{
		int x{};
		int y{};
	};

	inline bool operator==(const Position& lhs, const Position& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	inline bool operator!=(const Position& lhs, const Position& rhs)
	{
		return !(lhs == rhs);
	}

	inline int chebyshevDistance(const Position& lhs, const Position& rhs)
	{
		return std::max(std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y));
	}

	inline Position stepToward(const Position& from, const Position& to)
	{
		const auto stepAxis = [](int value) {
			if (value > 0)
			{
				return 1;
			}
			if (value < 0)
			{
				return -1;
			}
			return 0;
		};

		return Position{
			from.x + stepAxis(to.x - from.x),
			from.y + stepAxis(to.y - from.y),
		};
	}
}
