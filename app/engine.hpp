#ifndef BITSMITHERY_ENGINE_HPP
	#define BITSMITHERY_ENGINE_HPP

	#include <unordered_set>
	#include <unordered_map>
	#include <cstdint>
	#include <memory>
	#include <tuple>

	#include "entity.hpp"
	#include "system.hpp"

	namespace bitsmithery
	{
		namespace detail
		{
			class engine_base
			{
				public:
					engine_base() = default;
					engine_base(engine_base const&) = delete;
					engine_base& operator=(engine_base const&) = delete;
					~engine_base() = default;

				protected:
					std::unordered_map<std::uintptr_t, std::shared_ptr<void>> aspect_map_ptrs;
					entity::id entity_id_seed = reinterpret_cast<entity::id>(this);
					std::unordered_set<entity::id> entity_ids = {};
			};
		}

		template <template <typename Engine> class... Systems>
		class engine
			: private detail::engine_base
			, private Systems<engine<Systems...>>...
		{
			template <typename Aspect, typename Engine>
			friend std::shared_ptr<std::unordered_map<entity::id, Aspect>> detail::system_get_aspect_map_ptr(Engine& engine);
			public:
				engine();
				engine(engine const&) = delete;
				engine& operator=(engine const&) = delete;
				~engine() = default;

				template <template <typename Engine> class System>
				System<engine<Systems...>>& system();
				template <template <typename Engine> class System>
				System<engine<Systems...>> const& system() const;



//				entity::id entity_create();
//				bool entity_exists(entity::id entity_id);
//				void entity_delete(entity::id entity_id);

//				template <typename Aspect, typename... AspectConstructorArguments>
//				void aspect_attach(entity::id entity_id, AspectConstructorArguments&&... aspect_constructor_arguments);
//				template <typename Aspect>
//				Aspect* aspect_search(entity::id entity_id);
//				template <typename Aspect>
//				void aspect_remove(entity::id entity_id);

			private:
				template <typename Aspect>
				std::shared_ptr<std::unordered_map<entity::id, Aspect>> aspect_map_ptr();
		};
	}

	#include "engine.inl"

#endif
