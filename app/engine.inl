#include <algorithm>
#include <functional>
#include <utility>

#include "util/tuple_find.hpp"

namespace bitsmithery
{
	namespace detail
	{
		template <template <typename Engine> class System, template <typename Engine> class... Systems>
		inline engine<Systems...>& engine_systems_arg(engine<Systems...>& engine)
		{
			return engine;
		}
	}

	template <template <typename Engine> class... Systems>
	engine<Systems...>::engine()
		: systems(detail::engine_systems_arg<Systems>(*this)...)
	{
	}

	template <template <typename Engine> class... Systems>
	template <template <typename Engine> class System>
	System<engine<Systems...>>& engine<Systems...>::system()
	{
		return std::get<util::tuple_find<std::tuple<Systems<engine>...>, System<engine>>::value>(systems);
	}
	template <template <typename Engine> class... Systems>
	template <template <typename Engine> class System>
	System<engine<Systems...>> const& engine<Systems...>::system() const
	{
		return std::get<util::tuple_find<std::tuple<Systems<engine>...>, System<engine>>::value>(systems);
	}




//	namespace detail
//	{
//		std::uint32_t random(std::uint32_t seed)
//		{
//			return seed*312937 + 54769273;
//		}
//	}


//	template <template <typename Engine> class... Systems>
//	entity::id engine<Systems...>::entity_create()
//	{
//		entity::id entity_id;
//		if (entity_id_buffer.empty()) {
//			entity_id = entity_id_next++;
//		} else {
//			entity_id = entity_id_buffer.front();
//			std::pop_heap(entity_id_buffer.begin(), entity_id_buffer.end(), std::greater());
//			entity_id_buffer.pop_back();
//		}
//		entity_ids.insert(entity_id);
//		return entity_id;
//	}
//
//	template <template <typename Engine> class... Systems>
//	bool engine<Systems...>::entity_exists(entity::id entity_id)
//	{
//		return entity_ids.find(entity_id) != entity_ids.end();
//	}
//
//	template <template <typename Engine> class... Systems>
//	void engine<Systems...>::entity_delete(entity::id entity_id)
//	{
//		entity_ids.erase(entity_id);
//		if
//	}
//

	template <template <typename Engine> class... Systems>
	template <typename Aspect, typename... AspectConstructorArguments>
	Aspect& engine<Systems...>::aspect_attach(entity::id entity_id, AspectConstructorArguments&&... aspect_constructor_arguments)
	{
		auto& aspect_map = std::get<util::tuple_find<typename detail::engine_aspect_maps<Systems<engine>...>::type, typename detail::engine_aspect_map<Aspect>::type>::value>(aspect_maps);
		aspect_map.emplace({entity_id, Aspect(std::forward<AspectConstructorArguments>(aspect_constructor_arguments)...)});
	}

	template <typename Aspect>
	bool aspect_exists(entity::id entity_id);

	template <template <typename Engine> class... Systems>
	template <typename Aspect>
	Aspect& engine<Systems...>::aspect(entity::id entity_id)
	{
		return std::get<util::tuple_find<typename detail::engine_aspect_maps<Systems<engine>...>::type, typename detail::engine_aspect_map<Aspect>::type>::value>(aspect_maps)[entity_id];
	}

	template <typename Aspect>
	void aspect_remove(entity::id entity_id)
	{

	}
}
