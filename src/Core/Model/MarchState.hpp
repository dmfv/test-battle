#pragma once

#include "Position.hpp"

namespace sw::core
{
	struct MarchState
	{
		Position destination{};
		bool active{true};
	};
}
