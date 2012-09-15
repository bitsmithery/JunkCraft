#include "target.hpp"

namespace bitsmithery
{
	namespace event
	{
		template <typename... Parameters>
		origin<Parameters...>::~origin()
		{
			for (auto target : targets)
				target->origins.erase(this);
		}

		template <typename... Parameters>
		void origin<Parameters...>::operator()(Parameters... parameters) const
		{
			for (auto target : targets)
				if (target->handler)
					target->handler(parameters...);
		}

		template <typename... Parameters>
		void origin<Parameters...>::attach(target<Parameters...>& target)
		{
			targets.insert(&target);
			target.origins.insert(this);
		}

		template <typename... Parameters>
		void origin<Parameters...>::detach(target<Parameters...>& target)
		{
			target.origins.erase(this);
			targets.erase(&target);
		}
	}
}
