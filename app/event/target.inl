#include "origin.hpp"

namespace app
{
	namespace event
	{
		template <typename... Parameters>
		target<Parameters...>::target(std::function<void(Parameters...)> handler)
			: handler(handler)
		{
		}

		template <typename... Parameters>
		target<Parameters...>::~target()
		{
			for (auto origin : origins)
				origin->targets.erase(this);
		}
	}
}
