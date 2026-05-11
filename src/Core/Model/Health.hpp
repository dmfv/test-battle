#pragma once

#include <optional>

namespace sw::core
{
	struct Health
	{
		int current{};
		std::optional<int> maximum{};
		bool receivesDamage{true};
		bool removedWhenDepleted{true};
	};
}
