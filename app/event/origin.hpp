#ifndef APP_EVENT_ORIGIN_HPP
	#define APP_EVENT_ORIGIN_HPP

	#include <unordered_set>

	namespace bitsmithery
	{
		namespace event
		{
			template <typename... Parameters>
			class target;

			template <typename... Parameters>
			class origin
			{
				public:
					origin() = default;
					origin(origin const& that) = delete;
					origin& operator=(origin const& that) = delete;
					~origin();

					void operator()(Parameters... parameters) const;

					void attach(target<Parameters...>& target);
					void detach(target<Parameters...>& target);

				private:
					std::unordered_set<target<Parameters...>*> targets;
			};
		}
	}

	#include "origin.inl"

#endif
