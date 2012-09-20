#ifndef BITSMITHERY_SYSTEM_HPP
	#define BITSMITHERY_SYSTEM_HPP

	#include <tuple>
	#include <unordered_map>

	namespace bitsmithery
	{
		template <typename Engine>
		class system
		{
			public:
				typedef std::tuple<> aspects;

				system(Engine& engine);
				system(system const& that) = delete;
				system& operator=(system const& that) = delete;
				~system() = default;

			private:
				Engine& engine;
		};
	}

	#include "system.inl"

#endif
