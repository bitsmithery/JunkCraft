#ifndef BITSMITHERY_ENGINE_HPP
	#define BITSMITHERY_ENGINE_HPP

	#include <unordered_set>
	#include <unordered_map>
	#include <queue>
	#include <cstddef>
	#include <tuple>

	#include "util/tuple_wrap.hpp"
	#include "util/tuple_join.hpp"
	#include "util/tuple_uniquize.hpp"

	#include "entity.hpp"
	#include "system.hpp"

	namespace bitsmithery
	{
		namespace detail
		{
			template <typename Aspect>
			struct engine_aspect_map
			{
				typedef std::unordered_map<entity::id, Aspect> type;
			};

			template <typename... Systems>
			struct engine_aspect_maps
			{
				typedef typename util::tuple_wrap<typename util::tuple_uniquize<typename util::tuple_join<typename Systems::aspects...>::type>::type, engine_aspect_map>::type type;
			};
		}

		template <template <typename Engine> class... Systems>
		class engine
		{
			public:
				engine();
				engine(engine const&) = delete;
				engine& operator=(engine const&) = delete;
				~engine() = default;

				template <template <typename Engine> class System>
				System<engine>& system();
				template <template <typename Engine> class System>
				System<engine> const& system() const;



//				entity::id entity_create();
//				bool entity_exists(entity::id entity_id);
//				void entity_delete(entity::id entity_id);

				template <typename Aspect, typename... AspectConstructorArguments>
				Aspect& aspect_attach(entity::id entity_id, AspectConstructorArguments&&... aspect_constructor_arguments);
				template <typename Aspect>
				bool aspect_exists(entity::id entity_id);
				template <typename Aspect>
				Aspect& aspect(entity::id entity_id);
				template <typename Aspect>
				void aspect_remove(entity::id entity_id);

			private:
				typename detail::engine_aspect_maps<Systems<engine>...>::type aspect_maps;
				entity::id entity_id_next = 0;
				std::vector<entity::id> entity_id_buffer = {};
				std::unordered_set<entity::id> entity_ids = {};
				std::tuple<Systems<engine>...> systems;


		};
	}

	#include "engine.inl"

#endif
