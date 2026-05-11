#pragma once

#include "Core/Events/Event.hpp"

namespace sw::core
{
	class IEventSink
	{
	public:
		virtual ~IEventSink() = default;
		virtual void publish(const events::Event& event) = 0;
	};
}
