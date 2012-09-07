#ifndef APP_EVENT_TARGET_HPP
	#define APP_EVENT_TARGET_HPP

	#include <functional>
	#include <unordered_set>

	namespace app
	{
		namespace event
		{
			template <typename... Parameters>
			class origin;

			template <typename... Parameters>
			class target
			{
				public:
					std::function<void(Parameters...)> handler;

					target() = default;
					explicit target(std::function<void(Parameters...)> handler);
					target(target const& that) = delete;
					target& operator=(target const& that) = delete;
					~target();

				private:
					std::unordered_set<origin<Parameters...>*> origins;
			};
		}
	}

	#include "target.inl"

#endif
