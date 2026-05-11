#pragma once

#include "Position.hpp"

namespace sw::core
{
	struct MapBounds
	{
		int width{};
		int height{};

		bool contains(const Position& position) const
		{
			return position.x >= 0 && position.y >= 0 && position.x < width && position.y < height;
		}
	};
}
