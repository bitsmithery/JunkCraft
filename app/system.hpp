#ifndef BITSMITHERY_SYSTEM_HPP
	#define BITSMITHERY_SYSTEM_HPP

	#include <tuple>
	#include <memory>
	#include <unordered_map>

	#include "entity.hpp"

	namespace bitsmithery
	{
		template <typename Engine, typename... Aspects>
		class system
		{
			public:
				system(Engine& engine);
				system(system const& that) = delete;
				system& operator=(system const& that) = delete;
				~system() = default;

			private:
				Engine& engine;
				std::tuple<std::shared_ptr<std::unordered_map<entity::id, Aspects>>...> aspect_map_ptrs;
		};
	}

	#include "system.inl"

#endif
